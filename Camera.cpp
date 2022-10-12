#include "Camera.h"

using namespace MathUtility;

void Camera::Initialize(float playerRadius)
{
	//�J�������W�����@�̊p�x���g���Čv�Z
	float cameraRad = playerRadius + 45.0f;
	cameraPos.y = 20.0f;
	cameraPos.x = sin(cameraRad * PI / 180) * cameraDistance;
	cameraPos.z = cos(cameraRad * PI / 180) * cameraDistance;
	cameraPosMemory.y = 20.0f;
	cameraPosMemory.x = 0;
	cameraPosMemory.z = 0;
}

void Camera::Update(float playerRadius)
{
	//�J�����̍X�V
	float cameraRad = playerRadius + 30.0f;
	cameraPos.x = sin(cameraRad * PI / 180) * cameraDistance;
	cameraPos.z = cos(cameraRad * PI / 180) * cameraDistance;
	//�J�����̔��]���W
	float afterRad = cameraRad + 180.0f;
	cameraPosMemory.z = cameraDistance * cos(PI / 180 * afterRad);
	cameraPosMemory.x = cameraDistance * sin(PI / 180 * afterRad);

}
