#include "game.h"
#include "player.h"

class Stage;

class PlayerCube :
    public Player
{
public:
	PlayerCube();
	virtual ~PlayerCube() {}

	void setStage(Stage* stage) { m_pStage = stage; }

	// プレイヤーの初期化
	void Init(int playerHandle);

	// プレイヤーの更新処理
	void Update(const InputState& input);

	// オブジェクトと当たった時の処理
	void OnHitObject(const InputState& input);
	
	// プレイヤーの描画処理
	void Draw();
private:
	// ステージのポインタ
	Stage* m_pStage;

	void NormalUpdate(const InputState& input);
	// プレイヤー死亡時の更新処理
	void DeadUpdate(const InputState& input);

	using UpdateFunc_t = void (PlayerCube::*) (const InputState& input);
	UpdateFunc_t updateFunc_ = nullptr;
};
