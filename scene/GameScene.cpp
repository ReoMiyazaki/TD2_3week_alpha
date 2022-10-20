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

	texture_ = TextureManager::Load("mario.jpg");
	whiteTexture_ = TextureManager::Load("white1x1.png");

	model_ = Model::Create();
	player_ = new Player();
	player_->Initialize(moveCircleRadius, moveCircle);
	camera_ = new Camera();

	// 敵の初期化
	for (int i = 0; i < 10; i++)
	{
		enemy_[i] = new Enemy();
		enemy_[i]->Initialize(model_, texture_, i);
	}

	//	enemy_ = new Enemy();
	//	enemy_->Initialize(model_, texture_);

	//乱数
	random_device seed_gem;
	mt19937_64 engine(seed_gem());
	uniform_real_distribution<float> rotDist(0.0f, 360.0f);

	//	for (int i = 0; i < 10; i++) {
	//		daruma[i].Initialize();
	//		daruma[i].translation_.y += 2.0 * i;
	//		daruma[i].rotation_.y = rotDist(engine);
	//		daruma[i].MatUpdate();
	//
	//	}

	for (int i = 0; i < 64; i++) {
		randObj[i].Initialize();
		Vector3 pos;
		pos.x = Random(-50.0f, 50.0f);
		pos.y = Random(-50.0f, 50.0f);
		pos.z = Random(-50.0f, 50.0f);
		randObj[i].translation_ = pos;
		pos.x = Random(0.0f, 360.0f);
		pos.y = Random(0.0f, 360.0f);
		pos.z = Random(0.0f, 360.0f);
		randObj[i].rotation_ = pos;
		randObj[i].scale_ = { 0.1f,0.1f,0.1f };
		randObj[i].MatUpdate();
	}

	viewProjection_.eye = camera_->GetCameraPos();
	viewProjection_.Initialize();

	camera_->Initialize(player_->GetRadian());

	texture_ = TextureManager::Load("mario.jpg");
	whiteTexture_ = TextureManager::Load("white1x1.png");

}

void GameScene::Update() {

	player_->Update(moveCircleRadius);
	camera_->Update(player_->GetRadian(), player_->GetPlayerState());
	for (int i = 0; i < 10; i++)
	{
		enemy_[i]->UpDate(i);
	}
	//	enemy_->UpDate();
	//	enemy_->DebugTex();

	viewProjection_.eye = camera_->GetCameraPos();

	viewProjection_.UpdateMatrix();

	CheckAllCollisions();


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
	camera_->Draw();

	for (int i = 0; i < 10; i++)
	{
		enemy_[i]->Draw(viewProjection_);
		enemy_[i]->DebugTex(i);
	}
	//	enemy_[0]->DebugTex();
	//	enemy_->Draw(viewProjection_);

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

void GameScene::CheckAllCollisions()
{
#pragma region 自キャラとダルマの当たり判定(中心)
	{
		// 判定対象aとbの座標
		Vector3 posA, posB[10];

		float x[10] = { 0 }, y[10] = { 0 }, z[10] = { 0 };

		// 自キャラ座標
		posA = player_->GetWorldPosition();
		// 敵キャラ座標
	//	posB = enemy_->GetWorldPosition();

		for (int i = 0; i < 10; i++) {
			posB[i] = enemy_[i]->GetWorldPosition(i);
			//	posB[i] = enemy_->GetWorldPosition(i);

			x[i] = posA.x - posB[i].x;
			y[i] = posA.y - posB[i].y;
			z[i] = posA.z - posB[i].z;

			float distance = sqrt(x[i] * x[i] + y[i] * y[i] + z[i] * z[i]);

			Matrix4 matA = player_->GetMatrix();
			Matrix4 matB = enemy_[i]->GetMatrix();
			//	Matrix4 matB = enemy_->GetMatrix();

				// 自キャラと敵キャラの交差判定
			if (distance < matA.m[0][0] + matB.m[0][0])
			{
				enemy_[i]->OnCollision();
				//	enemy_->OnCollision();
			}
		}
	}
#pragma endregion
#pragma region 自キャラとダルマの当たり判定(下辺)
	{
		// 判定対象aとbの座標
		Vector3 posA, posB[10];

		float x[10] = {}, y[10] = {}, z[10] = {};

		// 自キャラ座標
		posA = player_->GetWorldPosition();
		// 敵キャラ座標
	//	posB = enemy_->GetWorldPosition();

		for (int i = 0; i < 10; i++) {
			posB[i] = enemy_[i]->GetWorldPosition(i);
			//	posB[i] = enemy_->GetWorldPosition(i);

				// 半径分値をずらす
			x[i] = posA.x - posB[i].x;
			y[i] = posA.y - posB[i].y - 1;
			//	y[i] = posA.y - posB[i].y - enemy_->worldTransforms_->scale_.y;
			z[i] = posA.z - posB[i].z;

			float distance = sqrt(x[i] * x[i] + y[i] * y[i] + z[i] * z[i]);

			Matrix4 matA = player_->GetMatrix();
			Matrix4 matB = enemy_[i]->GetMatrix();
			//	Matrix4 matB = enemy_->GetMatrix();

				// 自キャラと敵キャラの交差判定
			if (distance < matA.m[0][0] + matB.m[0][0])
			{
				enemy_[i]->OnCollision();
				//	enemy_->OnCollision();
			}
		}
	}
#pragma endregion
#pragma region 自キャラとダルマの当たり判定(上辺)
	{
		// 判定対象aとbの座標
		Vector3 posA, posB[10];

		float x[10], y[10], z[10];

		// 自キャラ座標
		posA = player_->GetWorldPosition();
		// 敵キャラ座標
	//	posB = enemy_->GetWorldPosition();

		for (int i = 0; i < 10; i++) {
			posB[i] = enemy_[i]->GetWorldPosition(i);
			//	posB[i] = enemy_->GetWorldPosition(i);

				// 半径分値をずらす
			x[i] = posA.x - posB[i].x;
			y[i] = posA.y - posB[i].y + 1;
			//	y[i] = posA.y - posB[i].y + enemy_->worldTransforms_->scale_.y;
			z[i] = posA.z - posB[i].z;

			float distance = sqrt(x[i] * x[i] + y[i] * y[i] + z[i] * z[i]);

			Matrix4 matA = player_->GetMatrix();
			Matrix4 matB = enemy_[i]->GetMatrix();
			//	Matrix4 matB = enemy_->GetMatrix();

				// 自キャラと敵キャラの交差判定
			if (distance < matA.m[0][0] + matB.m[0][0])
			{
				enemy_[i]->OnCollision();
				//	enemy_->OnCollision();
			}
		}
	}
#pragma endregion
}


