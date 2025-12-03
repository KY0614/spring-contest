#include <DxLib.h>
#include "../../Utility/AsoUtility.h"
#include "../../Utility/MatrixUtility.h"
#include "../../Manager/InputManager.h"
#include "../../Manager/ResourceManager.h"
#include "../../Manager/SoundManager.h"
#include "../../Scene/GameScene.h"
#include "../Camera/Camera.h"
#include "Player.h"

Player::Player()
{

}
Player::~Player()
{

}
// 初期化
void Player::Init(Camera* camera, GameScene* game)
{
	game_ = game;
	camera_ = camera;

	// 初期ステイト
	state_ = STATE::STANDBY;
	ChangeState(state_);
	//モデル読み込み
	// 画像の読み込み
	ResourceManager& res = ResourceManager::GetInstance(); // リソースマネージャのインスタンス取得

	
	model_ = res.Load(ResourceManager::SRC::PLAYER).handleId_;

	avoidSE_ = res.Load(ResourceManager::SRC::AVOID).handleId_;
	parrySE_ = res.Load(ResourceManager::SRC::PARRY).handleId_;
	guardSE_ = res.Load(ResourceManager::SRC::GUARD).handleId_;
	slouSE_ = res.Load(ResourceManager::SRC::SLOU).handleId_;

	// 初期位置
	pos_ = { 0.0f, 50.0f, 0.0f };
	
	// 初期回転
	rot_ = { 0.0f, 0.0f, 0.0f };

	localrot_ = { 0.0f, AsoUtility::Deg2RadF(180.0f), 0.0f};
	// 初期大きさ
	scale_ = { 0.5f, 0.5f, 0.5f };

	// 初期体力
	hp_ = MAX_HP;
	// 初期スタミナ
	sp_ = MAX_SP;
	// 初期ガード
	gp_ = MAX_GP;

	trgAvoid_ = false;

	// 生存フラグ
	isAlive_ = true;
	// 無敵カウント
	invCnt_ = 0;

	attackCnt_ = 0.0f;


	// モデルの自己発光色設定
	MV1SetMaterialEmiColor(model_, 0, COLOR_EMI_DEFAULT);

	MV1SetPosition(model_, pos_);
	MV1SetRotationMatrix(model_, MatrixUtility::Multiplication(localrot_, rot_));
	MV1SetScale(model_, scale_);

}
// ステイトチェンジ
void Player::ChangeStandby()
{
}

void Player::ChangeAvoid()
{
	
}
void Player::ChangeGuard()
{
}
void Player::ChangeParry()
{
	parryCount_ = 0.0f;
}
void Player::ChangeAttack()
{
}
void Player::ChangeDamage()
{
	
}
void Player::ChangeDead()
{
}
// アプデ
void Player::Update()
{
	
	switch (state_)
	{
	case Player::STATE::STANDBY:
		StandbyUpdate();
		break;
	case Player::STATE::AVOID:
		AvoidUpdate();
		break;
	case Player::STATE::GUARD:
		GuardUpdate();
		break;
	case Player::STATE::PARRY:
		ParryUpdate();
		break;
	case Player::STATE::ATTACK:
		AttackUpdate();
		break;

	case Player::STATE::DAMAGE:
		DamageUpdate();
		break;
	case Player::STATE::DEAD:
		DeadUpdate();
		break;
	default:
		break;
	}
	MV1SetPosition(model_, pos_);
	VECTOR localPos = { 0.0f, 0.0f, -ATTACK_RADIUS * 2 };
	attackPos_ = VAdd(pos_, VTransform(localPos, MatrixUtility::Multiplication(localrot_, rot_)));
	// 行列の合成(子, 親と指定すると親⇒子の順に適用される)
	MATRIX mat = MatrixUtility::Multiplication(localrot_, rot_);
	// 回転行列をモデルに反映
	MV1SetRotationMatrix(model_, mat);

	
}
// ステイトアプデ
void Player::StandbyUpdate()
{
	
	auto& ins = InputManager::GetInstance();
	Move(MOVE_SPEED);
	DelayRotate();
	if (sp_ > LOST_SP)
	{
		
		if (ins.IsTrgDown(KEY_INPUT_LSHIFT)|| ins.IsPadBtnTrgDown(InputManager::JOYPAD_NO::PAD1, InputManager::JOYPAD_BTN::DOWN))
		{
			
			
			
			trgAvoid_ = true;
			auto& ins = SoundManager::GetInstance();
			ins.PlaySE(avoidSE_);
			
		}
		if (trgAvoid_)
		{
			avoidDelay_++;
		}
		if (avoidDelay_ > MAX_AVOID_DELAY)
		{
			sp_ -= LOST_SP;
			trgAvoid_ = false;
			avoidDelay_ = 0.0f;
			ChangeState(STATE::AVOID);
		}
	}
	// ガード
	if (gp_ > 10.0f)
	{
		if (ins.IsTrgDown(KEY_INPUT_SPACE))
		{
			ChangeState(STATE::GUARD);
		}
		if (ins.IsPadBtnTrgDown(InputManager::JOYPAD_NO::PAD1, InputManager::JOYPAD_BTN::R_TRIGGER))
		{
			ChangeState(STATE::GUARD);
		}
	}
	if (sp_ < MAX_SP)
	{
		sp_ += 1.0f;
	}
	if (gp_ < MAX_GP)
	{
		gp_ += 1.0f;
	}

	if (ins.IsTrgDown(KEY_INPUT_K) || ins.IsPadBtnTrgDown(InputManager::JOYPAD_NO::PAD1, InputManager::JOYPAD_BTN::RIGHT))
	{
		ChangeState(STATE::ATTACK);
	}

}

