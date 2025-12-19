#include "ShotBase.h"
ShotBase::ShotBase(TYPE type, int baseModelId)
{
    // 使用メモリ容量と読み込み時間の削減のため
    // モデルデータをいくつもメモリ上に存在させない
    // CreateShotで処理してしまうと、再利用する度にモデルが複製され、
    // Releaseもされない状況になってしまう
    modelId_ = MV1DuplicateModel(baseModelId);
    type_ = type;
}
ShotBase::~ShotBase(void)
{
}
void ShotBase::CreateShot(VECTOR pos, VECTOR dir ,VECTOR scl,float rad)
{
    // 弾の発射位置を設定
    pos_ = pos;
    // 弾の発射方向の設定
    dir_ = dir;

    scales_ = scl;

    collisionRadius_ = rad;

    ChangeAttack(ATTACK_HIT::ENEMY);
    //// 使用メモリ容量と読み込み時間の削減のため
    //// モデルデータをいくつもメモリ上に存在させない
    //modelId_ = MV1DuplicateModel(baseModelId_);
    // パラメータ設定
    SetParam();
    // 大きさの設定
    MV1SetScale(modelId_, scales_);
    // 位置の設定
    MV1SetPosition(modelId_, pos_);
}
void ShotBase::Update(void)
{
    if (!IsAlive())
    {
        // 生存していなければ処理中断
        return;
    }
    // 弾を移動させる
    // 移動量の計算(方向×スピード)
    VECTOR movePow = VScale(dir_, speed_);
    // 移動処理
    pos_ = VAdd(pos_, movePow);
    // 位置の設定
    MV1SetPosition(modelId_, pos_);

    // 生存カウンタの減少
    ReduceCntAlive();
}
void ShotBase::Draw()
{

    if (!IsAlive())
    {
        // 生存していなければ処理中断
        return;
    }
    // モデルの描画

    MV1DrawModel(modelId_);
#ifdef _DEBUG
    // デバッグ用：衝突判定用球体
    DrawSphere3D(pos_, collisionRadius_, 10, 0x0000ff, 0x0000ff, false);
#endif // _DEBUG
}
void ShotBase::Release(void)
{
    MV1DeleteModel(modelId_);
}
bool ShotBase::IsAlive(void)
{
    return isAlive_;
}
void ShotBase::SetIsAlive(bool is)
{
    	isAlive_ = is;
}
VECTOR ShotBase::GetPos(void)
{
    return pos_;
}
float ShotBase::GetCollisionRadius(void)
{
    return collisionRadius_;
}
ShotBase::TYPE ShotBase::GetType(void)
{
    return type_;
}

ShotBase::ATTACK_HIT ShotBase::GetAttack(void)
{
    return attack_;
}

void ShotBase::SetParam(void)
{
}
void ShotBase::ReduceCntAlive(void)
{
    cntAlive_--;
    if (cntAlive_ < 0)
    {
        isAlive_ = false;
    }
}

float ShotBase::GetRadius(void)
{
    return collisionRadius_;
}

void ShotBase::ReDir(void)
{
    dir_ = VScale(dir_, -1.0f);
    ChangeAttack(ATTACK_HIT::PLAYER);
}

void ShotBase::ChangeAttack(ATTACK_HIT attack)
{
    attack_ = attack;

    switch (attack_)
    {
    case ShotBase::ATTACK_HIT::ENEMY:
        break;
    case ShotBase::ATTACK_HIT::PLAYER:
        break;
    }
}

