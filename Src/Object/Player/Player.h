#pragma once

class Camera;
class GameScene;

class Player
{
public:
	//ステートパターン=========================================================
	enum class STATE
	{
		STANDBY,
		AVOID,
		GUARD,
		PARRY,
		ATTACK,
		DAMAGE,
		DEAD,

	};


	
	//ナンバー=========================================================

	static constexpr int ONE = 1;
	static constexpr int TWO = 2;
	static constexpr int THREE = 3;
	static constexpr int FOUR = 4;
	static constexpr int FIVE = 5;
	static constexpr int SIX = 6;
	static constexpr int SEVEN = 7;
	static constexpr int EIGHT = 8;
	static constexpr int NINE = 9;
	static constexpr int TEN = 10;

	//定数=========================================================
	static constexpr float MOVE_SPEED = 10.0f; //移動速度
	static constexpr float MOVE_SPEED_HALF = 5.0f; //移動速度半分
	static constexpr float AVOID_SPEED = 30.0f; //回避速度

	static constexpr float AVOID_ROLL = 20.0f;//回避回転量
	static constexpr float AVOID_MAX_ROLL = 360.0f;//回避最大回転量

	static constexpr float LOST_HP = 10.0f;//HP消費量
	static constexpr float LOST_SP = 30.0f;//SP消費量
	static constexpr float LOST_GP = 20.0f;//GP消費量


	static constexpr float MAX_HP = 100; //最大体力
	static constexpr float MAX_SP = 90; //最大スタミナ
	static constexpr float MAX_GP = 100; //最大ガード
	static constexpr float MAX_PARRY_COUNT = 5.0f; //カウントの最大値
	static constexpr float MAX_AVOID_DELAY = 3.0f;//回避遅延
	static constexpr float MAX_ATTACK_COUNT = 10.0f;//攻撃カウントの最大値
	
	static constexpr float DAMAGE_RADIUS = 60.0f;//ダメージ時の半径
	static constexpr float AVOID_RADIUS = 80.0f;//回避時の半径
	static constexpr float GUARD_RADIUS = 100.0f;//ガード時の半径
	static constexpr float PARRY_RADIUS = 120.0f;//パリィ時の半径
	static constexpr float ATTACK_RADIUS = 60.0f;//攻撃範囲

	static constexpr float MAX_STOP_DIR = 30.0f;

	// 標準の自己発光色
	static constexpr COLOR_F COLOR_EMI_DEFAULT = { 0.5f, 0.5f, 0.5f, 0.5f };
private:

	int model_;//モデル
	VECTOR pos_;//位置
	VECTOR attackPos_;//攻撃位置
	VECTOR rot_;//回転
	VECTOR localrot_;//ローカル回転
	VECTOR scale_;//大きさ
	STATE state_;//状態
	float hp_;//体力
	float sp_;//スタミナ
	float gp_;//ガード
	VECTOR moveDir_;//移動方向
	bool isAlive_;//生存フラグ
	int invCnt_;//無敵カウント
	float parryCount_;//パリィ受付時間
	float attackCnt_;//攻撃受付時間
	bool trgAvoid_;//回避トリガー
	float avoidDelay_;//回避再使用時間
	float collisionRadiusGS_;//当たり判定用半径
	float collisionRadiusH_;//当たり判定用半径
	float attackRange_;//攻撃範囲


	//SE
	int avoidSE_;
	int parrySE_;
	int guardSE_;
	int slouSE_;

	int stopDir_;

	Camera* camera_;

	GameScene* game_;

public:
	Player();
	~Player();
	//初期化
	void Init(Camera*camera,GameScene*game);
	//ステイトチェンジ
	void ChangeStandby();
	void ChangeAvoid();
	void ChangeGuard();
	void ChangeParry();
	void ChangeAttack();
	void ChangeDamage();
	void ChangeDead();

	//アプデ
	void Update();
	//ステイトアプデ
	void StandbyUpdate();
	void AvoidUpdate();
	void GuardUpdate();
	void ParryUpdate();
	void AttackUpdate();
	void DamageUpdate();
	void DeadUpdate();

	//ドロー
	void Draw();
	//ステイトドロー
	void StandbyDraw();
	void AvoidDraw();
	void GuardDraw();
	void ParryDraw();
	void AttackDraw();
	void DamageDraw();
	void DeadDraw();

	//ステイトチェンジ関数
	void ChangeState(STATE state);

	//機能
	void Move(float speed);
	
	bool IsCollisionState(void);
	void HitGS(bool is);
	void HitH(bool is);


	//ゲッターセッター
	VECTOR GetPos();
	void SetPos(VECTOR pos);
	VECTOR GetAttackPos();

	VECTOR GetRot();
	int GetHp();
	void SetHp(int hp);
	int GetSp();
	void SetSp(int sp);
	int GetGp();
	void SetGp(int gp);
	STATE GetState();
	float GetCollisionRadiusGS();
	float GetCollisionRadiusH();
	float GetAttackRange();
	bool GetSlow();
	bool GetStop();


	void DelayRotate();
};

