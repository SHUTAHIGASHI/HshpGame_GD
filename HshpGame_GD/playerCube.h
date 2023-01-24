#include "game.h"
#include "player.h"

class Stage;

class PlayerCube :
    public Player
{
public:
	PlayerCube();
	virtual ~PlayerCube() {}

	void setStage(Stage* stage) { pStage = stage; }

	// プレイヤーの初期化
	void Init(int playerHandle);

	// プレイヤーの更新処理
	void NormalUpdate(const InputState& input);
	// プレイヤー死亡時の更新処理
	void DeadUpdate();

	// オブジェクトと当たった時の処理
	void OnHitObject(const InputState& input);
	
	// プレイヤーの描画処理
	void Draw();
private:
	// ステージのポインタ
	Stage* pStage;
};
