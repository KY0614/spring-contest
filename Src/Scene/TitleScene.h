//#pragma once
#include "SceneBase.h"


class TitleScene : public SceneBase
{

public:

	// コンストラクタ
	TitleScene(void);

	// デストラクタ
	~TitleScene(void);

	void Init(void) override;
	void Update(void) override;
	void Draw(void) override;

private:

	//サウンド
	int bgmHandle_;		//BGM

	int img_;//画像
	int loopCount;						//文字カウント
	int FontHandle;
	int StrLen;
	bool moziFlag;						//文字フラグ

};