void Player::AvoidUpdate()
{
	rot_.x += AsoUtility::Deg2RadF(AVOID_ROLL);
	Move(AVOID_SPEED);
	DelayRotate();
	if (rot_.x >= AsoUtility::Deg2RadF(AVOID_MAX_ROLL))
	{
		rot_.x = 0.0f;
		ChangeState(STATE::STANDBY);
	}

}

	
void Player::GuardUpdate()
{
	auto& ins = InputManager::GetInstance();
	Move(MOVE_SPEED_HALF);
	DelayRotate();

	if (gp_ <= 0.0f)
	{
		ChangeState(STATE::STANDBY);
	}

	if (ins.IsTrgUp(KEY_INPUT_SPACE))
	{
		ChangeState(STATE::PARRY);
	}
	if (ins.IsPadBtnTrgUp(InputManager::JOYPAD_NO::PAD1, InputManager::JOYPAD_BTN::R_TRIGGER))
	{
		ChangeState(STATE::PARRY);
	}
}
void Player::ParryUpdate()
{
	parryCount_ += 0.5f;
	Move(MOVE_SPEED_HALF);
	DelayRotate();
	if (parryCount_ >= MAX_PARRY_COUNT)
	{
		ChangeState(STATE::STANDBY);
	}
	
}
void Player::AttackUpdate()
{
	
	attackCnt_ += 1.0f;
	if (attackCnt_ >= MAX_ATTACK_COUNT)
	{
		attackCnt_ = 0.0f;
		ChangeState(STATE::STANDBY);
	}
}
void Player::DamageUpdate()
{
	auto& ins = InputManager::GetInstance();
	Move(MOVE_SPEED);
	DelayRotate();
	if (sp_ > LOST_SP)
	{
		sp_ -= LOST_SP;
		if (ins.IsTrgDown(KEY_INPUT_LSHIFT) || ins.IsPadBtnTrgDown(InputManager::JOYPAD_NO::PAD1, InputManager::JOYPAD_BTN::DOWN))
		{
			Move(AVOID_SPEED);
		}
	}
	if (isAlive_ == false)
	{
		isAlive_ = true;
		// 無敵時間
		invCnt_ = 120;
	}
	invCnt_--;	
	if (invCnt_ < 0)
	{
		ChangeState(STATE::STANDBY);
	}
	
}
void Player::DeadUpdate()
{
}
// ドロー
void Player::Draw()
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
			MV1SetMaterialEmiColor(model_, 0, { 0.0f,0.0f,0.0f });
		}
		else
		{

			MV1SetMaterialEmiColor(model_, 0, COLOR_EMI_DEFAULT);
		}
	}
	switch (state_)
	{
	case Player::STATE::STANDBY:
		StandbyDraw();
		break;
	case Player::STATE::AVOID:
		AvoidDraw();
		break;
	case Player::STATE::GUARD:
		GuardDraw();
		break;
	case Player::STATE::PARRY:
		ParryDraw();
		break;
	case Player::STATE::ATTACK:
		AttackDraw();
		break;
	case Player::STATE::DAMAGE:
		DamageDraw();
		break;
	case Player::STATE::DEAD:
		DeadDraw();
		break;
	default:
		break;
	}
	float hpS = hp_ / MAX_HP;
	float hpDrawS = hpS * 200.0f;
	DrawBox(50, 70, 50 + hpDrawS, 100, 0xff0000, true);
	float spS = sp_ / MAX_SP;
	float spDrawS = spS * 200.0f;
	DrawBox(50, 110, 50 + spDrawS, 140, 0x00FF00, true);
	float gpS = gp_ / MAX_GP;
	float gpDrawS = gpS * 200.0f;
	DrawBox(50, 150, 50 + gpDrawS, 180, 0x0000FF, true);
	DrawBox(0, 70, 50, 180, 0x000000, true);
	SetFontSize(30);
	DrawString(10, 70, "HP", 0xffffff);
	DrawString(10, 110, "SP", 0xffffff);
	DrawString(10, 150, "GP", 0xffffff);
	SetFontSize(16);
}
// ステイトドロー
void Player::StandbyDraw()
{
	MV1DrawModel(model_);
#ifdef _DEBUG
	DrawSphere3D(pos_, DAMAGE_RADIUS, TEN + SIX, 0x0000ff, 0x0000ff, false);
#endif
	collisionRadiusH_ = DAMAGE_RADIUS;
}

