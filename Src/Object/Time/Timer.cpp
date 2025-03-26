#include "DxLib.h"

#include"Timer.h"


Timer::Timer(void)
{
}

Timer::~Timer(void)
{
}

void Timer::Init(void)
{
    //文字の色の取得
    White = GetColor(255, 255, 255);
    countTime = 0;
    count = 30;



}

void Timer::Update(void)
{
    countTime += 1;

    if (countTime == 120)
    {

        if (count > 0)
        {

            //カウントを増加させる
            count--;
            countTime = 0;
        }
    }
}

void Timer::Draw(void)
{


    DrawFormatString(900, 20, White, "残り時間%ds", count);
}