#pragma once
class Timer
{

public:

    // �R���X�g���N�^
    Timer(void);

    // �f�X�g���N�^
    ~Timer(void);

    void Init(void);
    void Update(void);
    void Draw(void);

private:

    //int i, a = 0;
    int White;

    int countTime;
    int count;

};

