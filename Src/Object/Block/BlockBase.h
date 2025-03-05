#pragma once

#include <vector>
#include "../../Common/Vector2.h"

class BlockBase
{
public:
	static constexpr int IMAGE_SCALSE = 320;

	enum class CONECTION
	{
		TOP,
		RIGHT,
		DOWN,
		LEFT
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
protected:

	int img_;		//�摜
	bool isHold_;	//
	int rotate_;	//�p�x
	Vector2 pos_;	//���W(int�^)
	std::vector<std::pair<int, int>> connections; // �ڑ��\�ȕ���

	void UpdateConnections(void); // �ڑ��������X�V����
private:

};

