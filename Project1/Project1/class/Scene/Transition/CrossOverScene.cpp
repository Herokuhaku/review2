#include "CrossOverScene.h"
#include <DxLib.h>

CrossOverScene::CrossOverScene(double limit,UniqueScene before, UniqueScene after):TransitionScene(limit,std::move(before),std::move(after))
{
}

CrossOverScene::~CrossOverScene()
{
}

bool CrossOverScene::UpdateTransition(double delta)
{
	return TransitionScene::LimitCheck(delta);
}

//void CrossOverScene::Draw(double delta)
//{
//	count_ = (drawmax_ * drawsum_) / 3.0;
//	SetDrawScreen(screen_);
//	ClsDrawScreen();
//
//	SetDrawBlendMode(DX_BLENDMODE_ALPHA, static_cast<int>(drawmax_ - count_));
//	before_->Draw(delta);
//
//	SetDrawBlendMode(DX_BLENDMODE_ALPHA, static_cast<int>(count_));
//	after_->Draw(delta);
//
//	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, count_);
//
//	SetDrawScreen(DX_SCREEN_BACK);
//	DrawGraph(0, 0, screen_, true);
//}

void CrossOverScene::DrawOwnScreen(double delta)
{
	count_ = (drawmax_ * drawsum_) / 3.0;
	SetDrawScreen(screen_);
	ClsDrawScreen();

	SetDrawBlendMode(DX_BLENDMODE_ALPHA, static_cast<int>(drawmax_ - count_));
	before_->Draw(delta);

	SetDrawBlendMode(DX_BLENDMODE_ALPHA, static_cast<int>(count_));
	after_->Draw(delta);

	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, static_cast<int>(count_));

	//SetDrawScreen(DX_SCREEN_BACK);
	//DrawGraph(0, 0, screen_, true);
}
