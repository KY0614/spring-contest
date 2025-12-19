#pragma once

#include "SceneBase.h"
class Camera;

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

	void SetCount(int count) { count_ = count; }

private:
	int count_;



	bool sousa_;
	
	int stageId_;
	int enemyMId_;
	int enemyRId_;
	int enemyUId_;
	int playerId_;
	VECTOR stagePos_;
	VECTOR stageScale_;
	VECTOR stagelocalRot_;
	VECTOR stageRot_;
	VECTOR enemyMPos_;
	VECTOR enemyMScale_;
	VECTOR enemyMlocalRot_;
	VECTOR enemyMRot_;
	VECTOR enemyRPos_;
	VECTOR enemyRScale_;
	VECTOR enemyRlocalRot_;
	VECTOR enemyRRot_;
	VECTOR enemyUPos_;
	VECTOR enemyUScale_;
	VECTOR enemyUlocalRot_;
	VECTOR enemyURot_;
	VECTOR playerPos_;
	VECTOR playerScale_;
	VECTOR playerlocalRot_;
	VECTOR playerRot_;


	Camera* camera_;
	
	
};
