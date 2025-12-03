#pragma once
#include "EnemyBase.h"

class EnemyR:public EnemyBase
{
public:
	static constexpr int TERM_ATTACK = 120.0f;
	// コンストラクタ
	EnemyR(void);
	// デストラクタ
	~EnemyR(void);
private:

protected:
	// パラメータ設定
	void SetParam(void) override;

	void UpdateStandby(void) override;
};

