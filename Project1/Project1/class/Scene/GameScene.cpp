#include "GameScene.h"
#include <DxLib.h>
#include "TitleScene.h"
GameScene::GameScene()
{
	Init();
}

GameScene::~GameScene()
{
}

bool GameScene::Init(void)
{
	image_ = LoadGraph(L"image/no_002.png");
	return true;
}

UniqueScene GameScene::Update(double delta, UniqueScene own)
{
	click_[1] = click_[0];
	click_[0] = GetMouseInput();
	if (!click_[0] && (click_[1] & MOUSE_INPUT_LEFT))
	{
		return std::make_unique<TitleScene>();
	}
	return std::move(own);
}

void GameScene::Draw(double delta)
{
	DrawGraph(0,0,image_,true);
}
