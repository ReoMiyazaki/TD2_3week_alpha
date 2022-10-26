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
	enemyBullet_.scale_ = { 0.8f,0.8f,0.8f };
	radius = enemyBullet_.scale_;
}

void EnemyBullet::Update(PlayerState state)
{
	float bulletAngle = 0.0f;
	float bulletS = 0.2f;
	// �����錾
	random_device seed_gem;
	mt19937_64 engine(seed_gem());
	uniform_real_distribution<float> rotDist(5.0f, 15.0f);
	uniform_real_distribution<float> angleDist(0.0f, 180.0f);
	
	Vector3 pos = GetWorldTransform().translation_;
	//�v���C�����W�����v�����Ȃ�
	if (state == PlayerState::Jump)
	{
		// �e���o�Ė������
		if (isFire != 1)
		{
			// �e�̏o���ʒu
			enemyBullet_.translation_.y = rotDist(engine);

			// �p�x�̌���
			bulletAngle = angleDist(engine);
			// �A���O�����ǂ��擾����̂�?
			//���x�̕���
			bulletSpeed.z = cos(bulletAngle * PI / 180) * bulletS;
			bulletSpeed.x = sin(bulletAngle * PI / 180) * bulletS;
			// �擾�������̂��X�s�[�h��
			
			// �o��
			isFire = 1;
		}
	}
	if (isFire == 1)
	{
		// ����ȊO�Ȃ�e��i�߂�
		if (enemyBullet_.translation_.x >= -14.0f && enemyBullet_.translation_.x <= 14.0f)
		{
			if (enemyBullet_.translation_.z >= -14.0f && enemyBullet_.translation_.z <= 14.0f)
			{
				enemyBullet_.rotation_.x += 0.2f;
				enemyBullet_.rotation_.z += 0.2f;
				enemyBullet_.translation_ += bulletSpeed;
			}
		}
		else
		{
			deleteTimer -= 0.5f;
			if (deleteTimer <= 0.0f)
			{
				enemyBullet_.translation_ = { 0.0f,0.0f,0.0f };
				deleteTimer = 150.0f;
				aliveTimer = 0.0f;
				isFire = 0;
			}
		}
		aliveTimer += 0.5f;
		if (aliveTimer >= 300.0f)
		{
			enemyBullet_.translation_ = { 0.0f,0.0f,0.0f };
			deleteTimer = 150.0f;
			aliveTimer = 0.0f;
			isFire = 0;
		}
		upCollision = { pos.x + radius.x, pos.y + radius.y, pos.z + radius.z };
		downCollision = { pos.x - radius.x, pos.y - radius.y, pos.z - radius.z };
	}
	
	enemyBullet_.MatUpdate();

	//debugText_->SetPos(20, 20);
	//debugText_->Printf("Angle:%f", bulletAngle);
	//debugText_->SetPos(20, 40);
	//debugText_->Printf("rotation:(%f,%f,%f)", enemyBullet_.rotation_.x, enemyBullet_.rotation_.y, enemyBullet_.rotation_.z);
	//debugText_->SetPos(20, 60);
	//debugText_->Printf("bulletAngle:%f", bulletAngle);
	//debugText_->SetPos(20, 80);
	//debugText_->Printf("bulletPos:(%f,%f,%f)", enemyBullet_.translation_.x, enemyBullet_.translation_.y, enemyBullet_.translation_.z);
	
}

void EnemyBullet::Draw(ViewProjection viewProjection)
{
	if (isFire == 1)
	{
		model_->Draw(enemyBullet_, viewProjection);
	}
}

void EnemyBullet::OnCollision()
{
	isCollision_ = true;
}

void EnemyBullet::DrawDebugText()
{
	/*debugText_->SetPos(500, 20);
	debugText_->Printf("bulletPos[%3.2f][%3.2f][%3.2f]", enemyBullet_.translation_.x, enemyBullet_.translation_.y, enemyBullet_.translation_.z);
	debugText_->SetPos(50, 40);
	debugText_->Printf("Speed:[%f]", bulletSpeed.z);
	debugText_->SetPos(50, 60);
	debugText_->Printf("Timer:[%f][%f]", aliveTimer, deleteTimer);*/
}

Vector3 EnemyBullet::GetWorldPosition()
{
	//���[���h���W�����邽�߂̕ϐ�
	Vector3 worldPos;

	// ���[���h�s��̕��s�ړ��������擾
	worldPos.y = enemyBullet_.matWorld_.m[3][1];
	worldPos.z = enemyBullet_.matWorld_.m[3][2];
	worldPos.x = enemyBullet_.matWorld_.m[3][0];

	return worldPos;
}
