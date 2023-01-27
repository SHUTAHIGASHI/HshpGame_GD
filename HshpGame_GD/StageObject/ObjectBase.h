#pragma once

#include "game.h"

class ObjectBase
{
public:
	ObjectBase();
	~ObjectBase() {}

	virtual void Init();

	virtual void SetPos();

	virtual void Update();

	virtual void Draw();

	virtual bool CollisionCheck(float X, float Y);

	// プレイヤーの中心座標取得
	virtual float GetCenterX() { return m_pos.x + (Game::kBlockSize / 2); }
	virtual float GetCenterY() { return m_pos.y + (Game::kBlockSize / 2); }

	// 当たり判定用に四方向の座標取得　
	virtual float GetLeft()	{ return m_pos.x; }
	virtual float GetRight() { return m_pos.x + Game::kBlockSize; }
	virtual float GetTop() { return m_pos.y; }
	virtual float GetBottom() { return m_pos.y + Game::kBlockSize; }

	virtual Vec2 GetPos() { return m_pos; }
protected:
	// ブロック表示位置
	Vec2 m_pos;

	// 画像ハンドル
	int m_hObjectImg;
	// 画像サイズ
	float m_height;
	float m_width;
};

