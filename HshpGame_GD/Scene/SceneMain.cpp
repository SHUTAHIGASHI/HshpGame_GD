#include "SceneMain.h"
#include "game.h"
#include "Player.h"
#include "Stage.h"
#include "ScenePause.h"
#include "SceneClear.h"
#include "SceneRanking.h"
#include <cassert>
#include <memory>

namespace
{
	// スタート時の遅延時間
	constexpr int kStartDelay = 300;
	// スタートカウントダウンの文字サイズ
	constexpr int kStartTextSizeMax = 100;
	// 死亡時の遅延
	constexpr int kGameOverDelay = 30;
	// 挑戦回数描画時間
	constexpr int kAttemptDrawMax = 180;
}

SceneMain::SceneMain() :
	m_pPlayer(std::make_shared<Player>()),
	m_pStage(std::make_shared<Stage>()),
	m_pPause(std::make_shared<ScenePause>()),
	m_updateFunc(&SceneMain::SceneStartUpdate),
	m_hPlayer(-1),
	m_hDeathEffect(-1),
	m_hObjectSpike(-1),
	m_hPortal(-1),
	m_hBlock(-1),
	m_hJumpPad(-1),
	m_hBg(-1),
	m_hDeathSound(-1),
	m_hPlayBgm(-1),
	m_fadeCount(0),
	m_scroll(0),
	m_startDelay(0),
	m_startTextSize(0),
	m_textTimer(0),
	m_gameOverDelay(0),
	m_countAttempt(0),
	m_attemptDrawTime(0),
	m_attemptDrawNum(0),
	m_isPracticeMode(false),
	m_isPause(false),
	m_isEnd(false),
	m_selectedStage(StageState::firstStage),
	m_pManager(nullptr),
	m_pClear(nullptr),
	m_pRanking(nullptr)
{
}

SceneMain::~SceneMain()
{
}

// 初期化
void SceneMain::Init()
{
	// シーン終了変数を初期化
	m_isEnd = false;	// ゲーム終了フラグ
	m_isPause = false;
	m_fadeCount = 255;	// フェード処理の数値
	m_updateFunc = &SceneMain::SceneStartUpdate;	// フェード処理を実行する

	// アドレスの設定
	m_pPlayer->SetStage(m_pStage.get());
	m_pStage->SetPlayer(m_pPlayer.get());
	m_pPause->SetMain(this);

	// ポーズシーン初期化
	m_pPause->Init();

	// 画像読み込み
	m_hPlayer = LoadGraph(Game::kPlayerImg);	// プレイヤー画像
	m_hDeathEffect = LoadGraph(Game::kPlayerDeathEffectImg);	// 死亡エフェクト
	m_hObjectSpike = LoadGraph(Game::kObjectSpikeImg);	// スパイク画像
	m_hPortal = LoadGraph(Game::kPortalImg);	// ゴールポータル
	m_hBlock = LoadGraph(Game::kBlockImg);	// ブロック
	m_hJumpPad = LoadGraph(Game::kJumpPadImg);	// ジャンプパッド
	m_hBg = LoadGraph(Game::kBgImg);	// 背景画像

	// 音データの読み込み
	m_hDeathSound = LoadSoundMem(Game::kDeathSound);	// 死亡時の音

	// BGMのセット
	if (m_isPracticeMode) m_hPlayBgm = LoadSoundMem(Game::kPracBgm); // 練習モードの場合、練習用BGMをセット
	else m_hPlayBgm = LoadSoundMem(Game::kChallengeBgm); // チャレンジモードの場合、チャレンジモード用BGMをセット

	// ステージ選択
	// チャレンジモードの場合、ステージ１をセット
	if (!m_isPracticeMode) m_pStage->SetFirstStage();
	// ステージが選ばれた場合、そのステージにセット
	else if (m_selectedStage != StageState::Empty) m_pStage->SetSelectedStage(m_selectedStage);
	// クリア後に "次のステージ" が選ばれた場合、次ステージをセット
	else if (m_pClear->IsNextStage()) m_pStage->SetNextStageState();
	else assert(0);

	// スタート遅延の初期化
	m_startDelay = kStartDelay;
	// スタートカウントダウンの初期化
	m_startTextSize = kStartTextSizeMax;

	// 挑戦回数のカウント初期化
	m_countAttempt = 1;

	// ゲームスタート(再スタート)時の初期化処理
	OnGameStart();
}

// ゲームスタート(再スタート)時の初期化処理
void SceneMain::OnGameStart()
{	
	// 挑戦回数テキストの描画時間リセット
	m_attemptDrawTime = kAttemptDrawMax;
	m_attemptDrawNum = 255;

	// ゲームオーバー時の遅延初期化
	m_gameOverDelay = kGameOverDelay;

	// プレイヤー初期化
	m_pPlayer->Init(m_hPlayer, m_hDeathEffect, m_hDeathSound);
	// ステージ初期化
	m_pStage->Init(m_hObjectSpike, m_hBg, m_hPortal, m_hBlock, m_hJumpPad);
}

