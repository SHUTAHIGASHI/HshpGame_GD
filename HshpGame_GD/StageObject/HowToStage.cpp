#include "HowToStage.h"
#include "game.h"
#include "HowToPlayer.h"
#include <cassert>

namespace
{
	//�}�b�v�f�[�^
	// 1 �S�[�� / 2 �u���b�N / 3 �W�����v�����O / 4 �W�����v�p�b�h 
	// 5 �X�p�C�N / 6 �O���r�e�B�����O / 7 �_�b�V�������O / 8 ���o�[�X�����O

	//{2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2},
	//{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},

	// �X�e�[�W�P
	int CubeTest[Game::kScreenHeightNum][Game::kScreenWidthNum] = {
		{2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,0,0,0,0,0,2,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,2,0,0,0,0,0,0,0,2,2,0,0,2,2,0,0,2,2,0,0,0,0,0,0,0,0,0,0,0},
		{2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,5,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,0,0,2,2,2,2,2,2,2,2,2,2}
	};

	// �X�e�[�W�Q
	int JumpRingTest[Game::kScreenHeightNum][Game::kScreenWidthNum] = {
		{2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,3,0,0,0,0,0,0,0,0,0,0,0,0,0,3,0,0,5,0,0,3,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,0,0,0,0,0,0,0,0,0},
		{2,2,2,2,2,2,2,2,2,2,2,0,0,0,0,0,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2}
	};

	// �X�e�[�W�R
	int GravityRingTest[Game::kScreenHeightNum][Game::kScreenWidthNum] = {
		{2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,6,0,0,0,0,0,0,0,6,0,0,0,0,0,0,0,0,6,0,0,0,0,0,0,0,6,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,6,0,0,0,0,0,0,0,6,0,0,0,0,0,0,0,0,6,0,0,0,0,0,0,0,6,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{5,5,5,5,5,5,5,5,5,5,5,5,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,5,5,5,5,5,5,5,5,5,5,5,5},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,6,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,6,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,6,0,0,0,0,0,0,0,0,0,0,0,0,0,0,6,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{2,2,2,2,2,2,2,2,2,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,2,2,2,2,2,2,2,2,2}
	};

	// �X�e�[�W�S
	int DashRingTest[Game::kScreenHeightNum][Game::kScreenWidthNum] = {
		{2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,7,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,7,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,2,2,2,2,2,2,2,2,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,2,2,2,2,2,2,2,2,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,5,5,5,5,5,5,5,5,5,5,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,5,0,0,0,0,0,0,0,0,0,7,0,0,0,0,0,0,0,0,0,0,0,0,7,0,0,0,0,0,0,0,0,0,5,0,0,0},
		{0,0,0,5,0,0,0,0,0,0,0,0,0,7,0,0,0,0,0,0,0,0,0,0,0,0,7,0,0,0,0,0,0,0,0,0,5,0,0,0},
		{0,0,0,5,0,0,0,0,0,0,0,0,0,7,0,0,0,0,0,0,0,0,0,0,0,0,7,0,0,0,0,0,0,0,0,0,5,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,5,5,5,5,5,5,5,5,5,5,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2}
		// �X�e�[�W�n��
	};

	// �X�e�[�W�T
	int RevRingTest[Game::kScreenHeightNum][Game::kScreenWidthNum] = {
		{2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,8,0,0,0,0,0,8,0,0,0,0,0,8,0,0,0,0,0,8,0,0,0,0,0,0,8,0,0,0,0,0,8,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,8,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,8,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}
	};
}

namespace
{
	// �X�N���[���̑��x
	constexpr int kScrollSpeed = 7;

