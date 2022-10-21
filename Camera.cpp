#include "Camera.h"
#include<time.h>

using namespace MathUtility;

int GetNowTime();

void Camera::Initialize(float playerRadius)
{
	input_ = Input::GetInstance();
	debugText_ = DebugText::GetInstance();
	//カメラ座標を自機の角度を使って計算
	float cameraRad = playerRadius + 45.0f;
	cameraPos.y = 20.0f;
	cameraPos.x = sin(cameraRad * PI / 180) * cameraDistance;
	cameraPos.z = cos(cameraRad * PI / 180) * cameraDistance;
	cameraPosMemory.y = 20.0f;
	cameraPosMemory.x = 0;
	cameraPosMemory.z = 0;

	//------------ イージング関係 -------------------//
	startCount = 0;
	nowCount = 0;
	endCount = 0;

	maxTime = 2.0f;
	startCount = 0;
	//------------ イージング関係 -------------------//
	cameraFlag = false;
}

void Camera::Update(float playerRadius, PlayerState state)
{
	//カメラの更新
	float cameraRad = playerRadius + 30.0f;
	cameraPos.x = sin(cameraRad * PI / 180) * cameraDistance;
	cameraPos.z = cos(cameraRad * PI / 180) * cameraDistance;
	//カメラの反転座標
	float afterRad = cameraRad + 180.0f;
	cameraPosMemory.z = cameraDistance * cos(PI / 180 * afterRad);
	cameraPosMemory.x = cameraDistance * sin(PI / 180 * afterRad);

	//--------------- イージング関係 ----------------------------------//
		//int ft = clock();



	if (state == PlayerState::dash)
	{
		//イージングのカウント開始
		startCount = clock();
		//開始角度の取得
		//beforeplayerRad = playerRadius
		beforeRad = playerRadius + 30.0f;
	}

	//現在時刻を常に取得
	nowCount = clock();
	//取得している時刻でイージングの終了時間も設定
	endCount = nowCount - startCount;
	//タイマーが今どれ暗い進んでいるかの情報をfloatに変換
	endTimer = static_cast<float> (endCount) / 1'000.0f;
	//(タイマーの進み具合/タイマーの最大時間)で0~1の間のどこなのか計算
	timeRate = min(endTimer / maxTime, 1.0f);

	//タイマーが1か0(イージングが終了している)なら
	if (timeRate >= 1) {
		//カメラの角度はデフォルト
		cameraRad = playerRadius + 30.0f;
	}//それ以外(イージングの途中)なら
	else {
		//角度はイージングで増減している角度(0~180) + イージング開始時の角度に
		float rad = playerRadius + 30.0f;
		if (rad < beforeRad) {
			rad += 360.0f;
		}

	//	debugText_->SetPos(800, 100);
	//	debugText_->Printf("rad:[%3.2f]", rad);

		cameraRad = EZ(beforeRad + 180.0f, rad, timeRate);
	}

	if (state == PlayerState::dash || state == PlayerState::Jump) {
		//カメラの角度はデフォルト
		cameraRad = playerRadius + 30.0f;
	}

	//cameraRad = fmodf(cameraRad, 360.0f);

	//角度で座標を計算
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
