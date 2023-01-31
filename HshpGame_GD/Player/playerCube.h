#include "game.h"
#include "playerBase.h"

class Stage;

class PlayerCube :
    public PlayerBase
{
public:
	PlayerCube();
	virtual ~PlayerCube() {}

	void SetStage(Stage* stage) { m_pStage = stage; }

	// プレイヤーの初期化
	void Init(int playerHandle, int playerDeathEffect);

	// プレイヤーの更新処理
	void Update(const InputState& input);

	// オブジェクトと当たった時の処理
	void OnHitObject(const InputState& input);
	
	// プレイヤーの描画処理
	void Draw();

	void ChangeUpdateType();

	void SetSpawn();

	// 右回転するかどうかの設定
	void SetRotaRight(bool isRight) { m_isRotaRight = isRight; }
	bool IsRotaRight() const { return m_isRotaRight; }

	void SetPlayerVec(int scroll);
	void DeleteVecX() { m_vec.x = 0.0f; }
private:
	// ステージのポインタ
	Stage* m_pStage;

	// 通常時の更新処理
	void NormalUpdate(const InputState& input);
	// 重力反転時の更新処理
	void RevGravityUpdate(const InputState& input);
	// ステージスクロール時の更新処理
	void StageScrollUpdate(const InputState& input);
	// プレイヤー死亡時の更新処理
	void DeadUpdate(const InputState& input);

	using m_tUpdateFunc = void (PlayerCube::*) (const InputState& input);
	m_tUpdateFunc m_updateFunc = nullptr;
};
