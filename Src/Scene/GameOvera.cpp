#include <string>
#include <DxLib.h>
#include "../Application.h"
#include "../Utility/AsoUtility.h"
#include "../Manager/SceneManager.h"
#include "../Manager/InputManager.h"
#include "../Manager/ResourceManager.h"
#include "../Manager/SoundManager.h"
#include "../Object/Timer/Timer.h"
#include "GameOvera.h"

GameOvera::GameOvera(Timer*timer)
{
		timer_ = timer;
}

GameOvera::~GameOvera(void)
{

}

void GameOvera::Init(void)
{
	ResourceManager& res = ResourceManager::GetInstance();
	bgm_ = res.Load(ResourceManager::SRC::GAMEOVERBGM).handleId_;
	
	
	count_ = 0;
	SoundManager::GetInstance().PlayBGM(bgm_, VOLUME_MAX);

}

void GameOvera::Update(void)
{

	count_++;
	// シーン遷移
	InputManager& ins = InputManager::GetInstance();

	if (ins.IsTrgDown(KEY_INPUT_SPACE) || ins.IsPadBtnTrgDown(InputManager::JOYPAD_NO::PAD1, InputManager::JOYPAD_BTN::DOWN))
	{
		SceneManager::GetInstance().ChangeScene(SceneManager::SCENE_ID::TITLE);

	}
	if (count_ > MAX_COUNT)
	{
		if (timer_->GetMin() <= 0 && timer_->GetSec() <= 0)
		{
			SceneManager::GetInstance().ChangeScene(SceneManager::SCENE_ID::TITLE);
		}
		count_ = MAX_COUNT + 1;
	}
}

void GameOvera::Draw(void)
{
	DrawString(0, 100, "GameOvera", 0x000000);
	DrawString(0, 130, "スベース(Aボタン)でリスタート", 0x000000);
}

