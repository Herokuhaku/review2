#include "GameScene.h"
#include <DxLib.h>
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

void GameScene::Update(double delta)
{
}

void GameScene::Draw(double delta)
{
	DrawGraph(0,0,image_,true);
}
