

#include "../Manager/InputManager.h"
#include"../Application.h"
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
	int mousePosX, mousePosY;
	//マウス座標取得
	GetMousePoint(&mousePosX, &mousePosY);
	//座標保存
	mousePosX_ = mousePosX;
	mousePosY_ = mousePosY;
	//移動制限
	//左制限
	if (mousePosX_ < 0)
	{
		SetMousePoint(0, mousePosY);
	}
	//右制限
	if (mousePosX_ > Application::SCREEN_SIZE_X)
	{
		SetMousePoint(Application::SCREEN_SIZE_X, mousePosY);
	}
	//上
	if (mousePosY_ < 0)
	{
		SetMousePoint(mousePosX,0);
	}
	//下制限
	if (mousePosY_ > Application::SCREEN_SIZE_Y)
	{
		SetMousePoint(mousePosX, Application::SCREEN_SIZE_Y);
	}
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


	//移動制限
	//右制限
	if (boxPosX_ > Application::SCREEN_SIZE_X-SIZE_X)
	{
		boxPosX_ = Application::SCREEN_SIZE_X - SIZE_X;
	}
	//左制限
	if (boxPosX_ < 0)
	{
		boxPosX_ = 0;
	}
	//上制限
	if (boxPosY_ < 0)
	{
		boxPosY_ = 0;
	}
	//下制限
	if (boxPosY_ > Application::SCREEN_SIZE_Y - SIZE_Y)
	{
		boxPosY_ = Application::SCREEN_SIZE_Y - SIZE_Y;
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