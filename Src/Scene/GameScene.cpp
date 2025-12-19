#include <DxLib.h>
#include "../Application.h"
#include "../Utility/AsoUtility.h"
#include "../Manager/SceneManager.h"
#include "../Manager/ResourceManager.h"
#include "../Manager/InputManager.h"
#include "../Manager/SoundManager.h"
#include "../Manager/EnemyManager.h"
#include "../Object/Collision/Collision.h"
#include "../Object/Camera/Camera.h"
#include "../Object/Grid/Grid.h"
#include "../Object/Player/Player.h"
#include "../Object/Timer/Timer.h"
#include "../Object/Stage/Stage.h"
#include "GameScene.h"

GameScene::GameScene(Timer*timer)
{
	timer_ = timer;
}

GameScene::~GameScene(void)
{
	
}

void GameScene::Init(void)
{

	ResourceManager& res = ResourceManager::GetInstance();
	bgm_ = res.Load(ResourceManager::SRC::GAMEBGM).handleId_;
	

	//インストラクター
	//カメラ機能の初期化
	camera_ = new Camera();

	//グリッド機能の初期化
	grid_ = new Grid();

	//プレイヤー機能の初期化
	player_ = new Player();

	//エネミー管理機能の初期化
	enemyManager_ = new EnemyManager(player_,this);

	//当たり判定機能の初期化
	collision_ = new Collision();

	stage_=new Stage();

	//Init
	camera_->Init(player_);
	grid_->Init();
	player_->Init(camera_,this);
	enemyManager_->Init();
	collision_->Init(player_,enemyManager_,this,stage_);
	stage_->Init();


	camera_->ChangeMode(Camera::MODE::FOLLOW);

	count_ = 0;
	slowTime_ = 0.0f;
	slowCount_ = 0;
	isSlow_ = false;

	stopTime_ = 0.0f;
	isStop_ = false;

	SoundManager::GetInstance().PlayBGM(bgm_, VOLUME_MAX);
}

void GameScene::Update(void)
{
	

	count_++;
	InputManager& ins = InputManager::GetInstance();
	
	stage_->Update();

	if (isStop_)
	{
		stopTime_ += 1.0f;
		if (stopTime_ >= MAX_STOP_TIME)
		{
			stopTime_ = 0.0f;
			isStop_ = false;
		}
	}
	else
	{
		if (isSlow_)
		{
			slowTime_ += 1.0f;
			if (slowTime_ <= MAX_SLOW_TIME)
			{
				slowCount_++;
			}
			if (slowCount_ >= MAX_SLOW_COUNT)
			{
				if (isSlowP_)
				{
					player_->Update();
				}

				enemyManager_->Update();
				slowCount_ = 0;
			}
			if (slowTime_ >= MAX_SLOW_TIME)
			{
				isSlow_ = false;
				slowTime_ = 0.0f;
				slowCount_ = 0;
			}
			if (slowTime_ >= MAX_SLOW_TIME_P*2)
			{
				isSlowP_ = false;
			}
		}
		else
		{
			enemyManager_->Update();
		}
		if (!isSlowP_)
		{
			player_->Update();
		}

	}
	collision_->Update();
	// シーン遷移
	if (ins.IsTrgDown(KEY_INPUT_R)||ins.IsPadBtnTrgDown(InputManager::JOYPAD_NO::PAD1, InputManager::JOYPAD_BTN::BACK))
	{
		SceneManager::GetInstance().ChangeScene(SceneManager::SCENE_ID::TITLE);
	}
	if (player_->GetHp() <= 0)
	{
		SceneManager::GetInstance().ChangeScene(SceneManager::SCENE_ID::GAMEOVER);
	}

	if (count_ > MAX_COUNT)
	{
		
		if (timer_->GetMin() <= 0 && timer_->GetSec() <= 0)
		{
			SceneManager::GetInstance().ChangeScene(SceneManager::SCENE_ID::CLEAR);
		}
		
	}
}

void GameScene::Draw(void)
{
	// カメラ設定
	camera_->SetBeforeDraw();
	//グリッド線
	//grid_->Draw();
	stage_->Draw();
	//プレイヤー
	player_->Draw();
	
	//エネミー
	enemyManager_->Draw();
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255 / 2);
	DrawBox(0, 0, Application::SCREEN_SIZE_X, 60, 0x000000, true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

	//DrawString(10, 30, "Game Scene", 0x000000);
	SetFontSize(32);
	DrawString(1500, 10, "ESC（START）でメニュー", 0xffffff);
	SetFontSize(16);
}

void GameScene::SetIsSlow(bool isSlow)
{
	isSlow_ = isSlow;
	isSlowP_ = isSlow;
}

bool GameScene::GetIsSlow(void)
{
	return isSlow_;
}

bool GameScene::GetIsSlowP(void)
{
	return isSlowP_;
}

bool GameScene::GetIsStop(void)
{
	return isStop_;
}

void GameScene::SetIsStop(bool isStop)
{
	isStop_ = isStop;
}


