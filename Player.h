#pragma once

#include "Input.h"
#include "Model.h"
#include "WorldTransform.h"
#include "ViewProjection.h"
#include "DebugText.h"

enum movePattern
{
	revolution,
	jump,
	dash,
};

class Player
{
public:
	/// <summary>
	/// ‰Šú‰»ˆ—
	/// </summary>
	/// <param name="moveCircleRadius"></param>
	/// <param name="moveCircle"></param>
	void Initialize(float moveCircleRadius, Vector2 moveCircle);

	/// <summary>
	/// XVˆ—
	/// </summary>
	/// <param name="moveCircleRadius"></param>
	void Update(float moveCircleRadius);
	/// <summary>
	/// •`‰æˆ—
	/// </summary>
	void Draw(ViewProjection viewProjection_);
	float GetRadian()const { return playerRad; }
private:
	WorldTransform player_;
	WorldTransform playerMoveLine[64];
	Model* model_ = nullptr;
	DebugText* debugText_ = nullptr;
	Input* input_ = nullptr;

	float playerRad;

	int moveType;


};

