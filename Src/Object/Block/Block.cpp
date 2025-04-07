#include <DxLib.h>
#include "../../Application.h"
#include "../../Manager/ResourceManager.h"
#include "../../Manager/InputManager.h"
#include "BlockBase.h"
#include "Block.h"

Block::Block(Vector2 pos, int img):BlockBase(pos,img)
{
	connections = { {0,0},{1,1} };
	exits[0] = { -80, 0 }; // ç∂
	exits[1] = { 0, -80 }; // è„

	exitsPos_[0] = { -80,0 };
	exitsPos_[1] = { 0, 80 };
	UpdateExits();
}

void Block::Init(void)
{
	auto& res = ResourceManager::GetInstance();

	//âÊëúì«Ç›çûÇ›
	img_ = res.Load(ResourceManager::SRC::BLOCK).handleId_;
	if (img_ == -1)
	{
		return;
	}

}

void Block::Update(void)
{
	auto& ins = InputManager::GetInstance();

}

void Block::SetParam(void)
{
	img_ = 0;
	rotate_ = 0;

	pos_ = { 0,0 };
	SetConnection(TYPE::LSHAPE);

	//UpdateConnections();
}
