#include <DxLib.h>
#include "../Application.h"
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
	cat1Img_ = LoadGraph("Data/Image/cat_1.png");
	if (cat1Img_ == -1) return;
	cat2Img_ = LoadGraph("Data/Image/cat_2.png");
	if (cat2Img_ == -1) return;
	img_ = cat1Img_;
}

void GameClearScene::Update(void)
{
	// �V�[���J��
	InputManager& ins = InputManager::GetInstance();
	if (ins.IsTrgDown(KEY_INPUT_SPACE))
	{
		SceneManager::GetInstance().ChangeScene(SceneManager::SCENE_ID::TITLE);
	}

	if (img_ == cat1Img_ && ins.IsTrgDown(KEY_INPUT_R))
	{
		img_ = cat2Img_;
	}
	else if(img_ == cat2Img_ && ins.IsTrgDown(KEY_INPUT_R)) {
		img_ = cat1Img_;
	}
}

void GameClearScene::Draw(void)
{
	int time = SceneManager::GetInstance().GetTimer();
	//DrawString(0, 0, "clear", 0xFFFFFF);

	//�N���A�\��

	SetFontSize(80);
	DrawString(160, 100, "Thank You For Playing", 0xffffff);
	SetFontSize(16);

	SetFontSize(40);
	DrawString(500, 250, "push Space", 0xffffff);
	SetFontSize(16);

	SetFontSize(25);
	DrawString(50, 300, "<�^�C���X�R�A>", 0xffffff);
	SetFontSize(16);

	SetFontSize(30);
	DrawString(190, 350, "1st�@:", 0xffffff);
	DrawString(190, 400, "2nd�@:", 0xffffff);
	DrawString(190, 450, "3rd�@:", 0xffffff);
	DrawString(190, 500, "4th�@:", 0xffffff);
	DrawString(190, 550, "5th�@:", 0xffffff);

	DrawFormatString(350, 350, 0xffffff,"%ds", time);

	DrawRotaGraph(Application::SCREEN_SIZE_X - 160, Application::SCREEN_SIZE_Y - 160, 1.0f, 0.0f, img_, true, false, false);
}