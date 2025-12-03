#include <string>
#include <DxLib.h>
#include "../Application.h"
#include "../Utility/AsoUtility.h"
#include "../Utility/MatrixUtility.h"
#include "../Manager/SceneManager.h"
#include "../Manager/ResourceManager.h"
#include "../Manager/InputManager.h"
#include "../Manager/SoundManager.h"
#include "../Object/Camera/Camera.h"

#include "TitleScene.h"

TitleScene::TitleScene(void)
{

}

TitleScene::~TitleScene(void)
{
	
}

void TitleScene::Init(void)
{

	camera_ = new Camera();
	
	ResourceManager& res = ResourceManager::GetInstance();

	stageId_ = res.Load(ResourceManager::SRC::STAGE).handleId_;
	enemyMId_ = res.Load(ResourceManager::SRC::ENEMYM).handleId_;
	enemyRId_ = res.Load(ResourceManager::SRC::ENEMYR).handleId_;
	enemyUId_ = res.Load(ResourceManager::SRC::ENEMYU).handleId_;
	playerId_ = res.Load(ResourceManager::SRC::PLAYER).handleId_;

	bgm_= res.Load(ResourceManager::SRC::TITLEBGM).handleId_;

	stagePos_ = { Application::SCREEN_SIZE_X/2, 200.0f, 0.0f };
	stageScale_ = { 1.0f,1.0f,1.0f };
	stagelocalRot_ = { 0.0f,0.0f,0.0f };
	stageRot_ = { 0.0f,0.0f,0.0f };
	enemyMPos_ = { 0.0f,0.0f,0.0f };
	enemyMScale_ = { 0.5f,0.5f,0.5f };
	enemyMlocalRot_ = { 0.0f,AsoUtility::Deg2RadF(180.0f),0.0f };
	enemyMRot_ = { 0.0f,0.0f,0.0f };
	enemyRPos_ = { 0.0f,0.0f,0.0f };
	enemyRScale_ = { 0.5f,0.5f,0.5f };
	enemyRlocalRot_ = { 0.0f,AsoUtility::Deg2RadF(180.0f),0.0f };
	enemyRRot_ = { 0.0f,0.0f,0.0f };
	enemyUPos_ = { 0.0f,0.0f,0.0f };
	enemyUScale_ = { 0.05f,0.05f,0.05f };
	enemyUlocalRot_ = { 0.0f,AsoUtility::Deg2RadF(180.0f),0.0f };
	enemyURot_ = { 0.0f,0.0f,0.0f };
	playerPos_ = { 0.0f,0.0f,0.0f };
	playerScale_ = { 0.5f,0.5f,0.5f };
	playerlocalRot_ = { 0.0f,AsoUtility::Deg2RadF(0.0f),0.0f };
	playerRot_ = { 0.0f,0.0f,0.0f };

	MV1SetPosition(stageId_, stagePos_);
	MV1SetRotationMatrix(stageId_, MatrixUtility::Multiplication(stagelocalRot_, stageRot_));
	MV1SetScale(stageId_, stageScale_);

	MV1SetPosition(enemyMId_, enemyMPos_);
	MV1SetRotationMatrix(enemyMId_, MatrixUtility::Multiplication(enemyMlocalRot_, enemyMRot_));
	MV1SetScale(enemyMId_, enemyMScale_);

	MV1SetPosition(enemyRId_, enemyRPos_);
	MV1SetRotationMatrix(enemyRId_, MatrixUtility::Multiplication(enemyRlocalRot_, enemyRRot_));
	MV1SetScale(enemyRId_, enemyRScale_);

	MV1SetPosition(enemyUId_, enemyUPos_);
	MV1SetRotationMatrix(enemyUId_, MatrixUtility::Multiplication(enemyUlocalRot_, enemyURot_));
	MV1SetScale(enemyUId_, enemyUScale_);

	MV1SetPosition(playerId_, playerPos_);
	MV1SetRotationMatrix(playerId_, MatrixUtility::Multiplication(playerlocalRot_, playerRot_));
	MV1SetScale(playerId_, playerScale_);


	camera_->ChangeMode(Camera::MODE::FIXED_POINT);

	camera_->SetPos({ 0.0f,200.0f,0.0f });
	count_ = 0;
	sousa_ = false;
	SoundManager::GetInstance().PlayBGM(bgm_, VOLUME_MAX);
	
}

