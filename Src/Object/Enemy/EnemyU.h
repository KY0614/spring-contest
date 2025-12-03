#pragma once

#include "EnemyBase.h"

class EnemyU: public EnemyBase
{
public:
	static constexpr int TERM_ATTACK = 120.0f;
	static constexpr int ATTACK_CNT_MAX = 120;
	// コンストラクタ
	EnemyU(void);
	// デストラクタ
	~EnemyU(void);
private:
	int termAttackCounter_ = 0;
	int termAttack_ = TERM_ATTACK;
	int attackCnt_ = 0;

protected:
	// パラメータ設定
	void SetParam(void) override;

	void UpdateStandby(void) override;
	void UpdateAttack(void) override;
};

