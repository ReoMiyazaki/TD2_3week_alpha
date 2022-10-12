#include "Enemy.h"
#include <random>
using namespace std;

void Enemy::Initialize(Model* model, uint32_t textureHandle)
{
	// NULL�|�C���^�`�F�b�N
	assert(model);
	// �����Ƃ��Ď󂯎�����f�[�^�������o�ϐ��ɋL��������
	this->model_ = model;
	this->textureHandle_ = textureHandle;

	// �����錾
	random_device seed_gem;
	mt19937_64 engine(seed_gem());
	uniform_real_distribution<float> rotDist(0.0f, 360.0f);

	for (int i = 0; i < 10; i++)
	{
		// ���ꂼ��̏�����
		worldTransforms_[i].Initialize();
		worldTransforms_[i].translation_.y = 2.0f * i;
		worldTransforms_[i].rotation_.y = rotDist(engine);
		worldTransforms_[i].MatUpdate();
	}
}

void Enemy::UpDate()
{
}

void Enemy::Draw(ViewProjection viewProjection)
{
	for (int i = 0; i < 10; i++)
	{
		model_->Draw(worldTransforms_[i], viewProjection, textureHandle_);
	}
}
