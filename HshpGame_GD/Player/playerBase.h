#pragma once
#include "Vec2.h"

// プレイヤークラス
class PlayerBase
{
public:
	PlayerBase() :
		m_handle(-1),
		m_deathEffectHandle(-1),
		m_height(0),
		m_width(0),
		m_effectHeight(0),
		m_effectWidth(0),
		m_countFrame(0),
		m_angle(0.0f),
		m_isRotaRight(true),
		m_isRevGravity(false),
		m_isField(false),
		m_pos(),
		m_vec(),
		m_isScroll(false),
		m_isStageClear(false),
		m_isDead(false)
	{
	}
	virtual ~PlayerBase() {}

	// プレイヤーの中心座標取得
	virtual float GetCenterX() const { return m_pos.x + (m_width / 2); }
	virtual float GetCenterY() const { return m_pos.y + (m_height / 2); }

	// m_isGameClear を取得
	virtual bool IsStageClear() const { return m_isStageClear; }
	// m_isDead を true にする
	virtual void SetDead() { m_isDead = true; }
	// m_isDead を取得
	virtual bool IsDead() const { return m_isDead; }

	// 当たり判定用に四方向の座標取得　
	virtual float GetLeft()	const { return m_pos.x; }
	virtual float GetRight() const { return m_pos.x + static_cast<float>(m_width); }
	virtual float GetTop() const { return m_pos.y; }
	virtual float GetBottom() const { return m_pos.y + static_cast<float>(m_height); }
	
	// プレイヤーの座標取得
	Vec2 GetPos() const { return m_pos; }

	virtual bool IsRevGravity() const { return m_isRevGravity; }

protected:
	// 画像データ
	int m_handle;
	int m_deathEffectHandle;

	// 画像サイズ
	float m_height;
	float m_width;
	// エフェクト画像サイズ
	float m_effectHeight;
	float m_effectWidth;
	// フレーム数をカウント
	int m_countFrame;

	// 画像表示角度
	float m_angle;
	// 移動方向
	bool m_isRotaRight;
	// 重力方向
	bool m_isRevGravity;

	// 地面との当たり判定用変数
	bool m_isField;

	// プレイヤー座標
	Vec2 m_pos;
	// 移動量
	Vec2 m_vec;

	bool m_isScroll;

	// ゴール判定
	bool m_isStageClear;
	// 死亡判定
	bool m_isDead;
};