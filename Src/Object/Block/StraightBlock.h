#pragma once
#include "BlockBase.h"

class StraightBlock : public  BlockBase
{
public:
	static constexpr int BLOCK_SIZE = 320;

	//�R���X�g���N�^	
	StraightBlock(Vector2 pos, int img);

	//�f�X�g���N�^
	~StraightBlock(void) = default;

protected:

	void SetParam(void)override;

private:
};

