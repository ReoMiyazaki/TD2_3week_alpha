#pragma once

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
	void Initialize(Model* model, uint32_t textureHandle);
	
	/// <summary>
	/// �X�V����
	/// </summary>
	void UpDate();
	
	/// <summary>
	/// �`�揈��
	/// </summary>
	/// <param name="viewProjection"></param>
	void Draw(ViewProjection viewProjection);


private:
	// ���[���h�ϊ��f�[�^
	WorldTransform worldTransforms_[10];
	// ���f��
	Model* model_ = nullptr;
	// �e�N�X�`���n���h��
	uint32_t textureHandle_ = 0u;
};

