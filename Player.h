#pragma once

#include "Input.h"
#include "Model.h"
#include "WorldTransform.h"
#include "ViewProjection.h"
#include "DebugText.h"

enum class PlayerState {
	Idle,
	Charge,
	Jump,
	dash
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

	/// <summary>
	/// デバック用テキスト専用の関数
	/// </summary>
	void DrawDebugText();

	/// <summary>
	/// 当たり判定
	/// </summary>
	/// <returns></returns>
	void OnCollision();

	float GetRadian()const { return playerRad; }

	// ワールド座標を取得
	Vector3 GetWorldPosition();

	Matrix4 GetMatrix() { return player_.matWorld_; };

	PlayerState GetPlayerState()const { return state; }

	WorldTransform GetWorldTransform() { return player_; };

	// 座標の格納用
	Vector3 pos = GetWorldTransform().translation_;

	// 半径の格納用
	Vector3 radiusu = GetWorldTransform().scale_;

	// pos + radiusu / pos - collision を格納
	Vector3 upCollision;
	Vector3 downCollision;

	bool IsCollision() { return isCollision_; }

private:
	WorldTransform player_;
	WorldTransform playerMoveLine[64];
	Model* model_ = nullptr;
	DebugText* debugText_ = nullptr;
	Input* input_ = nullptr;

	float playerRad;

	float jumpPower;
	PlayerState state = PlayerState::Idle;

	Vector3 movePos;
	Vector3 rotation;
	Vector3 playerPosition;
	Vector3 afterPos;
	Vector3 dashSpeed;

	int dashTime = 50;

	float kMoveSpeed = 4.0f;

	// あたり判定
	bool isCollision_ = false;

};