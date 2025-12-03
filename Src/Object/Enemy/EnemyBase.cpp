
#include <math.h>
#include "../../Application.h"
#include "../../Utility/AsoUtility.h"
#include "../../Utility/MatrixUtility.h"
#include "../../Manager/InputManager.h"
#include "../../Manager/SceneManager.h"
#include "../Common/AnimationController.h"
#include "../Player/Player.h"
#include "../Shot/ShotStraight.h"
//#include "../Shot/ShotRock.h"
#include "../Shot/ShotBase.h"
#include "EnemyBase.h"

EnemyBase::EnemyBase(void)
{
	
}

EnemyBase::~EnemyBase(void)
{
	
}

void EnemyBase::Init(TYPE type, int baseModelId, int baseAttackEffectModelId, Player* player)
{
	// エネミー種別
	type_ = type;
	// プレイヤーポインタの設定
	player_ = player;
	// モデルのロード
	modelId_ = MV1DuplicateModel(baseModelId);

	// エフェクトモデルID
	baseAttackEffectModelId_ = baseAttackEffectModelId;

	// アニメーションの設定
	animationController_ = new AnimationController(modelId_);
	for (int i = 0; i < static_cast<int>(ANIM_TYPE::MAX); i++)
	{
		animationController_->AddInFbx(i, 30.0f, i);
	}
	// アニメーションの再生
	animationController_->Play(static_cast<int>(ANIM_TYPE::IDLE));

	stanCnt_ = 0;

	isHit_ = false;

	//パラメータ設定
	SetParam();

	// モデルの初期位置
	SetSpaenPos();
	// モデルの初期角度
	localAngles_ = { 0.0f,AsoUtility::Deg2RadF(180.0f),0.0f };
	angles_ = { 0.0f,AsoUtility::Deg2RadF(0.0f),0.0f };
	MV1SetRotationMatrix(modelId_, MatrixUtility::Multiplication(localAngles_, angles_));

	// 初期状態
	ChangeState(STATE::STANDBY);

	// モデルの座標設定
	MV1SetPosition(modelId_, pos_);
	// モデルの自己発光色設定
	MV1SetMaterialEmiColor(modelId_, 0, COLOR_EMI_DEFAULT);

	
}

void EnemyBase::Update(void)
{


	switch (state_)
	{
	case EnemyBase::STATE::STANDBY:
		UpdateStandby();
		break;
	case EnemyBase::STATE::ATTACK:
		UpdateAttack();
		break;
	case EnemyBase::STATE::STAN:
		UpdateStan();
		break;
	case EnemyBase::STATE::HIT_REACT:
		UpdateHitReact();
		break;
	case EnemyBase::STATE::DEAD_REACT:
		UpdateDeadReact();
		break;
	case EnemyBase::STATE::END:
		UpdateEnd();
		break;
	}

	VECTOR localPos = { 0.0f, 80.0f, 120 };
	attackPos_ = VAdd(pos_, VTransform(localPos, MatrixUtility::Multiplication(localAngles_, angles_)));

	UpdateShot();
	animationController_->Update();
}

void EnemyBase::Draw(void)
{
	if (isAlive_)
	{

		bool isTrans = false;
		if (invCnt_ > 0)
		{
			if (invCnt_ / 5 % 2 == 0)
			{
				isTrans = true;
			}
		}
		if (isTrans)
		{
			MV1SetMaterialEmiColor(modelId_, 0, { 0.0f,0.0f,0.0f });
		}
		else
		{

			MV1SetMaterialEmiColor(modelId_, 0, COLOR_EMI_DEFAULT);
		}
	}
	switch (state_)
	{
	case EnemyBase::STATE::STANDBY:
		DrawStandby();
		break;
	case EnemyBase::STATE::ATTACK:
		DrawAttack();
		break;
	case EnemyBase::STATE::HIT_REACT:
		DrawHitReact();
		break;
	case EnemyBase::STATE::STAN:
		DrawStan();
		break;
	case EnemyBase::STATE::DEAD_REACT:
		DrawDeadReact();
		break;
	case EnemyBase::STATE::END:
		DrawEnd();
		break;
	}
	DrawShot();
#ifdef _DEBUG
	// デバッグ用衝突判定
	DrawSphere3D(pos_, collisionRadius_, 10.0f, 0x0000FF, 0x0000FF, false);
#endif // _DEBUG
}



