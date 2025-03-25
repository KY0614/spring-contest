//#pragma once
#include "SceneBase.h"


class TitleScene : public SceneBase
{

public:

	// �R���X�g���N�^
	TitleScene(void);

	// �f�X�g���N�^
	~TitleScene(void);

	void Init(void) override;
	void Update(void) override;
	void Draw(void) override;

private:

	
	int img_;//�摜
	int loopCount;						//�����J�E���g
	int FontHandle;
	int StrLen;
	bool moziFlag;						//�����t���O

	int bgmHandle_;						//BGM
	int seDecision_;					//���艹

	void InitSoundEffect();

};
