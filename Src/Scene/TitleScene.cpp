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
	bgmHandle_ = LoadSoundMem();

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

		SceneManager::GetInstance().ChangeScene(SceneManager::SCENE_ID::GAME);
	}


}

void TitleScene::Draw(void)
{
	DrawString(0, 0, "title", 0xFFFFFF);
}
