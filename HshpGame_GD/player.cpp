#include "DxLib.h"
#include "player.h"
#include "game.h"

namespace
{
    // 移動速度
    constexpr float kMoveSpeed = 12.0f;

    // 画像の表示位置
    constexpr float kPlayerDrawPosX = 16.0f;
    constexpr float kPlayerDrawPosY = 34.0f;
}

Player::Player()
{
    m_height = 0;
    m_width = 0;

    m_isDead = false;
}

// プレイヤーの初期化
void Player::init()
{
    // 死亡判定を false に設定
    m_isDead = false;
    
    // 移動量の初期化
    m_vec.x = 0;
    m_vec.y = kMoveSpeed;
}

// プレイヤーの画像セット
void Player::setHandle(int playerHandle)
{
    // 画像サイズの取得
    GetGraphSize(m_handle, &m_width, &m_height);
}

// プレイヤーの座標設定
void Player::setPos(float x, float y)
{
    m_pos.x = x;
    m_pos.y = y;
}

// プレイヤーの更新処理
void Player::update()
{
    // パッド(もしくはキーボード)からの入力を取得する
    int padState = GetJoypadInputState(DX_INPUT_KEY_PAD1);

    // 現在の座標に移動量を加える
    m_pos += m_vec;

    // キー入力があった場合
    if (padState & PAD_INPUT_RIGHT) // 右
    {
        m_pos.x += kMoveSpeed;
    }
    if (padState & PAD_INPUT_LEFT)  // 左
    {
        m_pos.x += -kMoveSpeed;
    }

    // 画面端に行こうとした場合
    if (getLeft() < 0)
    {
        m_pos.x = 0.0f;    // 画面端より左には行かない
    }
    if (getRight() > Game::kScreenWidth)
    {
        m_pos.x = static_cast<float>(Game::kScreenWidth - m_width); // 画面端より右には行かない
    }
    // ステージの範囲外に行こうとした場合
    if (getTop() < Game::kStageUpperLimit)
    {
        m_pos.y = Game::kStageUpperLimit;   // ステージの範囲より上には行かない
        m_vec.y *= -1;                      // 重力変更
    }
    if (getBottom() > Game::kStageLowerLimit)
    {
        m_pos.y = static_cast<float>(Game::kStageLowerLimit - m_height);    // ステージの範囲より下には行かない
        m_vec.y *= -1;                      // 重力変更
    }
}

// プレイヤーの描画処理
void Player::draw()
{
    // 描画用グラフィックハンドル
    int handle = m_handle;

    // 描画角度用変数
    double angle = 0.0;
    
    // プレイヤー描画
    DrawRotaGraphF(m_pos.x + kPlayerDrawPosX, m_pos.y + kPlayerDrawPosY, 1.0, angle, handle, true, false);
}