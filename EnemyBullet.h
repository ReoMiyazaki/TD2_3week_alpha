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
	void Update(float moveCircle, PlayerState state);

	/// <summary>
	/// �`�揈��
	/// </summary>
	/// <param name="viewProjection"></param>
	void Draw(ViewProjection viewProjection);

	/// <summary>
	/// �f�o�b�N�p�e�L�X�g��p�̊֐�
	/// </summary>
	void DrawDebugText();

	// ���[���h���W���擾
	Vector3 GetWorldPosition();

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
};

