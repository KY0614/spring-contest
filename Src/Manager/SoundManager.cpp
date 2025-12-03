#include <DxLib.h>
#include "SoundManager.h"

SoundManager* SoundManager::instance_ = nullptr;

void SoundManager::CreateInstance(void)
{
	if (instance_ == nullptr)
	{
		instance_ = new SoundManager();

		instance_->Init();
	}

}

SoundManager& SoundManager::GetInstance(void)
{
	// TODO: return ステートメントをここに挿入します
	if (instance_ == nullptr)
	{
		SoundManager::CreateInstance();
	}
	return *instance_;
}

void SoundManager::Init(void)
{
	se_ = -1;
	slowSE_ = -1;
	bgm_ = -1;
}


void SoundManager::PlayBGM(int handle,int volume)
{
	// 既にBGMが再生されている場合は停止する
	if (bgm_ != -1)
	{
		StopSoundMem(bgm_);
		DeleteSoundMem(bgm_);
		bgm_ = -1;
	}


	// BGMを再生する
	bgm_ = DuplicateSoundMem(handle);
	ChangeVolumeSoundMem(volume,bgm_ );
	if (bgm_ != -1)
	{
		PlaySoundMem(bgm_, DX_PLAYTYPE_LOOP);
	}
	
}

void SoundManager::PlaySlowBGM(int handle)
{
	// 既にBGMが再生されている場合は停止する
	if (bgm_ != -1)
	{
		StopSoundMem(bgm_);
		DeleteSoundMem(bgm_);
		bgm_ = -1;
	}
	// BGMを二分の一の速度で再生する
	bgm_ = DuplicateSoundMem(handle);
	int slowBGM = GetFrequencySoundMem(handle);
	if (bgm_ != -1)
	{
		SetFrequencySoundMem(slowBGM / 2, bgm_);
		PlaySoundMem(bgm_, DX_PLAYTYPE_LOOP);
	}
}

void SoundManager::StopBGM()
{
	// BGMを停止する
	if (bgm_ != -1)
	{
		StopSoundMem(bgm_);
		DeleteSoundMem(bgm_);
		bgm_ = -1;
	}
}

void SoundManager::PlaySE(int handle)
{
	se_= DuplicateSoundMem(handle);
	// 複製したハンドルを再生する
	if (se_ != -1) 
	{
		PlaySoundMem(se_, DX_PLAYTYPE_BACK);
	}

}

void SoundManager::PlaySlowSE(int handle)
{
	se_ = DuplicateSoundMem(handle);
	slowSE_ = GetFrequencySoundMem(handle);
	// 複製したハンドルを再生する
	if (se_ != -1)
	{
		SetFrequencySoundMem(slowSE_/2, se_);
		PlaySoundMem(se_, DX_PLAYTYPE_BACK);
	}
}

void SoundManager::StopSE()
{
	StopSoundMem(se_);
}


