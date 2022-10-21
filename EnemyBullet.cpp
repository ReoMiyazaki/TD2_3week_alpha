#include "EnemyBullet.h"
#include <random>
using namespace std;
using namespace MathUtility;

void EnemyBullet::Initialize(Model* model, uint32_t textureHandle)
{
	debugText_ = DebugText::GetInstance();
	model_ = Model::Create();
	input_ = Input::GetInstance();
	enemyBullet_.Initialize();
	enemyBullet_.translation_ = { 0.0f,0.0f,0.0f };

}

void EnemyBullet::Update(float moveCircle, PlayerState state)
{
	float bulletAngle = 0.0f;
	float bulletS = 0.2f;
	// 乱数宣言
	random_device seed_gem;
	mt19937_64 engine(seed_gem());
	uniform_real_distribution<float> rotDist(5.0f, 15.0f);
	uniform_real_distribution<float> angleDist(0.0f, 180.0f);
	
	//プレイヤがジャンプしたなら
	if (state == PlayerState::Jump)
	{
		// 弾が出て無ければ
		if (isFire != 1)
		{
			// 弾の出現位置
			enemyBullet_.translation_.y = rotDist(engine);

			// 角度の決定
			bulletAngle = angleDist(engine);
			// アングルをどう取得するのか?
			//速度の分解
			bulletSpeed.z = cos(bulletAngle * PI / 180) * bulletS;
			bulletSpeed.x = sin(bulletAngle * PI / 180) * bulletS;
			// 取得したものをスピードに
			
			// 出す
			isFire = 1;
		}
	}
	if (isFire == 1)
	{
		if (enemyBullet_.translation_.x >= moveCircle || enemyBullet_.translation_.x <= -moveCircle)
		{
			if (enemyBullet_.translation_.y >= moveCircle || enemyBullet_.translation_.y <= -moveCircle)
			{
				bulletSpeed = { 0.0f,0.0f,0.0f };
			}
		}
		// それ以外なら弾を進める
		enemyBullet_.translation_ += bulletSpeed;
	}
	
	enemyBullet_.MatUpdate();

	debugText_->SetPos(20, 20);
	debugText_->Printf("Angle:%f", bulletAngle);
	debugText_->SetPos(20, 40);
	debugText_->Printf("rotation:(%f,%f,%f)", enemyBullet_.rotation_.x, enemyBullet_.rotation_.y, enemyBullet_.rotation_.z);
	debugText_->SetPos(20, 60);
	debugText_->Printf("bulletAngle:%f", bulletAngle);
	debugText_->SetPos(20, 80);
	debugText_->Printf("bulletPos:(%f,%f,%f)", enemyBullet_.translation_.x, enemyBullet_.translation_.y, enemyBullet_.translation_.z);
	
}

void EnemyBullet::Draw(ViewProjection viewProjection)
{
	if (isFire == 1)
	{
		model_->Draw(enemyBullet_, viewProjection);
	}
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
