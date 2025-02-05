#pragma once
class Player
{

public:
	//定数



private:
	//変数
	

	//座標保存用
	int posX_;
	int posY_;



	//デバッグ
	int count_;
	int cr_;

public:
	//

	//初期化
	void Init(void);
	//アプデ
	void Updeta(void);
	//移動
	void MoveUpdeta(void);
	//描画
	void Draw(void);
	//削除
	void Rerease(void);

};