void EnemyBase::ProcessMove(void)
{
	
	// 敵の移動量
	VECTOR movePos = VScale(moveDir_, moveSpeed_);
	// 敵の移動
	pos_ = VAdd(pos_, movePos);
}

void EnemyBase::LookPlayer(void)
{
	if (player_)
	{
		// プレイヤーの位置を取得
		VECTOR playerPos = player_->GetPos();
		// プレイヤーの位置に向かう方向を計算
		moveDir_ = VSub(playerPos, pos_);
		moveDir_.y = 0.0f;
	}
	else
	{
		moveDir_ = { 0.0f, 0.0f, 0.0f }; // プレイヤーがいない場合は移動しない
	}
	moveDir_ = VNorm(moveDir_);

	angles_.y = atan2(moveDir_.x, moveDir_.z) + DX_PI_F;
	// 角度の設定
	MV1SetRotationMatrix(modelId_, MatrixUtility::Multiplication(localAngles_, angles_));
	MV1SetScale(modelId_, scales_);
}

void EnemyBase::Move()
{
	pos_ = VAdd(pos_, VScale(moveDir_, SPEED_MOVE));
	MV1SetPosition(modelId_, pos_);
}

void EnemyBase::AttackMove(void)
{
	pos_ = VAdd(pos_, VScale(moveDir_, SPEED_MOVE*3));
	MV1SetPosition(modelId_, pos_);
}

void EnemyBase::SetSpaenPos(void)
{
	//半径をとる
	float radius = 2000.0f;

	float spaenRadius = radius * spaen_;

	//中心座標を取る
	VECTOR centerPos = { 0.0f,0.0f,0.0f };



	float degree = GetRand(360);
	float radian = AsoUtility::Deg2RadF(degree);

	float dirX = sinf(radian);
	float dirZ = cosf(radian);
	VECTOR dir = { dirX,0.0f,dirZ };



	VECTOR vec = VScale(dir, spaenRadius);



	VECTOR pos = VAdd(centerPos, vec);

	pos_ = pos;

	MV1SetPosition(modelId_, pos_);
}

void EnemyBase::ChangeState(STATE state)
{
	state_ = state;

	switch (state_)
	{
	case EnemyBase::STATE::STANDBY:
		ChangeStandby();
		break;
	case EnemyBase::STATE::ATTACK:
		ChangeAttack();
		break;
	case EnemyBase::STATE::STAN:
		ChangeStan();
		break;

	case EnemyBase::STATE::HIT_REACT:
		ChangeHitReact();
		break;
	case EnemyBase::STATE::DEAD_REACT:
		ChangeDeadReact();
		break;
	case EnemyBase::STATE::END:
		ChangeEnd();
		break;
	}
}

VECTOR EnemyBase::GetPos(void)
{
	return pos_;
}

void EnemyBase::SetPos(VECTOR pos)
{
	pos_ = pos;
}

VECTOR EnemyBase::GetAttackPos(void)
{
	return attackPos_;
}

float EnemyBase::GetAttackRadius(void)
{
	return attackRadius_;
}

float EnemyBase::GetRadius(void)
{
	return 0.0f;
}

bool EnemyBase::GetIsAlaive(void)
{
	return collisionRadius_;
}

void EnemyBase::SetIsAlive(bool is)
{
}

int EnemyBase::GetInvCnt(void)
{
	return 0;
}

void EnemyBase::SetInvCnt(int cnt)
{
}

void EnemyBase::Damage(int damage)
{
	isAlive_ = false;
	hp_ -= damage;
	if (hp_ < 0)
	{
		hp_ = -1;
	}
	if (hp_ == 0)
	{
		ChangeState(STATE::DEAD_REACT);
	}
	if (hp_ > 0)
	{
		ChangeState(STATE::HIT_REACT);
	}
}

bool EnemyBase::IsCollisionState(void)
{
	if (state_ == STATE::STANDBY || state_ == STATE::ATTACK|| state_ == STATE::STAN)
	{
		return true;
	}
	return false;
}

