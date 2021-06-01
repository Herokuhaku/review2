#include "BaseScene.h"
#include <DxLib.h>

BaseScene::BaseScene()
{
	click_.fill(0);
	SetDrawScreen(DX_SCREEN_BACK);
	GetDrawScreenSize(&screenSize_.x,&screenSize_.y);
	screen_ = MakeScreen(screenSize_.x,screenSize_.y);
}

BaseScene::~BaseScene()
{
}

void BaseScene::Draw(double delta)
{
	DrawGraph(0,0,screen_,true);
}
