#include <DxLib.h>
#include "../../Manager/ResourceManager.h"
#include "BlockBase.h"
#include "PlusBlock.h"

PlusBlock::PlusBlock(Vector2 pos, int img) :BlockBase(pos, img)
{
	//exits[0] = { -80, 0 }; // ��
	//exits[1] = { 0, -80 }; // ��	
	//exits[2] = { 80, 0 }; // ��
	//exits[3] = { 0, 80 }; // ��
	//SetConnection(TYPE::PLUS);
	UpdatePlusExits();
}

void PlusBlock::SetParam(void)
{
	img_ = LoadGraph("Data/Image/PlusBlock.png");

	SetConnection(TYPE::PLUS);
	type_ = TYPE::PLUS;
	UpdatePlusExits();
}
