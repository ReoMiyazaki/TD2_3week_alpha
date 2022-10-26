#pragma once
#include "DebugText.h"
#include "Global.h"
#include"Input.h"
#include <memory>
#include "Sprite.h"
#include "Vector2.h"

class TitleScene
{
public:
	/// <summary>
	/// ����������
	/// </summary>
	void Initialize();

	/// <summary>
	/// �X�V����
	/// </summary>
	/// <param name="scene"></param>
	void Update(Scene& scene);

	/// <summary>
	/// �`�揈��
	/// </summary>
	void Draw();

	void Select(Scene& scene);

private:
	Input* input_ = nullptr;

	DebugText* debugText_ = nullptr;

	// �摜�p�ϐ�
	uint32_t titleLogo = 0;
	uint32_t goToGame = 0;
	uint32_t endGame = 0;
	uint32_t pushToState = 0;
	

	// �摜�̃X�v���C�g
	std::unique_ptr<Sprite> titleLogo_;
	std::unique_ptr<Sprite> goToGame_;
	std::unique_ptr<Sprite> endGame_;
	std::unique_ptr<Sprite> pushToState_;
	

};

