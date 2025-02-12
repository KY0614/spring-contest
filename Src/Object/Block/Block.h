//#pragma once

class Block
{
public:

	static constexpr int BLOCK_SIZE = 320;

	//コンストラクタ	
	Block(void);

	//デストラクタ
	~Block(void);

	void Init(void);
	void Update(void);
	void Draw(void);
	void Release(void);

private:
	int img_;
};

