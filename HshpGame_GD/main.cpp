#include "DxLib.h"
#include "game.h"
#include "SceneMain.h"
#include "SceneManager.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	// ウィンドウモード設定
	ChangeWindowMode(Game::kWindowMode);
	// ウィンドウ名設定
	SetMainWindowText(Game::kTitleText);
	// 画面サイズの設定
	SetGraphMode(Game::kScreenWidth, Game::kScreenHeight, Game::kColorDepth);

	if (DxLib_Init() == -1)		// ＤＸライブラリ初期化処理
	{
		return -1;			// エラーが起きたら直ちに終了
	}

	// リソースの読み込み
	LPCSTR font_path = "fontData/QuinqueFive.otf";	// 読み込むフォントファイルのパス
	if (AddFontResourceEx(font_path, FR_PRIVATE, NULL) > 0) {

	}
	else {
		// フォント読み込みエラー処理
		MessageBox(NULL, "フォント読み込み失敗", "", MB_OK);
	}

	// ダブルバッファモード
	SetDrawScreen(DX_SCREEN_BACK);

	ChangeFont("QuinqueFive");

	SetMouseDispFlag(false);

	InputState input;

	SceneManager scene;

	// 画像のロード
	scene.Init();

	bool isGameEnd = false;

	while (ProcessMessage() == 0)
	{
		LONGLONG time = GetNowHiPerformanceCount();
		SetMousePoint(static_cast<int>(Game::kScreenWidthHalf), static_cast<int>(Game::kScreenHeightHalf));

		// 画面のクリア
		ClearDrawScreen();

		input.Update();

		// 現在のシーンの更新
		scene.Update(input, isGameEnd);

		// 現在のシーンの描画
		scene.Draw();

		// 裏画面を表画面と入れ替える
		ScreenFlip();

		//if (CheckHitKey(KEY_INPUT_ESCAPE)) isGameEnd = true;
			
		if(isGameEnd) break;

		while (GetNowHiPerformanceCount() - time < 16667)
		{

		}
	}

	SetMouseDispFlag(true);

	// 画像のアンロード
	scene.End();

	DxLib_End();				// ＤＸライブラリ使用の終了処理

	return 0;				// ソフトの終了 
}