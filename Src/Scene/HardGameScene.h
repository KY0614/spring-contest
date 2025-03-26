//#pragma once
#include "SceneBase.h"
#include "../Common/Vector2.h"
#include <vector>


class Player;
class BlockBase;

class HardGameScene : public SceneBase
{
public:

	// コンストラクタ
	HardGameScene(void);

	// デストラクタ
	~HardGameScene(void);

	void Init(void) override;
	void Update(void) override;
	void Draw(void) override;

private:
	Player* player_;

	//サウンド
	int bgmHandle_;		//BGM

	std::vector<BlockBase*> blocks;
	BlockBase* selectBlock;
	BlockBase* startBlock;
	BlockBase* goalBlock;
	int gridSize_;
	int startX_;
	int startY_;

	int img_;

	void InitBlock(void);
	void AddBlock(BlockBase* block);
	bool BlocksConnected(const BlockBase* block1, const BlockBase* block2) const;
	bool CheckConnections(const BlockBase* block) const;
	void BlockProcess(Vector2 pos);
};

