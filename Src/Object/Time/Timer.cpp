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
    //�����̐F�̎擾
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

            //�J�E���g�𑝉�������
            count--;
            countTime = 0;
        }
    }
}

void Timer::Draw(void)
{


    DrawFormatString(900, 20, White, "�c�莞��%ds", count);
}