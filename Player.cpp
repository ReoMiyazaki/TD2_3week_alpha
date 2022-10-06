#include "Player.h"
using namespace MathUtility;

void Player::Initialize(float moveCircleRadius, Vector2 moveCircle)
{
	debugText_ = DebugText::GetInstance();
	model_ = Model::Create();
	input_ = Input::GetInstance();

	player_.Initialize();
	playerRad = 0;

	//プレイヤーの行動円
	for (int i = 0; i < 64; i++)
	{
		playerMoveLine[i].Initialize();
		float rad = 360.0f / 64.0f * i;
		moveCircle.x = sin(PI / 180 * rad) * moveCircleRadius;
		moveCircle.y = cos(PI / 180 * rad) * moveCircleRadius;
		Vector3 pos;
		pos.x = moveCircle.x;
		pos.z = moveCircle.y;
		pos.y = 0;
		playerMoveLine[i].translation_ = pos;
		playerMoveLine[i].scale_ = { 0.1f,0.1f,0.1f };
		playerMoveLine[i].MatUpdate();
	}
}

void Player::Update(float moveCircleRadius)
{
	if (moveType == revolution)
	{
		//プレイヤーが原点を中心に回転
		playerRad += 2.0f;
		playerRad = fmodf(playerRad, 360.0f);
		Vector3 movePos;
		Vector3 rotation = player_.rotation_;
		rotation.y += playerRad;
		player_.rotation_.y = playerRad * PI / 180.0f;
		player_.rotation_.z -= 0.25f;
		player_.rotation_.z = fmodf(player_.rotation_.z, 360.0f);

		movePos.x = sin(PI / 180 * playerRad) * moveCircleRadius;
		movePos.z = cos(PI / 180 * playerRad) * moveCircleRadius;
		player_.translation_ = movePos;
		player_.MatUpdate();

		if (input_->PushKey(DIK_SPACE))
		{
			moveType = dash;
		}
	}
	else if (moveType == dash)
	{
		player_.translation_.x = player_.translation_.x * -1;
		player_.translation_.z = player_.translation_.z * -1;
		player_.MatUpdate();
		moveType = revolution;
	}
}

void Player::Draw(ViewProjection viewProjection_)
{
	model_->Draw(player_, viewProjection_);

	for (int i = 0; i < 64; i++)
	{
		model_->Draw(playerMoveLine[i], viewProjection_);
	}
	//デバッグフォント
	debugText_->Printf("playerRad:%f", playerRad);
}
