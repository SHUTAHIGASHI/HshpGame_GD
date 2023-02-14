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

	// ���\�[�X�̓ǂݍ���
	LPCSTR font_path = "fontData/QuinqueFive.otf";	// �ǂݍ��ރt�H���g�t�@�C���̃p�X
	if (AddFontResourceEx(font_path, FR_PRIVATE, NULL) > 0) {

	}
	else {
		// �t�H���g�ǂݍ��݃G���[����
		MessageBox(NULL, "�t�H���g�ǂݍ��ݎ��s", "", MB_OK);
	}

	// �_�u���o�b�t�@���[�h
	SetDrawScreen(DX_SCREEN_BACK);

	ChangeFont("QuinqueFive");

	SetMouseDispFlag(false);

	InputState input;

	SceneManager scene;

	// �摜�̃��[�h
	scene.Init();

	bool isGameEnd = false;

	while (ProcessMessage() == 0)
	{
		LONGLONG time = GetNowHiPerformanceCount();
		SetMousePoint(static_cast<int>(Game::kScreenWidthHalf), static_cast<int>(Game::kScreenHeightHalf));

		// ��ʂ̃N���A
		ClearDrawScreen();

		input.Update();

		// ���݂̃V�[���̍X�V
		scene.Update(input, isGameEnd);

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

	SetMouseDispFlag(true);

	// �摜�̃A�����[�h
	scene.End();

	DxLib_End();				// �c�w���C�u�����g�p�̏I������

	return 0;				// �\�t�g�̏I�� 
}