#include <DxLib.h>
#include "../Application.h"
#include "../Utility/AsoUtility.h"
#include "../Manager/SceneManager.h"
#include "../Manager/ResourceManager.h"
#include "../Manager/InputManager.h"
#include "../Object/Player/Player.h"
#include "../Object/Block/Block.h"
#include "../Object/Time/Timer.h"
#include "EasyGameScene.h"

EasyGameScene::EasyGameScene(void)
{
	InitBlock();
}

EasyGameScene::~EasyGameScene(void)
{
	for (auto block : blocks) {
		delete block;
	}
	blocks.clear();
	delete goalBlock;
}

void EasyGameScene::Init(void)
{
	//�T�E���h�ǂݍ���
	bgmHandle_ = LoadSoundMem("Data/Sound/Bgm/maou_bgm_cyber40.mp3");

	//���ʒ���
	ChangeVolumeSoundMem(255 * 30 / 100, bgmHandle_);

	auto& res = ResourceManager::GetInstance();
	img_ = res.Load(ResourceManager::SRC::SELECT).handleId_;
	if (img_ == -1)
	{
		return;
	}

	//BGM�X�^�[�g
	PlaySoundMem(bgmHandle_, DX_PLAYTYPE_LOOP);

	player_ = new Player;
	player_->Init();	
	
	timer_ = new Timer;
	timer_->Init();

	//SE������
	InitSoundEffect();

	preHighlightBlock = nullptr;
	highlightBlock = nullptr;
}

void EasyGameScene::Update(void)
{
	InputManager& ins = InputManager::GetInstance();

	player_->Updeta();
	timer_->Update();

	HighlightUpdate();

	PlaySoundEffect();

	for (auto block : blocks) {
		block->Update();
		//CheckConnections(block);
	}

	//�X�y�[�X�L�[�����ŉE��]
	if (highlightBlock && ins.IsTrgDown(KEY_INPUT_SPACE))
	{
		highlightBlock->RightRotate();
	}	

	//�N���b�N�ŉ�]
	BlockProcess(ins.GetMousePos());

	ClearElectricity();
	startBlock->SetElectricity(true);
	UpdateElectricity(startBlock); // �X�^�[�g�n�_����ēx�d�C�̗�����X�V

	// �V�[���J��
	if (IsConnectedToGoal())
	{

		//BGM��~
		StopSoundMem(bgmHandle_);

		//SceneManager::GetInstance().ChangeScene(SceneManager::SCENE_ID::TITLE);
		SceneManager::GetInstance().ChangeScene(SceneManager::SCENE_ID::GAMECLEAR);
	}
	if (timer_->GetTime() <= 0)
	{
		SceneManager::GetInstance().ChangeScene(SceneManager::SCENE_ID::GAMECLEAR);
	}
}

void EasyGameScene::Draw(void)
{

	DrawString(0, 0, "game", 0xFFFFFF);

	//�w�i
	DrawRotaGraph(Application::SCREEN_SIZE_X / 2,
		Application::SCREEN_SIZE_Y / 2,
		1.0f, 0.0f, img_, true, false);

	//�X�^�[�g�n�_
	//DrawBox(startX_ - gridSize_, startY_ + gridSize_,
	//	startX_, startY_,
	//	0xFFFF00, true);

	//�S�[���n�_
	//DrawBox(startX_ + (gridSize_ * 3), startY_ + (gridSize_),
	//	startX_ + (gridSize_ * 4), startY_ + (gridSize_ * 2),
	//	0xFFFF00, true);

	DrawBox(startX_, startY_,
		startX_ + (160 * 3), startY_ + (160 * 3),
		0xFF0000, true);



	//for (auto block : blocks) {
	//	if (CheckConnections(block)) {
	//		// �ڑ�����Ă���u���b�N�̉��ɉ��F�̃{�b�N�X��\��
	//		int blockX = block->GetX();
	//		int blockY = block->GetY();
	//		DrawBox(blockX - gridSize_ / 2, blockY - gridSize_ / 2,
	//			blockX + gridSize_ / 2, blockY + gridSize_ / 2,
	//			0xFFFF00, true);
	//	}
	//	//block->Draw();
	//}

	// �I������Ă���u���b�N�̉��ɗ΂̃{�b�N�X��\��
	if (selectBlock) {
		int blockX = selectBlock->GetX();
		int blockY = selectBlock->GetY();
		DrawBox(blockX - gridSize_ / 2, blockY - gridSize_ / 2,
			blockX + gridSize_ / 2, blockY + gridSize_ / 2,
			GetColor(0, 255, 0), true);
	}

	for (auto block : blocks) {
		block->Draw();
	}
	DrawString(0, 0, "EASYgame", 0xFFFFFF);
	startBlock->Draw();
	goalBlock->Draw();

	HighlightDraw();

	player_->Draw();
	timer_->Draw();
}

