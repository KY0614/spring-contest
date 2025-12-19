#pragma once
#include <DxLib.h>

class Player;

class Camera
{
public:
	// カメラモード
	enum class MODE
	{
		NONE,
		FIXED_POINT,
		FREE,
		FOLLOW, // 追従モード
	};


	//カメラの初期座標
	static constexpr VECTOR DERFAULT_POS = { 0.0f,400.0f,-800.0f };

	//カメラの初期角度
	static constexpr VECTOR DERFAULT_ANGLES = { 0.0f, 0.0f, 0.0f
	};
	// カメラのクリップ範囲
	static constexpr float VIEW_NEAR = 10.0f;
	static constexpr float VIEW_FAR = 30000.0f;


	// 追従対象からの相対座標
	static constexpr VECTOR FOLLOW_LOCAL_POS = { 0.0f, 200.0f, -500.0f };
	// 追従対象からカメラへの相対座標(通常）
	static constexpr VECTOR FOLLOW_CAMERA_LOCAL_POS = { 0.0f, 400.0f,-800.0f };
	//追従対象からカメラへの相対座標(注視）
	static constexpr VECTOR FOLLOW_CAMERA_LOCAL_POS_UP = { 0.0f, 200.0f,-500.0f };

	// 追従対象から注視点への相対座標
	static constexpr VECTOR FOLLOW_TARGET_LOCAL_POS = { 0.0f, 0.0f, 150.0f };
	// コンストラクタ
	Camera(void);
	// デストラクタ
	~Camera(void);
	// 初期化
	void Init(Player*player);
	// 更新
	void Update(void);
	// 描画前のカメラ設定
	void SetBeforeDraw(void);
	// デバッグ用描画
	void DrawDebug(void);
	// 解放
	void Release(void);

	
	// カメラモードの変更
	void ChangeMode(MODE mode);

	VECTOR GetPos();
	void SetPos(VECTOR pos){ pos_ = pos;}
	VECTOR GetAngles();

	// 描画前のカメラ設定
	void SetBeforeDrawFixedPoint(void);
	void SetBeforeDrawFree(void);
	void SetBeforeDrawFollow(void);

	// 注視点の取得
	const VECTOR& GetTargetPos(void) const;


	//カメラの移動
	void MoveXYZDirection(void);
	//カメラの移動
	void MoveXYZDirectionPad(void);

	

private:
	// カメラの位置
	VECTOR pos_;
	// カメラの角度
	VECTOR angles_;

	// カメラモード
	MODE mode_;

	// プレイヤーのポインタ
	Player* player_;

	VECTOR targetPos_;
};

