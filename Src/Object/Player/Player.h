//#pragma once
class Player
{

public:
	//�萔
	
	//�T�C�Y
	static constexpr int SIZE_X = 32;
	static constexpr int SIZE_Y = 32;

	//�ړ���
	static constexpr int MOVE_X = 32;
	static constexpr int MOVE_Y = 32;


private:
	//�ϐ�
	
	//
	int boxPosX_;
	int boxPosY_;

	//�}�E�X���W�ۑ��p
	int mousePosX_;
	int mousePosY_;
	
	//�f�o�b�O
	int count_;
	int cr_;

	//�摜
	int img_;

public:
	//

	//������
	void Init(void);
	//�A�v�f
	void Updeta(void);
	//�}�E�X�ړ�
	void MoveMouseUpdeta(void);
	//�L�[�ړ�
	void MoveKeyUpdata(void);
	//����
	void InputUpdeta(void);
	//�`��
	void Draw(void);
	//�폜
	void Rerease(void);

};

