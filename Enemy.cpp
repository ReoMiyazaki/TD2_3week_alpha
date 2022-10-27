#include "Enemy.h"
#include <random>
using namespace std;
using namespace MathUtility;

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
	uniform_real_distribution<float> enemyState(0, 3);
	
	// 敵の状態取得
	state_ = enemyState(engine);
	if (state_ == 0)
	{
		state = State::normal;
	}
	if (state_ == 1)
	{
		state = State::needle;
	}
	if (state_ == 2)
	{
		state = State::cole;
	}
	
	
	enemy_.Initialize();
	enemy_.scale_ = { 1.0f,1.0f,1.0f };
	enemy_.translation_.y = (enemy_.scale_.y * 2) * i;
	enemy_.rotation_.y = rotDist(engine);
	enemy_.MatUpdate();

	// Vector3型のradiusuにscale_の値を渡す
	radiusu = enemy_.scale_;

	isCollision_ = false;

	needleCount_ = 0;
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

	//debugText_->SetPos(50, 250 - 20 * i);
	//debugText_->Printf("state[%d] : %d", i , state);
	//debugText_->SetPos(800, 250 - 20 * i);
	//debugText_->Printf("Count : %d", needleCount_);
}

void Enemy::OnCollision()
{
	if (state == State::normal)
	{
		isCollision_ = true;
	}
	if (state == State::needle)
	{
		isCollision_ = true;
		needleCount_ += 1;
		if (needleCount_ >= 2)
		{
			state = State::normal;
		}
	}
	if (state == State::cole)
	{
		isCollision_ = true;
	}
}

void Enemy::SetWorldTransform(Vector3 pos)
{
	enemy_.translation_ = pos;
}

void Enemy::ReSet(int i)
{
	// 乱数宣言
	random_device seed_gem;
	mt19937_64 engine(seed_gem());
	uniform_real_distribution<float> rotDist(0.0f, 360.0f);
	uniform_real_distribution<float> enemyState(0, 3);

	// 敵の状態取得
	state_ = enemyState(engine);
	if (state_ == 0)
	{
		state = State::normal;
	}
	if (state_ == 1)
	{
		state = State::needle;
	}
	if (state_ == 2)
	{
		state = State::cole;
	}


	enemy_.Initialize();
	enemy_.scale_ = { 1.0f,1.0f,1.0f };
	enemy_.translation_.y = (enemy_.scale_.y * 2) * i;
	enemy_.rotation_.y = rotDist(engine);
	enemy_.MatUpdate();

	// Vector3型のradiusuにscale_の値を渡す
	radiusu = enemy_.scale_;

	isCollision_ = false;

	needleCount_ = 0;
}