#include "GameScene.h"
#include "TextureManager.h"
#include "FPS.h"
#include <cassert>
#include<random>
using namespace std;
using namespace MathUtility;

GameScene::GameScene() {}

GameScene::~GameScene()
{
	delete model_;
	delete player_;
	delete camera_;
	//	delete enemy_;
}

void GameScene::Initialize() {

	dxCommon_ = DirectXCommon::GetInstance();
	input_ = Input::GetInstance();
	audio_ = Audio::GetInstance();
	debugText_ = DebugText::GetInstance();

	texture_ = TextureManager::Load("daruma.jpg");
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
	for (int i = 0; i < 4; i++)
	{
		enemyBullet_[i] = new EnemyBullet();
		enemyBullet_[i]->Initialize(model_, texture_);
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

}

void GameScene::Update() {

	player_->Update(moveCircleRadius);
	camera_->Update(player_->GetRadian(), player_->GetPlayerState());
	for (int i = 0; i < 10; i++)
	{
		enemy_[i]->UpDate();

	}
	for (int i = 0; i < 4; i++)
	{
		enemyBullet_[i]->Update(player_->GetPlayerState());
	}

	//	enemy_->UpDate();
	//	enemy_->DebugTex();

	viewProjection_.eye = camera_->GetCameraPos();

	viewProjection_.UpdateMatrix();

	if (player_->GetPlayerState() == PlayerState::dash)
	{
		CheckAllCollisions();
	}

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
//	player_->DrawDebugText();
	camera_->Draw();
	for (int i = 0; i < 4; i++)
	{
		enemyBullet_[i]->Draw(viewProjection_);
		enemyBullet_[i]->DrawDebugText();
	}

	for (int i = 0; i < 10; i++)
	{
		enemy_[i]->Draw(viewProjection_);
		//		enemy_[i]->DrawDebugText(i);
	}

	for (int i = 0; i < 64; i++) {
		model_->Draw(randObj[i], viewProjection_, whiteTexture_);
	}

//	debugText_->SetPos(50, 200);
//	debugText_->Printf("player(posX,posY,posZ) = (%3.1f,%3.1f,%3.1f)", player_->pos.x, player_->pos.y, player_->pos.z);
//	debugText_->SetPos(50, 220);
//	debugText_->Printf("player(collisionX,collisionY,collisionZ) = (%3.0f,%3.0f,%3.0f)",
//		player_->upCollision.x, player_->upCollision.y, player_->upCollision.z);
//	debugText_->SetPos(50, 240);
//	debugText_->Printf("player(collisionX,collisionY,collisionZ) = (%3.0f,%3.0f,%3.0f)",
//		player_->downCollision.x, player_->downCollision.y, player_->downCollision.z);
//
//	debugText_->SetPos(50, 260);
//	debugText_->Printf("player(collisionX,collisionY,collisionZ) = (%3.0f,%3.0f,%3.0f)",
//		enemy_[0]->upCollision.x, enemy_[0]->upCollision.y, enemy_[0]->upCollision.z);
//	debugText_->SetPos(50, 280);
//	debugText_->Printf("player(collisionX,collisionY,collisionZ) = (%3.0f0,%3.0f,%3.0f)",
//		enemy_[0]->downCollision.x, enemy_[0]->downCollision.y, enemy_[0]->downCollision.z);


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
	//float upperSole[10] = { 0 };
	//float lowerSole[10] = { 0 };
#pragma region 自キャラとダルマの当たり判定(中心)
	//{
	//	// 判定対象aとbの座標
	//	Vector3 posA, posB[10];

	//	float x[10] = { 0 }, y[10] = { 0 }, z[10] = { 0 };

	//	// 自キャラ座標
	//	posA = player_->GetWorldPosition();
	//	// 敵キャラ座標
	////	posB = enemy_->GetWorldPosition();

	//	for (int i = 0; i < 10; i++) {
	//		posB[i] = enemy_[i]->GetWorldPosition(i);
	//		//	posB[i] = enemy_->GetWorldPosition(i);

	//		x[i] = posA.x - posB[i].x;
	//		y[i] = posA.y - posB[i].y;
	//		z[i] = posA.z - posB[i].z;

	//		float distance = sqrt(x[i] * x[i] + y[i] * y[i] + z[i] * z[i]);

	//		Matrix4 matA = player_->GetMatrix();
	//		Matrix4 matB = enemy_[i]->GetMatrix();
	//		//	Matrix4 matB = enemy_->GetMatrix();

	//			// 自キャラと敵キャラの交差判定
	//		if (distance < matA.m[0][0] + matB.m[0][0])
	//		{
	//			enemy_[i]->OnCollision();
	//			//	enemy_->OnCollision();
	//		}
	//	}
	//}
#pragma endregion
#pragma region 自キャラとダルマの当たり判定(下辺)
	//{
	//	// 判定対象aとbの座標
	//	Vector3 posA, posB[10];
	//	// 座標差の保管用の変数
	//	float x[10] = {}, y[10] = {}, z[10] = {};
	//	// 自キャラ座標
	//	posA = player_->GetWorldPosition();
	//
	//	for (int i = 0; i < 10; i++)
	//	{
	//		// 敵キャラの座標を取得
	//		posB[i] = enemy_[i]->GetWorldPosition(i);
	//
	//		// それぞれのポジションの差を計算
	//		x[i] = posB[i].x - posA.x;
	//		y[i] = (posB[i].y + 1) - posA.y; // 半径の分だけ加算( enemy->scale_.y の値と同値)
	//		z[i] = posB[i].z - posA.z;
	//		// ベクトルの計算
	//		upperSole[i] = sqrt(x[i] * x[i] + y[i] * y[i] + z[i] * z[i]);
	//	}
	//}
#pragma endregion
#pragma region 自キャラとダルマの当たり判定(上辺)
	//{
	//	// 判定対象aとbの座標
	//	Vector3 posA, posB[10];
	//	// 座標差の保管用の変数
	//	float x[10] = {}, y[10] = {}, z[10] = {};
	//	// 自キャラ座標
	//	posA = player_->GetWorldPosition();
	//
	//	for (int i = 0; i < 10; i++) {
	//		// 敵キャラの座標を取得
	//		posB[i] = enemy_[i]->GetWorldPosition(i);
	//
	//		// それぞれのポジションの差を計算
	//		x[i] = posB[i].x - posA.x;
	//		y[i] = (posB[i].y - 1) - posA.y; // 半径の分だけ加算( enemy->scale_.y の値と同値)
	//		z[i] = posB[i].z - posA.z;
	//
	//		// ベクトルの計算
	//		lowerSole[i] = sqrt(x[i] * x[i] + y[i] * y[i] + z[i] * z[i]);
	//	}
	//}
#pragma endregion


	for (int i = 0; i < 10; i++)
	{
		if (player_->upCollision.x > enemy_[i]->downCollision.x && player_->downCollision.x < enemy_[i]->upCollision.x)
		{
			if (player_->upCollision.z > enemy_[i]->downCollision.z && player_->downCollision.z < enemy_[i]->upCollision.z)
			{
				if (player_->upCollision.y > enemy_[i]->downCollision.y && player_->downCollision.y < enemy_[i]->upCollision.y)
				{
					enemy_[i]->OnCollision();
					debugText_->SetPos(800, 100 + 20 * i);
					debugText_->Printf("Hit : %d",i);
				}
			}
		}
	}

	for (int i = 0; i < 4; i++)
	{
		if (player_->upCollision.x > enemyBullet_[i]->downCollision.x && player_->downCollision.x < enemyBullet_[i]->upCollision.x)
		{
			if (player_->upCollision.z > enemyBullet_[i]->downCollision.z && player_->downCollision.z < enemyBullet_[i]->upCollision.z)
			{
				if (player_->upCollision.y > enemyBullet_[i]->downCollision.y && player_->downCollision.y < enemyBullet_[i]->upCollision.y)
				{
					enemyBullet_[i]->OnCollision();
					debugText_->SetPos(800, 100 + 20 * i);
					debugText_->Printf("Hit : %d", i);
				}
			}
		}
	}
}


