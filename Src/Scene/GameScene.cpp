#include <DxLib.h>
#include "../Utility/AsoUtility.h"
#include "../Manager/SceneManager.h"
#include "../Manager/InputManager.h"
#include "../Object/Player.h"
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
	//サウンド読み込み
	//bgmHandle_ = LoadSoundMem();

	//BGMスタート
	PlaySoundMem(bgmHandle_, DX_PLAYTYPE_LOOP);

	player_ = new Player;
	player_->Init();
}

void GameScene::Update(void)
{
	player_->Updeta();
	// シーン遷移
	InputManager& ins = InputManager::GetInstance();
	if (ins.IsTrgDown(KEY_INPUT_SPACE))
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
	player_->Draw();
}
