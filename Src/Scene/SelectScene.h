#pragma once
#include "SceneBase.h"

class SelectScene : public SceneBase
{
public:
	enum class SELECT_TYPE
	{
		EASY = 0,			//簡単
		NORMAL = 1,		//普通
		HARD = 2,	//難しい
	};
public:

	// コンストラクタ
	SelectScene(void);

	// デストラクタ
	~SelectScene(void);

	void Init(void) override;
	void Update(void) override;
	void Draw(void) override;

	void State(void);
private:

	int img_;
	SELECT_TYPE select_;
	bool changeFlag_;
	bool isUpPressed_;
	bool isDownPressed_;
	bool inputLock_;  // 入力ロックフラグを追加
	bool stateFlag_;	 //無効かフラグ
	float lockTimer_;      // ロック時間用変数

	//サウンド
	int bgmHandle_;		//BGM
};

