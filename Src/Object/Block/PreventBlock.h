#pragma once
#include "BlockBase.h"

class PreventBlock : public  BlockBase
{
public:
	static constexpr int BLOCK_SIZE = 320;

	//�R���X�g���N�^	
	PreventBlock(Vector2 pos, int img);

	//�f�X�g���N�^
	~PreventBlock(void) = default;

protected:

	void SetParam(void)override;

private:
};

