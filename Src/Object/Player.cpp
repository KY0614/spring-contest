

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
	//マウス座標取得用
	int mousPosX_, mousPosY_;
	//マウス座標取得
	GetMousePoint(&mousPosX_, &mousPosY_);
	//座標保存
	posX_ = mousPosX_;
	posY_ = mousPosY_;

	//左クリック
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




	//デバッグ
	DrawFormatString(0, 20, 0xffffff, "X%d", posX_);
	DrawFormatString(0, 40, 0xffffff, "Y%d", posY_);
	DrawFormatString(0, 60, 0xffffff, "count%d", count_);
	DrawBox(100, 100, 200, 200, cr_, true);
}
void Player::Rerease(void)
{

}