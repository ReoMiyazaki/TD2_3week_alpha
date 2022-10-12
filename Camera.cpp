#include "Camera.h"

using namespace MathUtility;

void Camera::Initialize(float playerRadius)
{
	input_ = Input::GetInstance();
	debugText_ = DebugText::GetInstance();
	//�J�������W�����@�̊p�x���g���Čv�Z
	float cameraRad = playerRadius + 45.0f;
	cameraPos.y = 20.0f;
	cameraPos.x = sin(cameraRad * PI / 180) * cameraDistance;
	cameraPos.z = cos(cameraRad * PI / 180) * cameraDistance;
	cameraPosMemory.y = 20.0f;
	cameraPosMemory.x = 0;
	cameraPosMemory.z = 0;

//------------ �C�[�W���O�֌W -------------------//
	startCount = 0;
	nowCount = 0;
	endCount = 0;

	maxTime = 5.0f;
//------------ �C�[�W���O�֌W -------------------//
	cameraFlag = false;
}

void Camera::Update(float playerRadius, PlayerState state)
{
	//�J�����̍X�V
	float cameraRad = playerRadius + 30.0f;
	cameraPos.x = sin(cameraRad * PI / 180) * cameraDistance;
	cameraPos.z = cos(cameraRad * PI / 180) * cameraDistance;
	//�J�����̔��]���W
	float afterRad = cameraRad + 180.0f;
	cameraPosMemory.z = cameraDistance * cos(PI / 180 * afterRad);
	cameraPosMemory.x = cameraDistance * sin(PI / 180 * afterRad);

//--------------- �C�[�W���O�֌W ----------------------------------//
	nowCount = 
	endCount = nowCount - startCount;
	float endTimer = static_cast<float> (endCount) / 1'000'000.0f;
	timeRate = min(endTimer / maxTime, 1.0f);
	
	if (state == PlayerState::dash)
	{
		cameraRad += EZ(cameraRad, afterRad, timeRate);
	}
//----------------------------------------------------------------//
}

void Camera::Draw()
{
	debugText_->SetPos(800, 50);
	debugText_->Printf("cameraPos:[%f][%f]", cameraPos.x, cameraPos.z);
	debugText_->SetPos(800, 70);
	debugText_->Printf("cameraPosMemory:[%f][%f]", cameraPosMemory.x, cameraPosMemory.z);
	debugText_->SetPos(800, 90);
	debugText_->Printf("cameraFlag:[%d]", cameraFlag);
}

float Camera::EZ(float start, float end, float timer)
{
	return start * (1.0f - timer) + end * timer;
}
