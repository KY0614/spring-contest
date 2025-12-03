#include <EffekseerForDXLib.h>
#include "../../Manager/InputManager.h"
#include "../../Utility/AsoUtility.h"
#include "../../Object/Player/Player.h"

#include "Camera.h"
Camera::Camera(void)
{
	// DxLibの初期設定では、
   // カメラの位置が x = 320.0f, y = 240.0f, z = (画面のサイズによって変化)、
   // 注視点の位置は x = 320.0f, y = 240.0f, z = 1.0f
	// カメラの上方向は x = 0.0f, y = 1.0f, z = 0.0f
	// 右上位置からZ軸のプラス方向を見るようなカメラ
}
Camera::~Camera()
{
}
void Camera::Init(Player*player)
{

	player_ = player;
	// カメラの初期位置
	pos_ = DERFAULT_POS;
	// カメラの初期角度
	angles_ = { AsoUtility::Deg2RadF(9.5f),0.0f,0.0f };
}
void Camera::Update(void)
{
	
	
}
void Camera::SetBeforeDraw(void)
{
	// クリップ距離を設定する(SetDrawScreenでリセットされる)
	SetCameraNearFar(VIEW_NEAR, VIEW_FAR);
	switch (mode_)
	{
	case Camera::MODE::FIXED_POINT:
		SetBeforeDrawFixedPoint();
		break;
	case Camera::MODE::FREE:
		SetBeforeDrawFree();
		break;
	case Camera::MODE::FOLLOW:
		SetBeforeDrawFollow();
		break;
	}
	// カメラの設定(位置と角度による制御)
	SetCameraPositionAndAngle(
		pos_,
		angles_.x,
		angles_.y,
		angles_.z
	);
	// DXライブラリのカメラとEffekseerのカメラを同期する
	Effekseer_Sync3DSetting();
}
void Camera::DrawDebug(void)
{
	DrawFormatString(
		0, 0, 0x000000, "カメラ座標：(%.2f, %.2f, %.2f)",
		pos_.x, pos_.y, pos_.z);
	DrawFormatString(
		0, 20, 0x000000, "カメラ角度：(%.2f, %.2f, %.2f)",
		angles_.x * 180.0f / DX_PI_F,
		angles_.y * 180.0f / DX_PI_F,
		angles_.z * 180.0f / DX_PI_F);
}
void Camera::Release(void)
{
}

void Camera::ChangeMode(MODE mode)
{
	//カメラモードの変更
	mode_ = mode;
	// 変更時の初期化処理
	switch (mode_)
	{
	case Camera::MODE::FIXED_POINT:
		break;
	case Camera::MODE::FREE:
		break;
	case Camera::MODE::FOLLOW:
		break;
	}
}

VECTOR Camera::GetPos()
{
	return pos_;
}

VECTOR Camera::GetAngles()
{
	return angles_;
}

void Camera::SetBeforeDrawFixedPoint(void)
{
	
	// カメラの設定(位置と角度による制御)
	SetCameraPositionAndAngle(
		pos_,
		angles_.x,
		angles_.y,
		angles_.z
	);
}

void Camera::SetBeforeDrawFree(void)
{
	MoveXYZDirection();
	MoveXYZDirectionPad();
	// カメラの設定(位置と角度による制御)
	SetCameraPositionAndAngle(
		pos_,
		angles_.x,
		angles_.y,
		angles_.z
	);
}


