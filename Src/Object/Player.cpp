


#include "Player.h"
#include <DxLib.h>


void Player::Init(void)
{
	posX_ = 0;
	posY_ = 0;
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
}
void Player::Draw(void)
{




	//�f�o�b�O
	DrawFormatString(0, 20, 0xffffff, "X%d", posX_);
	DrawFormatString(0, 40, 0xffffff, "Y%d", posY_);
}
void Player::Rerease(void)
{

}