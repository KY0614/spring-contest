#include <DxLib.h>
#include "../Utility/AsoUtility.h"
#include "../Manager/SceneManager.h"
#include "../Manager/InputManager.h"
#include "GameScene.h"

GameScene::GameScene(void)
{

}

GameScene::~GameScene(void)
{
}

void GameScene::Init(void)
{
	//�T�E���h�ǂݍ���
	bgmHandle_ = LoadSoundMem();

	//BGM�X�^�[�g
	PlaySoundMem(bgmHandle_, DX_PLAYTYPE_LOOP);

}

void GameScene::Update(void)
{

	// �V�[���J��
	InputManager& ins = InputManager::GetInstance();
	if (ins.IsTrgDown(KEY_INPUT_SPACE))
	{
		SceneManager::GetInstance().ChangeScene(SceneManager::SCENE_ID::TITLE);
	}

}

void GameScene::Draw(void)
{
	DrawString(0, 0, "game", 0xFFFFFF);
}
