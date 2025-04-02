#include "DxLib.h"
#include "../../Manager/SceneManager.h"
#include "../../Manager/InputManager.h"
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
    //�������Ԑݒ�
    count = 40;
}

void Timer::Update(void)
{
    InputManager& ins = InputManager::GetInstance();

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


    DrawString(350, 20, "�c�莞��", 0xffffff);
    SetFontSize(40);
    DrawFormatString(550, 25, White, "%ds", count);
}