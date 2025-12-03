
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

}

void Collision::Update(void)
{
	if (!player_->IsCollisionState())
	{
		return;
	}


	enemys_ = enemyManager_->GetEnemys();
	for (EnemyBase* enemy : enemys_)
	{
		for (EnemyBase* enemy2 : enemys_)
		{
			if (enemy == enemy2)
			{
				continue;
			}
			VECTOR posA = enemy->GetPos();
			VECTOR posB = enemy2->GetPos();
			Puss(posA, enemy->GetRadius(), posB, enemy2->GetRadius());
			enemy->SetPos(posA);
			enemy2->SetPos(posB);
		}
	
		
		if (!enemy->IsCollisionState())
		{
			continue;
		}

		/*VECTOR tempPosA = enemy->GetPos();
		VECTOR tempPosB = player_->GetPos();
		Puss(tempPosA, enemy->GetRadius(), tempPosB, player_->GetCollisionRadiusH());
		enemy->SetPos(tempPosA);
		player_->SetPos(tempPosB);*/
		VECTOR posP= player_->GetPos();
		VECTOR posS= stage_->GetPos();
		StageStop(posP, posS, stage_->GetRadius());
		



		if (enemy->GetState() == EnemyBase::STATE::ATTACK)
		{
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
			else
			{

				if (HitSphere(enemy->GetAttackPos(), enemy->GetAttackRadius(), player_->GetPos(), player_->GetCollisionRadiusH()))
				{
					enemy->ChangeState(EnemyBase::STATE::STANDBY);
					player_->HitH(true);
				}

			}
		}
		
		if (player_->GetState() == Player::STATE::ATTACK)
		{


			if (HitSphere(enemy->GetPos(), enemy->GetRadius(), player_->GetAttackPos(), player_->GetAttackRange()))
			{
				if (game_->GetIsSlow() == true|| enemy->GetState() == EnemyBase::STATE::STAN)
				{
					auto& ins = SoundManager::GetInstance();
					ins.PlaySE(HitSE_);
					enemy->Damage(1);
				}
				else
				{

				}
			}
		}

		shots_ = enemy->GetShot();
		for (ShotBase* shot : shots_)
		{
			if (player_->GetState() == Player::STATE::GUARD || player_->GetState() == Player::STATE::AVOID || player_->GetState() == Player::STATE::PARRY)
			{
				if (HitSphere(player_->GetPos(), player_->GetCollisionRadiusGS(), shot->GetPos(), shot->GetRadius()))
				{
					if (shot->IsAlive())
					{
						if (player_->GetState() == Player::STATE::PARRY)
						{
							shot->ReDir();
							player_->HitGS(true);
						}
						else
						{
							shot->SetIsAlive(false);
							player_->HitGS(true);
						}
					}
				}
			}
			else
			{
				if (HitSphere(player_->GetPos(), player_->GetCollisionRadiusH(), shot->GetPos(), shot->GetRadius()))
				{
					if (shot->IsAlive())
					{

						shot->SetIsAlive(false);
						player_->HitH(true);

					}
				}
			}
			if (HitSphere(enemy->GetPos(), enemy->GetRadius(), shot->GetPos(), shot->GetCollisionRadius()))
			{
				if (shot->IsAlive())
				{

					shot->SetIsAlive(false);
					enemy->Damage(1);
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
	VECTOR Hit;
	Hit.x = pos1.x - pos2.x;
	Hit.y = pos1.y - pos2.y;
	Hit.z = pos1.z - pos2.z;

	float dis_sq = Hit.x * Hit.x + Hit.y * Hit.y + Hit.z * Hit.z;
	float sum_radii = radius1 + radius2;
	float sum_radii_sq = sum_radii * sum_radii;

	if (dis_sq < sum_radii_sq && dis_sq != 0.0f) // dis_sq が 0 のケースは別途処理
	{
		float dis = sqrt(dis_sq); // 実際の距離 d を計算
		float overlap = sum_radii - dis; // めり込み量 O = R - d

		// 衝突方向の単位ベクトル (Normal) を計算
		VECTOR normal = VScale(Hit, 1.0f / dis);

		// それぞれが移動すべき量 (めり込み量の半分)
		VECTOR move_amount = VScale(normal, overlap * 0.5f);

		// pos1 は normal 方向に押し出し
		pos1 = VAdd(pos1, move_amount);
		// pos2 は normal と逆方向に押し出し
		pos2 = VSub(pos2, move_amount);
	}
	// dis_sq が 0 の場合の処理（位置が完全に一致している場合）
	else if (dis_sq == 0.0f)
	{
		// pos1 と pos2 を適当な方向に強制的に分離する
		float overlap = sum_radii;
		pos1.z += overlap * 0.5f;
		pos2.z -= overlap * 0.5f;
	}

	float dis = Hit.x * Hit.x + Hit.y * Hit.y + Hit.z * Hit.z;
	float radius = (radius1 + radius2);

	

	if (dis<(radius*radius))
	{
		float in = radius - dis;
		if (dis == 0.0f)
		{
			pos1.z += in * 0.5f;
			pos2.z -= in * 0.5f;
			return;
		}
		VECTOR normal = VScale(Hit, 1.0f / dis);
		VECTOR move1 = VScale(normal, in * 0.5f);
		VECTOR move2 = VScale(normal, in * 0.5f);

		pos1 = VAdd(pos1, move1);
		pos2 = VSub(pos2, move2);
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
