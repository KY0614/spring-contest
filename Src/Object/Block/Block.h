//#pragma once

class Block
{
public:

	static constexpr int BLOCK_SIZE = 320;

	//�R���X�g���N�^	
	Block(void);

	//�f�X�g���N�^
	~Block(void);

	void Init(void);
	void Update(void);
	void Draw(void);
	void Release(void);

private:
	int img_;
};