// ゲーム中のBGM再生
void SceneMain::PlayGameLoopBgm()
{
	// BGMが流れていない場合、曲を再生
	if(!CheckSoundMem(m_hPlayBgm)) PlaySoundMem(m_hPlayBgm, DX_PLAYTYPE_BACK);
}

// 終了処理
void SceneMain::End()
{
	// 選ばれたステージを空にセット
	m_selectedStage = StageState::Empty;

	// ステージの終了処理
	m_pStage->End();
	// ポーズシーンの終了処理
	m_pPause->End();

	// サウンドの停止
	StopSoundMem(m_hPlayBgm, true);

	// 画像データの削除
	DeleteGraph(m_hPlayer);	// プレイヤー画像
	DeleteGraph(m_hDeathEffect);	// 死亡エフェクト
	DeleteGraph(m_hObjectSpike);	// スパイク画像
	DeleteGraph(m_hPortal);	// ゴールポータル画像
	DeleteGraph(m_hBlock);	// ブロック
	DeleteGraph(m_hBg);	// 背景画像

	// 音データの削除
	DeleteSoundMem(m_hDeathSound);	// 死亡サウンド
	DeleteSoundMem(m_hPlayBgm);	// 現在再生するBGM
}

// 毎フレームの処理
void SceneMain::Update(const InputState& input, NextSceneState& nextScene)
{		
	if (m_isPause)
	{
		m_pPause->Update(input, nextScene, m_isEnd);
		if (input.IsTriggered(InputType::pause))
		{
			m_isPause = false;
			PlaySoundMem(m_hPlayBgm, DX_PLAYTYPE_BACK, false);
		}
		return;
	}

	(this->*m_updateFunc)(input, nextScene);
}

// リトライ選択時の処理
void SceneMain::OnRetry()
{
	m_isPause = false;
	
	// チャレンジモードの場合、曲を停止
	if (!m_isPracticeMode) StopSoundMem(m_hPlayBgm);
	// チャレンジモードの場合、ステージ１をセット
	if (!m_isPracticeMode) m_pStage->SetFirstStage();
	// ゲーム状態初期化
	OnGameStart();
	// 挑戦回数を増やす
	m_countAttempt++;
	return;
}

void SceneMain::OnDead()
{
	// 再生中のBGMを止める
	if (!m_isPracticeMode) StopSoundMem(m_hPlayBgm);

	// ゲームオーバー遅延が０以下になった場合
	if (m_gameOverDelay < 0)
	{
		// チャレンジモードの場合、ステージ１をセット
		if (!m_isPracticeMode) m_pStage->SetFirstStage();
		// ゲーム状態初期化
		OnGameStart();
		// 挑戦回数を増やす
		m_countAttempt++;
		return;
	}

	// ゲームオーバー遅延を1フレームごとに減少させる
	m_gameOverDelay--;
}

// 毎フレームの描画
void SceneMain::Draw()
{
	// ステージの描画
	m_pStage->Draw();

	// ゲームクリアしている場合、処理終了
	if (m_pPlayer->IsStageClear()) return;

	// プレイヤーの描画
	m_pPlayer->Draw();

	if(m_startDelay <= 0) DrawGameInfo();

	if (m_isPause)
	{
		m_pPause->Draw();
	}
	
	// フェード処理用の処理
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, m_fadeCount);
	DrawBox(0, 0, Game::kScreenWidth, Game::kScreenHeight, 0x000000, true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

	// スタート時のカウントダウン描画
	if (m_startDelay > 0)
	{
		OnStartCount();
	}
}

void SceneMain::DrawGameInfo()
{
	int drawX, drawY;
	//if (m_attemptDrawTime > 0)
	//{
	//	SetDrawBlendMode(DX_BLENDMODE_ALPHA, m_attemptDrawNum);
	//	drawX = static_cast<int>(m_pPlayer->GetPos().x - 100);
	//	drawY = static_cast<int>(m_pPlayer->GetPos().y - 50);
	//	if (drawX < 0) drawX = 0;

	//	// 挑戦回数の描画
	//	DrawFormatString(drawX, drawY, 0xe9e9e9, "Attempt : %d", m_countAttempt);
	//	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	//}

	if (m_isPracticeMode)
	{
		drawX = 10, drawY = 60;
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 200);
		DrawBox(5, drawY, drawX + 190, drawY + 25, 0x000000, true);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
		// 現在のモードの描画
		DrawFormatString(drawX, drawY, 0xe9e9e9, "stage %d", static_cast<int>(m_pStage->GetStageState()) + 1);
	}
}

