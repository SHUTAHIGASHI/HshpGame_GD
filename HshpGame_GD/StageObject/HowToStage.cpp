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
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,2,0,0,0,0,0,2,0,0,0,0,0,2,2,0,0,0,0,0,2,0,0,0,0,0,2,0,0,0,0,0,0,0},
		{2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,2,2,0,0,2,2,0,0,2,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,2,2,0,0,2,2,0,0,2,2,0,0,2,2,0,0,2,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,0,0,2,2,2,2,2,2,2,2}
	};

	// �X�e�[�W�Q
	int JumpRingTest[Game::kScreenHeightNum][Game::kScreenWidthNum] = {
		{2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,3,0,0,0,0,3,0,0,0,0,3,0,0,3,0,0,0,0,3,0,0,0,0,3,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,3,0,0,0,0,3,0,0,0,0,0,3,0,0,0,0,0,0,3,0,0,0,0,0,3,0,0,0,0,3,0,0,0,0,0},
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
		{0,0,0,0,0,0,0,0,0,0,0,0,0,3,0,0,0,0,0,0,0,0,0,0,0,0,0,3,0,5,5,0,3,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,2,0,0,0,0,0,0,0,0,0},
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
		{0,0,0,0,0,0,0,0,0,0,0,0,7,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,5,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,7,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,5,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,7,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,5,0,0,0,0,0,0},
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
		{2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,2,2,0,0,3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,8,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,0,0,0,0,0,0,0}
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
	m_tempNum(0),
	m_hBg(-1)
{
}

void HowToStage::Init(int hSpike, int hBg, int hPortal, int hBlock)
{
	End();
	StageManage();

	m_hBg = hBg;

	InitStage(hSpike, hPortal, hBlock);

	SetStage();
}

void HowToStage::InitStage(int hSpike, int hPortal, int hBlock)
{
	for (int i = 0; i < Game::kScreenHeightNum; i++)
	{
		for (int j = 0; j < Game::kScreenWidthNum; j++)
		{
			if (m_stage[i][j] == 2)
			{
				m_ObjectBlock.push_back(ObjectBlock());
			}
			if (m_stage[i][j] == 3)
			{
				m_ObjectJumpRing.push_back(ObjectJumpRing());
			}
			if (m_stage[i][j] == 4)
			{
				m_ObjectJumpPad.push_back(ObjectJumpPad());
			}
			if (m_stage[i][j] == 5)
			{
				m_ObjectSpike.push_back(ObjectSpike());
			}
			if (m_stage[i][j] == 6)
			{
				m_ObjectGravityRing.push_back(ObjectGravityRing());
			}
			if (m_stage[i][j] == 7)
			{
				m_ObjectDashRing.push_back(ObjectDashRing());
			}
			if (m_stage[i][j] == 8)
			{
				m_ObjectReverseRing.push_back(ObjectReverseRing());
			}
		}
	}

	for (int i = 0; i < m_ObjectBlock.size(); i++)
	{
		m_ObjectBlock[i].Init(hBlock);
	}

	for (int i = 0; i < m_ObjectJumpRing.size(); i++)
	{
		m_ObjectJumpRing[i].Init();
	}

	for (int i = 0; i < m_ObjectJumpPad.size(); i++)
	{
		m_ObjectJumpPad[i].Init();
	}

	for (int i = 0; i < m_ObjectSpike.size(); i++)
	{
		m_ObjectSpike[i].Init(hSpike);
	}

	for (int i = 0; i < m_ObjectGravityRing.size(); i++)
	{
		m_ObjectGravityRing[i].Init();
	}

	for (int i = 0; i < m_ObjectDashRing.size(); i++)
	{
		m_ObjectDashRing[i].Init();
	}

	for (int i = 0; i < m_ObjectReverseRing.size(); i++)
	{
		m_ObjectReverseRing[i].Init();
	}
}

void HowToStage::End()
{
	m_ObjectBlock.clear();
	m_ObjectJumpRing.clear();
	m_ObjectJumpPad.clear();
	m_ObjectSpike.clear();
	m_ObjectGravityRing.clear();
	m_ObjectDashRing.clear();
	m_ObjectReverseRing.clear();
}

void HowToStage::SetStage()
{
	int countGoal = 0;
	int countBlock = 0;
	int countJumpRing = 0;
	int countJumpPad = 0;
	int countSpike = 0;
	int countGravRing = 0;
	int countDashRing = 0;
	int countRevRing = 0;

	for (int i = 0; i < Game::kScreenHeightNum; i++)
	{
		for (int j = 0; j < Game::kScreenWidthNum; j++)
		{
			float blockPosX, blockPosY;
			blockPosX = j * Game::kBlockSize;
			blockPosY = i * Game::kBlockSize;

			if (m_stage[i][j] == 2)
			{
				m_ObjectBlock[countBlock].SetPos(blockPosX, blockPosY);
				countBlock++;
				if (countBlock > m_ObjectBlock.size()) countBlock = m_ObjectBlock.size();
			}
			if (m_stage[i][j] == 3)
			{
				m_ObjectJumpRing[countJumpRing].SetPos(blockPosX, blockPosY);
				countJumpRing++;
				if (countJumpRing > m_ObjectJumpRing.size()) countJumpRing = m_ObjectJumpRing.size();
			}
			if (m_stage[i][j] == 4)
			{
				m_ObjectJumpPad[countJumpPad].SetPos(blockPosX, blockPosY);
				countJumpPad++;
				if (countJumpPad > m_ObjectJumpPad.size()) countJumpPad = m_ObjectJumpPad.size();
			}
			if (m_stage[i][j] == 5)
			{
				m_ObjectSpike[countSpike].SetPos(blockPosX, blockPosY);
				countSpike++;
				if (countSpike > m_ObjectSpike.size()) countSpike = m_ObjectSpike.size();
			}
			if (m_stage[i][j] == 6)
			{
				m_ObjectGravityRing[countGravRing].SetPos(blockPosX, blockPosY);
				countGravRing++;
				if (countGravRing > m_ObjectGravityRing.size()) countGravRing = m_ObjectGravityRing.size();
			}
			if (m_stage[i][j] == 7)
			{
				m_ObjectDashRing[countDashRing].SetPos(blockPosX, blockPosY);
				countDashRing++;
				if (countDashRing > m_ObjectDashRing.size()) countDashRing = m_ObjectDashRing.size();
			}
			if (m_stage[i][j] == 8)
			{
				m_ObjectReverseRing[countRevRing].SetPos(blockPosX, blockPosY);
				countRevRing++;
				if (countRevRing > m_ObjectReverseRing.size()) countRevRing = m_ObjectReverseRing.size();
			}
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

	for (int i = 0; i < m_ObjectJumpRing.size(); i++)
	{
		m_ObjectJumpRing[i].Draw(0xFFD700);
	}

	for (int i = 0; i < m_ObjectJumpPad.size(); i++)
	{
		m_ObjectJumpPad[i].Draw();
	}

	for (int i = 0; i < m_ObjectSpike.size(); i++)
	{
		m_ObjectSpike[i].Draw();
	}

	for (int i = 0; i < m_ObjectGravityRing.size(); i++)
	{
		m_ObjectGravityRing[i].Draw(0x00bfff);
	}

	for (int i = 0; i < m_ObjectDashRing.size(); i++)
	{
		m_ObjectDashRing[i].Draw(0xdc143c);
	}

	for (int i = 0; i < m_ObjectReverseRing.size(); i++)
	{
		m_ObjectReverseRing[i].Draw(0x9932cc);
	}

	for (int i = 0; i < m_ObjectBlock.size(); i++)
	{
		m_ObjectBlock[i].Draw();
	}
}

// �v���C���[�ƃI�u�W�F�N�g�̓����蔻��`�F�b�N
bool HowToStage::CollisionCheck(const Vec2 playerPos, int H, int W, ObjectType& object)
{
	if (m_stage[H][W] == 0) return false;

	int playerScale = 1;

	for (int i = 0; i < m_ObjectBlock.size(); i++)
	{
		if (m_ObjectBlock[i].CollisionCheck(m_pHPlayer->GetPos()))
		{
			m_tempNum = i;
			object = ObjectType::Block;
			return true;
		}
	}
	// �W�����v�����O�̓����蔻��
	for (int i = 0; i < m_ObjectJumpRing.size(); i++)
	{
		if (m_ObjectJumpRing[i].CollisionCheck(m_pHPlayer->GetPos()))
		{
			object = ObjectType::JumpRing;
			return true;
		}
	}
	// �W�����v�p�b�h�̓����蔻��
	for (int i = 0; i < m_ObjectJumpPad.size(); i++)
	{
		if (m_ObjectJumpPad[i].CollisionCheck(m_pHPlayer->GetPos(), static_cast<int>(Game::kBlockSize - (Game::kBlockSize / 4))))
		{
			object = ObjectType::JumpPad;
			return true;
		}
	}
	// �X�p�C�N�̓����蔻��
	for (int i = 0; i < m_ObjectSpike.size(); i++)
	{
		if (m_ObjectSpike[i].CollisionCheck(m_pHPlayer->GetPos(), kResizeScale, playerScale))
		{
			object = ObjectType::Spike;
			return true;
		}
	}
	// �O���r�e�B�����O�̓����蔻��
	for (int i = 0; i < m_ObjectGravityRing.size(); i++)
	{
		if (m_ObjectGravityRing[i].CollisionCheck(m_pHPlayer->GetPos()))
		{
			object = ObjectType::GravityRing;
			return true;
		}
	}
	// �_�b�V�������O�̓����蔻��
	for (int i = 0; i < m_ObjectDashRing.size(); i++)
	{
		if (m_ObjectDashRing[i].CollisionCheck(m_pHPlayer->GetPos()))
		{
			object = ObjectType::DashRing;
			return true;
		}
	}
	// ���o�[�X�����O�̓����蔻��
	for (int i = 0; i < m_ObjectReverseRing.size(); i++)
	{
		if (m_ObjectReverseRing[i].CollisionCheck(m_pHPlayer->GetPos()))
		{
			object = ObjectType::ReverseRing;
			return true;
		}
	}

	// �������Ă��Ȃ��ꍇ�Afalse��Ԃ�
	return false;
}

// �I�u�W�F�N�g���v���C���[�̉��ɂ��邩�ǂ���
bool HowToStage::IsUnder(const Vec2 playerPos, int H, int W, float& tempPos)
{
	if (m_ObjectBlock[m_tempNum].GetTop() > m_pHPlayer->GetCenterY())
	{
		// �u���b�N�̍��W����
		tempPos = m_ObjectBlock[m_tempNum].GetTop() - Game::kBlockSize;
		return true;
	}

	// ���ł͂Ȃ��ꍇ�Afalse��Ԃ�
	return false;
}

bool HowToStage::IsTop(const Vec2 playerPos, int H, int W, float& tempPos)
{
	if (m_ObjectBlock[m_tempNum].GetTop() + Game::kBlockSize < m_pHPlayer->GetCenterY())
	{
		// �u���b�N�̍��W����
		tempPos = m_ObjectBlock[m_tempNum].GetTop() + Game::kBlockSize;
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

	for (int i = 0; i < m_ObjectJumpRing.size(); i++)
	{
		m_ObjectJumpRing[i].Update();
	}

	for (int i = 0; i < m_ObjectGravityRing.size(); i++)
	{
		m_ObjectGravityRing[i].Update();
	}

	for (int i = 0; i < m_ObjectDashRing.size(); i++)
	{
		m_ObjectDashRing[i].Update();
	}

	for (int i = 0; i < m_ObjectReverseRing.size(); i++)
	{
		m_ObjectReverseRing[i].Update();
	}
}