void EasyGameScene::InitBlock(void)
{
	gridSize_ = 160; // 1�u���b�N�̃T�C�Y

	// �u���b�N�̏����ʒu���v�Z�i��ʒ����ɔz�u�j
	startX_ = (Application::SCREEN_SIZE_X - (3 * gridSize_)) / 2;
	startY_ = (Application::SCREEN_SIZE_Y - (3 * gridSize_)) / 2;

	for (int i = 0; i < 3; ++i) {
		for (int j = 0; j < 3; ++j) {
			int x = startX_ + j * gridSize_ + gridSize_ / 2; // ���S�ɔz�u
			int y = startY_ + i * gridSize_ + gridSize_ / 2; // ���S�ɔz�u
			Vector2 pos = { x,y };
			// L���u���b�N��z�u�i��Ƃ��āj
			BlockBase* block = new Block(pos, LoadGraph("Data/Image/LBlock.png"));
			AddBlock(block);
		}
	}

	Vector2 startPos = { startX_ - gridSize_ / 2,startY_ + gridSize_ / 2 };
	Vector2 gaolPos = { startX_ + (gridSize_ * 3) + 80, startY_ + (gridSize_ * 2) - 80 };
	startBlock = new Block(startPos, LoadGraph("Data/Image/StartBlock.png"));
	startBlock->SetRot(0);
	goalBlock = new Block(gaolPos, LoadGraph("Data/Image/GoolBlock.png"));
	goalBlock->SetRot(180);

	// �X�^�[�g�n�_�̃u���b�N�ɓd�C���ʂ��Ă����Ԃ�ݒ�
	//startBlock->SetElectricity(true);
	//UpdateElectricity(startBlock);
}

void EasyGameScene::AddBlock(BlockBase* block)
{
	blocks.push_back(block);
}

//bool EasyGameScene::BlocksConnected(const BlockBase* block1, const BlockBase* block2) const
//{
//	// �u���b�N1�̐ڑ��������u���b�N2�̈ʒu�Ɉ�v���邩�𔻒�
//	for (const auto& conn1 : block1->GetConnections()) {
//		int connX = block1->GetX() + conn1.first;
//		int connY = block1->GetY() + conn1.second;
//		if (connX == block2->GetX() && connY == block2->GetY()) {
//			for (const auto& conn2 : block2->GetConnections()) {
//				int revConnX = block2->GetX() + conn2.first;
//				int revConnY = block2->GetY() + conn2.second;
//				if (revConnX == block1->GetX() && revConnY == block1->GetY()) {
//					return true;
//				}
//			}
//		}
//	}
//	return false;
//}

bool EasyGameScene::CheckConnections(const BlockBase* block) const
{
	//// ���ׂẴu���b�N���������ڑ�����Ă��邩���`�F�b�N
	//	for (size_t i = 0; i < blocks.size(); ++i) {
	//		for (size_t j = i + 1; j < blocks.size(); ++j) {
	//			if (AreBlocksConnected(blocks[i], blocks[j])) {
	//				// ���炩�̏����i��F�ڑ��̕\���Ȃǁj
	//				SceneManager::GetInstance().ChangeScene(SceneManager::SCENE_ID::GAMECLEAR);
	//			}
	//		}
	//	}
	//return true;

	// // �w�肳�ꂽ�u���b�N�����̃u���b�N�Ɛڑ�����Ă��邩���`�F�b�N
	//for (const auto& otherBlock : blocks) {
	//	if (block != otherBlock && BlocksConnected(block, otherBlock)) {
	//		return true;
	//	}
	//}
	//return false;

	// �w�肳�ꂽ�u���b�N�����̃u���b�N�Ɛڑ�����Ă��邩���`�F�b�N
	for (const auto& otherBlock : blocks) {
		if (block != otherBlock && AreBlocksConnected(block, otherBlock)) {
			return true;
		}
	}
	return false;
}

void EasyGameScene::BlockProcess(Vector2 pos)
{
	InputManager& ins = InputManager::GetInstance();
	//selectBlock = nullptr;
	////if (selectBlock) {
	////	// �u���b�N��u���ۂɃO���b�h�ɃX�i�b�v
	////	selectBlock->SnapToGrid(gridSize_, startX_, startY_);
	////	selectBlock->IsNotHold();
	////	selectBlock = nullptr;
	////}
	////else {
	//for (auto block : blocks) {
	//	int blockX = block->GetX();
	//	int blockY = block->GetY();
	//	int blockSize = gridSize_;

	//	if (pos.x >= blockX - blockSize / 2 && pos.x <= blockX + blockSize / 2 &&
	//		pos.y >= blockY - blockSize / 2 && pos.y <= blockY + blockSize / 2) {

	//		selectBlock = block;
	//		//block->IsHold();
	//		break;

	//	}
	//}
	////}

	BlockBase* block = GetBlockAtPosition(pos.x, pos.y);
	if (block) {
		if (ins.IsTrgMouseLeft()) {
			block->LeftRotate(); // ���N���b�N�ō���]
		}
		else if (ins.IsTrgMouseRight()) {
			block->RightRotate(); // �E�N���b�N�ŉE��]�i�E��]�̃��W�b�N��ǉ�����K�v������܂��j
		}
	}
}

