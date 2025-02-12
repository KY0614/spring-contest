

#include "../Manager/InputManager.h"
#include "Player.h"
#include <DxLib.h>


void Player::Init(void)
{
	boxPosX_ = 0;
	boxPosY_ = 0;
	mousePosX_ = 0;
	mousePosY_ = 0;
	count_ = 0;
	cr_ = 0x000000;
}
void Player::Updeta(void)
{
	MoveMouseUpdeta();
	MoveKeyUpdata();
	InputUpdeta();
}
void Player::MoveMouseUpdeta(void)
{
	//�}�E�X���W�擾�p
	int mousPosX, mousPosY;
	//�}�E�X���W�擾
	GetMousePoint(&mousPosX, &mousPosY);
	//���W�ۑ�
	mousePosX_ = mousPosX;
	mousePosY_ = mousPosY;
	
}
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
}

void Player::InputUpdeta(void)
{
	InputManager& ins = InputManager::GetInstance();
	//���N���b�N
	if (ins.IsTrgMouseLeft())
	{
		count_ += 1;
	}

	//�E�N���b�N
	if (ins.IsTrgMouseRight())
	{
		count_ += 1;
	}
	//�f�o�b�O
	if ((count_ % 2) == 0)
	{
		cr_ = 0xffffff;
	}
	else
	{
		cr_ = 0x000000;
	}
}

void Player::Draw(void)
{




	//�f�o�b�O
	DrawFormatString(0, 20, 0xffffff, "X%d", mousePosX_);
	DrawFormatString(0, 40, 0xffffff, "Y%d", mousePosY_);
	DrawFormatString(0, 60, 0xffffff, "count%d", count_);
	DrawBox(100, 100, 200, 200, cr_, true);
	DrawBox(boxPosX_, boxPosY_, boxPosX_ + SIZE_X, boxPosY_ + SIZE_Y, 0x0000ff, true);
}
void Player::Rerease(void)
{

}