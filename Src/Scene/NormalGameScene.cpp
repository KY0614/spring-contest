#include <DxLib.h>
#include "../Application.h"
#include "../Utility/AsoUtility.h"
#include "../Manager/SceneManager.h"
#include "../Manager/ResourceManager.h"
#include "../Manager/InputManager.h"
#include "../Object/Player/Player.h"
#include "../Object/Block/Block.h"
#include "../Object/Block/PlusBlock.h"
#include "../Object/Block/ToBlock.h"
#include "../Object/Block/StraightBlock.h"
#include "../Object/Time/Timer.h"
#include "NormalGameScene.h"

NormalGameScene::NormalGameScene(void)
{
	InitBlock();
}

NormalGameScene::~NormalGameScene(void)
{
	for (auto block : blocks) {
		delete block;
	}
	blocks.clear();
	delete goalBlock;
	DeleteSoundMem(bgmHandle_);
}

void NormalGameScene::Init(void)
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

void NormalGameScene::Update(void)
{
	InputManager& ins = InputManager::GetInstance();

	player_->Updeta();
	timer_->Update();

	HighlightUpdate();

	PlaySoundEffect();

	// �ڑ���Ԃ���U�N���A
	ClearElectricity();

	for (auto block : blocks)
	{
		block->Update();
		startBlock->SetElectricity(true);
		UpdateElectricity(startBlock); // �X�^�[�g�n�_����ēx�d�C�̗�����X�V
		block->GetType();
	}

	//�X�y�[�X�L�[�����ŉE��]
	if (highlightBlock && ins.IsTrgDown(KEY_INPUT_SPACE))
	{
		highlightBlock->RightRotate();
		PlaySoundMem(seRotate_, DX_PLAYTYPE_BACK);
	}

	if (highlightBlock && ins.IsTrgDown(KEY_INPUT_R))
	{
		ReplaceBlockWithPlusBlock();
	}

	//�N���b�N�ŉ�]
	BlockProcess(ins.GetMousePos());

	// �V�[���J��
	if (goalBlock->HasElectricity())
	{

		//BGM��~
		StopSoundMem(bgmHandle_);

		SceneManager::GetInstance().SetTimer(timer_->GetTime());
		SceneManager::GetInstance().ChangeScene(SceneManager::SCENE_ID::GAMECLEAR);
	}
	if (timer_->GetTime() <= 0)
	{
		SceneManager::GetInstance().ChangeScene(SceneManager::SCENE_ID::GAMECLEAR);
	}
}

void NormalGameScene::Draw(void)
{

	//DrawString(0, 0, "game", 0xFFFFFF);

	//�w�i
	DrawRotaGraph(Application::SCREEN_SIZE_X / 2,
		Application::SCREEN_SIZE_Y / 2,
		1.0f, 0.0f, img_, true, false);

	for (auto block : blocks) {
		block->Draw();
	}
	//DrawString(0, 0, "EASYgame", 0xFFFFFF);
	startBlock->Draw();
	goalBlock->Draw();

	HighlightDraw();

	player_->Draw();
	timer_->Draw();
	SetFontSize(32);
	DrawFormatString(140, Application::SCREEN_SIZE_Y - 32, 0xffffff, "R�L�[�Ńn�C���C�g�\���̃u���b�N��%d��u�������ł����", 1 - replaceCount);
	SetFontSize(16);

	if (replaceCount < 1) {
		UIBlock1->UIDraw();
	}
}

