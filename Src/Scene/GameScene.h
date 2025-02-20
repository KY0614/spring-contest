//#pragma once
#include "SceneBase.h"
class Player;

class GameScene : public SceneBase
{

public:
	
	// コンストラクタ
	GameScene(void);

	// デストラクタ
	~GameScene(void);

	void Init(void) override;
	void Update(void) override;
	void Draw(void) override;

private:
	Player* player_;

	//サウンド
	int bgmHandle_;		//BGM
};
