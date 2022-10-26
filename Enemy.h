#pragma once

#include "DebugText.h"
#include "Input.h"
#include "Model.h"
#include "WorldTransform.h"
#include "ViewProjection.h"
#include <cassert>

enum class State { //�G�̏��

	needle, // �j	0
	normal, // ����	1
	cole	// �R�A	2
};

class Enemy
{
public:
	/// <summary>
	/// ����������
	/// </summary>
	/// <param name="model"></param>
	/// <param name="textureHandle"></param>
	/// <param name="i">�G�L�����̔ԍ�</param>
	void Initialize(Model* model, uint32_t textureHandle, int i);

	/// <summary>
	/// �X�V����
	/// </summary>
	/// <param name="i">�G�L�����̔ԍ�</param>
	void UpDate(int i);

	/// <summary>
	/// �`�揈��
	/// </summary>
	/// <param name="viewProjection"></param>
	void Draw(ViewProjection viewProjection);

	/// <summary>
	/// �f�o�b�N�p�e�L�X�g��p�̊֐�
	/// </summary>
	void DrawDebugText(int i);

	/// <summary>
	/// �����蔻��
	/// </summary>
	/// <returns></returns>
	void OnCollision();

	Matrix4 GetMatrix() { return enemy_.matWorld_; };

	WorldTransform GetWorldTransform() { return enemy_; };

	void SetWorldTransform(Vector3 pos);

	// ���W�̊i�[�p
	Vector3 pos = GetWorldTransform().translation_;

	// ���a�̊i�[�p
	Vector3 radiusu = GetWorldTransform().scale_;

	// pos + radiusu / pos - collision ���i�[
	Vector3 upCollision;
	Vector3 downCollision;

	bool IsCollision() { return isCollision_; }

private:
	WorldTransform enemy_;
	// ���f��
	Model* model_ = nullptr;
	// �e�N�X�`���n���h��
	uint32_t textureHandle_ = 0u;

	DebugText* debugText_ = nullptr;
	// �����蔻��
	bool isCollision_ = false;

	State state;
};

