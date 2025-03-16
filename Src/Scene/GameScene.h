//#pragma once
#include "SceneBase.h"
#include "../Common/Vector2.h"
#include <vector>


class Player;
class BlockBase;

class GameScene : public SceneBase
{

public:
	
	// �R���X�g���N�^
	GameScene(void);

	// �f�X�g���N�^
	~GameScene(void);

	void Init(void) override;
	void Update(void) override;
	void Draw(void) override;

private:
	Player* player_;

	std::vector<BlockBase*> blocks;
	BlockBase* selectBlock;
	BlockBase* startBlock;
	BlockBase* goalBlock;
	int gridSize_;
	int startX_;
	int startY_;

	int img_;

	int bgmHandle_;			//bgm

	Vector2 highlightPos_;	//�n�C���C�g���W

	void InitBlock(void);
	void AddBlock(BlockBase* block);
	bool BlocksConnected(const BlockBase* block1, const BlockBase* block2) const;
	bool CheckConnections(const BlockBase* block) const;
	void BlockProcess(Vector2 pos);

	void HighlightUpdate();
	void HighlightDraw();
};
