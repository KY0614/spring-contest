//#pragma once
#include "BlockBase.h"

class Block : public  BlockBase
{
public:

	static constexpr int BLOCK_SIZE = 320;
	
	//�R���X�g���N�^	
	Block(Vector2 pos,int img);

	//�f�X�g���N�^
	~Block(void) = default;

protected:

	void SetParam(void)override;

private:

};

