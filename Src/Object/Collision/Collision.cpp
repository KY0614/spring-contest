
#include <DxLib.h>
#include "../../Manager/ResourceManager.h"
#include "../../Manager/SoundManager.h"
#include "../../Manager/EnemyManager.h"
#include "../../Utility/AsoUtility.h"
#include "../../Object/Player/Player.h"
#include "../../Object/Enemy/EnemyBase.h"
#include "../../Object/Shot/ShotBase.h"
#include "../../Object/Stage/Stage.h"
#include "../../Scene/GameScene.h"

#include "Collision.h"

Collision::Collision()
{


}

Collision::~Collision()
{
}

void Collision::Init(Player* player, EnemyManager* enemyManager,GameScene*game,Stage*stage)
{
	ResourceManager& res = ResourceManager::GetInstance(); // リソースマネー
	DamageSE_ = res.Load(ResourceManager::SRC::DAMAGE).handleId_;
	HitSE_ = res.Load(ResourceManager::SRC::HIT).handleId_;
	noDamageSE_ = res.Load(ResourceManager::SRC::NODAME).handleId_;

	player_ = player;
	enemyManager_ = enemyManager;
	game_ = game;
	stage_ = stage;

	ribasDir_ = 0;
}

void Collision::Update(void)
{
	ribasDir_++;

	if (ribasDir_ >= RIBAS_DIR)
	{
		ribasDir_ = RIBAS_DIR + 1;
	}

	if (!player_->IsCollisionState())
	{
		return;
	}


	enemys_ = enemyManager_->GetEnemys();
	enemys_ = enemyManager_->GetEnemys();

	// 1. エネミー同士の重なり防止
	for (size_t i = 0; i < enemys_.size(); ++i)
	{
		for (size_t j = i + 1; j < enemys_.size(); ++j)
		{
			if (!enemys_[i]->IsCollisionState() || !enemys_[j]->IsCollisionState()) continue;

			VECTOR posA = enemys_[i]->GetPos();
			VECTOR posB = enemys_[j]->GetPos();

			// y軸を無視して押し出し
			Puss(posA, enemys_[i]->GetRadius(), posB, enemys_[j]->GetRadius());

			enemys_[i]->SetPos(posA);
			enemys_[j]->SetPos(posB);
		}
	}

	// 2. プレイヤーと全エネミーの重なり防止
	for (EnemyBase* enemy : enemys_)
	{
		if (!enemy->IsCollisionState()) continue;

		VECTOR ePos = enemy->GetPos();
		VECTOR pPos = player_->GetPos();

		// プレイヤーの半径は、状況に応じて適切なものを選択してください
		Puss(ePos, enemy->GetRadius(), pPos, player_->GetCollisionRadiusGS());

		enemy->SetPos(ePos);
		player_->SetPos(pPos);
		if (!enemy->IsCollisionState())
		{
			continue;
		}

		
		VECTOR posP= player_->GetPos();
		VECTOR posS= stage_->GetPos();
		StageStop(posP, posS, stage_->GetRadius());
		


		//エネミー攻撃とプレイヤー
		if (enemy->GetState() == EnemyBase::STATE::ATTACK)
		{
			//ダメージを受けつかないとき
			if (player_->GetState() == Player::STATE::GUARD || player_->GetState() == Player::STATE::AVOID || player_->GetState() == Player::STATE::PARRY)
			{
				if (HitSphere(enemy->GetAttackPos(), enemy->GetAttackRadius(), player_->GetPos(), player_->GetCollisionRadiusGS()))
				{
					if (player_->GetState() == Player::STATE::PARRY)
					{
						enemy->ChangeState(EnemyBase::STATE::STAN);
					}
					else
					{
						enemy->ChangeState(EnemyBase::STATE::STANDBY);
					}

					player_->HitGS(true);
				}
			}
			else//ダメージを受け付けるとき
			{

				if (HitSphere(enemy->GetAttackPos(), enemy->GetAttackRadius(), player_->GetPos(), player_->GetCollisionRadiusH()))
				{
					enemy->ChangeState(EnemyBase::STATE::STANDBY);
					player_->HitH(true);
				}

			}
		}
		//プレイヤー攻撃とエネミー
		if (player_->GetState() == Player::STATE::ATTACK)
		{
			if (game_->GetIsSlow() == true || enemy->GetState() == EnemyBase::STATE::STAN)
			{

				if (HitSphere(enemy->GetPos(), enemy->GetRadius(), player_->GetAttackPos(), player_->GetAttackRange()))
				{

					auto& ins = SoundManager::GetInstance();
					ins.PlaySE(HitSE_);
					enemy->Damage(1);

				}
			}

		}

		shots_ = enemy->GetShot();
		for (ShotBase* shot : shots_)
		{
			if (shot->GetAttack() == ShotBase::ATTACK_HIT::ENEMY)
			{
				if (player_->GetState() == Player::STATE::GUARD || player_->GetState() == Player::STATE::AVOID || player_->GetState() == Player::STATE::PARRY)
				{

					//プレイヤーと弾
					if (HitSphere(player_->GetPos(), player_->GetCollisionRadiusGS(), shot->GetPos(), shot->GetRadius()))
					{
						if (shot->IsAlive())
						{
							if (player_->GetState() == Player::STATE::PARRY)//ダメージを受け付けないとき（弾反射
							{
								if (ribasDir_ >= RIBAS_DIR)
								{
									ribasDir_ = 0;
									shot->ReDir();
								}
								player_->HitGS(true);
							}
							else//ダメージを受け付けないとき（弾消滅
							{
								shot->SetIsAlive(false);
								player_->HitGS(true);
							}
						}
					}

				}
				else
				{
					//ダメージを受け付ける
					if (HitSphere(player_->GetPos(), player_->GetCollisionRadiusH(), shot->GetPos(), shot->GetRadius()))
					{
						if (shot->IsAlive())
						{

							shot->SetIsAlive(false);
							player_->HitH(true);

						}
					}
				}
			}
			else if (shot->GetAttack() == ShotBase::ATTACK_HIT::PLAYER)
			{
				if (HitSphere(enemy->GetPos(), enemy->GetRadius(), shot->GetPos(), shot->GetRadius()))
				{
					if (shot->IsAlive())
					{
						shot->SetIsAlive(false);
						enemy->Damage(1);
						// デバッグログを出すと確実です
						// printf("Hit Enemy!\n"); 
					}
				}
			}
		}

	}



}

