#include "TitleScene.h"
#include <DxLib.h>
#include "GameScene.h"
#include "Transition/CrossOverScene.h"
#include "Transition/GaussianblurScene.h"
#include "Transition/BlackAndWhiteScene.h"

TitleScene::TitleScene()
{
	Init();
}

TitleScene::~TitleScene()
{
}

bool TitleScene::Init(void)
{
	image_ = LoadGraph(L"image/no_001.png");
	return true;
}

UniqueScene TitleScene::Update(double delta, UniqueScene own)
{
	click_[1] = click_[0];
	click_[0] = GetMouseInput();
	if (!click_[0] && (click_[1] & MOUSE_INPUT_LEFT))
	{
		return std::make_unique<BlackAndWhiteScene>(3.0,std::move(own),std::make_unique<GameScene>());
	}
	return std::move(own);
}

void TitleScene::Draw(double delta)
{
	DrawGraph(0,0,image_,true);
}
