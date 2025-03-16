#pragma once
#include "SceneBase.h"

class SelectScene : public SceneBase
{
public:
	enum class SELECT_TYPE
	{
		EASY = 0,			//�ȒP
		NORMAL = 1,		//����
		HARD = 2,	//���
	};
public:

	// �R���X�g���N�^
	SelectScene(void);

	// �f�X�g���N�^
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
	bool inputLock_;  // ���̓��b�N�t���O��ǉ�
	bool stateFlag_;	 //�������t���O
	float lockTimer_;      // ���b�N���ԗp�ϐ�

	int bgmHandle_;		//BGM
};