bool Collision::HitSphere(VECTOR pos1, float radius1, VECTOR pos2, float radius2)
{
	VECTOR Hit;
	Hit.x = pos1.x - pos2.x;
	Hit.y = pos1.y - pos2.y;
	Hit.z = pos1.z - pos2.z;

	float dis =Hit.x * Hit.x + Hit.y * Hit.y + Hit.z * Hit.z;
	float radius = (radius1 + radius2) * (radius1 + radius2);
	if (dis <= radius)
	{
		return true;
	}
	return false;
	
}

void Collision::Puss(VECTOR& pos1, float radius1, VECTOR& pos2, float radius2)
{
	// xとzの差分だけを計算する（yを0にする）
	VECTOR Hit = VSub(pos1, pos2);
	Hit.y = 0.0f; // y軸の差分を無視

	float dis_sq = Hit.x * Hit.x + Hit.z * Hit.z;
	float sum_radii = radius1 + radius2;
	float sum_radii_sq = sum_radii * sum_radii;

	// 衝突判定（2D平面上での判定）
	if (dis_sq < sum_radii_sq && dis_sq != 0.0f)
	{
		float dis = sqrt(dis_sq);
		float overlap = sum_radii - dis;

		// 押し出し方向ベクトル（yは0）
		VECTOR normal = VScale(Hit, 1.0f / dis);

		// 移動量の計算（半分ずつ）
		VECTOR move_amount = VScale(normal, overlap * 0.5f);

		// pos1, pos2 の x と z だけを更新する
		pos1.x += move_amount.x;
		pos1.z += move_amount.z;

		pos2.x -= move_amount.x;
		pos2.z -= move_amount.z;
	}
	else if (dis_sq == 0.0f)
	{
		// 完全に重なっている場合は、x軸方向に少しずらす
		pos1.x += sum_radii * 0.5f;
		pos2.x -= sum_radii * 0.5f;
	}
}
void Collision::StageStop(VECTOR pos1, VECTOR pos2, float radius2)
{
	pos1.y = 0.0f;
	pos2.y = 0.0f;
	VECTOR vec = VSub(pos1, pos2);
	VECTOR dir = VNorm(vec);
	float dis = AsoUtility::Distance(pos1, pos2);

	if (dis > radius2)
	{
		VECTOR pos = VAdd(pos2, VScale(dir, radius2));
		pos.y = player_->GetPos().y;
		player_->SetPos(pos);
	}

}
