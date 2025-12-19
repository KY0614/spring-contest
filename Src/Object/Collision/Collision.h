#pragma once

class Player;
class EnemyManager;
class EnemyBase;
class ShotBase;
class GameScene;
class Stage;


class Collision
{
public:

	static constexpr int RIBAS_DIR = 30;

	Collision();
	~Collision();
	void Init(Player*player, EnemyManager* enemyManager,GameScene*game,Stage*satge);
	void Update(void);
	bool HitSphere(VECTOR pos1, float radius1, VECTOR pos2, float radius2);
	void Puss(VECTOR& pos1, float radius1, VECTOR& pos2, float radius2);
	void StageStop(VECTOR pos1, VECTOR pos2, float radius2);

private:

	Player* player_;
	EnemyManager* enemyManager_;
	std::vector<EnemyBase*> enemys_;
	std::vector<ShotBase*> shots_;
	GameScene* game_;
	Stage* stage_;

	int noDamageSE_;
	int DamageSE_;
	int HitSE_;

	int ribasDir_;

};

