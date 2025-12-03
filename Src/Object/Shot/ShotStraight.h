#pragma once
#include "ShotBase.h"
class ShotStraight : public ShotBase
{
public:
	ShotStraight(TYPE type, int baseModelId);

	//デストラクタ
	~ShotStraight(void);



protected:

	void SetParam(void)override;

	/*void Update(void)override;*/

};

