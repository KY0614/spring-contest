#include "ShotStraight.h"


ShotStraight::ShotStraight(TYPE type, int baseModelId) : ShotBase(type, baseModelId)
{
}

ShotStraight::~ShotStraight(void)
{
}

void ShotStraight::SetParam(void)
{

	

	//‘¬“x
	speed_ = 8.0f;

	// ¶‘¶”»’è‚Ì‰Šú‰»
	isAlive_ = true;

	cntAlive_ = 300;

	


}