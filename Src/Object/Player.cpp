


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
	//マウス座標取得用
	int mousPosX_, mousPosY_;
	//マウス座標取得
	GetMousePoint(&mousPosX_, &mousPosY_);
	//座標保存
	posX_ = mousPosX_;
	posY_ = mousPosY_;
}
void Player::Draw(void)
{




	//デバッグ
	DrawFormatString(0, 20, 0xffffff, "X%d", posX_);
	DrawFormatString(0, 40, 0xffffff, "Y%d", posY_);
}
void Player::Rerease(void)
{

}