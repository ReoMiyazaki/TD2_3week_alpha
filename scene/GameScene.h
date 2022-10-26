#pragma once

#include "Audio.h"
#include "DirectXCommon.h"
#include "DebugText.h"
#include "Input.h"
#include "Model.h"
#include "SafeDelete.h"
#include "Sprite.h"
#include "ViewProjection.h"
#include "WorldTransform.h"
#include "Player.h"
#include "Enemy.h"
#include "Camera.h"
#include "EnemyBullet.h"



/// <summary>
/// ゲームシーン
/// </summary>
class GameScene {

  public: // メンバ関数
	/// <summary>
	/// コンストクラタ
	/// </summary>
	GameScene();

	/// <summary>
	/// デストラクタ
	/// </summary>
	~GameScene();

	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize();

	/// <summary>
	/// 毎フレーム処理
	/// </summary>
	void Update();

	/// <summary>
	/// 描画
	/// </summary>
	void Draw();

	/// <summary>
	/// 当たり判定
	/// </summary>
	void CheckAllCollisions();

  private: // メンバ変数
	DirectXCommon* dxCommon_ = nullptr;
	Input* input_ = nullptr;
	Audio* audio_ = nullptr;
	DebugText* debugText_ = nullptr;
	ViewProjection viewProjection_;

	Model* model_ = nullptr;

	Player* player_ = nullptr;
	Camera* camera_ = nullptr;

	Enemy* enemy_[10] = { nullptr };
	EnemyBullet* enemyBullet_[4] = { nullptr };

	WorldTransform randObj[64];
	
	Vector2 moveCircle = {};
	float moveCircleRadius = 20.0f;

	
	uint32_t texture_ = 0;
	uint32_t whiteTexture_ = 0;

	

	/// <summary>
	/// ゲームシーン用
	/// </summary>
};
