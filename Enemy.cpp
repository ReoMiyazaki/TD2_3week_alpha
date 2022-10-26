#include "Enemy.h"
#include <random>
using namespace std;
using namespace MathUtility;

void Enemy::Initialize(Model* model, uint32_t textureHandle, int i)
{
	debugText_ = DebugText::GetInstance();
	// NULL�|�C���^�`�F�b�N
	assert(model);
	// �����Ƃ��Ď󂯎�����f�[�^�������o�ϐ��ɋL��������
	this->model_ = model;
	this->textureHandle_ = textureHandle;

	// �����錾
	random_device seed_gem;
	mt19937_64 engine(seed_gem());
	uniform_real_distribution<float> rotDist(0.0f, 360.0f);
	uniform_real_distribution<float> enemyState(0, 3);
	//for (int i = 0; i < 10; i++)
	//{
	//	// ���ꂼ��̏�����
	//	worldTransforms_[i].Initialize();
	//	worldTransforms_[i].translation_.y = 2.0f * i;
	//	worldTransforms_[i].rotation_.y = rotDist(engine);
	//	//	worldTransforms_[i].scale_ = { 2.0f,2.0f,2.0f };
	//	worldTransforms_[i].MatUpdate();
	//}
	
	// �G�̏�Ԏ擾
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
	enemy_.rotation_.y = rotDist(engine);
	enemy_.scale_ = { 1.0f,1.0f,1.0f };
	enemy_.translation_.y = 2.0f * i;
	enemy_.MatUpdate();

	// Vector3�^��radiusu��scale_�̒l��n��
	radiusu = enemy_.scale_;
	needleCount_ = 0;
}

void Enemy::UpDate()
{
	// Vector3�^��pos��translation_�̒l��n��
	pos = GetWorldTransform().translation_;
	upCollision = { pos.x + radiusu.x, pos.y + radiusu.y, pos.z + radiusu.z };
	downCollision = { pos.x - radiusu.x, pos.y - radiusu.y, pos.z - radiusu.z };
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

	model_->Draw(enemy_, viewProjection, textureHandle_);

}

void Enemy::DrawDebugText(int i)
{
	debugText_->SetPos(50, 250 - 20 * i);
	debugText_->Printf("state[%d] : %d", i , state);
	debugText_->SetPos(800, 250 - 20 * i);
	debugText_->Printf("Count : %d", needleCount_);
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

Vector3 Enemy::GetWorldPosition(int i)
{
	//���[���h���W�����邽�߂̕ϐ�
	Vector3 worldPos[10];

	// ���[���h�s��̕��s�ړ��������擾
	worldPos[i].y = enemy_.matWorld_.m[3][1];
	worldPos[i].z = enemy_.matWorld_.m[3][2];
	worldPos[i].x = enemy_.matWorld_.m[3][0];

	return worldPos[i];
}