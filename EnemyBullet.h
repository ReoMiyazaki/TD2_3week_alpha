#pragma once
#include "DebugText.h"
#include "Input.h"
#include "Model.h"
#include "WorldTransform.h"
#include "ViewProjection.h"
#include <cassert>
#include "Player.h"

class EnemyBullet
{
public:
	void Initialize(Model* model, uint32_t textureHandle);
	void Update(float moveCircle, PlayerState state);
	void Draw(ViewProjection viewProjection);

	// ワールド座標を取得
	Vector3 GetWorldPosition();

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
};