	// �T�C�Y�����p�萔
	constexpr float kResizeScale = 8.0f;
}

HowToStage::HowToStage() :
	m_updateFunc(&HowToStage::NormalUpdate),
	m_pHPlayer(nullptr),
	m_stageState(HowToStageState::CubeTest),
	m_stage(),
	m_hBg(-1),
	m_hBlock(-1)
{
}

void HowToStage::Init(int hSpike, int hBg, int hPortal, int hBlock)
{
	m_hBg = hBg;
	m_hBlock = hBlock;

	for (int i = 0; i < Game::kScreenHeightNum; i++)
	{
		for (int j = 0; j < Game::kScreenWidthNum; j++)
		{
			m_ObjectBlock[i][j].Init(hBlock);
			m_ObjectJumpRing[i][j].Init();
			m_ObjectJumpPad[i][j].Init();
			m_ObjectSpike[i][j].Init(hSpike);
			m_ObjectGravityRing[i][j].Init();
			m_ObjectDashRing[i][j].Init();
			m_ObjectReverseRing[i][j].Init();
		}
	}

	StageManage();
	SetStage();
}

void HowToStage::SetStage()
{
	for (int i = 0; i < Game::kScreenHeightNum; i++)
	{
		for (int j = 0; j < Game::kScreenWidthNum; j++)
		{
			float blockPosX, blockPosY;
			blockPosX = j * Game::kBlockSize;
			blockPosY = i * Game::kBlockSize;

			if (m_stage[i][j] == 2) m_ObjectBlock[i][j].SetPos(blockPosX, blockPosY);
			if (m_stage[i][j] == 3) m_ObjectJumpRing[i][j].SetPos(blockPosX, blockPosY);
			if (m_stage[i][j] == 4) m_ObjectJumpPad[i][j].SetPos(blockPosX, blockPosY);
			if (m_stage[i][j] == 5) m_ObjectSpike[i][j].SetPos(blockPosX, blockPosY);
			if (m_stage[i][j] == 6) m_ObjectGravityRing[i][j].SetPos(blockPosX, blockPosY);
			if (m_stage[i][j] == 7) m_ObjectDashRing[i][j].SetPos(blockPosX, blockPosY);
			if (m_stage[i][j] == 8) m_ObjectReverseRing[i][j].SetPos(blockPosX, blockPosY);
		}
	}
}

void HowToStage::Update()
{
	(this->*m_updateFunc)();
}

void HowToStage::Draw()
{
	int bgX = 0, bgY = 0, bgW = Game::kScreenWidth, bgH = Game::kScreenHeight;
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 100);
	DrawExtendGraph(bgX, bgY, bgW, bgH, m_hBg, true);
	DrawExtendGraph(bgX + Game::kScreenWidth, bgY, bgW + Game::kScreenWidth, bgH, m_hBg, true);
	DrawExtendGraph(bgX + (Game::kScreenWidth) * 2, bgY, bgW + (Game::kScreenWidth) * 2, bgH, m_hBg, true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

	for (int i = 0; i < Game::kScreenHeightNum; i++)
	{
		for (int j = 0; j < Game::kScreenWidthNum; j++)
		{
			// �X�e�[�W�M�~�b�N�̕`��
			if (m_stage[i][j] == 2) m_ObjectBlock[i][j].Draw();
			if (m_stage[i][j] == 3) m_ObjectJumpRing[i][j].Draw();
			if (m_stage[i][j] == 4) m_ObjectJumpPad[i][j].Draw();
			if (m_stage[i][j] == 5) m_ObjectSpike[i][j].Draw();
			if (m_stage[i][j] == 6) m_ObjectGravityRing[i][j].Draw();
			if (m_stage[i][j] == 7) m_ObjectDashRing[i][j].Draw();
			if (m_stage[i][j] == 8) m_ObjectReverseRing[i][j].Draw();
		}
	}
}

// �v���C���[�ƃI�u�W�F�N�g�̓����蔻��`�F�b�N
bool HowToStage::CollisionCheck(const Vec2 playerPos, int H, int W, ObjectType& object)
{
	if (m_stage[H][W] == 0) return false;

	float playerScale = 0.0f;

	// �������Ă���ꍇ�Atrue��Ԃ�
	// �u���b�N�̓����蔻��
	if (m_ObjectBlock[H][W].GetRight() >= m_pHPlayer->GetLeft() &&
		m_pHPlayer->GetRight() >= m_ObjectBlock[H][W].GetLeft() &&
		m_ObjectBlock[H][W].GetBottom() >= m_pHPlayer->GetTop() &&
		m_pHPlayer->GetBottom() >= m_ObjectBlock[H][W].GetTop())
	{
		object = ObjectType::Block;
		return true;
	}
	// �W�����v�����O�̓����蔻��
	if (m_ObjectJumpRing[H][W].GetRight() >= m_pHPlayer->GetLeft() &&
		m_pHPlayer->GetRight() >= m_ObjectJumpRing[H][W].GetLeft() &&
		m_ObjectJumpRing[H][W].GetBottom() >= m_pHPlayer->GetTop() &&
		m_pHPlayer->GetBottom() >= m_ObjectJumpRing[H][W].GetTop())
	{
		object = ObjectType::JumpRing;
		return true;
	}
	// �W�����v�p�b�h�̓����蔻��
	if (m_ObjectJumpPad[H][W].GetRight() - 5 > m_pHPlayer->GetLeft() &&
		m_pHPlayer->GetRight() > m_ObjectJumpPad[H][W].GetLeft() + 5 &&
		m_ObjectJumpPad[H][W].GetBottom() > m_pHPlayer->GetTop() &&
		m_pHPlayer->GetBottom() > m_ObjectJumpPad[H][W].GetTop() + Game::kBlockSize - (Game::kBlockSize / 4))
	{
		object = ObjectType::JumpPad;
		return true;
	}
	// �X�p�C�N�̓����蔻��
	if (m_ObjectSpike[H][W].GetRight() - kResizeScale > m_pHPlayer->GetLeft() + playerScale &&
		m_pHPlayer->GetRight() - playerScale > m_ObjectSpike[H][W].GetLeft() + kResizeScale &&
		m_ObjectSpike[H][W].GetBottom() - kResizeScale > m_pHPlayer->GetTop() + playerScale &&
		m_pHPlayer->GetBottom() - playerScale > m_ObjectSpike[H][W].GetTop() + kResizeScale)
	{
		object = ObjectType::Spike;
		return true;
	}
	// �O���r�e�B�����O�̓����蔻��
	if (m_ObjectGravityRing[H][W].GetRight() >= m_pHPlayer->GetLeft() &&
		m_pHPlayer->GetRight() >= m_ObjectGravityRing[H][W].GetLeft() &&
		m_ObjectGravityRing[H][W].GetBottom() >= m_pHPlayer->GetTop() &&
		m_pHPlayer->GetBottom() >= m_ObjectGravityRing[H][W].GetTop())
	{
		object = ObjectType::GravityRing;
		return true;
	}
	// �_�b�V�������O�̓����蔻��
	if (m_ObjectDashRing[H][W].GetRight() >= m_pHPlayer->GetLeft() &&
		m_pHPlayer->GetRight() >= m_ObjectDashRing[H][W].GetLeft() &&
		m_ObjectDashRing[H][W].GetBottom() >= m_pHPlayer->GetTop() &&
		m_pHPlayer->GetBottom() >= m_ObjectDashRing[H][W].GetTop())
	{
		object = ObjectType::DashRing;
		return true;
	}
	if (m_ObjectReverseRing[H][W].GetRight() >= m_pHPlayer->GetLeft() &&
		m_pHPlayer->GetRight() >= m_ObjectReverseRing[H][W].GetLeft() &&
		m_ObjectReverseRing[H][W].GetBottom() >= m_pHPlayer->GetTop() &&
		m_pHPlayer->GetBottom() >= m_ObjectReverseRing[H][W].GetTop())
	{
		object = ObjectType::ReverseRing;
		return true;
	}

	// �������Ă��Ȃ��ꍇ�Afalse��Ԃ�
	return false;
}

// �I�u�W�F�N�g���v���C���[�̉��ɂ��邩�ǂ���
bool HowToStage::IsUnder(const Vec2 playerPos, int H, int W, float& tempPos)
{
	if (m_ObjectBlock[H][W].GetPos().y > m_pHPlayer->GetCenterY())
	{
		// �u���b�N�̍��W����
		tempPos = m_ObjectBlock[H][W].GetPos().y - Game::kBlockSize;
		return true;
	}

	// ���ł͂Ȃ��ꍇ�Afalse��Ԃ�
	return false;
}

bool HowToStage::IsTop(const Vec2 playerPos, int H, int W, float& tempPos)
{
	if (m_ObjectBlock[H][W].GetPos().y + Game::kBlockSize < m_pHPlayer->GetCenterY())
	{
		// �u���b�N�̍��W����
		tempPos = m_ObjectBlock[H][W].GetPos().y + Game::kBlockSize;
		return true;
	}

	// ��ł͂Ȃ��ꍇ�Afalse��Ԃ�
	return false;
}

void HowToStage::StageManage()
{
	for (int i = 0; i < Game::kScreenHeightNum; i++)
	{
		for (int j = 0; j < Game::kScreenWidthNum; j++)
		{
			if (m_stageState == HowToStageState::CubeTest)
			{
				m_stage[i][j] = CubeTest[i][j];
			}
			else if (m_stageState == HowToStageState::JumpRingTest)
			{
				m_stage[i][j] = JumpRingTest[i][j];
			}
			else if (m_stageState == HowToStageState::GravityRingTest)
			{
				m_stage[i][j] = GravityRingTest[i][j];
			}
			else if (m_stageState == HowToStageState::DashRingTest)
			{
				m_stage[i][j] = DashRingTest[i][j];
			}
			else if (m_stageState == HowToStageState::RevRingTest)
			{
				m_stage[i][j] = RevRingTest[i][j];
			}
			else
			{
				assert(0);
			}
		}
	}
}

void HowToStage::SetNextStageState()
{
	m_stageState = static_cast<HowToStageState>(static_cast<int>(m_stageState) + 1);
	if (m_stageState == HowToStageState::End) m_stageState = HowToStageState::CubeTest;
}

void HowToStage::NormalUpdate()
{
	if (m_pHPlayer->IsDead()) return;

	for (int i = 0; i < Game::kScreenHeightNum; i++)
	{
		for (int j = 0; j < Game::kScreenWidthNum; j++)
		{
			m_ObjectJumpRing[i][j].Update();
			m_ObjectGravityRing[i][j].Update();
			m_ObjectDashRing[i][j].Update();
			m_ObjectReverseRing[i][j].Update();
		}
	}
}
