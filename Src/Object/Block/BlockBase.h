#pragma once

#include "../../Common/Vector2.h"

class BlockBase
{
public:
	static constexpr int IMAGE_SCALSE = 320;

	BlockBase(void);

	~BlockBase() = default;

	virtual void Init(void);
	virtual void Update(void);
	virtual void Draw(void);
	virtual void Release(void);

	void SetPos(Vector2 pos) {pos_ = pos;}
	Vector2 GetPos(void) { return pos_; }

	void RightRotate(void);
	void LeftRotate(void);

	virtual void SetParam(void) = 0;

protected:

	int img_;		//âÊëú
	bool isHold_;	//
	float angle_;	//äpìx
	Vector2 pos_;	//ç¿ïW(intå^)

private:

};

