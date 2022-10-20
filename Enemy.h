#pragma once

#include "DebugText.h"
#include "Input.h"
#include "Model.h"
#include "WorldTransform.h"
#include "ViewProjection.h"
#include <cassert>

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
	void UpDate(int i);
	
	/// <summary>
	/// �`�揈��
	/// </summary>
	/// <param name="viewProjection"></param>
	void Draw(ViewProjection viewProjection);

	/// <summary>
	/// �f�o�b�N�p�e�L�X�g
	/// </summary>
	void DebugTex(int i);

	/// <summary>
	/// �����蔻��
	/// </summary>
	/// <returns></returns>
	void OnCollision();

	// ���[���h���W���擾
	Vector3 GetWorldPosition(int i);

	// ���[���h�ϊ��f�[�^
//	WorldTransform worldTransforms_[10];

	Matrix4 GetMatrix() { return worldTransform_.matWorld_; };

private:
	WorldTransform worldTransform_;
	// ���f��
	Model* model_ = nullptr;
	// �e�N�X�`���n���h��
	uint32_t textureHandle_ = 0u;

	DebugText* debugText_ = nullptr;

	int isHit = 0;
};

