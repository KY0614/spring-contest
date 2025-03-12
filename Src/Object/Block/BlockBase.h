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
	void SnapToGrid(int gridSize, int startX, int startY); // グリッドにスナップする関数
protected:

	int img_;		//画像
	bool isHold_;	//
	int rotate_;	//角度
	Vector2 pos_;	//座標(int型)
	std::vector<std::pair<int, int>> connections; // 接続可能な方向

	void UpdateConnections(void); // 接続方向を更新する
private:

};

