#include <DxLib.h>
#include "../Manager/SceneManager.h"
#include "../Manager/InputManager.h"
#include "../Manager/ResourceManager.h"
#include"../Application.h"
#include "SelectScene.h"

SelectScene::SelectScene(void)
{
}

SelectScene::~SelectScene(void)
{
}

void SelectScene::Init(void)
{
	auto& res = ResourceManager::GetInstance();
	img_ = res.Load(ResourceManager::SRC::SELECT).handleId_;
	if (img_ == -1)
	{
		return;
	}
	select_ = SELECT_TYPE::EASY;  // �f�t�H���g�́u�J�n�v
	changeFlag_ = false;
	inputLock_ = false;  // ���̓��b�N�t���O��ǉ�
	stateFlag_ = false;
	lockTimer_ = 0;      // ���b�N���ԗp�ϐ�
}

void SelectScene::Update(void)
{
	State();

	InputManager& ins = InputManager::GetInstance();
	// ��ړ�
	isUpPressed_ = ins.IsTrgDown(KEY_INPUT_W);
	isDownPressed_ = ins.IsTrgDown(KEY_INPUT_S);

	//�Z���N�g����
	if (isUpPressed_)
	{
		if (select_ == SELECT_TYPE::EASY)
		{
			select_ = SELECT_TYPE::HARD;
		}
		else
		{
			select_ = static_cast<SELECT_TYPE>(static_cast<int>(select_) - 1);
		}
		stateFlag_ = true;
	}
	else if (isDownPressed_)
	{
		if (select_ == SELECT_TYPE::HARD)
		{
			select_ = SELECT_TYPE::EASY;
		}
		else
		{
			select_ = static_cast<SELECT_TYPE>(static_cast<int>(select_) + 1);
		}
		stateFlag_ = true;
	}
	if (!isUpPressed_ && !isDownPressed_)
	{
		stateFlag_ = false;
	}
}

void SelectScene::Draw(void)
{
	SetFontSize(16);
	int easy;
	easy = strlen("EASY");
	int normal;
	normal = strlen("NORMAL");
	int hard;
	hard = strlen("HARD");
	int select;
	select = strlen("��Փx�I��");

	DrawRotaGraph(Application::SCREEN_SIZE_X / 2,
		Application::SCREEN_SIZE_Y / 2,
		1.0f, 0.0f, img_, true, false);


	DrawString(0, 0, "select", 0xFFFFFF);

	SetFontSize(96);
	DrawString((Application::SCREEN_SIZE_X - GetDrawStringWidth("��Փx�I��",select )) / 2,10, "��Փx�I��", 0xffffff);
	if (select_ == SELECT_TYPE::EASY)
	{
		DrawString((Application::SCREEN_SIZE_X - GetDrawStringWidth("EASY", easy)) / 2, Application::SCREEN_SIZE_Y / 2 -128, "EASY", 0xffffff);
		DrawString((Application::SCREEN_SIZE_X - GetDrawStringWidth("NORMAL", normal)) / 2, Application::SCREEN_SIZE_Y / 2 +40, "NORMAL", 0xAAAAAA);
		DrawString((Application::SCREEN_SIZE_X - GetDrawStringWidth("HARD", hard)) / 2, Application::SCREEN_SIZE_Y / 2 + 200, "HARD", 0xAAAAAA);
	}
	if (select_ == SELECT_TYPE::NORMAL)
	{
		DrawString((Application::SCREEN_SIZE_X - GetDrawStringWidth("EASY", easy)) / 2, Application::SCREEN_SIZE_Y / 2 - 128, "EASY", 0xAAAAAA);
		DrawString((Application::SCREEN_SIZE_X - GetDrawStringWidth("NORMAL", normal)) / 2, Application::SCREEN_SIZE_Y / 2 + 40, "NORMAL", 0xFFFFFF);
		DrawString((Application::SCREEN_SIZE_X - GetDrawStringWidth("HARD", hard)) / 2, Application::SCREEN_SIZE_Y / 2 + 200, "HARD", 0xAAAAAA);
	}
	if (select_ == SELECT_TYPE::HARD)
	{
		DrawString((Application::SCREEN_SIZE_X - GetDrawStringWidth("EASY", easy)) / 2, Application::SCREEN_SIZE_Y / 2 - 128, "EASY", 0xAAAAAA);
		DrawString((Application::SCREEN_SIZE_X - GetDrawStringWidth("NORMAL", normal)) / 2, Application::SCREEN_SIZE_Y / 2 + 40, "NORMAL", 0xAAAAAA);
		DrawString((Application::SCREEN_SIZE_X - GetDrawStringWidth("HARD", hard)) / 2, Application::SCREEN_SIZE_Y / 2 + 200, "HARD", 0xFFFFFF);
	}
	SetFontSize(16);
}

//���菈��
void SelectScene::State(void)
{
	InputManager& ins = InputManager::GetInstance();
	if (!stateFlag_ && ins.IsTrgDown(KEY_INPUT_SPACE))
	{

		if (select_ == SELECT_TYPE::EASY)
		{
			SceneManager::GetInstance().ChangeScene(SceneManager::SCENE_ID::GAME);
		}
		if (select_ == SELECT_TYPE::NORMAL)
		{
			SceneManager::GetInstance().ChangeScene(SceneManager::SCENE_ID::GAME);
		}
		if (select_ == SELECT_TYPE::HARD)
		{
			SceneManager::GetInstance().ChangeScene(SceneManager::SCENE_ID::GAME);
		}
	}
}