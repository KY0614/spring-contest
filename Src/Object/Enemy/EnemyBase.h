#pragma once
#include <vector>
#include <DxLib.h>

class AnimationController;
class Player;
class ShotBase;

class EnemyBase
{
public:


	static constexpr int ATTAC_DIR_M = 40;
	static constexpr int ATTAC_DIR_R = 80;

	static constexpr VECTOR M_SCL = { 0.2f,0.2f, 0.2f };
	static constexpr VECTOR R_SCL = { 0.4f,0.4f, 0.4f };

	static constexpr float M_RAD = 30.0f;
	static constexpr float R_RAD = 30.0f;


	// エネミー種別
	enum class TYPE
	{
		ENEMYM,
		ENEMYR,
		ENEMYU,
	};


	// アニメーションの種類
	enum class ANIM_TYPE
	{
		ATTACK,
		DEATH,
		IDLE,
		MAX,
	};
	enum class STATE
	{
		NONE,
		STANDBY,
		ATTACK,
		STAN,
		HIT_REACT,
		DEAD_REACT,
		END,
	};
	



	// モデルの大きさ
	static constexpr VECTOR SCALES = { 0.5f, 0.5f, 0.5f };
	// 初期位置
	static constexpr VECTOR DEFAULT_POS = { 300.0f, 10.0f, 300.0f };
	// 標準の自己発光色
	static constexpr COLOR_F COLOR_EMI_DEFAULT = { 1.0f, 1.0f, 1.0f, 1.0f };
	// 移動スピード
	static constexpr float SPEED_MOVE = 7.5f;

	//アニメーションステージ
	static constexpr float ANIM_STAGE = 1.0f;

	//重力
	static constexpr float GRAVITY_POW = 0.8f;

	// 地面衝突用線分の長さ
	static constexpr float COLLISION_LEN = 10.0f;

	//移動限界
	static constexpr float POS_MAX_X = 2000.0f;
	static constexpr float POS_MAX_Z = 2000.0f;

	//当たり判定の半径


private:
	// モデルID
	int modelId_;


	int invCnt_;

	int stanCnt_;
	
	bool isHit_;

	int attackR_;
	int attackM_;

	// プレイヤーのポインタ
	Player* player_;

	// 種別
	TYPE type_;

public:

	// コンストラクタ
	EnemyBase(void);
	// デストラクタ
	virtual ~EnemyBase(void);

	// 初期処理
	void Init(TYPE type, int baseModelId, int baseAttackEffectModelId, Player* player);
	// 更新
	void Update(void);
	// 描画
	void Draw(void);
	
	//移動処理
	void ProcessMove(void);

	void LookPlayer(void);

	void Move(void);
	void AttackMove(void);

	void SetSpaenPos(void);

	void ChangeState(STATE state);

	

	VECTOR GetPos(void);
	void SetPos(VECTOR pos);

	VECTOR GetAttackPos(void);
	float GetAttackRadius(void);

	float GetRadius(void);

	bool GetIsAlaive(void);
	void SetIsAlive(bool is);

	int GetInvCnt(void);
	void SetInvCnt(int cnt);

	void Damage(int damage);

	void ShotCret(VECTOR pos, VECTOR scl,float rad);

	bool IsCollisionState(void);

	std::vector<ShotBase*> GetShot();

	STATE GetState();
protected:// 初期位置
	
	VECTOR pos_;
	VECTOR shotPos_;

	// 初期角度
	VECTOR localAngles_;//ローカル回転
	VECTOR angles_;

	// アニメーションコントローラー
	AnimationController* animationController_;

	// 移動方向
	VECTOR moveDir_;
	// モデルの大きさ
	VECTOR scales_;
	VECTOR attackPos_;

	int hp_;

	STATE state_;

	float spaen_;

	float cntAttack_;

	// 移動速度
	float moveSpeed_;

	bool isAlive_;

	//当たり判定の半径
	float collisionRadius_;
	float attackRadius_;

	// 弾
	std::vector<ShotBase*> shots_;
	// エフェクト用モデルハンドルID
	int baseAttackEffectModelId_;
	// 弾の更新
	void UpdateShot(void);
	// 弾の描画
	void DrawShot(void);
	// 有効な弾を取得
	ShotBase* GetValidShot(void);

	ShotBase* GetRockShot(void);
	// パラメータ設定
	virtual void SetParam(void);

	// 状態遷移
	virtual void ChangeStandby(void);
	virtual void ChangeAttack(void);
	virtual void ChangeStan(void);
	virtual void ChangeHitReact();
	virtual void ChangeDeadReact();
	virtual void ChangeEnd();
	// 状態別更新
	virtual void UpdateStandby(void);
	virtual void UpdateAttack(void);
	virtual void UpdateStan(void);
	virtual void UpdateHitReact();
	virtual void UpdateDeadReact();
	virtual void UpdateEnd();
	// 状態別描画
	virtual void DrawStandby(void);
	virtual void DrawAttack(void);
	virtual void DrawStan(void);
	virtual void DrawHitReact();
	virtual void DrawDeadReact();
	virtual void DrawEnd();

	

};

