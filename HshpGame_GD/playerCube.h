#include "player.h"


class PlayerCube :
    public Player
{
public:
	PlayerCube();
	virtual ~PlayerCube() {}

	// プレイヤーの初期化
	void Init(int playerHandle);

	// プレイヤーの更新処理
	void Update();
	// プレイヤーの描画処理
	void Draw();
private:
	// 画像データ
	int m_handle;

	// 画像サイズ
	float m_height;
	float m_width;

	// 表示位置
	Vec2 m_pos;

	// 移動量
	Vec2 m_vec;

	// 画像角度
	double m_angle;

	// 死亡判定
	bool m_isDead;
};
