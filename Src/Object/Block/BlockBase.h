#pragma once

#include <vector>
#include "../../Common/Vector2.h"

class BlockBase
{
public:
	static constexpr int IMAGE_SCALSE = 320;

	struct Exit {
		int x, y;
	};

	BlockBase(Vector2 startPos,int img);

	~BlockBase() = default;

	virtual void Init(void);
	virtual void Update(void);
	virtual void Draw(void);
	virtual void Release(void);

	int GetX(void) const;
	int GetY(void) const;
	void IsHold(void);
	void IsNotHold(void);

	void SetPos(Vector2 pos) {pos_ = pos;}
	void SetRot(int rot) {rotate_ = rot;}
	Vector2 GetPos(void) { return pos_; }

	void RightRotate(void);
	void LeftRotate(void);

	const std::vector<std::pair<int, int>>& GetConnections() const;

	virtual void SetParam(void) = 0;
	void SnapToGrid(int gridSize, int startX, int startY); // �O���b�h�ɃX�i�b�v����֐�
	
	const Exit* GetExits() const;
	const Exit* GetGoalExits() const { return goalExits; }
	bool HasElectricity() const;
	void SetElectricity(bool state);

	bool IsConnected(const BlockBase* otherBlock) const;

protected:

	int img_;		//�摜
	bool isHold_;	//
	int rotate_;	//�p�x
	Vector2 pos_;	//���W(int�^)
	std::vector<std::pair<int, int>> connections; // �ڑ��\�ȕ���
	Exit exits[2];			// �o���̍��W�̔z��
	Exit goalExits[1];		// �o��
	Exit startExits[1];		// �N�_
	bool hasElectricity;	// �d�C���ʂ��Ă��邩�ǂ���

	//void UpdateConnections(void); // �ڑ��������X�V����

	void UpdateExits(); // �o���̍��W���X�V����

private:

};