bool EasyGameScene::AreBlocksConnected(const BlockBase* block1, const BlockBase* block2) const
{
	// �u���b�N1�̏o�����u���b�N2�̓����ƈ�v���邩�𔻒�
	for (int i = 0; i < 2; ++i) 
	{
		int exitX1 = block1->GetX() + block1->GetExits()[i].x;
		int exitY1 = block1->GetY() + block1->GetExits()[i].y;

		for (int j = 0; j < 2; ++j) 
		{
			int exitX2 = block2->GetX() + block2->GetExits()[j].x;
			int exitY2 = block2->GetY() + block2->GetExits()[j].y;
			if (exitX1 == exitX2 && exitY1 == exitY2) {
				// �������m�F���邽�߂ɁA�o���̍��W�̍������v�Z
				return true;
			}
		}
	}
	return false;
}

BlockBase* EasyGameScene::GetBlockAtPosition(int x, int y) const
{
	for (auto block : blocks) {
		int blockX = block->GetX();
		int blockY = block->GetY();
		int blockSize = gridSize_; // �u���b�N�̃T�C�Y�i�s�N�Z���P�ʁj

		// x, y ���u���b�N�͈͓̔��ɂ��邩���肷�����
		if (x >= blockX - blockSize / 2 && x <= blockX + blockSize / 2 &&
			y >= blockY - blockSize / 2 && y <= blockY + blockSize / 2) {
			return block;
		}
	}
	return nullptr;
}

void EasyGameScene::UpdateElectricity(BlockBase* block)
{
	block->SetElectricity(true);
	for (auto otherBlock : blocks) {
		if (block != otherBlock && AreBlocksConnected(block, otherBlock) && !otherBlock->HasElectricity()) {
			UpdateElectricity(otherBlock); // �ċA�I�ɓd�C���ʂ�u���b�N���X�V
		}
	}
}

void EasyGameScene::ClearElectricity()
{
	for (auto block : blocks) {
		block->SetElectricity(false);
	}
}

void EasyGameScene::PropagateElectricity(BlockBase* block)
{
	if (!block->HasElectricity()) {
		block->SetElectricity(true);
		for (auto otherBlock : blocks) {
			if (block != otherBlock && AreBlocksConnected(block, otherBlock)) {
				PropagateElectricity(otherBlock);
			}
		}
	}
}

//void EasyGameScene::StartElectricity()
//{
//	// �X�^�[�g�n�_�̃u���b�N�ɓd�C��ʂ�
//	if (!blocks.empty()) {
//		startBlock->SetElectricity(true); // ���ɍŏ��̃u���b�N���X�^�[�g�n�_�Ƃ��Đݒ�
//		PropagateElectricity(startBlock);
//	}
//}

bool EasyGameScene::IsConnectedToGoal(void) const
{
	// �u���b�N1�̏o�����u���b�N2�̓����ƈ�v���邩�𔻒�
	for (int i = 0; i < 2; ++i)
	{
		int exitX1 = blocks[5]->GetX() + blocks[5]->GetExits()[i].x;
		int exitY1 = blocks[5]->GetY() + blocks[5]->GetExits()[i].y;

		for (int j = 0; j < 2; ++j)
		{
			int exitX2 = goalBlock->GetX() + goalBlock->GetGoalExits()[j].x;
			int exitY2 = goalBlock->GetY() + goalBlock->GetGoalExits()[j].y;
			if (exitX1 == exitX2 && exitY1 == exitY2) {
				// �������m�F���邽�߂ɁA�o���̍��W�̍������v�Z
				return true;
			}
		}
	}

	return false;
}

void EasyGameScene::HighlightUpdate()
{
	InputManager& ins = InputManager::GetInstance();
	Vector2 pos = ins.GetMousePos();

	preHighlightBlock = highlightBlock;
	highlightBlock = nullptr;

	for (auto block : blocks)
	{
		int blockX = block->GetX();
		int blockY = block->GetY();

		if (pos.x >= blockX - gridSize_ / 2 && pos.x <= blockX + gridSize_ / 2 &&
			pos.y >= blockY - gridSize_ / 2 && pos.y <= blockY + gridSize_ / 2)
		{
			highlightBlock = block;

			break;
		}
	}
}

void EasyGameScene::HighlightDraw()
{
	if (highlightBlock != nullptr)
	{
		highlightPos_ = highlightBlock->GetPos();
		highlightPos_.x -= gridSize_ / 2;
		highlightPos_.y -= gridSize_ / 2;

		DrawBox(highlightPos_.x, highlightPos_.y, highlightPos_.x + gridSize_, highlightPos_.y + gridSize_, 0xffff00, false);
	}

}

void EasyGameScene::InitSoundEffect()
{
	seTouch_ = LoadSoundMem("Data/Sound/SE/se_touch.mp3");
	seRotate_ = LoadSoundMem("Data/Sound/SE/se_rotate.mp3");
}

void EasyGameScene::PlaySoundEffect()
{
	if (preHighlightBlock != highlightBlock && highlightBlock != nullptr)
	{
		PlaySoundMem(seTouch_, DX_PLAYTYPE_BACK);
	}
}
