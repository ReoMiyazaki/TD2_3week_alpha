#include "EnemyBullet.h"
#include <random>
using namespace std;

void EnemyBullet::Initialize(Model* model, uint32_t textureHandle)
{
	debugText_ = DebugText::GetInstance();
	model_ = Model::Create();
	input_ = Input::GetInstance();
	enemyBullet_.Initialize();
	enemyBullet_.translation_ = { 0.0f,0.0f,0.0f };
	
}

void EnemyBullet::Update(PlayerState state)
{
	// 乱数宣言
	random_device seed_gem;
	mt19937_64 engine(seed_gem());
	uniform_real_distribution<float> rotDist(5.0f, 15.0f);
	//プレイヤがジャンプしたなら
	if (state == PlayerState::Jump)
	{
		// 弾が出て無ければ
		if (isFire != 1)
		{
			enemyBullet_.translation_.y = rotDist(engine);
			// 出す
			isFire = 1;
		}
	}
	if (isFire == 1)
	{
		if (enemyBullet_.translation_.x >= 13.0f /*←弾を残留させる座標が必要*/ || enemyBullet_.translation_.z >= 13.0f /*←弾を残留させる座標が必要*/)
		{
			// 残留地点についたら弾を止める
			bulletSpeed = { 0.0f,0.0f,0.0f };
		}
		// それ以外なら弾を進める
		enemyBullet_.translation_.x += bulletSpeed.x;
		enemyBullet_.translation_.z += bulletSpeed.z;
	}
	enemyBullet_.MatUpdate();
}

void EnemyBullet::Draw(ViewProjection viewProjection)
{
	if (isFire == 1)
	{
		model_->Draw(enemyBullet_, viewProjection);
	}
}

void EnemyBullet::DrawDebugText()
{
	debugText_->SetPos(500, 20);
	debugText_->Printf("bulletPos[%3.2f][%3.2f][%3.2f]", enemyBullet_.translation_.x, enemyBullet_.translation_.y, enemyBullet_.translation_.z);
	debugText_->SetPos(500, 40);
	debugText_->Printf("isFire:[%d]", isFire);
}

Vector3 EnemyBullet::GetWorldPosition()
{
	//ワールド座標を入れるための変数
	Vector3 worldPos;

	// ワールド行列の平行移動成分を取得
	worldPos.y = enemyBullet_.matWorld_.m[3][1];
	worldPos.z = enemyBullet_.matWorld_.m[3][2];
	worldPos.x = enemyBullet_.matWorld_.m[3][0];

	return worldPos;
}
