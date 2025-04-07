#include <DxLib.h>
#include "../Application.h"
#include "../Manager/SceneManager.h"
#include "../Manager/InputManager.h"
#include "../Manager/ResourceManager.h"
#include "GameClearScene.h"

GameClearScene::GameClearScene(void)
{
}

GameClearScene::~GameClearScene(void)
{
}

void GameClearScene::Init(void)
{
	auto& res = ResourceManager::GetInstance();
	img_ = res.Load(ResourceManager::SRC::SELECT).handleId_;
	if (img_ == -1)
	{
		return;
	}
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
	//背景
	DrawRotaGraph(Application::SCREEN_SIZE_X / 2,
		Application::SCREEN_SIZE_Y / 2,
		1.0f, 0.0f, img_, true, false);
	
	int time = SceneManager::GetInstance().GetTimer();
	DrawString(0, 0, "clear", 0xFFFFFF);

	//クリア表示

	SetFontSize(160);
	DrawString(100, 70, "GAMECLEAR", 0xffffff);
	SetFontSize(16);

	SetFontSize(40);
	DrawString(250, 220, "push Space", 0xffffff);
	SetFontSize(16);

	SetFontSize(25);
	DrawString(50, 280, "<タイムスコア>", 0xffffff);
	SetFontSize(16);

	SetFontSize(30);
	DrawString(190, 350, "1st　:", 0xffffff);
	DrawString(190, 400, "2nd　:", 0xffffff);
	DrawString(190, 450, "3rd　:", 0xffffff);
	DrawString(190, 530, "4th　:", 0xffffff);
	DrawString(190, 580, "5th　:", 0xffffff);

	DrawFormatString(350, 350, 0xffffff,"%ds", time);
}