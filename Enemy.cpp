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

	enemy_.Initialize();
	enemy_.scale_ = { 2.0f,2.0f,2.0f };
	enemy_.translation_.y = (enemy_.scale_.y * 2) * i;
	enemy_.rotation_.y = rotDist(engine);
	enemy_.MatUpdate();

	// Vector3型のradiusuにscale_の値を渡す
	radiusu = enemy_.scale_;

	isCollision_ = false;

}

void Enemy::UpDate(int i)
{
		// Vector3型のposにtranslation_の値を渡す
		pos = GetWorldTransform().translation_;
		upCollision = { pos.x + radiusu.x, pos.y + radiusu.y, pos.z + radiusu.z };
		downCollision = { pos.x - radiusu.x, pos.y - radiusu.y, pos.z - radiusu.z };
		enemy_.MatUpdate();
}

void Enemy::Draw(ViewProjection viewProjection)
{
	model_->Draw(enemy_, viewProjection, textureHandle_);
}

void Enemy::DrawDebugText(int i)
{
	debugText_->SetPos(50, 100 + 20 * i);
	//debugText_->Printf("eNum[%d]isCollision:%d", i, isCollision_);
	debugText_->SetPos(50, 100 + 20 * i);
	debugText_->Printf("eNum[%d]pos.y:%3.5f", i, pos.y);

}

void Enemy::OnCollision()
{
	isCollision_ = true;
}

void Enemy::SetWorldTransform(Vector3 pos)
{
	enemy_.translation_ = pos;
}
