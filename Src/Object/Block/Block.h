//#pragma once
#include "BlockBase.h"

class Block : public  BlockBase
{
public:

	static constexpr int BLOCK_SIZE = 320;
	
	//�R���X�g���N�^	
	Block(void);

	//�f�X�g���N�^
	~Block(void) = default;

	void Init(void) override;
	void Update(void)override;
	void Draw(void)override;
	void Release(void)override;

protected:

	void SetParam(void)override;

private:

};

