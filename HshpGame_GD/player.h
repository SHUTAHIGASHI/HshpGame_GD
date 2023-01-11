#pragma once
#include "Vec2.h"

// プレイヤークラス
class Player
{
public:
	Player();
	virtual ~Player() {}

	// プレイヤーの初期化
	virtual void Init();
	// プレイヤーの画像セット
	virtual void SetHandle(int playerHandle);

	// プレイヤーの更新処理
	virtual void Update();
	// プレイヤーの描画処理
	virtual void Draw();

	// プレイヤーの中心座標取得
	virtual float GetCenterX(){ return m_pos.x + (m_width / 2); }
	virtual float GetCenterY(){ return m_pos.y + (m_height / 2); }

	// m_isDead を true にする
	virtual void SetDead() { m_isDead = true; }
	// m_isDead を取得
	virtual bool IsDead() { return m_isDead; }

	// 当たり判定用に四方向の座標取得　
	float GetLeft()	const { return m_pos.x; }
	float GetRight()	const { return m_pos.x + static_cast<float>(m_width); }
	float GetTop()	const { return m_pos.y; }
	float GetBottom() const { return m_pos.y + static_cast<float>(m_height); }
	
	// プレイヤーの座標取得
	Vec2 GetPos() const { return m_pos; }

private:
	// 画像データ
	int m_handle;

	// 画像サイズ
	int m_height;
	int m_width;

	// 表示位置
	Vec2 m_pos;

	// 移動量
	Vec2 m_vec;

	// 死亡判定
	bool m_isDead;
};