#pragma once

#include "../../Common/Vector2.h"

class BlockBase
{
public:

	BlockBase(int startX, int startY, int img);

	virtual ~BlockBase() = default;

protected:
	int img_;
	bool isHold_;
	float angle_;
	Vector2 pos_;

private:

};

