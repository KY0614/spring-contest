#include <DxLib.h>
#include "../../Application.h"
#include "../../Manager/ResourceManager.h"
#include "Block.h"

Block::Block(void)
{
	img_ = -1;
}

Block::~Block(void)
{
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
}

void Block::Draw(void)
{
	DrawRotaGraph(Application::SCREEN_SIZE_X / 2,
		Application::SCREEN_SIZE_Y / 2,
		1.0f, 0.0f,img_, true, false);
}

void Block::Release(void)
{
}
