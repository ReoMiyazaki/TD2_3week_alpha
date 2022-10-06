#include "GameScene.h"
#include "TextureManager.h"
#include "FPS.h"
#include <cassert>
#include<random>
using namespace std;
using namespace MathUtility;

GameScene::GameScene() {}

GameScene::~GameScene() {}

void GameScene::Initialize() {

	dxCommon_ = DirectXCommon::GetInstance();
	input_ = Input::GetInstance();
	audio_ = Audio::GetInstance();
	debugText_ = DebugText::GetInstance();

	model_ = Model::Create();
	player_ = new Player();
	player_->Initialize(moveCircleRadius,moveCircle);

	//乱数
	random_device seed_gem;
	mt19937_64 engine(seed_gem());
	uniform_real_distribution<float> rotDist(0.0f, 360.0f);

	for (int i = 0; i < 10; i++) {
		daruma[i].Initialize();
		daruma[i].translation_.y += 2.0 * i;
		daruma[i].rotation_.y = rotDist(engine);
		daruma[i].MatUpdate();

	}

	for (int i = 0; i < 64; i++) {
		randObj[i].Initialize();
		Vector3 pos;
		pos.x = Random(-50.0f, 50.0f);
		pos.y = Random(-50.0f, 50.0f);
		pos.z = Random(-50.0f, 50.0f);
		randObj[i].translation_ = pos;
		pos.x = Random(0.0f,360.0f);
		pos.y = Random(0.0f,360.0f);
		pos.z = Random(0.0f,360.0f);
		randObj[i].rotation_ = pos;
		randObj[i].scale_ = { 0.1f,0.1f,0.1f };
		randObj[i].MatUpdate();
	}

	//カメラ座標を自機の角度を使って計算
	float cameraRad = player_->GetRadian() + 45.0f;
	cameraPos.y = 20.0f;
	cameraPos.x = sin(cameraRad * PI / 180) * cameraDistance;
	cameraPos.z = cos(cameraRad * PI / 180) * cameraDistance;
	viewProjection_.eye =cameraPos;
	viewProjection_.Initialize();

	texture_ = TextureManager::Load("mario.jpg");
	whiteTexture_ = TextureManager::Load("white1x1.png");

}

void GameScene::Update() {

	player_->Update(moveCircleRadius);

	//カメラの更新
	float cameraRad = player_->GetRadian() + 30.0f;
	cameraPos.x = sin(cameraRad * PI / 180) * cameraDistance;
	cameraPos.z = cos(cameraRad * PI / 180) * cameraDistance;
	viewProjection_.eye = cameraPos;

	viewProjection_.UpdateMatrix();


	//デバッグフォント
	debugText_->SetPos(50, 50);
	

}

void GameScene::Draw() {

	// コマンドリストの取得
	ID3D12GraphicsCommandList* commandList = dxCommon_->GetCommandList();

#pragma region 背景スプライト描画
	// 背景スプライト描画前処理
	Sprite::PreDraw(commandList);

	/// <summary>
	/// ここに背景スプライトの描画処理を追加できる
	/// </summary>

	// スプライト描画後処理
	Sprite::PostDraw();
	// 深度バッファクリア
	dxCommon_->ClearDepthBuffer();
#pragma endregion

#pragma region 3Dオブジェクト描画
	// 3Dオブジェクト描画前処理
	Model::PreDraw(commandList);

	/// <summary>
	/// ここに3Dオブジェクトの描画処理を追加できる
	/// </summary>

	player_->Draw(viewProjection_);

	for (int i = 0; i < 10; i++) {
		model_->Draw(daruma[i], viewProjection_,texture_);
	}

	for (int i = 0; i < 64; i++) {
		model_->Draw(randObj[i], viewProjection_, whiteTexture_);
	}

	// 3Dオブジェクト描画後処理
	Model::PostDraw();
#pragma endregion

#pragma region 前景スプライト描画
	// 前景スプライト描画前処理
	Sprite::PreDraw(commandList);

	/// <summary>
	/// ここに前景スプライトの描画処理を追加できる
	/// </summary>

	// デバッグテキストの描画
	debugText_->DrawAll(commandList);
	//
	// スプライト描画後処理
	Sprite::PostDraw();

#pragma endregion
}
