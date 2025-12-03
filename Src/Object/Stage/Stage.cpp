#include <DxLib.h>
#include "../../Application.h"
#include "../../Manager/ResourceManager.h"
#include "../../Utility/AsoUtility.h"
#include "../../Utility/MatrixUtility.h"



#include "Stage.h"

Stage::Stage()
{
}

Stage::~Stage()
{
}

void Stage::Init()
{
	ResourceManager& res = ResourceManager::GetInstance(); // リソースマネージャのインスタンス取得


	model_ = res.Load(ResourceManager::SRC::STAGE).handleId_;
	pos_= {0.0f,0.0f,0.0f};
	localRot_ = {0.0f,0.0f,0.0f};
	rot_ = {0.0f,0.0f,0.0f};
	scl_ = {3.0f,3.0f,3.0f};
	radius_ = 2500.0f;
	MV1SetPosition(model_, pos_);
	MV1SetRotationMatrix(model_, MatrixUtility::Multiplication(localRot_, rot_));
	MV1SetScale(model_, scl_);

	// モデルの自己発光色設定
	MV1SetMaterialEmiColor(model_, 0, COLOR_EMI_DEFAULT);
}

void Stage::Update()
{
}

void Stage::Draw()
{
	MV1DrawModel(model_);
	
#ifdef _DEBUG
	DrawSphere3D(pos_, radius_, 16, 0x00FF00FF, 0x0000FFFF, false);
#endif
}