void NormalGameScene::InitBlock(void)
{
	gridSize_ = 160; // 1�u���b�N�̃T�C�Y

	// �u���b�N�̏����ʒu���v�Z�i��ʒ����ɔz�u�j
	startX_ = (Application::SCREEN_SIZE_X - (BLOCK_NUM * gridSize_)) / 2;
	startY_ = (Application::SCREEN_SIZE_Y - (BLOCK_NUM * gridSize_)) / 2;

	for (int i = 0; i < BLOCK_NUM; ++i) {
		for (int j = 0; j < BLOCK_NUM; ++j) {
			int x = startX_ + j * gridSize_ + gridSize_ / 2; // ���S�ɔz�u
			int y = startY_ + i * gridSize_ + gridSize_ / 2; // ���S�ɔz�u
			Vector2 pos = { x,y };
			// L���u���b�N��z�u
			//BlockBase* block = new Block(pos, LoadGraph("Data/Image/LBlock.png"));
			//BlockBase* block = new PlusBlock(pos, LoadGraph("Data/Image/PlusBlock.png"));
			//BlockBase* block = new ToBlock(pos, LoadGraph("Data/Image/ToBlock.png"));
			//BlockBase* block = new StraightBlock(pos, LoadGraph("Data/Image/LineBlock.png"));

			int blockType = rand() % 10;
			BlockBase* block = nullptr;

		/*	switch (blockType) {
			case 0:
				block = new Block(pos, LoadGraph("Data/Image/LBlock.png"));
				break;
			case 1:
				block = new PlusBlock(pos, LoadGraph("Data/Image/PlusBlock.png"));
				break;
			case 2:
				block = new ToBlock(pos, LoadGraph("Data/Image/ToBlock.png"));
				break;
			case 3:
				block = new StraightBlock(pos, LoadGraph("Data/Image/LineBlock.png"));
				break;
			}*/

			if (blockType < 3) {
				block = new Block(pos, LoadGraph("Data/Image/LBlock.png"));
			}
			else if (blockType < 6) {
				block = new ToBlock(pos, LoadGraph("Data/Image/ToBlock.png"));
			}
			else if (blockType < 8) {
				block = new StraightBlock(pos, LoadGraph("Data/Image/LineBlock.png"));
			}
			else {
				block = new PlusBlock(pos, LoadGraph("Data/Image/PlusBlock.png"));
			}


			block->Init();
			AddBlock(block);
		}
	}

	Vector2 startPos = { startX_ - gridSize_ / 2,startY_ + gridSize_ / 2 };
	Vector2 gaolPos = { startX_ + (gridSize_ * BLOCK_NUM) + 80, startY_ + (gridSize_ * 2) - 80 };
	startBlock = new Block(startPos, LoadGraph("Data/Image/StartBlock.png"));
	startBlock->SetRot(0);
	startBlock->SetConnection(Block::TYPE::ONE);
	goalBlock = new Block(gaolPos, LoadGraph("Data/Image/GoolBlock.png"));
	goalBlock->SetRot(180);
	goalBlock->SetConnection(Block::TYPE::ONE);
	Vector2 UIPos = { 60,Application::SCREEN_SIZE_Y - 48 };
	UIBlock1 = new PlusBlock(UIPos, LoadGraph("Data/Image/PlusBlock.png"));
}

void NormalGameScene::AddBlock(BlockBase* block)
{
	blocks.push_back(block);
}

void NormalGameScene::BlockProcess(Vector2 pos)
{
	InputManager& ins = InputManager::GetInstance();

	BlockBase* block = GetBlockAtPosition(pos.x, pos.y);
	if (block) {
		if (ins.IsTrgMouseLeft()) {
			block->LeftRotate(); // ���N���b�N�ō���]
			PlaySoundMem(seRotate_, DX_PLAYTYPE_BACK);
		}
		else if (ins.IsTrgMouseRight()) {
			block->RightRotate(); // �E�N���b�N�ŉE��]
			PlaySoundMem(seRotate_, DX_PLAYTYPE_BACK);
		}
	}

}

