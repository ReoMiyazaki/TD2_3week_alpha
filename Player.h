#pragma once
#include "Model.h"
#include "WorldTransform.h"
#include "ViewProjection.h"
#include "DebugText.h"
#include"Input.h"

enum class PlayerState {
	Idle,
Charge,
	Jump,
};

class Player
{
public:
	void Initialize(float moveCircleRadius,Vector2 moveCircle);
	void Update(float moveCircleRadius);
	void Draw(ViewProjection viewProjection_);
	float GetRadian()const { return playerRad; }
private:
	WorldTransform player_;
	WorldTransform playerMoveLine[64];
	Model* model_ = nullptr;
	DebugText* debugText_ = nullptr;
	Input* input_ = nullptr;

	float playerRad;

	float jumpPower;
	PlayerState state = PlayerState::Idle;
};

