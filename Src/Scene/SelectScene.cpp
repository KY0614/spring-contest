#include <DxLib.h>
#include "../Manager/SceneManager.h"
#include "../Manager/InputManager.h"
#include "SelectScene.h"

SelectScene::SelectScene(void)
{
}

SelectScene::~SelectScene(void)
{
}

void SelectScene::Init(void)
{
}

void SelectScene::Update(void)
{
	// ÉVÅ[ÉìëJà⁄
	InputManager& ins = InputManager::GetInstance();
	if (ins.IsTrgDown(KEY_INPUT_SPACE))
	{
		SceneManager::GetInstance().ChangeScene(SceneManager::SCENE_ID::GAME);
	}
}

void SelectScene::Draw(void)
{
	DrawString(0, 0, "select", 0xFFFFFF);
}
