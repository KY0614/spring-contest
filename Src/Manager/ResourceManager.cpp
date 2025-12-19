#include <DxLib.h>
#include "../Application.h"
#include "Resource.h"
#include "ResourceManager.h"

ResourceManager* ResourceManager::instance_ = nullptr;

void ResourceManager::CreateInstance(void)
{
	if (instance_ == nullptr)
	{
		instance_ = new ResourceManager();
	}
	instance_->Init();
}

ResourceManager& ResourceManager::GetInstance(void)
{
	return *instance_;
}

void ResourceManager::Init(void)
{

	// 推奨しませんが、どうしても使いたい方は
	using RES = Resource;
	using RES_T = RES::TYPE;
	static std::string PATH_IMG = Application::PATH_IMAGE;
	static std::string PATH_MDL = Application::PATH_MODEL;
	static std::string PATH_EFF = Application::PATH_EFFECT;
	static std::string PATH_SND = Application::PATH_SOUND;

	std::unique_ptr<Resource> res;

	//モデル
	res = std::make_unique<RES>(RES_T::MODEL, PATH_MDL + "Player/無題.mv1");
	resourcesMap_.emplace(SRC::PLAYER, std::move(res));
	res = std::make_unique<RES>(RES_T::MODEL, PATH_MDL + "Enemy/minigann.mv1");
	resourcesMap_.emplace(SRC::ENEMYM, std::move(res));

	res = std::make_unique<RES>(RES_T::MODEL, PATH_MDL + "Enemy/usi.mv1");
	resourcesMap_.emplace(SRC::ENEMYU, std::move(res));

	res = std::make_unique<RES>(RES_T::MODEL, PATH_MDL + "Enemy/ranntya.mv1");
	resourcesMap_.emplace(SRC::ENEMYR, std::move(res));

	res = std::make_unique<RES>(RES_T::MODEL, PATH_MDL + "Stage/Stage.mv1");
	resourcesMap_.emplace(SRC::STAGE, std::move(res));

	res = std::make_unique<RES>(RES_T::MODEL, PATH_MDL + "Stage/cora.mv1");
	resourcesMap_.emplace(SRC::CLEARSTAGE, std::move(res));

	res = std::make_unique<RES>(RES_T::MODEL, PATH_MDL + "Stage/gameovera.mv1");
	resourcesMap_.emplace(SRC::GAMEOVERA, std::move(res));


	//エフェクト
	res = std::make_unique<RES>(RES_T::MODEL, PATH_MDL + "Effect/Fireball.mv1");
	resourcesMap_.emplace(SRC::EFFCT1, std::move(res));


	//サウンド
	//SE
	res = std::make_unique<RES>(RES_T::SOUND, PATH_SND + "SE/回避.mp3");
	resourcesMap_.emplace(SRC::AVOID, std::move(res));
	res = std::make_unique<RES>(RES_T::SOUND, PATH_SND + "SE/AS_846334_魔法音.mp3");
	resourcesMap_.emplace(SRC::SLOU, std::move(res));
	res = std::make_unique<RES>(RES_T::SOUND, PATH_SND + "SE/剣で打ち合う3.mp3");
	resourcesMap_.emplace(SRC::PARRY, std::move(res));
	res = std::make_unique<RES>(RES_T::SOUND, PATH_SND + "SE/盾で防御.mp3");
	resourcesMap_.emplace(SRC::GUARD, std::move(res));
	res = std::make_unique<RES>(RES_T::SOUND, PATH_SND + "SE/刀で斬る2.mp3");
	resourcesMap_.emplace(SRC::HIT, std::move(res));
	res = std::make_unique<RES>(RES_T::SOUND, PATH_SND + "SE/AS_778954_キン-モノラル（剣の当たる音）攻撃・防御_Audio Trimmer.mp3");
	resourcesMap_.emplace(SRC::NODAME, std::move(res));
	res = std::make_unique<RES>(RES_T::SOUND, PATH_SND + "SE/AS_221787_斬撃・刺す4・槍や剣_Audio Trimmer.mp3");
	resourcesMap_.emplace(SRC::DAMAGE, std::move(res));

	//BGM
	res = std::make_unique<RES>(RES_T::SOUND, PATH_SND + "Bgm/Title.mp3");
	resourcesMap_.emplace(SRC::TITLEBGM, std::move(res));
	res = std::make_unique<RES>(RES_T::SOUND, PATH_SND + "Bgm/game.mp3");
	resourcesMap_.emplace(SRC::GAMEBGM, std::move(res));
	res = std::make_unique<RES>(RES_T::SOUND, PATH_SND + "Bgm/over.mp3");
	resourcesMap_.emplace(SRC::GAMEOVERBGM, std::move(res));
	res = std::make_unique<RES>(RES_T::SOUND, PATH_SND + "Bgm/clia.mp3");
	resourcesMap_.emplace(SRC::CLEARBGM, std::move(res));

	

}

void ResourceManager::Release(void)
{
	for (auto& p : loadedMap_)
	{
		p.second.Release();
	}

	loadedMap_.clear();
}

void ResourceManager::Destroy(void)
{
	Release();
	resourcesMap_.clear();
	delete instance_;
}

const Resource& ResourceManager::Load(SRC src)
{
	Resource& res = _Load(src);
	if (res.type_ == Resource::TYPE::NONE)
	{
		return dummy_;
	}
	return res;
}

int ResourceManager::LoadModelDuplicate(SRC src)
{
	Resource& res = _Load(src);
	if (res.type_ == Resource::TYPE::NONE)
	{
		return -1;
	}

	int duId = MV1DuplicateModel(res.handleId_);
	res.duplicateModelIds_.push_back(duId);

	
	return duId;
}

ResourceManager::ResourceManager(void)
{
}

Resource& ResourceManager::_Load(SRC src)
{

	// ロード済みチェック
	const auto& lPair = loadedMap_.find(src);
	if (lPair != loadedMap_.end())
	{
		return lPair->second;
	}

	// リソース登録チェック
	const auto& rPair = resourcesMap_.find(src);
	if (rPair == resourcesMap_.end())
	{
		// 登録されていない
		return dummy_;
	}

	// ロード処理
	rPair->second->Load();

	// 念のためコピーコンストラクタ
	loadedMap_.emplace(src, *rPair->second);

	return *rPair->second;

}
