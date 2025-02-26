#include <string>
#include <DxLib.h>
#include "../Application.h"
#include "../Utility/AsoUtility.h"
#include "../Manager/SceneManager.h"
#include "../Manager/ResourceManager.h"
#include "../Manager/InputManager.h"
#include "TitleScene.h"

TitleScene::TitleScene(void)
{

}

TitleScene::~TitleScene(void)
{
}

void TitleScene::Init(void)
{
	//サウンド読み込み
	//bgmHandle_ = LoadSoundMem();
	auto& res = ResourceManager::GetInstance();

	//画像読み込み
	img_ = res.Load(ResourceManager::SRC::TITLE).handleId_;
	if (img_ == -1)
	{
		return;
	}
	loopCount = 0;//カウント
	moziFlag = true;//描画フラグ
	//BGMスタート
	PlaySoundMem(bgmHandle_, DX_PLAYTYPE_LOOP);
}

void TitleScene::Update(void)
{

	// シーン遷移
	InputManager& ins = InputManager::GetInstance();
	if (ins.IsTrgDown(KEY_INPUT_SPACE))
	{
		//BGM停止
		StopSoundMem(bgmHandle_);

		//SceneManager::GetInstance().ChangeScene(SceneManager::SCENE_ID::GAME);
		SceneManager::GetInstance().ChangeScene(SceneManager::SCENE_ID::SELECT);
	}
	if (moziFlag == true)
	{
		loopCount++;
		if (loopCount >= 120)
		{
			loopCount = 0;
			moziFlag = false;
		}
	}
	else if (moziFlag == false)
	{
		loopCount++;
		if (loopCount >= 60)
		{
			loopCount = 0;
			moziFlag = true;
		}
	}
}

void TitleScene::Draw(void)
{
	SetFontSize(16);


	DrawRotaGraph(Application::SCREEN_SIZE_X / 2,
		Application::SCREEN_SIZE_Y / 2,
		1.0f, 0.0f, img_, true, false);
	
	DrawString(0, 0, "title", 0xFFFFFF);

	int StrLen;
	StrLen = strlen("スペースを押して次へ");
	if (moziFlag == true)
	{
		SetFontSize(64);
		DrawString((Application::SCREEN_SIZE_X - GetDrawStringWidth("スペースを押して次へ", StrLen)) / 2, Application::SCREEN_SIZE_Y / 2 + 180, "スペースを押して次へ", 0xffffff);
	}
	SetFontSize(16);
}
