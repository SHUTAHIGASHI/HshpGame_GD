#include "game.h"
#include "player.h"

class MapObject;

class PlayerCube :
    public Player
{
public:
	PlayerCube();
	virtual ~PlayerCube() {}

	void setObject(MapObject* Object) { pObject = Object; }

	// プレイヤーの初期化
	void Init(int playerHandle);

	// プレイヤーの更新処理
	void Update(const InputState& input);
	// プレイヤーの描画処理
	void Draw();

private:
	MapObject* pObject;
};
