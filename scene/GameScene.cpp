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
	delete titleSclene_;
	delete resultScene_;
}

void GameScene::Initialize() {

	dxCommon_ = DirectXCommon::GetInstance();
	input_ = Input::GetInstance();
	audio_ = Audio::GetInstance();
	debugText_ = DebugText::GetInstance();

	texture_ = TextureManager::Load("daruma.jpg");
	whiteTexture_ = TextureManager::Load("white1x1.png");

	titleSclene_ = new TitleScene();
	titleSclene_->Initialize();

	resultScene_ = new ResultScene();
	resultScene_->Initialize();

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

	//乱数
	random_device seed_gem;
	mt19937_64 engine(seed_gem());
	uniform_real_distribution<float> rotDist(0.0f, 360.0f);

	// 粒子の初期化処理
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

	switch (scene_)
	{
	case Scene::TitleScene:
		titleSclene_->Update(scene_);
		break;

	case Scene::GameScene:
		//if (input_->PushKey(DIK_R))
		//{
			//ReSet();
		//}

		//if (input_->PushKey(DIK_Q))
		//{
			//scene_ = Scene::ResultScene;
		//}

		player_->Update(moveCircleRadius);
		camera_->Update(player_->GetRadian(), player_->GetPlayerState());
		for (int i = 0; i < 10; i++)
		{
			enemy_[i]->UpDate(i);

		}
		for (int i = 0; i < 4; i++)
		{
			enemyBullet_[i]->Update(player_->GetPlayerState());
		}

		viewProjection_.eye = camera_->GetCameraPos();

		viewProjection_.UpdateMatrix();

		if (player_->GetPlayerState() == PlayerState::dash)
		{
			CheckAllCollisions();
		}
		//デバッグフォント
		debugText_->SetPos(50, 50);
		//debugText_->Printf("dethCount : %d", dethCount);

		if (dethCount > 9)
		{
			scene_ = Scene::ResultScene;
		}

		break;

	case Scene::ResultScene:
		resultScene_->Update(scene_);
		ReSet();
		break;

	}


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

	switch (scene_)
	{
	case Scene::TitleScene:
		break;

	case Scene::GameScene:
		player_->Draw(viewProjection_);
		player_->DrawDebugText();
		camera_->Draw();
		for (int i = 0; i < 4; i++)
		{
			enemyBullet_[i]->Draw(viewProjection_);
			//enemyBullet_[i]->DrawDebugText();
		}

		for (int i = 0; i < 10; i++)
		{
			if (enemy_[i]->IsCollision() != true)
			{
				enemy_[i]->Draw(viewProjection_);
			}
			enemy_[i]->DrawDebugText(i);
		}

		for (int i = 0; i < 64; i++) {
			model_->Draw(randObj[i], viewProjection_, whiteTexture_);
		}
		break;

	case Scene::ResultScene:
		//ReSet();
		break;
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

	switch (scene_)
	{
	case Scene::TitleScene:
		titleSclene_->Draw();
		break;

	case Scene::GameScene:
		break;


	case Scene::ResultScene:
		resultScene_->Draw();
		break;
	}

	// デバッグテキストの描画
	debugText_->DrawAll(commandList);
	//
	// スプライト描画後処理
	Sprite::PostDraw();

#pragma endregion
}

void GameScene::CheckAllCollisions()
{
	for (int i = 9; -1 < i; i--)
	{
		if (player_->IsCollision() == false)
		{
			// x軸の両端の当たり判定
			if (player_->upCollision.x > enemy_[i]->downCollision.x && player_->downCollision.x < enemy_[i]->upCollision.x)
			{
				// z軸の両端の当たり判定
				if (player_->upCollision.z > enemy_[i]->downCollision.z && player_->downCollision.z < enemy_[i]->upCollision.z)
				{
					// y軸の両端の当たり判定
					if (player_->upCollision.y > enemy_[i]->downCollision.y && player_->downCollision.y < enemy_[i]->upCollision.y)
					{
						enemy_[i]->OnCollision();
						player_->OnCollision_(enemy_[i]->GetState_(), enemy_[i]->GetCount());
						dethCount++;
					}
				}
			}

			if (enemy_[i]->IsCollision() == true && player_->IsCollision() == true)
			{
				for (int j = 9; i < j; j--)
				{
					enemy_[j]->pos.y = enemy_[j - 1]->pos.y;
					enemy_[j]->SetWorldTransform(enemy_[j]->pos);
					/*debugText_->Printf("Hit : %d",i);*/
				}
				enemy_[i]->pos.y = -500.0f;
				enemy_[i]->SetWorldTransform(enemy_[i]->pos);
			}

			/*for (int j = i; j < 8 - dethCount; j++)
			{
				enemy_[j] = enemy_[j + 1];
				if (j == 9 - dethCount)
				{
					enemy_[j]->pos.y = -500.0f;
				}
			}*/
		}
	}
	// 弾とプレイヤーの判定
	for (int i = 0; i < 4; i++)
	{
		if (player_->upCollision.x > enemyBullet_[i]->downCollision.x && player_->downCollision.x < enemyBullet_[i]->upCollision.x)
		{
			if (player_->upCollision.z > enemyBullet_[i]->downCollision.z && player_->downCollision.z < enemyBullet_[i]->upCollision.z)
			{
				if (player_->upCollision.y > enemyBullet_[i]->downCollision.y && player_->downCollision.y < enemyBullet_[i]->upCollision.y)
				{
					enemyBullet_[i]->OnCollision();
					player_->OnCollision_B();
					debugText_->SetPos(800, 100 + 20 * i);
					//debugText_->Printf("Hit : %d", i);
				}
			}
		}
	}
}

void GameScene::ReSet()
{
	player_->Initialize(moveCircleRadius, moveCircle);

	// 敵の初期化
	for (int i = 0; i < 10; i++)
	{
		enemy_[i]->Initialize(model_, texture_, i);
	}
	for (int i = 0; i < 4; i++)
	{
		enemyBullet_[i]->Initialize(model_, texture_);
	}

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

	viewProjection_.Initialize();

	camera_->Initialize(player_->GetRadian());

	dethCount = 0;
}


