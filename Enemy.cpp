#include "Enemy.h"
#include <random>
using namespace std;

void Enemy::Initialize(Model* model, uint32_t textureHandle, int i)
{

	debugText_ = DebugText::GetInstance();
	// NULLポインタチェック
	assert(model);
	// 引数として受け取ったデータをメンバ変数に記憶させる
	this->model_ = model;
	this->textureHandle_ = textureHandle;

	// 乱数宣言
	random_device seed_gem;
	mt19937_64 engine(seed_gem());
	uniform_real_distribution<float> rotDist(0.0f, 360.0f);
	//for (int i = 0; i < 10; i++)
	//{
	//	// それぞれの初期化
	//	worldTransforms_[i].Initialize();
	//	worldTransforms_[i].translation_.y = 2.0f * i;
	//	worldTransforms_[i].rotation_.y = rotDist(engine);
	//	//	worldTransforms_[i].scale_ = { 2.0f,2.0f,2.0f };
	//	worldTransforms_[i].MatUpdate();
	//}

	worldTransform_.Initialize();
	worldTransform_.translation_.y = 2.0f * i;
	worldTransform_.rotation_.y = rotDist(engine);
	worldTransform_.MatUpdate();

}

void Enemy::UpDate(int i)
{
}

void Enemy::Draw(ViewProjection viewProjection)
{
	//	for (int i = 0; i < 10; i++)
	//	{
	//		model_->Draw(worldTransforms_[i], viewProjection, textureHandle_);
	//	}
	//	model_->Draw(worldTransform_, viewProjection, textureHandle_);
	//	debugText_->SetPos(50, 190 + 35 * i);
	//	debugText_->Printf("isHit[%d] : %d", i, isHit);

	model_->Draw(worldTransform_, viewProjection, textureHandle_);

}

void Enemy::DebugTex(int i)
{
	debugText_->SetPos(50, 200 + 20 * i);
	debugText_->Printf("enemy_[%d]->pos.y : %3.2f", i, worldTransform_.translation_.y);
	debugText_->SetPos(800, 250 + 20 * i);
	debugText_->Printf("isHit[%d] : %d", i, isHit);
}

void Enemy::OnCollision()
{
	isHit = 1;
}

Vector3 Enemy::GetWorldPosition(int i)
{
	//ワールド座標を入れるための変数
	Vector3 worldPos[10];

	// ワールド行列の平行移動成分を取得
	worldPos[i].y = worldTransform_.matWorld_.m[3][1];
	worldPos[i].z = worldTransform_.matWorld_.m[3][2];
	worldPos[i].x = worldTransform_.matWorld_.m[3][0];

	return worldPos[i];
}