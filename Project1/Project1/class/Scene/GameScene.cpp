#include "GameScene.h"
#include <DxLib.h>
#include "TitleScene.h"
#include "../common/ImageMng.h"

GameScene::GameScene()
{
	Init();
	DrawOwnScreen(0.0f);
}

GameScene::~GameScene()
{
}

bool GameScene::Init(void)
{
	tmxobj_.LoadTmx("Tiled/stage001.tmx");
	lpImageMng.GetID("image/no_002.png", "Game");
	return true;
}

UniqueScene GameScene::Update(double delta, UniqueScene own)
{
	click_[1] = click_[0];
	click_[0] = GetMouseInput();
	if (!click_[0] && (click_[1] & MOUSE_INPUT_LEFT)){
		return std::make_unique<TitleScene>();
	}
	DrawOwnScreen(delta);
	return std::move(own);
}
//
//void GameScene::Draw(double delta)
//{
//}

void GameScene::DrawOwnScreen(double delta)
{
	SetDrawScreen(screen_);
	ClsDrawScreen();
	DrawGraph(0, 0, lpImageMng.GetID("Game")[0], true);
	DrawGraph(0, 0,lpImageMng.GetID("map")[0], true);
}
