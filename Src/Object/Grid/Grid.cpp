#include <DxLib.h>
#include "Grid.h"
Grid::Grid(void)
{
}
Grid::~Grid(void)
{
}
void Grid::Init(void)
{
}
void Grid::Update(void)
{
}
void Grid::Draw(void)
{
	for (int z = -NUM; z < NUM; z++)
	{
		VECTOR sPos = { -LEN,0.0f,static_cast<float>(z * TERM) };
		VECTOR ePos = { LEN,0.0f,static_cast<float>(z * TERM) };
		DrawLine3D(sPos, ePos, 0xff0000);
	}
	for (int x = -NUM; x < NUM; x++)
	{
		VECTOR sPos = { static_cast<float>(x * TERM),0.0f,-LEN };
		VECTOR ePos = { static_cast<float>(x * TERM),0.0f,LEN };
		DrawLine3D(sPos, ePos, 0x0000ff);
	}
}
void Grid::Release(void)
{
}
