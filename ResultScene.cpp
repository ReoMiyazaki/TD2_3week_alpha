#include "ResultScene.h"
#include "TextureManager.h"

void ResultScene::Initialize()
{
	input_ = Input::GetInstance();
	debugText_ = DebugText::GetInstance();

	// �摜�̓ǂݍ���
	gameClear = TextureManager::Load("texture/gameClear.png");
	buckTitle = TextureManager::Load("texture/buckTitle.png");

	// �ǂݍ��މ摜�̍��W���̏�����
	gameClear_.reset(Sprite::Create(gameClear, Vector2(640, 275), Vector4(1, 1, 1, 1),
		Vector2(0.5f, 0.5f)));
	buckTitle_.reset(Sprite::Create(buckTitle, Vector2(640, 475), Vector4(1, 1, 1, 1),
		Vector2(0.5f, 0.5f)));
}

void ResultScene::Update(Scene& scene)
{
	Select(scene);
}

void ResultScene::Draw()
{
	gameClear_->Draw();
	buckTitle_->Draw();
}

void ResultScene::Select(Scene& scene)
{
	if (scene == Scene::ResultScene) {

		if (input_->TriggerKey(DIK_SPACE))
		{
			scene = Scene::TitleScene;
		}
	}
}
