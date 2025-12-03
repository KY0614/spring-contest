#pragma once
class SoundManager
{
public:

	


	// インスタンスの生成
	static void CreateInstance(void);

	// インスタンスの取得
	static SoundManager& GetInstance(void);

	void Init(void);

	
	void PlayBGM(int handle,int volume);
	void PlaySlowBGM(int handle);
	void StopBGM();
	void PlaySE(int handle);
	void PlaySlowSE(int handle);
	void StopSE();

private:
	static SoundManager* instance_;

	int se_;
	int slowSE_;

	int bgm_;
	

};

