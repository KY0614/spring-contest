#include <DxLib.h>
#include "../../Manager/InputManager.h"
#include "../../Manager/SceneManager.h"
#include "BlockBase.h"

BlockBase::BlockBase(Vector2 startPos, int img):pos_(startPos),img_(img),isHold_(false),rotate_(0)
{
	// ランダムに初期角度を設定
	int randomAngle = GetRand(3) * 90; // 0, 1, 2, 3 のいずれかを生成し、×90度にする
	rotate_ = randomAngle;
	UpdateConnections();
}

void BlockBase::Init(void)
{
}

void BlockBase::Update(void)
{
	auto& ins = InputManager::GetInstance();

	// マウス操作による位置更新
	if (isHold_) {
		int mouseX, mouseY;
		GetMousePoint(&mouseX, &mouseY);
		
		//pos_.x = mouseX;
		//pos_.y = mouseY;		
		pos_.x = ins.GetMousePos().x;
		pos_.y = ins.GetMousePos().y;
	}
}

void BlockBase::Draw(void)
{
	DrawRotaGraph(pos_.x, pos_.y,
		0.5f, rotate_ * DX_PI_F / 180, img_, true, false);
}

void BlockBase::Release(void)
{
	DeleteGraph(img_);
}

int BlockBase::GetX(void) const
{
	return pos_.x;
}

int BlockBase::GetY(void) const
{
	return pos_.y;
}

void BlockBase::IsHold(void)
{
	isHold_ = true;
}

void BlockBase::IsNotHold(void)
{
	isHold_ = false;
}

void BlockBase::RightRotate(void)
{
	rotate_ = (rotate_ + 90) % 360;
	UpdateConnections();
}

void BlockBase::LeftRotate(void)
{
	rotate_ -= 90;
	if (rotate_ < 0) { rotate_ = 0; }

	UpdateConnections();
}

const std::vector<std::pair<int, int>>& BlockBase::GetConnections() const
{
	return connections;
}

void BlockBase::SnapToGrid(int gridSize, int startX, int startY)
{
	pos_.x = ((pos_.x - startX) / gridSize) * gridSize + gridSize / 2 + startX;
	pos_.y = ((pos_.y - startY) / gridSize) * gridSize + gridSize / 2 + startY;
}

void BlockBase::UpdateConnections(void)
{
	// 90度回転ごとに接続方向を更新
	for (auto& conect : connections) {
		int dx = conect.first;
		int dy = conect.second;
		conect.first = -dy;
		conect.second = dx;
	}
}
