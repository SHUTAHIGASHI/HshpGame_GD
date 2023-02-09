#include "DxLib.h"
#include "game.h"
#include "SceneMain.h"
#include "SceneManager.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	// �E�B���h�E���[�h�ݒ�
	ChangeWindowMode(Game::kWindowMode);
	// �E�B���h�E���ݒ�
	SetMainWindowText(Game::kTitleText);
	// ��ʃT�C�Y�̐ݒ�
	SetGraphMode(Game::kScreenWidth, Game::kScreenHeight, Game::kColorDepth);

	if (DxLib_Init() == -1)		// �c�w���C�u��������������
	{
		return -1;			// �G���[���N�����璼���ɏI��
	}

	// �_�u���o�b�t�@���[�h
	SetDrawScreen(DX_SCREEN_BACK);

	ChangeFont("QuinqueFive");

	InputState input;

	SceneManager scene;

	// �摜�̃��[�h
	scene.Init();

	bool isGameEnd = false;

	while (ProcessMessage() == 0)
	{
		LONGLONG time = GetNowHiPerformanceCount();

		// ��ʂ̃N���A
		ClearDrawScreen();

		input.Update();

		// ���݂̃V�[���̍X�V
		scene.update(input, isGameEnd);

		// ���݂̃V�[���̕`��
		scene.Draw();

		// ����ʂ�\��ʂƓ���ւ���
		ScreenFlip();

		//if (CheckHitKey(KEY_INPUT_ESCAPE)) isGameEnd = true;
			
		if(isGameEnd) break;

		while (GetNowHiPerformanceCount() - time < 16667)
		{

		}
	}

	// �摜�̃A�����[�h
	scene.End();

	DxLib_End();				// �c�w���C�u�����g�p�̏I������

	return 0;				// �\�t�g�̏I�� 
}