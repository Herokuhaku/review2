#include "GaussianblurScene.h"
#include <DxLib.h>
#include "../SceneMng.h"

GaussianblurScene::GaussianblurScene(double limit, UniqueScene before, UniqueScene after) :TransitionScene(limit, std::move(before), std::move(after))
{
}

GaussianblurScene::~GaussianblurScene()
{
}

bool GaussianblurScene::UpdateTransition(double delta)
{
	return TransitionScene::LimitCheck(delta);
}

//void GaussianblurScene::Draw(double delta)
//{
//	count_ = (drawmax_ * drawsum_) / limit_;
//
//	SetDrawScreen(screen_);
//	ClsDrawScreen();
//
//	SetDrawBlendMode(DX_BLENDMODE_ALPHA, static_cast<int>(drawmax_ - count_));
//
//	before_->Draw(delta);
//
//	SetDrawBlendMode(DX_BLENDMODE_ALPHA, static_cast<int>(count_));
//	after_->Draw(delta);
//
//	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, count_);
//
//	GraphFilter(screen_, DX_GRAPH_FILTER_GAUSS,16,3200);
//	//int saturation_ = (static_cast<int>((drawsum_ / limit_) * 255));
//	//if (drawsum_ < limit_/2) {
//	//	GraphFilter(screen_, DX_GRAPH_FILTER_HSB, 0, 0,-saturation_, 0);
//	//}else{
//	//	GraphFilter(screen_, DX_GRAPH_FILTER_HSB, 0, 0, -128 + (saturation_ % 128), 0);
//	//}
//
//	SetDrawScreen(DX_SCREEN_BACK);
//	DrawRotaGraph(lpSceneMng.GetScreenSize().x / 2,lpSceneMng.GetScreenSize().y/2,1.0f,0.0f,screen_, true);
//}

void GaussianblurScene::DrawOwnScreen(double delta)
{
	count_ = (drawmax_ * drawsum_) / limit_;

	SetDrawScreen(screen_);
	ClsDrawScreen();

	SetDrawBlendMode(DX_BLENDMODE_ALPHA, static_cast<int>(drawmax_ - count_));

	before_->Draw(delta);

	SetDrawBlendMode(DX_BLENDMODE_ALPHA, static_cast<int>(count_));
	after_->Draw(delta);

	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, count_);

	GraphFilter(screen_, DX_GRAPH_FILTER_GAUSS, 16, 3200);
}
