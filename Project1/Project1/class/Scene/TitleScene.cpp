#include "TitleScene.h"

#include <DxLib.h>
#include "GameScene.h"
#include "../common/ImageMng.h"
#include "Transition/CrossOverScene.h"
#include "Transition/GaussianblurScene.h"
#include "Transition/BlackAndWhiteScene.h"

TitleScene::TitleScene()
{
	Init();
	DrawOwnScreen(0.0f);
}

TitleScene::~TitleScene()
{
}

bool TitleScene::Init(void)
{
	lpImageMng.GetID("image/no_001.png","Title");
	//image_ = LoadGraph("image/no_001.png");
	return true;
}

UniqueScene TitleScene::Update(double delta, UniqueScene own)
{
	click_[1] = click_[0];
	click_[0] = GetMouseInput();
	if (!click_[0] && (click_[1] & MOUSE_INPUT_LEFT)){
		//return std::make_unique<BlackAndWhiteScene>(3,std::move(own),std::make_unique<GameScene>());
		return std::make_unique<BlackAndWhiteScene>(3, std::move(own), std::make_unique<GameScene>());
	}
	DrawOwnScreen(delta);
	return std::move(own);
}

void TitleScene::DrawOwnScreen(double delta)
{
	SetDrawScreen(screen_);
	ClearDrawScreen();
	DrawGraph(0, 0,lpImageMng.GetID("Title")[0], true);
	//SetDrawScreen(DX_SCREEN_BACK);
}
