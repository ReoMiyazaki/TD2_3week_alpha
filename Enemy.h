#pragma once

#include "DebugText.h"
#include "Input.h"
#include "Model.h"
#include "WorldTransform.h"
#include "ViewProjection.h"
#include <cassert>

class Enemy
{
public:
	/// <summary>
	/// 初期化処理
	/// </summary>
	/// <param name="model"></param>
	/// <param name="textureHandle"></param>
	/// <param name="i">敵キャラの番号</param>
	void Initialize(Model* model, uint32_t textureHandle, int i);

	/// <summary>
	/// 更新処理
	/// </summary>
	void UpDate(int i);

	/// <summary>
	/// 描画処理
	/// </summary>
	/// <param name="viewProjection"></param>
	void Draw(ViewProjection viewProjection);

	/// <summary>
	/// デバック用テキスト専用の関数
	/// </summary>
	void DrawDebugText(int i);

	/// <summary>
	/// 当たり判定
	/// </summary>
	/// <returns></returns>
	void OnCollision();

	// ワールド座標を取得
	Vector3 GetWorldPosition(int i);

	// ワールド変換データ
//	WorldTransform worldTransforms_[10];

	Matrix4 GetMatrix() { return worldTransform_.matWorld_; };

	WorldTransform GetWorldTransform() { return worldTransform_; };

	Vector3 pos = GetWorldTransform().translation_;
	Vector3 scale = GetWorldTransform().scale_;

	bool IsCollision() const { return isCollision_; }

private:
	WorldTransform worldTransform_;
	// モデル
	Model* model_ = nullptr;
	// テクスチャハンドル
	uint32_t textureHandle_ = 0u;

	DebugText* debugText_ = nullptr;
	// あたり判定
	bool isCollision_ = false;
};