void Camera::SetBeforeDrawFollow(void)
{
	auto& ins = InputManager::GetInstance();
	if (GetJoypadNum() == 0)
	{
		// 方向回転によるXYZの移動
		MoveXYZDirection();
	}
	else
	{
		// 方向回転によるXYZの移動(ゲームパッド)
		MoveXYZDirectionPad();
	}
	// 注視点の移動
	//VECTOR followPos = follow_->GetPos();
	//targetPos_ = followPos;
	// カメラの移動
	// カメラの回転行列を作成
	MATRIX mat = MGetIdent();
	//mat = MMult(mat, MGetRotX(angles_.x));
	mat = MMult(mat, MGetRotY(angles_.y));
	//mat = MMult(mat, MGetRotZ(angles_.z));

	// 注視点の移動
	VECTOR followPos = player_->GetPos();
	VECTOR targetLocalRotPos = VTransform(FOLLOW_TARGET_LOCAL_POS, mat);
	targetPos_ = VAdd(followPos, targetLocalRotPos);
	// カメラの移動
	// 相対座標を回転させて、回転後の相対座標を取得する
	VECTOR cameraLocalRotPos = VTransform(FOLLOW_CAMERA_LOCAL_POS, mat);
	// 相対座標からワールド座標に直して、カメラ座標とする
	pos_ = VAdd(followPos, cameraLocalRotPos);



	/* //相対座標を回転させて、回転後の相対座標を取得する
	VECTOR localRotPos = VTransform(FOLLOW_LOCAL_POS, mat);
	 相対座標からワールド座標に直して、カメラ座標とする
	pos_ = VAdd(followPos, localRotPos);*/

	// カメラの上方向を計算
	VECTOR up = VTransform(AsoUtility::DIR_U, mat);
	// カメラの設定(位置と注視点による制御)
	SetCameraPositionAndTargetAndUpVec(
		pos_,
		targetPos_,
		up
	);
}
const VECTOR& Camera::GetTargetPos(void) const
{
	return targetPos_;
}
void Camera::MoveXYZDirection(void)
{
	auto& ins = InputManager::GetInstance();
	// 矢印キーでカメラの角度を変える
	float rotPow = 1.0f * DX_PI_F / 180.0f;

	if (GetJoypadNum() == 0)
	{
		if (ins.IsNew(KEY_INPUT_DOWN)) { angles_.x += rotPow; }
		if (ins.IsNew(KEY_INPUT_UP)) { angles_.x -= rotPow; }
		if (ins.IsNew(KEY_INPUT_RIGHT)) { angles_.y += rotPow; }
		if (ins.IsNew(KEY_INPUT_LEFT)) { angles_.y -= rotPow; }
	}


	// WASDでカメラを移動させる
	const float movePow = 3.0f;
	VECTOR dir = AsoUtility::VECTOR_ZERO;
	if (ins.IsNew(KEY_INPUT_W)) { dir = { 0.0f, 0.0f, 1.0f }; }
	if (ins.IsNew(KEY_INPUT_A)) { dir = { -1.0f, 0.0f, 0.0f }; }
	if (ins.IsNew(KEY_INPUT_S)) { dir = { 0.0f, 0.0f, -1.0f }; }
	if (ins.IsNew(KEY_INPUT_D)) { dir = { 1.0f, 0.0f, 0.0f }; }

	if (!AsoUtility::EqualsVZero(dir))
	{
		// XYZの回転行列
	   // XZ平面移動にする場合は、XZの回転を考慮しないようにする
		MATRIX mat = MGetIdent();
		//mat = MMult(mat, MGetRotX(angles_.x));
		mat = MMult(mat, MGetRotY(angles_.y));
		//mat = MMult(mat, MGetRotZ(angles_.z));
		// 回転行列を使用して、ベクトルを回転させる
		VECTOR moveDir = VTransform(dir, mat);
		// 方向×スピードで移動量を作って、座標に足して移動
		pos_ = VAdd(pos_, VScale(moveDir, movePow));
	}
}

void Camera::MoveXYZDirectionPad(void)
{
	auto& ins = InputManager::GetInstance();
	// 矢印キーでカメラの角度を変える
	float rotPow = 3.0f * DX_PI_F / 180.0f;

	// 接続されているゲームパッド１の情報を取得
	InputManager::JOYPAD_IN_STATE padState =
		ins.GetJPadInputState(InputManager::JOYPAD_NO::PAD1);
	// アナログキーの入力値から方向を取得
	// アナログキーの入力値から方向を取得
	VECTOR dir = ins.GetDirectionXZAKey(padState.AKeyRX, padState.AKeyRY);

	angles_.y += dir.x * rotPow;
	//angles_.x += dir.z * rotPow;
	//角度限界
	if (angles_.x < -AsoUtility::Deg2RadF(30.0f)) { angles_.x = -AsoUtility::Deg2RadF(30.0f); }
	if (angles_.x > AsoUtility::Deg2RadF(50.0f)) { angles_.x = AsoUtility::Deg2RadF(50.0f); }
}