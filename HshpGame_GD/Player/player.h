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

	// m_isGameClear を取得
	virtual bool IsStageClear() { return m_isStageClear; }
	// m_isDead を true にする
	virtual void SetDead() { m_isDead = true; }
	// m_isDead を取得
	virtual bool IsDead() { return m_isDead; }

	// 当たり判定用に四方向の座標取得　
	virtual float GetLeft()	const { return m_pos.x; }
	virtual float GetRight()	const { return m_pos.x + static_cast<float>(m_width); }
	virtual float GetTop()	const { return m_pos.y; }
	virtual float GetBottom() const { return m_pos.y + static_cast<float>(m_height); }
	
	// プレイヤーの座標取得
	Vec2 GetPos() const { return m_pos; }

	virtual bool IsRevGravity() { return m_isRevGravity; }

protected:
	// 画像データ
	int m_handle;

	// 画像サイズ
	float m_height;
	float m_width;

	// 画像表示角度
	float m_angle;

	// 移動方向
	bool m_isMoveRight;
	// 重力方向
	bool m_isRevGravity;

	// 地面との当たり判定用変数
	bool m_isField;

	// プレイヤー座標
	Vec2 m_pos;

	// 移動量
	Vec2 m_vec;

	// ゴール判定
	bool m_isStageClear;

	// 死亡判定
	bool m_isDead;
};