//#pragma once
#include "SceneBase.h"

class Timer;

class GameClearScene : public SceneBase
{
public:

	// �R���X�g���N�^
	GameClearScene(void);

	// �f�X�g���N�^
	~GameClearScene(void);

	void Init(void) override;
	void Update(void) override;
	void Draw(void) override;

private:
	int img_;
};