// スタート時のカウントダウン描画
void SceneMain::OnStartCount()
{
	std::string temp = "";

	// 数字のサイズ調整
	// 余りが 0 になった場合、設定したフォントサイズに戻す
	if (m_startDelay % 60 == 0) m_startTextSize = kStartTextSizeMax;
	// 毎フレームフォントサイズを小さくする
	m_startTextSize--;
	// フォントサイズは 60 より小さくしない
	if (m_startTextSize < 60) m_startTextSize = 60;

	// カウントダウン描画
	if (m_startDelay / 60 == 5)
	{
		// ５秒の場合は何も描画しない
	}
	else if (m_startDelay / 60 == 0)
	{
		// ０秒の場合は "GO!" の文字を描画
		SetFontSize(m_startTextSize);
		// 後ろの白文字
		DrawString(Game::kScreenWidthHalf - (m_startTextSize * 3 / 2) + 2, Game::kScreenHeightHalf + 5, "GO!", 0xe9e9e9);
		// 赤文字
		DrawString(Game::kScreenWidthHalf - (m_startTextSize * 3 / 2), Game::kScreenHeightHalf, "GO!", 0xff2222);
	}
	else
	{
		// ４～１秒の間はその数字を描画
		SetFontSize(m_startTextSize);
		// 後ろの白文字
		DrawFormatString(Game::kScreenWidthHalf - (m_startTextSize / 2) + 2, Game::kScreenHeightHalf + 5, 0xe9e9e9, "%d", m_startDelay / 60);
		// 赤文字
		DrawFormatString(Game::kScreenWidthHalf - (m_startTextSize / 2), Game::kScreenHeightHalf, 0xff2222, "%d", m_startDelay / 60);
	}
	// フォントサイズを標準に戻す
	SetFontSize(20);

	if (m_startDelay / 60 != 5)
	{
		m_pPlayer->DrawSpawnPos();
	}

	if (m_startDelay / 60 <= 2 && m_startDelay / 60 != 0)
	{
		if (m_pPlayer->IsMoveRight())
		{
			temp = "→";
		}
		else
		{
			temp = "←";
		}

		if ((m_textTimer / 10) % 2 != 0)
		{
			SetFontSize(40);
			DrawFormatString(static_cast<int>(m_pPlayer->GetPos().x) + 5, 
				static_cast<int>(m_pPlayer->GetPos().y) - 50,
				0xff0000, "%s", temp.c_str());
			SetFontSize(0);
		}
		m_textTimer++;
	}
}

// ステージクリア時の処理
void SceneMain::OnStageClear(NextSceneState& nextScene)
{
	// ステージクリアのフラグが true かどうか
	if (m_pPlayer->IsStageClear())
	{
		// ステージ１０ or 練習モード の場合の処理
		if (m_pStage->GetStageState() == StageState::tenthStage || m_isPracticeMode)
		{
			// チャレンジモードの場合
			if (!m_isPracticeMode)
			{
				// ランキングデータ読み込み
				m_pRanking->LoadRankingData();
				// ランキングデータの更新
				m_pRanking->SetRanking(m_countAttempt, m_pStage->GetStageState());
			}

			// 挑戦回数を初期化
			m_countAttempt = 1;
			// 次のシーンを設定
			nextScene = NextSceneState::nextClear;
			// シーン終了フラグ
			m_isEnd = true;
		}
		else
		{
			m_startDelay = 180;
			m_updateFunc = &SceneMain::StartDelayUpdate;	// フェード処理を実行する
			// 次のステージ状態をセット
			m_pStage->SetNextStageState();
			// ゲームスタート時の処理へ
			OnGameStart();
		}
	}
}

// 通常時の更新処理
void SceneMain::NormalUpdate(const InputState& input, NextSceneState& nextScene)
{
	// ゲームBGM再生
	PlayGameLoopBgm();

	if (m_attemptDrawTime > 0)
	{
		m_attemptDrawTime--;
		if ((m_attemptDrawTime / 60) < 2)
		{
			m_attemptDrawNum -= 10;
		}
	}

	// escapeキーが押された場合
	if (input.IsTriggered(InputType::pause))
	{
		m_isPause = true;
		StopSoundMem(m_hPlayBgm);
	}

	// Rキーが押された場合
	if (input.IsTriggered(InputType::retry))
	{
		OnRetry();
	}

	// プレイヤーの更新処理
	m_pPlayer->Update(input);

	// ステージの更新処理
	m_pStage->Update();

	// ステージクリア時の処理
	OnStageClear(nextScene);

	// プレイヤーの死亡判定が true の場合
	if (m_pPlayer->IsDead())
	{
		OnDead();
		return;
	}
}

// スタートカウントダウン時の更新処理
void SceneMain::StartDelayUpdate(const InputState& input, NextSceneState& nextScene)
{
	// スタート遅延を毎フレーム減らす
	m_startDelay--;
	// スタート遅延が 1 以上の場合処理終了
	if (m_startDelay < 0)
	{
		m_updateFunc = &SceneMain::NormalUpdate;
		m_startDelay = 0;
		m_fadeCount = 0;
	}
}

// シーン開始時の更新処理
void SceneMain::SceneStartUpdate(const InputState& input, NextSceneState& nextScene)
{
	// フェードの数値を５ずつ減らす
	m_fadeCount -= 5;
	
	// フェードカウントが 150 以下になった場合
	if (m_fadeCount < 150)
	{
		// 150 にセット
		m_fadeCount = 150;
		// 通常の更新処理をセット
		m_updateFunc = &SceneMain::StartDelayUpdate;
	}
}
