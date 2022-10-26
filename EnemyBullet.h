#pragma once
#include "DebugText.h"
#include "Input.h"
#include "Model.h"
#include "WorldTransform.h"
#include "ViewProjection.h"
#include <cassert>
#include "Player.h"
#include <list>

class EnemyBullet
{
public:
	/// <summary>
	/// 初期化処理
	/// </summary>
	/// <param name="model"></param>
	/// <param name="textureHandle"></param>
	void Initialize(Model* model, uint32_t textureHandle);
	void Update(PlayerState state);

	/// <summary>
	/// 描画処理
	/// </summary>
	/// <param name="viewProjection"></param>
	void Draw(ViewProjection viewProjection);

	/// <summary>
	/// 当たり判定
	/// </summary>
	/// <returns></returns>
	void OnCollision();

	/// <summary>
	/// デバック用テキスト専用の関数
	/// </summary>
	void DrawDebugText();

	WorldTransform GetWorldTransform() { return enemyBullet_; };
	Vector3 radius = GetWorldTransform().scale_;

	// ワールド座標を取得
	Vector3 GetWorldPosition();

	bool GetOnCollision();
	// 座標の格納用
	Vector3 pos = GetWorldTransform().translation_;

	Vector3 upCollision;
	Vector3 downCollision;
private:
	// 座標
	WorldTransform enemyBullet_;
	Model* model_ = nullptr;
	DebugText* debugText_ = nullptr;
	Input* input_ = nullptr;

	//弾速度
	Vector3 bulletSpeed = { 0.0f,0.0f,0.2f };
	//フラグ
	int isFire = 0;
	// あたり判定
	bool isCollision_ = false;
	//削除タイマー
	float deleteTimer = 150;
	float aliveTimer = 0;
};

