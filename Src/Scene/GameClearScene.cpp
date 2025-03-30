#include <DxLib.h>
#include "../Manager/SceneManager.h"
#include "../Manager/InputManager.h"
#include "GameClearScene.h"

GameClearScene::GameClearScene(void)
{
}

GameClearScene::~GameClearScene(void)
{
}

void GameClearScene::Init(void)
{
}

void GameClearScene::Update(void)
{
	// シーン遷移
	InputManager& ins = InputManager::GetInstance();
	if (ins.IsTrgDown(KEY_INPUT_SPACE))
	{
		SceneManager::GetInstance().ChangeScene(SceneManager::SCENE_ID::TITLE);
	}
}

void GameClearScene::Draw(void)
{
	
	DrawString(0, 0, "clear", 0xFFFFFF);

	//クリア表示

	SetFontSize(160);
	DrawString(100, 100, "GAMECLEAR", 0xffffff);
	SetFontSize(16);

	SetFontSize(80);
	DrawString(200, 300, "push Space", 0xffffff);
	SetFontSize(16);
}