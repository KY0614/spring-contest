#pragma once
#include "BlockBase.h"

class ToBlock : public  BlockBase
{
public:
	static constexpr int BLOCK_SIZE = 320;

	//�R���X�g���N�^	
	ToBlock(Vector2 pos, int img);

	//�f�X�g���N�^
	~ToBlock(void) = default;

protected:

	void SetParam(void)override;

private:

};

