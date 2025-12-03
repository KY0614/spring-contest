#pragma once
#include <memory>
#include <chrono>

// 推奨しませんが、どうしても使いたい方は
#define mainCamera SceneManager::GetInstance().GetCamera().lock()

class SceneBase;
class Timer;
class Fader;

class SceneManager
{

public:

	// シーン管理用
	enum class SCENE_ID
	{
		NONE,
		
		TITLE,
		GAME,
		GAMEOVER,
		CLEAR,
		
	};

	enum class MANEW_SERECT
	{
		GAME_END,
		TITLE,
		EXIT,
	};
	
	// インスタンスの生成
	static void CreateInstance(void);

	// インスタンスの取得
	static SceneManager& GetInstance(void);

	void Init(void);
	void Init3D(void);
	void Update(void);
	void Draw(void);

	// リソースの破棄
	void Destroy(void);

	// 状態遷移
	void ChangeScene(SCENE_ID nextId);

	void SetTimer(int time) { clearTime_ = time; }
	int GetTimer(void) { return clearTime_; }

	// シーンIDの取得
	SCENE_ID GetSceneID(void);

	// デルタタイムの取得
	float GetDeltaTime(void) const;



	//// カメラの取得
	//Camera* GetCamera(void) const;

	void State(void);

	//文字のX 座標
	static const int TEXT_POS_X = 400;
	//文字のY 座標
	static const int TEXT_POS_Y = 200;

	// 文字の大きさ(大)
	static const int TEXT_SIZE_LARGE = 100;
	// 文字の大きさ(小)
	static const int TEXT_SIZE_SMALL = 16;

	//ディレイマックス
	static const int DELAY_MAX = 10;

private:

	int clearTime_;

	// 静的インスタンス
	static SceneManager* instance_;

	SCENE_ID sceneId_;
	SCENE_ID waitSceneId_;

	// フェード
	std::unique_ptr<SceneBase> scene_;

	// 各種シーン
	std::unique_ptr<Fader> fader_;

	//タイマー
	Timer* timer_;


	MANEW_SERECT manewSerect_;

	// シーン遷移中判定
	bool isSceneChanging_;


	//メニュー関連
	int delayCount_;
	bool stateFlag_;
	bool isUp_;
	bool isDown_;
	bool isUpStick_;
	bool isDownStick_;
	// デルタタイム
	std::chrono::system_clock::time_point preTime_;
	float deltaTime_;
	
	// デフォルトコンストラクタをprivateにして、
	// 外部から生成できない様にする
	SceneManager(void);
	// コピーコンストラクタも同様
	SceneManager(const SceneManager& manager) = default;
	// デストラクタも同様
	~SceneManager(void) = default;

	// デルタタイムをリセットする
	void ResetDeltaTime(void);

	// シーン遷移
	void DoChangeScene(SCENE_ID sceneId);

	// フェード
	void Fade(void);

	bool manew_;
	int count_;
};
