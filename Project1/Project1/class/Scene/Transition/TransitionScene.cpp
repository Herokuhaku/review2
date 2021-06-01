#include <DxLib.h>
#include "TransitionScene.h"
#include "../../../_debug/_DebugConOut.h"
#include "../SceneMng.h"
TransitionScene::TransitionScene(double limit, UniqueScene before, UniqueScene after)
{
	before_ = std::move(before);
	after_ = std::move(after);
	limit_ = limit;
	Init();
}

TransitionScene::~TransitionScene()
{
	GraphFilter(screen_, DX_GRAPH_FILTER_HSB,0,0,0,0);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND,255);
}

bool TransitionScene::Init(void)
{
	SetDrawScreen(screen_);
	ClsDrawScreen();
	before_->Draw(0.0f);
	drawsum_ = 0;
	drawmax_ = 255;
	return true;
}

UniqueScene TransitionScene::Update(double delta, UniqueScene own)
{
	if (UpdateTransition(delta)) {
		return std::move(after_);
	}
	DrawOwnScreen(delta);
	return own;
}

//void TransitionScene::DrawOwnScreen(double delta)
//{
//}

bool TransitionScene::LimitCheck(double delta)
{
	drawsum_ += delta;

	if (drawsum_ >= limit_) {
		return true;
	}
	return false;
}

//void TransitionScene::Draw(double delta)
//{
//
//}
