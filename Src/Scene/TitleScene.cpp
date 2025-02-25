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
	//�T�E���h�ǂݍ���
	//bgmHandle_ = LoadSoundMem();
	auto& res = ResourceManager::GetInstance();

	//�摜�ǂݍ���
	img_ = res.Load(ResourceManager::SRC::TITLE).handleId_;
	if (img_ == -1)
	{
		return;
	}
	loopCount = 0;//�J�E���g
	moziFlag = true;//�`��t���O
	//BGM�X�^�[�g
	PlaySoundMem(bgmHandle_, DX_PLAYTYPE_LOOP);
}

void TitleScene::Update(void)
{

	// �V�[���J��
	InputManager& ins = InputManager::GetInstance();
	if (ins.IsTrgDown(KEY_INPUT_SPACE))
	{
		//BGM��~
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
	StrLen = strlen("�X�y�[�X�������Ď���");
	if (moziFlag == true)
	{
		SetFontSize(64);
		DrawString((Application::SCREEN_SIZE_X - GetDrawStringWidth("�X�y�[�X�������Ď���", StrLen)) / 2, Application::SCREEN_SIZE_Y / 2 + 180, "�X�y�[�X�������Ď���", 0xffffff);
	}
	SetFontSize(16);
}
