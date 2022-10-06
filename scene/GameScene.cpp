#include "GameScene.h"
#include "TextureManager.h"
#include <cassert>
using namespace MathUtility;

GameScene::GameScene() {}

GameScene::~GameScene() {}

void GameScene::Initialize() {

	dxCommon_ = DirectXCommon::GetInstance();
	input_ = Input::GetInstance();
	audio_ = Audio::GetInstance();
	debugText_ = DebugText::GetInstance();

	model_ = Model::Create();
	player_.Initialize();

	viewProjection_.eye = { 0.0f, 20.0f,-50.0f };
	viewProjection_.Initialize();

	for (int i = 0; i < 64; i++) {
		playerMoveLine[i].Initialize();
		float rad = 360.0f / 64.0f * i;
		moveCircle.x = sin(PI / 180 * rad) * moveCircleRadius;
		moveCircle.y = cos(PI / 180 * rad) * moveCircleRadius;
		Vector3 pos;
		pos.x = moveCircle.x;
		pos.z = moveCircle.y;
		pos.y = 0;
		playerMoveLine[i].translation_ = pos;
		playerMoveLine[i].scale_ = { 0.1f,0.1f,0.1f };
		playerMoveLine[i].MatUpdate();
	
	}


	//viewProjection_.UpdateMatrix();

}

void GameScene::Update() {

//プレイヤーが原点を中心に回転
	playerRad += 2.0f;
	fmodf(playerRad, 360.0f);
	Vector3 movePos;
	movePos.x = sin(PI / 180 * playerRad) * moveCircleRadius;
	movePos.z = cos(PI / 180 * playerRad) * moveCircleRadius;
	player_.translation_ = movePos;
	player_.MatUpdate();

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

	model_->Draw(player_, viewProjection_);

	for (int i = 0; i < 64; i++) {
		model_->Draw(playerMoveLine[i], viewProjection_);
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
