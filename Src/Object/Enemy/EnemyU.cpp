#include <DxLib.h>
#include "../../Utility/MatrixUtility.h"
#include "../Common/AnimationController.h"
#include "EnemyU.h"

EnemyU::EnemyU(void)
{
}

EnemyU::~EnemyU(void)
{
}

void EnemyU::SetParam(void)
{
	hp_ = 1;
	scales_ = { 0.04f, 0.04f, 0.04f };
	moveSpeed_ = 0.0f;
	spaen_ = 0.8f;

	collisionRadius_ = 120.0f;
	isAlive_ = true;
}

void EnemyU::UpdateStandby(void)
{
	LookPlayer();
	Move();
	VECTOR localPos = { 0.0f, 80.0f, 120 };
	attackPos_ = VAdd(pos_, VTransform(localPos, MatrixUtility::Multiplication(localAngles_, angles_)));
	if (termAttackCounter_ < termAttack_)
	{
		termAttackCounter_++;
	}
	else
	{
		termAttackCounter_ = 0;
		animationController_->Play(static_cast<int>(ANIM_TYPE::ATTACK), false);
		ChangeState(STATE::ATTACK);
	}
	
}

void EnemyU::UpdateAttack(void)
{
	AttackMove();
	VECTOR localPos = { 0.0f, 80.0f, 120 };
	attackPos_ = VAdd(pos_, VTransform(localPos, MatrixUtility::Multiplication(localAngles_, angles_)));
	attackRadius_ = 30.0f;

	
	if (attackCnt_ < ATTACK_CNT_MAX)
	{
		attackCnt_++;
	}
	else
	{
		attackCnt_ = 0;
		ChangeState(STATE::STANDBY);
	}

}
