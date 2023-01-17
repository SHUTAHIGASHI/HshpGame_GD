#include "game.h"
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
	void Update(const InputState& input);
	// プレイヤーの描画処理
	void Draw();
};
