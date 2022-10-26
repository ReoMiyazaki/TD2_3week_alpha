#pragma once
#include "DebugText.h"
#include "Input.h"
#include "Model.h"
#include "WorldTransform.h"
#include "ViewProjection.h"
#include <cassert>
#include "Player.h"
#include <list>

class EnemyBullet
{
public:
	/// <summary>
	/// ����������
	/// </summary>
	/// <param name="model"></param>
	/// <param name="textureHandle"></param>
	void Initialize(Model* model, uint32_t textureHandle);
	void Update(PlayerState state);

	/// <summary>
	/// �`�揈��
	/// </summary>
	/// <param name="viewProjection"></param>
	void Draw(ViewProjection viewProjection);

	/// <summary>
	/// �����蔻��
	/// </summary>
	/// <returns></returns>
	void OnCollision();

	/// <summary>
	/// �f�o�b�N�p�e�L�X�g��p�̊֐�
	/// </summary>
	void DrawDebugText();

	WorldTransform GetWorldTransform() { return enemyBullet_; };
	Vector3 radius = GetWorldTransform().scale_;

	// ���[���h���W���擾
	Vector3 GetWorldPosition();

	bool GetOnCollision();
	// ���W�̊i�[�p
	Vector3 pos = GetWorldTransform().translation_;

	Vector3 upCollision;
	Vector3 downCollision;
private:
	// ���W
	WorldTransform enemyBullet_;
	Model* model_ = nullptr;
	DebugText* debugText_ = nullptr;
	Input* input_ = nullptr;

	//�e���x
	Vector3 bulletSpeed = { 0.0f,0.0f,0.2f };
	//�t���O
	int isFire = 0;
	// �����蔻��
	bool isCollision_ = false;
	//�폜�^�C�}�[
	float deleteTimer = 150;
	float aliveTimer = 0;
};

