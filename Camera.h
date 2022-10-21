#pragma once
#include "Input.h"
#include "WorldTransform.h"
#include "ViewProjection.h"
#include "DebugText.h"
#include "Player.h"

class Camera
{
public:
	/// <summary>
	/// ����������
	/// </summary>
	/// <param name="playerRadius"></param>
	void Initialize(float playerRadius);

	/// <summary>
	/// �X�V����
	/// </summary>
	/// <param name="playerRadius"></param>
	/// <param name="state"></param>
	void Update(float playerRadius, PlayerState state);

	/// <summary>
	/// �`�揈��
	/// </summary>
	void Draw();

	/// <summary>
	/// �f�o�b�N�p�e�L�X�g��p�̊֐�
	/// </summary>
	void DrawDebugText();

	float EZ(float start, float end, float timer);

	Vector3 GetCameraPos()const { return cameraPos; }
private:
	Input* input_ = nullptr;
	DebugText* debugText_ = nullptr;
	float cameraDistance = 50.0f;

	Vector3 cameraPos;
	Vector3 cameraPosMemory;

	float maxTime;
	float timeRate;
	float beforeRad = 0; 
	float beforeplayerRad = 0;
	long long startCount;
	long long nowCount;
	long long endCount;
	float endTimer;

	int cameraFlag;
};