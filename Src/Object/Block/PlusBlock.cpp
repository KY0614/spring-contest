#include <DxLib.h>
#include "../../Manager/ResourceManager.h"
#include "BlockBase.h"
#include "PlusBlock.h"

PlusBlock::PlusBlock(Vector2 pos, int img) :BlockBase(pos, img)
{
	//exits[0] = { -80, 0 }; // ç∂
	//exits[1] = { 0, -80 }; // è„

	UpdatePlusExits();
}

void PlusBlock::Init(void)
{
	auto& res = ResourceManager::GetInstance();

	//âÊëúì«Ç›çûÇ›
	img_ = res.Load(ResourceManager::SRC::BLOCK).handleId_;
	if (img_ == -1)
	{
		return;
	}
}

void PlusBlock::Update(void)
{
}

void PlusBlock::SetParam(void)
{
	img_ = 0;
	rotate_ = 0;

	pos_ = { 0,0 };
	SetConnection(TYPE::PLUS);
}