bool NormalGameScene::AreBlocksConnected(const BlockBase* block1, const BlockBase* block2) const
{
	int num1 = 0;
	int num2 = 0;
	if (block1->GetType() == BlockBase::TYPE::LSHAPE || block1->GetType() == BlockBase::TYPE::STRAIGHT) num1 = 2;
	if (block1->GetType() == BlockBase::TYPE::PLUS) num1 = 4;
	if (block1->GetType() == BlockBase::TYPE::TO) num1 = 3;
	if (block1->GetType() == BlockBase::TYPE::ONE) num1 = 1;
	if (block2->GetType() == BlockBase::TYPE::LSHAPE || block2->GetType() == BlockBase::TYPE::STRAIGHT) num2 = 2;
	if (block2->GetType() == BlockBase::TYPE::PLUS) num2 = 4;
	if (block2->GetType() == BlockBase::TYPE::TO) num2 = 3;
	if (block2->GetType() == BlockBase::TYPE::ONE) num2 = 1;
	// �u���b�N1�̏o�����u���b�N2�̓����ƈ�v���邩�𔻒�
	for (int i = 0; i < num1; ++i)
	{
		int exitX1 = block1->GetX() + block1->GetExits()[i].x;
		int exitY1 = block1->GetY() + block1->GetExits()[i].y;

		for (int j = 0; j < num2; ++j)
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

BlockBase* NormalGameScene::GetBlockAtPosition(int x, int y) const
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

void NormalGameScene::UpdateElectricity(BlockBase* startblock)
{
	std::vector<BlockBase*> tmpBlocks;
	std::vector<BlockBase*> connectedBlocks;
	connectedBlocks.emplace_back(startBlock);

	while (connectedBlocks.size() > 0)
	{

		tmpBlocks.clear();

		for (auto connectedBlock : connectedBlocks)
		{
			for (auto block : blocks)
			{

				// �X�^�[�g�u���b�N�łȂ�����
				// �u���b�N1�̏o�����u���b�N2�̓����ƈ�v���邩�𔻒�
				if (startBlock != block
					&& AreBlocksConnected(connectedBlock, block)
					&& !block->HasElectricity())
				{
					// �d�C��ʂ�
					block->SetElectricity(true);
					tmpBlocks.emplace_back(block);
				}
			}
			if (AreBlocksConnected(connectedBlock, goalBlock)
				&& !goalBlock->HasElectricity())
			{
				// �d�C��ʂ�
				goalBlock->SetElectricity(true);
				tmpBlocks.emplace_back(goalBlock);
			}
		}

		connectedBlocks = tmpBlocks;

	}

}

void NormalGameScene::ClearElectricity()
{
	for (auto block : blocks) {
		block->SetElectricity(false);
	}
}

void NormalGameScene::PropagateElectricity(BlockBase* block)
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

void NormalGameScene::ReplaceBlockWithPlusBlock()
{
	if (replaceCount >= 1) return; // �u�������񐔂�1��𒴂����珈�����I��

	int mouseX, mouseY;
	GetMousePoint(&mouseX, &mouseY);
	BlockBase* block = GetBlockAtPosition(mouseX, mouseY);

	if (block && dynamic_cast<PlusBlock*>(block) == nullptr) {
		Vector2 pos = block->GetPos();

		// ���̃u���b�N���폜
		auto it = std::find(blocks.begin(), blocks.end(), block);
		if (it != blocks.end()) {
			delete* it;
			*it = new PlusBlock(pos, LoadGraph("Data/Image/PlusBlock.png"));
			(*it)->Init();
		}
		replaceCount++;
	}
}

void NormalGameScene::HighlightUpdate()
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

void NormalGameScene::HighlightDraw()
{
	if (highlightBlock != nullptr)
	{
		highlightPos_ = highlightBlock->GetPos();
		highlightPos_.x -= gridSize_ / 2;
		highlightPos_.y -= gridSize_ / 2;

		DrawBox(highlightPos_.x, highlightPos_.y, highlightPos_.x + gridSize_, highlightPos_.y + gridSize_, 0xffff00, false);
	}

}

void NormalGameScene::InitSoundEffect()
{
	seTouch_ = LoadSoundMem("Data/Sound/SE/se_touch.mp3");
	seRotate_ = LoadSoundMem("Data/Sound/SE/se_rotate.mp3");
	ChangeVolumeSoundMem(255 * 30 / 100, seRotate_);
}

void NormalGameScene::PlaySoundEffect()
{
	if (preHighlightBlock != highlightBlock && highlightBlock != nullptr)
	{
		PlaySoundMem(seTouch_, DX_PLAYTYPE_BACK);
	}
}