#include <DxLib.h>
#include "../Application.h"
#include "../Utility/AsoUtility.h"
#include "../Manager/SceneManager.h"
#include "../Manager/ResourceManager.h"
#include "../Manager/InputManager.h"
#include "../Object/Player/Player.h"
#include "../Object/Block/Block.h"
#include "GameScene.h"

GameScene::GameScene(void):selectBlock(nullptr)
{
	InitBlock();
}

GameScene::~GameScene(void)
{
	for (auto block : blocks) {
		delete block;
	}
}

void GameScene::Init(void)
{
	//サウンド読み込み
	//bgmHandle_ = LoadSoundMem();

	auto& res = ResourceManager::GetInstance();
	img_ = res.Load(ResourceManager::SRC::SELECT).handleId_;
	if (img_ == -1)
	{
		return;
	}

	//BGMスタート
	PlaySoundMem(bgmHandle_, DX_PLAYTYPE_LOOP);

	player_ = new Player;
	player_->Init();
}

void GameScene::Update(void)
{
	InputManager& ins = InputManager::GetInstance();

	player_->Updeta();
	for (auto block : blocks) {
		block->Update();
		CheckConnections(block);
	}

	if (selectBlock && ins.IsTrgDown(KEY_INPUT_SPACE))
	{
		selectBlock->RightRotate();
	}

	if (ins.IsTrgMouseLeft()) {
		BlockProcess(ins.GetMousePos());
	}

	// シーン遷移
	if (ins.IsTrgDown(KEY_INPUT_R))
	{

		//BGM停止
		StopSoundMem(bgmHandle_);

		//SceneManager::GetInstance().ChangeScene(SceneManager::SCENE_ID::TITLE);
		SceneManager::GetInstance().ChangeScene(SceneManager::SCENE_ID::GAMECLEAR);
	}

}

void GameScene::Draw(void)
{
	
	DrawString(0, 0, "game", 0xFFFFFF);

	//背景
	DrawRotaGraph(Application::SCREEN_SIZE_X / 2,
		Application::SCREEN_SIZE_Y / 2,
		1.0f, 0.0f, img_, true, false);

	//スタート地点
	DrawBox(startX_ - gridSize_ , startY_ + gridSize_,
		startX_, startY_,
		0xFFFF00, true);
	
	//ゴール地点
	DrawBox(startX_ + (gridSize_ * 3), startY_ + (gridSize_),
		startX_ + (gridSize_ * 4), startY_ + (gridSize_ * 2),
		0xFFFF00, true);

	DrawBox(startX_, startY_,
		startX_ + (160 * 3), startY_ + (160 * 3),
		0xFF0000, true);

	// 選択されているブロックの下に緑のボックスを表示
	if (selectBlock) {
		int blockX = selectBlock->GetX();
		int blockY = selectBlock->GetY();
		DrawBox(blockX - gridSize_ / 2, blockY - gridSize_ / 2,
			blockX + gridSize_ / 2, blockY + gridSize_ / 2,
			GetColor(0, 255, 0), true);
	}

	for (auto block : blocks) {
		if (CheckConnections(block)) {
			// 接続されているブロックの下に黄色のボックスを表示
			int blockX = block->GetX();
			int blockY = block->GetY();
			DrawBox(blockX - gridSize_ / 2, blockY - gridSize_ / 2,
				blockX + gridSize_ / 2, blockY + gridSize_ / 2, 
				0xFFFF00, true);
		}
		block->Draw();
	}

	//for (auto block : blocks) {
	//	block->Draw();
	//}

	startBlock->Draw();
	goalBlock->Draw();

	player_->Draw();
}

void GameScene::InitBlock(void)
{
	gridSize_ = 160; // 1ブロックのサイズ

	// ブロックの初期位置を計算（画面中央に配置）
	startX_ = (Application::SCREEN_SIZE_X - (3 * gridSize_)) / 2;
	startY_ = (Application::SCREEN_SIZE_Y - (3 * gridSize_)) / 2;

	for (int i = 0; i < 3; ++i) {
		for (int j = 0; j < 3; ++j) {
			int x = startX_ + j * gridSize_ + gridSize_ / 2; // 中心に配置
			int y = startY_ + i * gridSize_ + gridSize_ / 2; // 中心に配置
			Vector2 pos = { x,y };
			// L字ブロックを配置（例として）
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
}

void GameScene::AddBlock(BlockBase* block)
{
	blocks.push_back(block);
}

bool GameScene::BlocksConnected(const BlockBase* block1, const BlockBase* block2) const
{
	// ブロック1の接続方向がブロック2の位置に一致するかを判定
	for (const auto& conn1 : block1->GetConnections()) {
		int connX = block1->GetX() + conn1.first;
		int connY = block1->GetY() + conn1.second;
		if (connX == block2->GetX() && connY == block2->GetY()) {
			for (const auto& conn2 : block2->GetConnections()) {
				int revConnX = block2->GetX() + conn2.first;
				int revConnY = block2->GetY() + conn2.second;
				if (revConnX == block1->GetX() && revConnY == block1->GetY()) {
					return true;
				}
			}
		}
	}
	return false;
}

bool GameScene::CheckConnections(const BlockBase* block) const
{
	//// すべてのブロックが正しく接続されているかをチェック
	//	for (size_t i = 0; i < blocks.size(); ++i) {
	//		for (size_t j = i + 1; j < blocks.size(); ++j) {
	//			if (AreBlocksConnected(blocks[i], blocks[j])) {
	//				// 何らかの処理（例：接続の表示など）
	//				SceneManager::GetInstance().ChangeScene(SceneManager::SCENE_ID::GAMECLEAR);
	//			}
	//		}
	//	}
	//return true;

	 // 指定されたブロックが他のブロックと接続されているかをチェック
	for (const auto& otherBlock : blocks) {
		if (block != otherBlock && BlocksConnected(block, otherBlock)) {
			return true;
		}
	}
	return false;
}

void GameScene::BlockProcess(Vector2 pos)
{
	InputManager& ins = InputManager::GetInstance();
	selectBlock = nullptr;
	//if (selectBlock) {
	//	// ブロックを置く際にグリッドにスナップ
	//	selectBlock->SnapToGrid(gridSize_, startX_, startY_);
	//	selectBlock->IsNotHold();
	//	selectBlock = nullptr;
	//}
	//else {
		for (auto block : blocks) {
			int blockX = block->GetX();
			int blockY = block->GetY();
			int blockSize = gridSize_;

			if (pos.x >= blockX - blockSize / 2 && pos.x <= blockX + blockSize / 2 &&
				pos.y >= blockY - blockSize / 2 && pos.y <= blockY + blockSize / 2) {

				selectBlock = block;
				//block->IsHold();
				break;

			}
		}
	//}
}
