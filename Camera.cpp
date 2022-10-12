#include "Camera.h"

using namespace MathUtility;

void Camera::Initialize(float playerRadius)
{
	//カメラ座標を自機の角度を使って計算
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
	//カメラの更新
	float cameraRad = playerRadius + 30.0f;
	cameraPos.x = sin(cameraRad * PI / 180) * cameraDistance;
	cameraPos.z = cos(cameraRad * PI / 180) * cameraDistance;
	//カメラの反転座標
	float afterRad = cameraRad + 180.0f;
	cameraPosMemory.z = cameraDistance * cos(PI / 180 * afterRad);
	cameraPosMemory.x = cameraDistance * sin(PI / 180 * afterRad);

}
