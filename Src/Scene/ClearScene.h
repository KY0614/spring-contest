#pragma once

#include <vector>
#include "SceneBase.h"

class Timer;
class AnimationController;

class ClearScene : public SceneBase
{
public:

	enum class ANIM_TYPE 
	{
		CLEAR,
		MAX,
	};

	static constexpr int MAX_COUNT = 5;
	// コンストラクタ
	ClearScene(Timer*timer);

	// デストラクタ
	~ClearScene(void);

	void Init(void) override;
	void Update(void) override;
	void Draw(void) override;
	
private:
	int count_;
	int modelid_;
	VECTOR pos_;
	VECTOR rot_;
	VECTOR localrot_;

	ANIM_TYPE animType_;


	Timer* timer_;
	AnimationController* animationController_;
};

