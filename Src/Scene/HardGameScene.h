//#pragma once
#include "SceneBase.h"
#include "../Common/Vector2.h"
#include <vector>


class Player;
class BlockBase;
class Timer;

class HardGameScene : public SceneBase
{
public:

	static constexpr int BLOCK_NUM_X = 5;
	static constexpr int BLOCK_NUM_Y = 4;

	// �R���X�g���N�^
	HardGameScene(void);

	// �f�X�g���N�^
	~HardGameScene(void);

	void Init(void) override;
	void Update(void) override;
	void Draw(void) override;

private:
	Player* player_;
	Timer* timer_;

	//�T�E���h
	int bgmHandle_;		//BGM

	std::vector<BlockBase*> blocks;
	BlockBase* startBlock;
	BlockBase* goalBlock;
	BlockBase* UIBlock1;
	BlockBase* UIBlock2;
	int gridSize_;
	int startX_;
	int startY_;

	int img_;

	int seTouch_;					//�u���b�N�G�����Ƃ�
	int seRotate_;					//��]

	Vector2 highlightPos_;			//�n�C���C�g���W
	BlockBase* highlightBlock;		//�n�C���C�g������u���b�N
	BlockBase* preHighlightBlock;	//

	int replaceCount;

	void InitBlock(void);
	void AddBlock(BlockBase* block);

	void BlockProcess(Vector2 pos);	//�u���b�N�̑��쏈��
	bool AreBlocksConnected(const BlockBase* block1, const BlockBase* block2) const;
	BlockBase* GetBlockAtPosition(int x, int y) const; // �}�E�X�ʒu�ɂ���u���b�N���擾����
	void UpdateElectricity(BlockBase* block);
	void ClearElectricity();	//�d�C�̏�Ԃ�S�����Z�b�g
	void PropagateElectricity(BlockBase* block); // �d�C��`�d������
	void ReplaceBlockWithPlusBlock();

	void HighlightUpdate();
	void HighlightDraw();

	void InitSoundEffect();
	void PlaySoundEffect();
};