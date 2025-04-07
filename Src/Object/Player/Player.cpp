
#include <DxLib.h>
#include "../../Application.h"
#include "../../Manager/InputManager.h"
#include "../../Manager/ResourceManager.h"
#include "Player.h"



void Player::Init(void)
{
	auto& res = ResourceManager::GetInstance();

	//�摜�ǂݍ���
	img_ = res.Load(ResourceManager::SRC::PLAYER).handleId_;
	if (img_ == -1)
	{
		return;
	}
	boxPosX_ = 0;
	boxPosY_ = 0;
	mousePosX_ = 0;
	mousePosY_ = 0;
	count_ = 0;
	cr_ = 0x000000;
	//�N���b�N
	inputLFlag_ = false;
	inputRFlag_ = false;
}
//�v���C���[�S�̍X�V
void Player::Updeta(void)
{
	MoveMouseUpdeta();
	MoveKeyUpdata();
	InputUpdeta();
}
//�J�[�\���X�V
void Player::MoveMouseUpdeta(void)
{
	SetMouseDispFlag(false);
	//�}�E�X���W�擾�p
	int mousePosX, mousePosY;
	//�}�E�X���W�擾
	GetMousePoint(&mousePosX, &mousePosY);
	//���W�ۑ�
	mousePosX_ = mousePosX;
	mousePosY_ = mousePosY;
	//�ړ�����
	//������
	if (mousePosX_ < 0)
	{
		SetMousePoint(0, mousePosY);
	}
	//�E����
	if (mousePosX_ > Application::SCREEN_SIZE_X)
	{
		SetMousePoint(Application::SCREEN_SIZE_X, mousePosY);
	}
	//��
	if (mousePosY_ < 0)
	{
		SetMousePoint(mousePosX,0);
	}
	//������
	if (mousePosY_ > Application::SCREEN_SIZE_Y)
	{
		SetMousePoint(mousePosX, Application::SCREEN_SIZE_Y);
	}
}
//�L�[���͍X�V
void Player::MoveKeyUpdata(void)
{
	InputManager& ins = InputManager::GetInstance();

	//��ړ�
	if (ins.IsTrgDown(KEY_INPUT_W))
	{
		boxPosY_ -= MOVE_Y;
	}
	//���ړ�
	if (ins.IsTrgDown(KEY_INPUT_S))
	{
		boxPosY_ += MOVE_Y;
	}
	//�E�ړ�
	if (ins.IsTrgDown(KEY_INPUT_D))
	{
		boxPosX_ += MOVE_X;
	}
	//���ړ�
	if (ins.IsTrgDown(KEY_INPUT_A))
	{
		boxPosX_ -= MOVE_X;
	}


	//�ړ�����
	//�E����
	if (boxPosX_ > Application::SCREEN_SIZE_X - SIZE_X)
	{
		boxPosX_ = Application::SCREEN_SIZE_X - SIZE_X;
	}
	//������
	if (boxPosX_ < 0)
	{
		boxPosX_ = 0;
	}
	//�㐧��
	if (boxPosY_ < 0)
	{
		boxPosY_ = 0;
	}
	//������
	if (boxPosY_ > Application::SCREEN_SIZE_Y - SIZE_Y)
	{
		boxPosY_ = Application::SCREEN_SIZE_Y - SIZE_Y;
	}
}
//�}�E�X���͍X�V
void Player::InputUpdeta(void)
{
	InputManager& ins = InputManager::GetInstance();
	//���N���b�N
	if (ins.IsTrgMouseLeft())
	{
		inputLFlag_ = true;
	}
	else
	{
		inputLFlag_ = false;
	}

	//�E�N���b�N
	if (ins.IsTrgMouseRight())
	{
		inputRFlag_ = true;
	}
	else
	{
		inputRFlag_ = false;
	}

}
//�摜
void Player::Draw(void)
{
	//DrawBox(boxPosX_, boxPosY_, boxPosX_ + SIZE_X, boxPosY_ + SIZE_Y, 0x0000ff, false);
	DrawRotaGraph(mousePosX_+30,
		mousePosY_+30,
		1.0f, 0.0f, img_, true, false);


	////�f�o�b�O
	/*DrawFormatString(0, 20, 0xffffff, "X%d", inputLFlag_);
	DrawFormatString(0, 40, 0xffffff, "Y%d", inputRFlag_);*/
	//DrawFormatString(0, 60, 0xffffff, "count%d", count_);
	//DrawBox(100, 100, 200, 200, cr_, true);
}
void Player::Rerease(void)
{

}
//�Q�b�g�E�Z�b�g
bool Player::GetIsInputL(void)
{
	return inputLFlag_;
}

bool Player::GetIsInputR(void)
{
	return inputRFlag_;
}