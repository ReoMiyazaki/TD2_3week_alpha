#include "TitleScene.h"
#include "TextureManager.h"

void TitleScene::Initialize()
{
	input_ = Input::GetInstance();
	debugText_ = DebugText::GetInstance();

	// ‰æ‘œ‚Ì“Ç‚Ýž‚Ý
	titleLogo = TextureManager::Load("texture/titleLogo.png");
	goToGame = TextureManager::Load("texture/goGameScene.png");
	endGame = TextureManager::Load("texture/endGame.png");
	pushToState = TextureManager::Load("texture/pushToState.png");

	// “Ç‚Ýž‚Þ‰æ‘œ‚ÌÀ•W“™‚Ì‰Šú‰»
	titleLogo_.reset(Sprite::Create(titleLogo, Vector2(640, 200), Vector4(1, 1, 1, 1),
		Vector2(0.5f, 0.5f)));
	goToGame_.reset(Sprite::Create(goToGame, Vector2(640, 375), Vector4(1, 1, 1, 1),
		Vector2(0.5f, 0.5f)));
	pushToState_.reset(Sprite::Create(pushToState, Vector2(640, 475), Vector4(1, 1, 1, 1),
		Vector2(0.5f, 0.5f)));
}

void TitleScene::Update(Scene& scene)
{
	Select(scene);
}

void TitleScene::Draw()
{
	titleLogo_->Draw();
	goToGame_->Draw();
	pushToState_->Draw();
}

void TitleScene::Select(Scene& scene)
{
	if (input_->TriggerKey(DIK_SPACE))
	{
		scene = Scene::GameScene;
	}
}
