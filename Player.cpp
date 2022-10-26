#include "Player.h"
#include<time.h>

using namespace MathUtility;

void Player::Initialize(float moveCircleRadius, Vector2 moveCircle)
{
	debugText_ = DebugText::GetInstance();
	input_ = Input::GetInstance();
	model_ = Model::Create();
	input_ = Input::GetInstance();

	player_.scale_ = { 1.0f, 1.0f, 1.0f };

	player_.Initialize();
	playerRad = 0;

	// プレイヤーの行動円
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

	// Vector3型のradiusuにscale_の値を渡す
	radiusu = player_.scale_;
	
	nowTimer = 0.0f;
	endTimer = 5.0f;
}

void Player::Update(float moveCircleRadius)
{
	// ステートがアイドルなら
	if (state == PlayerState::Idle)
	{
		// プレイヤーが原点を中心に回転
		playerRad += 2.0f;
		playerRad = fmodf(playerRad, 360.0f);
		rotation = player_.rotation_;
		rotation.y += playerRad;
		player_.rotation_.y = playerRad * PI / 180.0f;
		player_.rotation_.z -= 0.25f;
		player_.rotation_.z = fmodf(player_.rotation_.z, 360.0f);

		movePos.x = sin(PI / 180 * playerRad) * moveCircleRadius;
		movePos.z = cos(PI / 180 * playerRad) * moveCircleRadius;
		player_.translation_ = movePos;

		// スペースキーのトリガーでチャージ状態に移行
		if (input_->TriggerKey(DIK_SPACE))
		{
			state = PlayerState::Charge;
			player_.rotation_.z = 0.0f;

		}

		// Vector3型のposにtranslation_の値を渡す
		pos = GetWorldTransform().translation_;

	}
	//else if (state == PlayerState::Charge) {
	//	//チャージステート中はジャンプ力を溜めながら横に回転
	//	if (jumpPower <= 5.5f)// 制限
	//	{
	//		jumpPower += 0.1f;
	//	}
	//	else if (jumpPower > 5.5f)// 強制ジャンプ
	//	{
	//		state = PlayerState::Jump;
	//	}

	// playerチャージ処理
	else if (state == PlayerState::Charge)
	{
		// チャージステート中はジャンプ力を溜めながら横に回転
		jumpPower += 0.1f;
		player_.rotation_.y += jumpPower / 10.0f;

		// スペースキーが離されたらジャンプ状態に移行
		if (!input_->PushKey(DIK_SPACE)) {
			state = PlayerState::Jump;
		}
	}

	// playerジャンプ処理
	else if (state == PlayerState::Jump)
	{

		isCollision_ = false;
		// チャージされたジャンプ力でジャンプ
		player_.translation_.y += jumpPower;
		jumpPower--;
		translationMemory.x = player_.translation_.x;
		translationMemory.y = 0.0f;
		translationMemory.z = player_.translation_.z;
		// 高さが0以下になったらアイドルに戻る
		if (player_.translation_.y <= 0) {
			player_.translation_.y = 0;
			jumpPower = 0;
			state = PlayerState::Idle;
		}
		// トリガーでダッシュ移動
		if (input_->TriggerKey(DIK_SPACE))
		{
			state = PlayerState::dash;
			// Vector3型のposにtranslation_の値を渡す
			pos = GetWorldTransform().translation_;
			// 上下(左右)の当たり判定を計算
			upCollision = { pos.x + radiusu.x, pos.y + radiusu.y, pos.z + radiusu.z };
			downCollision = { pos.x - radiusu.x, pos.y - radiusu.y, pos.z - radiusu.z };

			player_.rotation_.y = 0.0f;
			//自機位置から180度回転した位置を移動後座標に設定
			afterPos.x = sin(PI / 180 * (180 + playerRad)) * moveCircleRadius;
			afterPos.y = player_.translation_.y;
			afterPos.z = cos(PI / 180 * (180 + playerRad)) * moveCircleRadius;
			playerPosition = GetWorldPosition();
			//移動後座標と現座標から移動用速度ベクトル計算
			dashSpeed.x = afterPos.x - player_.translation_.x;
			dashSpeed.z = afterPos.z - player_.translation_.z;
			//速度を移動時間で分割
			dashSpeed.x /= static_cast<int>(dashTime);
			dashSpeed.z /= static_cast<int>(dashTime);

			player_.rotation_.y = playerRad * PI / 180.0f;
		}
		pos.y = player_.translation_.y;
	}

	// playerダッシュ処理
	else if (state == PlayerState::dash)
	{
		/*Vector3Length(distance);
		Vector3Normalize(distance);*/

		//	dashSpeed *= kMoveSpeed;
			//移動速度の加算

			//dashSpeed /= 10.0f;

		player_.translation_.x += dashSpeed.x;
		player_.translation_.z += dashSpeed.z;

		player_.rotation_.z += 0.5f;

		//自機の平行移動量がスペースキー押下時に設定した移動後座標なら移動終了。落下フェーズへ
		if (static_cast<int>(player_.translation_.x) == static_cast<int>(afterPos.x) &&
			static_cast<int>(player_.translation_.y) == static_cast<int>(afterPos.y) &&
			static_cast<int>(player_.translation_.z) == static_cast<int>(afterPos.z)) {

		}

		int a, b;
		a = player_.translation_.x - afterPos.x;
		b = player_.translation_.z - afterPos.z;
		if (a == 0 && b == 0) {
			player_.rotation_.x = 0.0f;
			state = PlayerState::Jump;
			jumpPower = 0.0f;
		}

		if (player_.translation_.z == translationMemory.z)
		{
			state = PlayerState::Jump;
			jumpPower = 0.0f;
		}
		/*if (player_.translation_.x >= afterPos.x && player_.translation_.z >= afterPos.z ||
			player_.translation_.x >= afterPos.x && afterPos.z >= player_.translation_.z ||
			afterPos.x >= player_.translation_.x && player_.translation_.z >= afterPos.z ||
			afterPos.x >= player_.translation_.x && afterPos.z >= player_.translation_.z) {
			dashSpeed = { 0,0,0 };
			player_.translation_.x = afterPos.x;
			player_.translation_.z = afterPos.z;
			player_.translation_.y--;
		}
		if (player_.translation_.y < 0) {
			jumpPower = 0.0f;
			player_.translation_.y = 0;
			state = PlayerState::Idle;
		}*/
		// Vector3型のposにtranslation_の値を渡す
		pos = GetWorldTransform().translation_;

		upCollision = { pos.x + radiusu.x, pos.y + radiusu.y, pos.z + radiusu.z };
		downCollision = { pos.x - radiusu.x, pos.y - radiusu.y, pos.z - radiusu.z };

		
	}

	player_.MatUpdate();

}

