#pragma once
#include <vector>

class EnemyBase;
class Player;
class GameScene;

class EnemyManager
{
public:

	static constexpr int MAX_W = 2;
	static constexpr int MAX_DILAY = 30;



	// 敵の生成ウェーブ
	enum class WAVE
	{
		WAVE01,
		WAVE02,
		WAVE03,
		END
	};

	// コンストラクタ
	EnemyManager(Player* player, GameScene* gameScene);
	// デストラクタ
	~EnemyManager(void);
	void Init(void);
	void Update(void);
	void Draw(void);
	void Release(void);

	void WAVE01();
	void WAVE02();
	void WAVE03();
	void END();

	void ChangeWave(WAVE wave);

	std::vector<EnemyBase*> GetEnemys();

private:

	int sponCuntW_;

	int sponDilayM_;

	int sponR_;
	int sponDilayR_;
	
	int sponU_;
	int sponDilayU_;

	WAVE wave_;

	int waveCount_;

	

	// エネミー用のモデルハンドルID
	std::vector<int> enemyModelIds_;

	// 攻撃エフェクト用のモデルハンドルID
	std::vector<int> attackEffectModelIds_;

	// エネミー
	std::vector<EnemyBase*> enemys_;
	// プレイヤーのポインタ
	Player* player_;
	//ゲームシーンのポインタ
	GameScene* gameScene_;


};