#include "../Common/AnimationController.h"
#include "EnemyR.h"

EnemyR::EnemyR(void)
{
}

EnemyR::~EnemyR(void)
{
}

void EnemyR::SetParam(void)
{
	hp_ = 1;
	scales_ = { 0.5f, 0.5f, 0.5f };
	moveSpeed_ = 0.0f;
	spaen_ = 0.8f;

	collisionRadius_ = 40.0f;
	isAlive_ = true;
}

void EnemyR::UpdateStandby(void)
{
	LookPlayer();

	cntAttack_++;
	if (cntAttack_ > TERM_ATTACK)
	{
		cntAttack_ = 0;
		ChangeState(STATE::ATTACK);

	}
}
