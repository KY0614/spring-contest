//#pragma once
#include "SceneBase.h"
#include "../Common/Vector2.h"
#include <vector>

class EnemyManager;
class Collision;
class Player;
class Camera;
class Grid;
class Timer;
class Stage;

class GameScene : public SceneBase
{

public:
	static constexpr int MAX_COUNT = 5;
	static constexpr float MAX_SLOW_TIME = 600.0f;
	static constexpr float MAX_SLOW_TIME_P = 30.0f;
	static constexpr float MAX_STOP_TIME = 15.0f;
	static constexpr int MAX_SLOW_COUNT = 3;

	// コンストラクタ
	GameScene(Timer*timer);

	// デストラクタ
	~GameScene(void);

	void Init(void) override;
	void Update(void) override;
	void Draw(void) override;

	void SetIsSlow(bool isSlow);
	bool GetIsSlow(void);

	bool GetIsSlowP(void);

	bool GetIsStop(void);
	void SetIsStop(bool isStop);

private:


	//カメラ
	Camera* camera_;

	//グリッド線
	Grid* grid_;

	//プレイヤー
	Player* player_;

	//敵マネージャー
	EnemyManager* enemyManager_;

	//当たり判定
	Collision* collision_;

	//タイマー
	Timer* timer_;

	//ステージ
	Stage* stage_;

	int count_;

	float slowTime_;
	int slowCount_;
	bool isSlow_;
	bool isSlowP_;
	float stopTime_;
	bool isStop_;
};
