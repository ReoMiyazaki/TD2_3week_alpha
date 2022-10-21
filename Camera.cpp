#include "Camera.h"
#include<time.h>

using namespace MathUtility;

int GetNowTime();

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

	maxTime = 2.0f;
	startCount = 0;
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
		//int ft = clock();



	if (state == PlayerState::dash)
	{
		//�C�[�W���O�̃J�E���g�J�n
		startCount = clock();
		//�J�n�p�x�̎擾
		//beforeplayerRad = playerRadius
		beforeRad = playerRadius + 30.0f;
	}

	//���ݎ�������Ɏ擾
	nowCount = clock();
	//�擾���Ă��鎞���ŃC�[�W���O�̏I�����Ԃ��ݒ�
	endCount = nowCount - startCount;
	//�^�C�}�[�����ǂ�Â��i��ł��邩�̏���float�ɕϊ�
	endTimer = static_cast<float> (endCount) / 1'000.0f;
	//(�^�C�}�[�̐i�݋/�^�C�}�[�̍ő厞��)��0~1�̊Ԃ̂ǂ��Ȃ̂��v�Z
	timeRate = min(endTimer / maxTime, 1.0f);

	//�^�C�}�[��1��0(�C�[�W���O���I�����Ă���)�Ȃ�
	if (timeRate >= 1) {
		//�J�����̊p�x�̓f�t�H���g
		cameraRad = playerRadius + 30.0f;
	}//����ȊO(�C�[�W���O�̓r��)�Ȃ�
	else {
		//�p�x�̓C�[�W���O�ő������Ă���p�x(0~180) + �C�[�W���O�J�n���̊p�x��
		float rad = playerRadius + 30.0f;
		if (rad < beforeRad) {
			rad += 360.0f;
		}

	//	debugText_->SetPos(800, 100);
	//	debugText_->Printf("rad:[%3.2f]", rad);

		cameraRad = EZ(beforeRad + 180.0f, rad, timeRate);
	}

	if (state == PlayerState::dash || state == PlayerState::Jump) {
		//�J�����̊p�x�̓f�t�H���g
		cameraRad = playerRadius + 30.0f;
	}

	//cameraRad = fmodf(cameraRad, 360.0f);

	//�p�x�ō��W���v�Z
	cameraPos.x = sin(cameraRad * PI / 180) * cameraDistance;
	cameraPos.z = cos(cameraRad * PI / 180) * cameraDistance;

	//	debugText_->SetPos(800, 210);
	//	debugText_->Printf("playerRad:[%f]", playerRadius);
	//	debugText_->SetPos(800, 230);
	//	debugText_->Printf("cameraRad:[%f]", cameraRad);
	//	debugText_->SetPos(800, 250);
	//	debugText_->Printf("cameraRad2:[%f]", beforeRad);
	//	debugText_->SetPos(800, 270);
	//	debugText_->Printf("nowRad:[%f]", (timeRate * 180.0f) + beforeRad);

		/*debugText_->SetPos(800, 210);
		debugText_->Printf("nowTime:[%f]",ft );*/

		//----------------------------------------------------------------//
}

void Camera::Draw()
{
	
}

void Camera::DrawDebugText()
{
	debugText_->SetPos(800, 20);
	debugText_->Printf("cameraPos:[%3.2f][%3.2f]", cameraPos.x, cameraPos.z);
	debugText_->SetPos(800, 40);
	debugText_->Printf("cameraPosMemory:[%3.2f][%3.2f]", cameraPosMemory.x, cameraPosMemory.z);
	debugText_->SetPos(800, 60);
	debugText_->Printf("cameraFlag:[%d]", cameraFlag);*/
	//	debugText_->SetPos(800, 110);
	//	debugText_->Printf("startCount:[%d]", startCount);
	//	debugText_->SetPos(800, 130);
	//	debugText_->Printf("endCount:[%d]", endCount);
	//	debugText_->SetPos(800, 150);
	//	debugText_->Printf("nowCount:[%d]", nowCount);
	//	debugText_->SetPos(800, 170);
	//	debugText_->Printf("timeRate:[%f]", timeRate);
	//	debugText_->SetPos(800, 190);
	//	debugText_->Printf("endTimer:[%f]", endTimer);
}

float Camera::EZ(float start, float end, float timer)
{
	float x;

	//easeOut
	x = 1 - pow(1 - timer, 5);
	//easeIn
	//x = x * x * x * x * x;
	//easeOutBack
	//const float c1 = 1.70158;
	//const float  c3 = c1 + 1;

	//x = 1 + c3 * pow(x - 1, 3) + c1 * pow(x - 1, 2);
	////easeInBack
	//x = c3 * x * x * x - c1 * x * x;
	return start * (1.0f - x) + end * x;
}
/*start * (1.0f - timer) + end * timer;*/
int GetNowTime()
{
	return time(nullptr);
}
