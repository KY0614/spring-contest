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
	int time = SceneManager::GetInstance().GetTimer();
	DrawString(0, 0, "clear", 0xFFFFFF);

	//クリア表示

	SetFontSize(160);
	DrawString(100, 100, "GAMECLEAR", 0xffffff);
	SetFontSize(16);

	SetFontSize(40);
	DrawString(250, 250, "push Space", 0xffffff);
	SetFontSize(16);

	SetFontSize(25);
	DrawString(50, 300, "<タイムスコア>", 0xffffff);
	SetFontSize(16);

	SetFontSize(30);
	DrawString(190, 350, "1st　:", 0xffffff);
	DrawString(190, 400, "2nd　:", 0xffffff);
	DrawString(190, 450, "3rd　:", 0xffffff);
	DrawString(190, 500, "4th　:", 0xffffff);
	DrawString(190, 550, "5th　:", 0xffffff);

	DrawFormatString(350, 350, 0xffffff,"%ds", time);
}