#include <DxLib.h>
#include "BlockBase.h"

BlockBase::BlockBase(Vector2 pos,int angle, bool isHold, int img) : pos_(pos), angle_(angle), isHold_(isHold), img_(img)
{
}

void BlockBase::Init(void)
{
}

void BlockBase::Update(void)
{
}

void BlockBase::Draw(void)
{
	DrawRotaGraph(pos_.x, pos_.y,
		1.0f, angle_, img_, true, false);
}

void BlockBase::Release(void)
{
	DeleteGraph(img_);
}

void BlockBase::RightRotate(void)
{
	angle_ += 90.0f;
	if (angle_ > 360.0f) { angle_ = 0.0f; }
}

void BlockBase::LeftRotate(void)
{
	angle_ -= 90.0f;
	if (angle_ < 0.0f) { angle_ = 0.0f; }
}
