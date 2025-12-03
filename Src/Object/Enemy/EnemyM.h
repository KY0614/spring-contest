#pragma once
#include "EnemyBase.h"
class EnemyM : public EnemyBase
{
public:
	static constexpr int TERM_ATTACK = 120.0f;
	// コンストラクタ
	EnemyM(void);
	// デストラクタ
	~EnemyM(void);
private:

protected:
	// パラメータ設定
	void SetParam(void) override;

	void UpdateStandby(void) override;
};