std::vector<ShotBase*> EnemyBase::GetShot()
{
	return shots_;
}

EnemyBase::STATE EnemyBase::GetState()
{
	return state_;
}

void EnemyBase::UpdateShot(void)
{
	for (ShotBase* shot : shots_)
	{
		shot->Update();
	}
}

void EnemyBase::DrawShot(void)
{
	for (ShotBase* shot : shots_)
	{
		shot->Draw();
	}
}

ShotBase* EnemyBase::GetValidShot(void)
{
	size_t size = shots_.size();
	for (int i = 0; i < size; i++)
	{
		// 未使用(生存していない)
		if (!shots_[i]->IsAlive())
		{
			return shots_[i];
		}
	}
	// 新しい弾のインスタンスを生成する
	ShotBase* shot = new ShotStraight(
		ShotBase::TYPE::STRAIGHT, baseAttackEffectModelId_);


	// 可変長配列に追加
	shots_.push_back(shot);

	return shot;
}

ShotBase* EnemyBase::GetRockShot(void)
{
	return nullptr;
}

void EnemyBase::SetParam(void)
{
}

void EnemyBase::ChangeStandby(void)
{
	animationController_->Play(static_cast<int>(ANIM_TYPE::IDLE));
}

void EnemyBase::ChangeAttack(void)
{
	animationController_->Play(static_cast<int>(ANIM_TYPE::ATTACK), false);
	// 攻撃間隔用のカウンタをリセット
	cntAttack_ = 0;
	// 弾を生成
	if (type_ == TYPE::ENEMYM|| type_ == TYPE::ENEMYR)
	{

		ShotBase* shot = GetValidShot();
		// 弾を生成

		VECTOR localPos = { 0.0f,0.0f,-200.0f };

		VECTOR shotPos = VTransform(localPos, MatrixUtility::GetMatrixRotateXYZ(angles_));
		shotPos_ = VAdd(pos_, shotPos);

		shot->CreateShot(shotPos_, moveDir_);
	}
}

void EnemyBase::ChangeStan(void)
{
}

void EnemyBase::ChangeHitReact()
{
}

void EnemyBase::ChangeDeadReact()
{
	animationController_->Play(static_cast<int>(ANIM_TYPE::DEATH), false);
}

void EnemyBase::ChangeEnd()
{
}

void EnemyBase::UpdateStandby(void)
{
	LookPlayer();
	// 移動処理
	ProcessMove();
}

void EnemyBase::UpdateAttack(void)
{
	ChangeState(STATE::STANDBY);
}

void EnemyBase::UpdateStan(void)
{
	stanCnt_++;
	if (stanCnt_ <= 600)
	{
		return;
	}
	else
	{
		stanCnt_ = 0;
		ChangeState(STATE::STANDBY);
	}
}

void EnemyBase::UpdateHitReact()
{
	if (isAlive_ == false)
	{
		isAlive_ = true;
		// 無敵時間
		invCnt_ = 40;
	}
	//無敵時間処理
	if (invCnt_ > 0)
	{
		invCnt_--;
	}
	if (invCnt_ <= 0)
	{
		ChangeState(STATE::STANDBY);
		return;
	}
}

void EnemyBase::UpdateDeadReact()
{
	/*if (animationController_->IsEnd())
	{
		ChangeState(STATE::END);
	}*/
}

void EnemyBase::UpdateEnd()
{
}

void EnemyBase::DrawStandby(void)
{
	// モデルの描画
	MV1DrawModel(modelId_);
}

void EnemyBase::DrawAttack(void)
{
	// モデルの描画
	MV1DrawModel(modelId_);
	//DrawSphere3D(attackPos_, attackRadius_, 16, 0xff0000, 0xff0000, false);
}

void EnemyBase::DrawStan(void)
{
	// モデルの描画
	MV1DrawModel(modelId_);
}

void EnemyBase::DrawHitReact()
{
	// モデルの描画
	MV1DrawModel(modelId_);
}

void EnemyBase::DrawDeadReact()
{
	MV1DrawModel(modelId_);
}

void EnemyBase::DrawEnd()
{
	// モデルの描画
	//MV1DrawModel(modelId_);
}



