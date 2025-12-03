
#pragma once

#include <vector>
#include "SceneBase.h"

class Timer;

class  GameOvera : public SceneBase
{
public:
	static constexpr int MAX_COUNT = 5;
	// コンストラクタ
	GameOvera(Timer*timer);

	// デストラクタ
	~GameOvera(void);

	void Init(void) override;
	void Update(void) override;
	void Draw(void) override;
	

private:
	int count_;
	Timer* timer_;

};