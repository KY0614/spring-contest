#pragma once
#include "BlockBase.h"

class PlusBlock : public  BlockBase
{
public:
	static constexpr int BLOCK_SIZE = 320;

	//コンストラクタ	
	PlusBlock(Vector2 pos, int img);

	//デストラクタ
	~PlusBlock(void) = default;

	void Init(void) override;
	void Update(void)override;

protected:

	void SetParam(void)override;

private:

};