void TitleScene::Update(void)
{
	
	InputManager& ins = InputManager::GetInstance();

	stageRot_.y += AsoUtility::Deg2RadF(0.3f);
	MV1SetRotationMatrix(stageId_, MatrixUtility::Multiplication(stagelocalRot_, stageRot_));

	VECTOR enemyMlocalPos = { 0.0f,0.0f,-300.0f };

	VECTOR enemyMPos = VTransform(enemyMlocalPos, MatrixUtility::GetMatrixRotateXYZ(stageRot_));
	enemyMPos_ = VAdd(stagePos_, enemyMPos);

	MV1SetPosition(enemyMId_, enemyMPos_);

	VECTOR enemyRlocalPos = { -300.0f,0.0f,0.0f };

	VECTOR enemyRPos = VTransform(enemyRlocalPos, MatrixUtility::GetMatrixRotateXYZ(stageRot_));
	enemyRPos_ = VAdd(stagePos_, enemyRPos);

	MV1SetPosition(enemyRId_, enemyRPos_);

	VECTOR enemyUlocalPos = { 300.0f,0.0f,0.0f };

	VECTOR enemyUPos = VTransform(enemyUlocalPos, MatrixUtility::GetMatrixRotateXYZ(stageRot_));
	enemyUPos_ = VAdd(stagePos_, enemyUPos);

	MV1SetPosition(enemyUId_, enemyUPos_);

	VECTOR playerlocalPos = { 0.0f,50.0f,300.0f };

	VECTOR playerPos = VTransform(playerlocalPos, MatrixUtility::GetMatrixRotateXYZ(stageRot_));
	playerPos_ = VAdd(stagePos_, playerPos);

	MV1SetPosition(playerId_, playerPos_);

	

	enemyMRot_.y += AsoUtility::Deg2RadF(1.5f);
	MV1SetRotationMatrix(enemyMId_, MatrixUtility::Multiplication(enemyMlocalRot_, enemyMRot_));
	enemyRRot_.y += AsoUtility::Deg2RadF(1.5f);
	MV1SetRotationMatrix(enemyRId_, MatrixUtility::Multiplication(enemyRlocalRot_, enemyRRot_));
	enemyURot_.y += AsoUtility::Deg2RadF(1.5f);
	MV1SetRotationMatrix(enemyUId_, MatrixUtility::Multiplication(enemyUlocalRot_, enemyURot_));
	playerRot_.y += AsoUtility::Deg2RadF(1.5f);
	MV1SetRotationMatrix(playerId_, MatrixUtility::Multiplication(playerlocalRot_, playerRot_));







	count_++;
	if (!sousa_)
	{
		
		if (count_ >= 3)
		{
			if (ins.IsTrgDown(KEY_INPUT_SPACE)|| ins.IsPadBtnTrgDown(InputManager::JOYPAD_NO::PAD1, InputManager::JOYPAD_BTN::DOWN))
			{
				
				SceneManager::GetInstance().ChangeScene				(SceneManager::SCENE_ID::GAME);
				count_ = 0;
			}
			if (ins.IsTrgDown(KEY_INPUT_RETURN) || ins.IsPadBtnTrgDown(InputManager::JOYPAD_NO::PAD1, InputManager::JOYPAD_BTN::RIGHT))
			{
				sousa_ = true;
				count_ = 0;
			}
			
		}
	}
	else if(sousa_)
	{
		if (ins.IsTrgDown(KEY_INPUT_RETURN) || ins.IsPadBtnTrgDown(InputManager::JOYPAD_NO::PAD1, InputManager::JOYPAD_BTN::RIGHT))
		{
			sousa_ = false;
			count_ = 0;
		}

	}
	
}

void TitleScene::Draw(void)
{
	MV1DrawModel(stageId_);
	MV1DrawModel(enemyMId_);
	MV1DrawModel(enemyRId_);
	MV1DrawModel(enemyUId_);
	MV1DrawModel(playerId_);
	if (!sousa_)
	{

		//DrawString(0, 100, "Title Scene", 0x000000);
		SetFontSize(150);
		DrawString(600, 130, "ヨケアク", 0xffffff);
		SetFontSize(96);
		DrawString(250, 800, "スベース(Aボタン)でゲームスタート", 0xffffff);
		DrawString(350, 900, "ENTER(Bボタン)で操作方法", 0xffffff);
		SetFontSize(16);
	}
	else if (sousa_)
	{
		SetFontSize(80);
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255 / 2);
		DrawBox(0, 0, Application::SCREEN_SIZE_X, Application::SCREEN_SIZE_Y, 0x000000, true);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
		DrawString(0, 100, "操作方法", 0xffffff);
		DrawString(0, 200, "移動         ：Lスティック　/　WASD", 0xffffff);
		DrawString(0, 300, "カメラ操作   ：Rスティック　/　←→", 0xffffff);
		DrawString(0, 400, "ガード       ：RT長押し　/　スペース長押し", 0xffffff);
		DrawString(0, 500, "パリ―       ：RTを離す　/　スペースを離す", 0xffffff);
		DrawString(0, 600, "回避         ：A　/　Lシフト", 0xffffff);
		DrawString(0, 700, "攻撃         ：B　/　Kキー", 0xffffff);
		DrawString(0, 800, "ENTER(Bボタン)でタイトルへ戻る", 0xffffff);
		SetFontSize(16);
	}
}

