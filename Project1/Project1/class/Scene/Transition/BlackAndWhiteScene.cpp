#include "BlackAndWhiteScene.h"
#include <DxLib.h>
#include "../SceneMng.h"

BlackAndWhiteScene::BlackAndWhiteScene(double limit, UniqueScene before, UniqueScene after) :TransitionScene(limit, std::move(before), std::move(after))
{
}

BlackAndWhiteScene::~BlackAndWhiteScene()
{
}

bool BlackAndWhiteScene::UpdateTransition(double delta)
{
	return TransitionScene::LimitCheck(delta);
}

void BlackAndWhiteScene::DrawOwnScreen(double delta)
{
	count_ = (drawmax_ * drawsum_) / limit_;

	SetDrawScreen(screen_);
	ClsDrawScreen();

	int saturation_ = (static_cast<int>((drawsum_ / limit_) * static_cast<int>(drawmax_))) % static_cast<int>(drawmax_);
	//if (drawsum_ < limit_ / 2) {
	if(saturation_ < static_cast<int>(drawmax_)/2+1){
	before_->Draw(delta);
		GraphFilter(screen_, DX_GRAPH_FILTER_HSB, 0, 0, -(saturation_ % (static_cast<int>(drawmax_+1)/2)) * 2, (saturation_ % (static_cast<int>(drawmax_+1)/2)) * 2);
	}
	else {
		after_->Draw(delta);		
		int tmp = (saturation_ %  (static_cast<int>(drawmax_+1)/2)) * 2;
		GraphFilter(screen_, DX_GRAPH_FILTER_HSB, 0, 0, static_cast<int>(-drawmax_) + tmp,static_cast<int>(drawmax_) - tmp);
	}
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, count_);
}
//
//void BlackAndWhiteScene::Draw(double delta)
//{
//	count_ = (drawmax_ * drawsum_) / limit_;
//
//	SetDrawScreen(screen_);
//	ClsDrawScreen();
//
//	int saturation_ = (static_cast<int>((drawsum_ / limit_) * 255))%255;
//	if (drawsum_ <= limit_/2) {
//		before_->Draw(delta);
//		GraphFilter(screen_, DX_GRAPH_FILTER_HSB, 0, 0, -(saturation_ % 128) *2, (saturation_ % 128)* 2);
//	}else{
//		after_->Draw(delta);
//		int tmp = (saturation_ % 127) * 2;
//		GraphFilter(screen_, DX_GRAPH_FILTER_HSB, 0, 0,-255 + tmp,255 - tmp);
//	}
//	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, count_);
//	SetDrawScreen(DX_SCREEN_BACK);
//	DrawRotaGraph(lpSceneMng.GetScreenSize().x / 2, lpSceneMng.GetScreenSize().y / 2, 1.0f, 0.0f, screen_, true);
//}
