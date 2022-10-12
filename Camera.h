#pragma once
#include "Input.h"
#include "ViewProjection.h"
#include "DebugText.h"

class Camera
{
public:
	void Initialize(float playerRadius);

	void Update(float playerRadius);

	Vector3 GetCameraPos()const { return cameraPos; }
private:
	float cameraDistance = 50.0f;

	Vector3 cameraPos;
	Vector3 cameraPosMemory;
};