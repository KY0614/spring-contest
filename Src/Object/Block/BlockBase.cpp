#include <DxLib.h>
#include "../../Manager/InputManager.h"
#include "../../Manager/SceneManager.h"
#include "BlockBase.h"

BlockBase::BlockBase(Vector2 startPos, int img):pos_(startPos),img_(img),isHold_(false),rotate_(0)
{
	// �����_���ɏ����p�x��ݒ�
	int randomAngle = GetRand(3) * 90; // 0, 1, 2, 3 �̂����ꂩ�𐶐����A�~90�x�ɂ���
	rotate_ = randomAngle;
	UpdateConnections();

	// �����o���̍��W��ݒ�
	int halfSize = 320 / 2 * 0.5;
	exits[0] = { 0, 0 };  // �E
	exits[1] = { 0, 0 };  // ��
	exits[2] = { 0, 0 }; // ��
	exits[3] = { 0, 0 }; // ��
	UpdateExits();
}

void BlockBase::Init(void)
{
}

void BlockBase::Update(void)
{
	auto& ins = InputManager::GetInstance();

	// �}�E�X����ɂ��ʒu�X�V
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
	rotate_ = (rotate_ + 90+ 360) % 360;
	//UpdateConnections();
	UpdateExits();
}

void BlockBase::LeftRotate(void)
{
	rotate_ = (rotate_ - 90 + 360) % 360;

	//UpdateConnections();
	UpdateExits();
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

const BlockBase::Exit* BlockBase::GetExits() const
{
	return exits;
}

void BlockBase::UpdateConnections(void)
{
	// 90�x��]���Ƃɐڑ��������X�V
	for (auto& conect : connections) {
		int dx = conect.first;
		int dy = conect.second;
		conect.first = -dy;
		conect.second = dx;
	}
}

void BlockBase::UpdateExits()
{
	//for (int i = 0; i < 4; ++i) {
	//	int dx = exits[i].x;
	//	int dy = exits[i].y;
	//	exits[i].x = -dy;
	//	exits[i].y = dx;
	//}

	int halfSize = 320 / 2 * 0.5; // 160 * 0.5 = 80
	switch (rotate_) {
	case 0:
		exits[0] = { -halfSize, 0 };  // ��
		exits[1] = { 0, -halfSize };  // ��
		break;
	case 90:
		exits[0] = { 0, -halfSize };  // ��
		exits[1] = { halfSize, 0 };   // �E
		break;
	case 180:
		exits[0] = { halfSize, 0 };   // �E
		exits[1] = { 0, halfSize };   // ��
		break;
	case 270:
		exits[0] = { 0, halfSize };   // ��
		exits[1] = { -halfSize, 0 };  // ��
		break;
	}
}
