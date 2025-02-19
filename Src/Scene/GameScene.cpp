#include <DxLib.h>
#include "../Utility/AsoUtility.h"
#include "../Manager/SceneManager.h"
#include "../Manager/InputManager.h"
#include "../Object/Block/Block.h"
#include "GameScene.h"

GameScene::GameScene(void)
{

}

GameScene::~GameScene(void)
{
}

void GameScene::Init(void)
{
	block_ = new Block();
	block_->Init();

}

void GameScene::Update(void)
{
	block_->Update();
	// ƒV[ƒ“‘JˆÚ
	InputManager& ins = InputManager::GetInstance();
	if (ins.IsTrgDown(KEY_INPUT_SPACE))
	{
		SceneManager::GetInstance().ChangeScene(SceneManager::SCENE_ID::GAMECLEAR);
	}

}

void GameScene::Draw(void)
{
	DrawString(0, 0, "game", 0xFFFFFF);
	block_->Draw();
}
