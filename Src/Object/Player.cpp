

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
	//マウス座標取得用
	int mousPosX, mousPosY;
	//マウス座標取得
	GetMousePoint(&mousPosX, &mousPosY);
	//座標保存
	mousePosX_ = mousPosX;
	mousePosY_ = mousPosY;
	
}
void Player::MoveKeyUpdata(void)
{
	InputManager& ins = InputManager::GetInstance();
	//上移動
	if (ins.IsTrgDown(KEY_INPUT_W))
	{
		boxPosY_ -= MOVE_Y;
	}
	//下移動
	if (ins.IsTrgDown(KEY_INPUT_S))
	{
		boxPosY_ += MOVE_Y;
	}
	//右移動
	if (ins.IsTrgDown(KEY_INPUT_D))
	{
		boxPosX_ += MOVE_X;
	}
	//左移動
	if (ins.IsTrgDown(KEY_INPUT_A))
	{
		boxPosX_ -= MOVE_X;
	}
}

void Player::InputUpdeta(void)
{
	InputManager& ins = InputManager::GetInstance();
	//左クリック
	if (ins.IsTrgMouseLeft())
	{
		count_ += 1;
	}

	//右クリック
	if (ins.IsTrgMouseRight())
	{
		count_ += 1;
	}
	//デバッグ
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
	DrawFormatString(0, 20, 0xffffff, "X%d", mousePosX_);
	DrawFormatString(0, 40, 0xffffff, "Y%d", mousePosY_);
	DrawFormatString(0, 60, 0xffffff, "count%d", count_);
	DrawBox(100, 100, 200, 200, cr_, true);
	DrawBox(boxPosX_, boxPosY_, boxPosX_ + SIZE_X, boxPosY_ + SIZE_Y, 0x0000ff, true);
}
void Player::Rerease(void)
{

}