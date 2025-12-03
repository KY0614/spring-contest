#include "ShotStraight.h"


ShotStraight::ShotStraight(TYPE type, int baseModelId) : ShotBase(type, baseModelId)
{
}

ShotStraight::~ShotStraight(void)
{
}

void ShotStraight::SetParam(void)
{

	scales_ = { 0.4f,0.4f,0.4f };

	//ë¨ìx
	speed_ = 8.0f;

	// ê∂ë∂îªíËÇÃèâä˙âª
	isAlive_ = true;

	cntAlive_ = 300;

	collisionRadius_ = 30.0f;


}