void Player::Draw(ViewProjection viewProjection_)
{
	model_->Draw(player_, viewProjection_);

	for (int i = 0; i < 64; i++)
	{
		model_->Draw(playerMoveLine[i], viewProjection_);
	}

	//	debugText_->SetPos(50, 70);
	//	debugText_->Printf("state:%d(0:Idle,1:Charge,2:Jump)", state);
	//	debugText_->SetPos(50, 90);
	//	debugText_->Printf("jumpPower:%f", jumpPower);
	//	debugText_->SetPos(50, 130);
	//	debugText_->Printf("dashSpeed:(%f,%f,%f)", dashSpeed.x, dashSpeed.y, dashSpeed.z);
	//	debugText_->SetPos(50, 170);
	//	debugText_->Printf("rotation_:(%f,%f,%f)", player_.rotation_.x, player_.rotation_.y, player_.rotation_.z);

}

void Player::DrawDebugText()
{
	/*debugText_->SetPos(50, 20);
	debugText_->Printf("playerTranslation:[%3.1f][%3.1f][%3.1f]", player_.translation_.x, player_.translation_.y, player_.translation_.z);
	debugText_->SetPos(50, 40);
	debugText_->Printf("translationMemory:(%3.2f,%3.2f,%3.2f)", translationMemory.x, translationMemory.y, translationMemory.z);*/
	/*debugText_->SetPos(50, 60);
	debugText_->Printf("afterPos:(%3.2f,%3.2f,%3.2f)", afterPos.x, afterPos.y, afterPos.z);
	debugText_->SetPos(50, 100);
	debugText_->Printf("pos - afterpos:(%d,%d,%d)", player_.translation_.x - afterPos.x, 0, player_.translation_.z - afterPos.z);*/
}

void Player::OnCollision()
{
	isCollision_ = true;
}

Vector3 Player::GetWorldPosition()
{
	//ワールド座標を入れるための変数
	Vector3 worldPos;

	//ワールド行列の平行移動成分を取得
	worldPos.x = player_.matWorld_.m[3][0];
	worldPos.y = player_.matWorld_.m[3][1];
	worldPos.z = player_.matWorld_.m[3][2];

	return worldPos;
}

void Player::OnCollision(int enemyState, int needleCount)
{
	isCollision_ = true;
	if (enemyState == 1 && needleCount < 2 && isCollision_ == true)
	{	
		//スタート,エンド,中間を取得
		startPoint = player_.translation_;
		endPoint = translationMemory;
		whilePoint = { (startPoint.x - endPoint.x) / 2,startPoint.y + startPoint.y / 2,startPoint.z - endPoint.z };
		//タイマーのカウントを開始
		
		// 弾く
		dashSpeed = -dashSpeed;
		if (needleCount == 2)
		{
			isCollision_ = false;
		}
	}
	
}