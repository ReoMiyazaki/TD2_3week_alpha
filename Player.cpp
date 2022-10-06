#include "Player.h"
using namespace MathUtility;

void Player::Initialize(float moveCircleRadius, Vector2 moveCircle)
{
	debugText_ = DebugText::GetInstance();
	input_ = Input::GetInstance();
	model_ = Model::Create();

	player_.Initialize();
	playerRad = 0;

	//プレイヤーの行動円
	for (int i = 0; i < 64; i++) {
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
	//ステートがアイドルなら
	if (state == PlayerState::Idle) {

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
		

		//スペースキーのトリガーでチャージ状態に移行
		if (input_->TriggerKey(DIK_SPACE)) {
			state = PlayerState::Charge;
			player_.rotation_.z = 0.0f;
			
		}
	}
	else if (state == PlayerState::Charge) {
		//チャージステート中はジャンプ力を溜めながら横に回転
		jumpPower += 0.1f;
		player_.rotation_.y += jumpPower / 10.0f;

		//スペースキーが離されたらジャンプ状態に移行
		if (!input_->PushKey(DIK_SPACE)) {
			state = PlayerState::Jump;
		}
	}
	else if (state == PlayerState::Jump) {
		//チャージされたジャンプ力でジャンプ
		player_.translation_.y += jumpPower;
		jumpPower--;
		//高さが0以下になったらアイドルに戻る
		if (player_.translation_.y <= 0) {
			player_.translation_.y = 0;
			jumpPower = 0;
			state = PlayerState::Idle;
		}
	}



	player_.MatUpdate();
}

void Player::Draw(ViewProjection viewProjection_)
{
	model_->Draw(player_, viewProjection_);

	for (int i = 0; i < 64; i++) {
		model_->Draw(playerMoveLine[i], viewProjection_);
	}
	//デバッグフォント
	debugText_->Printf("playerRad:%f", playerRad);
	debugText_->SetPos(50,70);
	debugText_->Printf("state:%d(0:Idle,1:Charge,2:Jump)", state);
	debugText_->SetPos(50, 90);
	debugText_->Printf("jumpPower:%f", jumpPower);
}
