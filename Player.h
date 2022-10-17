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
	/// ����������
	/// </summary>
	/// <param name="moveCircleRadius"></param>
	/// <param name="moveCircle"></param>
	void Initialize(float moveCircleRadius, Vector2 moveCircle);

	/// <summary>
	/// �X�V����
	/// </summary>
	/// <param name="moveCircleRadius"></param>
	void Update(float moveCircleRadius);
	/// <summary>
	/// �`�揈��
	/// </summary>
	void Draw(ViewProjection viewProjection_);

	float GetRadian()const { return playerRad; }

	// ���[���h���W���擾
	Vector3 GetWorldPosition();

	Matrix4 GetMatrix() { return player_.matWorld_; };

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

};

