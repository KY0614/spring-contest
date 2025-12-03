#include <string>
#include <DxLib.h>
#include "../Application.h"
#include "../Utility/AsoUtility.h"
#include "../Utility/MatrixUtility.h"
#include "../Manager/SceneManager.h"
#include "../Manager/InputManager.h"
#include "../Manager/ResourceManager.h"
#include "../Manager/SoundManager.h"
#include "../Object/Timer/Timer.h"
#include "../Object/Common/AnimationController.h"
#include "ClearScene.h"

ClearScene::ClearScene(Timer*timer)
{
	timer_ = timer;
}

ClearScene::~ClearScene(void)
{
	
}

void ClearScene::Init(void)
{
	ResourceManager& res = ResourceManager::GetInstance();
	bgm_ = res.Load(ResourceManager::SRC::CLEARBGM).handleId_;
	
	modelid_ = res.Load(ResourceManager::SRC::CLEARSTAGE).handleId_;
	
	pos_ = { Application::SCREEN_SIZE_X / 2, 400.0f, -400.0f };
	localrot_ = { 0.0f,0.0f,0.0f };
	rot_ = { 0.0f,0.0f,0.0f };

	count_ = 0;
	// アニメーションの設定
	animationController_ = new AnimationController(modelid_);
	for (int i = 0; i < static_cast<int>(ANIM_TYPE::MAX); i++)
	{
		animationController_->AddInFbx(i, 30.0f, i);
	}
	// アニメーションの再生
	animationController_->Play(static_cast<int>(ANIM_TYPE::CLEAR));
	
	MV1SetPosition(modelid_, pos_);
	MV1SetRotationMatrix(modelid_, MatrixUtility::Multiplication(localrot_, rot_));


	SoundManager::GetInstance().PlayBGM(bgm_, VOLUME_MAX);
}

void ClearScene::Update(void)
{
	rot_.y += AsoUtility::Deg2RadF(0.3f);
	MV1SetRotationMatrix(modelid_, MatrixUtility::Multiplication(localrot_, rot_));

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
	animationController_->Update();
}

void ClearScene::Draw(void)
{
	MV1DrawModel(modelid_);
	SetFontSize(150);
	DrawString(600, 130, "Gama Clear", 0xffffff);
	SetFontSize(96);
	DrawString(250, 800, "スベース(Aボタン)でゲームスタート", 0xffffff);
	SetFontSize(16);
}

