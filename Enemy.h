#pragma once

#include "DebugText.h"
#include "Input.h"
#include "Model.h"
#include "WorldTransform.h"
#include "ViewProjection.h"
#include <cassert>

enum class State { //敵の状態

	needle, // 針	0
	normal, // 普通	1
	cole	// コア	2
};

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
	/// <param name="i">敵キャラの番号</param>
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

	Matrix4 GetMatrix() { return enemy_.matWorld_; };

	WorldTransform GetWorldTransform() { return enemy_; };

	void SetWorldTransform(Vector3 pos);

	// 座標の格納用
	Vector3 pos = GetWorldTransform().translation_;

	// 半径の格納用
	Vector3 radiusu = GetWorldTransform().scale_;

	// pos + radiusu / pos - collision を格納
	Vector3 upCollision;
	Vector3 downCollision;

	bool IsCollision() { return isCollision_; }

private:
	WorldTransform enemy_;
	// モデル
	Model* model_ = nullptr;
	// テクスチャハンドル
	uint32_t textureHandle_ = 0u;

	DebugText* debugText_ = nullptr;
	// あたり判定
	bool isCollision_ = false;

	State state;
};

