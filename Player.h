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
	/// 初期化処理
	/// </summary>
	/// <param name="moveCircleRadius"></param>
	/// <param name="moveCircle"></param>
	void Initialize(float moveCircleRadius, Vector2 moveCircle);

	/// <summary>
	/// 更新処理
	/// </summary>
	/// <param name="moveCircleRadius"></param>
	void Update(float moveCircleRadius);
	/// <summary>
	/// 描画処理
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