void Player::AvoidDraw()
{
	MV1DrawModel(model_);
#ifdef _DEBUG
	DrawSphere3D(pos_, DAMAGE_RADIUS, TEN + SIX, 0x0000ff, 0x0000ff, false);
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255 / 2);
	DrawSphere3D(pos_, AVOID_RADIUS, TEN + SIX, 0x00ff00, 0x00ff00, true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
#endif
	collisionRadiusGS_ = AVOID_RADIUS;
}

void Player::GuardDraw()
{

	MV1DrawModel(model_);
#ifdef _DEBUG
	DrawSphere3D(pos_, DAMAGE_RADIUS, TEN + SIX, 0x0000ff, 0x0000ff, false);
#endif
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255 / 2);
	DrawSphere3D(pos_, GUARD_RADIUS, TEN+SIX, 0x0000ff, 0x0000ff, true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	collisionRadiusGS_ = GUARD_RADIUS;
	
}

void Player::ParryDraw()
{
	MV1DrawModel(model_);
#ifdef _DEBUG
	DrawSphere3D(pos_, DAMAGE_RADIUS, TEN + SIX, 0x0000ff, 0x0000ff, false);
#endif
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255 / 2);
	DrawSphere3D(pos_, PARRY_RADIUS, TEN + SIX, 0x0000ff, 0x0000ff, true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	collisionRadiusGS_ = PARRY_RADIUS;
	
}

void Player::AttackDraw()
{
	MV1DrawModel(model_);
#ifdef _DEBUG
	DrawSphere3D(pos_, DAMAGE_RADIUS, TEN + SIX, 0x0000ff, 0x0000ff, false);
#endif

	DrawSphere3D(attackPos_, ATTACK_RADIUS, TEN + SIX, 0xff0000, 0xff0000, true);
	
}

void Player::DamageDraw()
{
	
	MV1DrawModel(model_);
}

void Player::DeadDraw()
{
	MV1DrawModel(model_);
}
// ステイトチェンジ
void Player::ChangeState(STATE state)
{
	state_ = state;
	switch (state_)
	{
	case Player::STATE::STANDBY:
		ChangeStandby();
		break;
	case Player::STATE::AVOID:
		ChangeAvoid();
		break;
	case Player::STATE::GUARD:
		ChangeGuard();
		break;
	case Player::STATE::PARRY:
		ChangeParry();
		break;
	case Player::STATE::ATTACK:
		ChangeAttack();
		break;
	case Player::STATE::DAMAGE:
		ChangeDamage();
		break;
	case Player::STATE::DEAD:
		ChangeDead();
		break;
	default:
		break;
	}

	


}



