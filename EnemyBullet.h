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

	// ���[���h���W���擾
	Vector3 GetWorldPosition();

private:
	// ���W
	WorldTransform enemyBullet_;
	Model* model_ = nullptr;
	DebugText* debugText_ = nullptr;
	Input* input_ = nullptr;

	//�e���x
	Vector3 bulletSpeed = { 0.0f,0.0f,0.2f };
	//�t���O
	int isFire = 0;
};

