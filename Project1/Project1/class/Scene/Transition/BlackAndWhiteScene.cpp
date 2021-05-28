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

void BlackAndWhiteScene::Draw(double delta)
{
	count_ = (drawmax_ * drawsum_) / limit_;

	SetDrawScreen(screen_);
	ClsDrawScreen();

	int saturation_ = (static_cast<int>((drawsum_ / limit_) * 255));
	if (drawsum_ < limit_/2) {
		before_->Draw(delta);
		GraphFilter(screen_, DX_GRAPH_FILTER_HSB, 0, 0, -saturation_*2, saturation_ * 2);
	}else{
		after_->Draw(delta);
		GraphFilter(screen_, DX_GRAPH_FILTER_HSB, 0, 0,-256 + (saturation_ % 128)*2, 256 - (saturation_ % 128) * 2);
	}
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, count_);
	SetDrawScreen(DX_SCREEN_BACK);
	DrawRotaGraph(lpSceneMng.GetScreenSize().x / 2, lpSceneMng.GetScreenSize().y / 2, 1.0f, 0.0f, screen_, true);
}