//機能＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
void Player::Move(float speed)
{
	VECTOR camPos = camera_->GetPos();
	VECTOR camAngles = camera_->GetAngles();


	auto& ins = InputManager::GetInstance();
	VECTOR dir = AsoUtility::VECTOR_ZERO;

	// ゲームパッドが接続数で処理を分ける
	if (GetJoypadNum() == 0)
	{
		// WASDで移動する
		if (ins.IsNew(KEY_INPUT_W)) { dir = { 0.0f, 0.0f, 1.0f }; }
		if (ins.IsNew(KEY_INPUT_A)) { dir = { -1.0f, 0.0f, 0.0f }; }
		if (ins.IsNew(KEY_INPUT_S)) { dir = { 0.0f, 0.0f, -1.0f }; }
		if (ins.IsNew(KEY_INPUT_D)) { dir = { 1.0f, 0.0f, 0.0f }; }
	}
	else
	{
		// 接続されているゲームパッド１の情報を取得
		InputManager::JOYPAD_IN_STATE padState =
			ins.GetJPadInputState(InputManager::JOYPAD_NO::PAD1);
		// アナログキーの入力値から方向を取得
		dir = ins.GetDirectionXZAKey(padState.AKeyLX, padState.AKeyLY);
	}


	if (!AsoUtility::EqualsVZero(dir))
	{
		
		MATRIX mat = MGetIdent();
		
		mat = MMult(mat, MGetRotY(camAngles.y));
		// 回転行列を使用して、ベクトルを回転させる
		VECTOR moveDir = VTransform(dir, mat);

		// 回転行列を使用して、ベクトルを回転させる
		moveDir_ = VTransform(dir, mat);
		// 方向×スピードで移動量を作って、座標に足して移動
		pos_ = VAdd(pos_, VScale(moveDir_, speed));

		//animationController_->Play(static_cast<int>(ANIM_TYPE::WALK));


	}
	else
	{
		//animationController_->Play(static_cast<int>(ANIM_TYPE::IDLE));
	}

}

bool Player::IsCollisionState(void)
{
	// プレイヤーの状態が衝突判定を行う状態かどうか
	if (state_ == STATE::STANDBY || state_ == STATE::AVOID||state_==STATE::GUARD||state_==STATE::PARRY || state_ == STATE::ATTACK)
	{
		return true;
	}
	return false;
}

void Player::HitGS(bool is)
{
	bool isHit = false;
	isHit = is;
	if (isHit)
	{
		auto& ins = SoundManager::GetInstance();
		switch (state_)
		{
		case Player::STATE::AVOID:
			if (sp_ < 0.0f)
			{
				return;
			}
			ins.PlaySE(slouSE_);
			sp_ -= LOST_SP;
			game_->SetIsSlow(true);
			break;

		case Player::STATE::GUARD:
			gp_ -= LOST_GP;
			ins.PlaySE(guardSE_);
			break;

		case Player::STATE::PARRY:
			ins.PlaySE(parrySE_);
			gp_ += LOST_GP;
			if (gp_ > MAX_GP)
			{
				gp_ = MAX_GP;
			}
			break;
		}
		
	}

}

void Player::HitH(bool is)
{
	bool isHit = false;
	isHit = is;

	if (isHit)
	{
		hp_ -= LOST_HP;
	}
}


void Player::DelayRotate(void)
{
	// 移動方向から角度に変換する
	float goal = atan2f(moveDir_.x, moveDir_.z);
	// 常に最短経路で補間
	rot_.y = AsoUtility::LerpAngle(rot_.y, goal, 0.2f);
}

// ゲッターセッター＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
VECTOR Player::GetPos()
{
	return pos_;
}

void Player::SetPos(VECTOR pos)
{
	pos_ = pos;
}

VECTOR Player::GetAttackPos()
{
	return attackPos_;
}

VECTOR Player::GetRot()
{
	return attackPos_;
}


int Player::GetHp()
{
	return hp_;
}

void Player::SetHp(int hp)
{
	hp_ = hp;
}

int Player::GetSp()
{
	return sp_;
}

void Player::SetSp(int sp)
{
	sp_ = sp;
}

int Player::GetGp()
{
	return gp_;
}

void Player::SetGp(int gp)
{
	gp_ = gp;
}

Player::STATE Player::GetState()
{
	return state_;
}

float Player::GetCollisionRadiusGS()
{
	return collisionRadiusGS_;
}
float Player::GetCollisionRadiusH()
{
	return collisionRadiusH_;
}

float Player::GetAttackRange()
{
	return ATTACK_RADIUS;
}
