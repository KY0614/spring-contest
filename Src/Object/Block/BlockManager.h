//#pragma once
class BlockManager
{
public:

	static constexpr int BLOCK_SIZE = 320;

	//�R���X�g���N�^	
	BlockManager(void);

	//�f�X�g���N�^
	~BlockManager(void);

	void Init(void);
	void Update(void);
	void Draw(void);
	void Release(void);

private:

};

