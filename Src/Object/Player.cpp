

#include "../Manager/InputManager.h"
#include "Player.h"
#include <DxLib.h>


void Player::Init(void)
{
	posX_ = 0;
	posY_ = 0;
	count_ = 0;
	cr_ = 0x000000;
}
void Player::Updeta(void)
{
	MoveUpdeta();
}
void Player::MoveUpdeta(void)
{
	//�}�E�X���W�擾�p
	int mousPosX_, mousPosY_;
	//�}�E�X���W�擾
	GetMousePoint(&mousPosX_, &mousPosY_);
	//���W�ۑ�
	posX_ = mousPosX_;
	posY_ = mousPosY_;

	//���N���b�N
	InputManager& ins = InputManager::GetInstance();
	if (ins.IsTrgMouseLeft())
	{
		count_+=1;
	}
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
	DrawFormatString(0, 20, 0xffffff, "X%d", posX_);
	DrawFormatString(0, 40, 0xffffff, "Y%d", posY_);
	DrawFormatString(0, 60, 0xffffff, "count%d", count_);
	DrawBox(100, 100, 200, 200, cr_, true);
}
void Player::Rerease(void)
{

}