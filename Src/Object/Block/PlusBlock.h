#pragma once
#include "BlockBase.h"

class PlusBlock : public  BlockBase
{
public:
	static constexpr int BLOCK_SIZE = 320;

	//�R���X�g���N�^	
	PlusBlock(Vector2 pos, int img);

	//�f�X�g���N�^
	~PlusBlock(void) = default;

protected:

	void SetParam(void)override;

private:

};

