#pragma once
#include "DebugText.h"
#include "Global.h"
#include"Input.h"
#include <memory>
#include "Sprite.h"
#include "Vector2.h"


class ResultScene
{
public:
	/// <summary>
	/// 初期化処理
	/// </summary>
	void Initialize();

	/// <summary>
	/// 更新処理
	/// </summary>
	/// <param name="scene"></param>
	void Update(Scene& scene);

	/// <summary>
	/// 描画処理
	/// </summary>
	void Draw();

	void Select(Scene& scene);

private:

	Input* input_ = nullptr;
	DebugText* debugText_ = nullptr;

	// 画像用変数
	uint32_t gameClear = 0;
	uint32_t buckTitle = 0;

	// 画像のスプライト
	// 画像のスプライト
	std::unique_ptr<Sprite> gameClear_ = nullptr;
	std::unique_ptr<Sprite> buckTitle_ = nullptr;
};

