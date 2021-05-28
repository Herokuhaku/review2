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
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND,255);
}

bool TransitionScene::Init(void)
{
	drawsum_ = 0;
	drawmax_ = 255;
	screen_ = MakeScreen(lpSceneMng.GetScreenSize().x, lpSceneMng.GetScreenSize().y,true);
	return true;
}

UniqueScene TransitionScene::Update(double delta, UniqueScene own)
{
	if (UpdateTransition(delta)) {
		return std::move(after_);
	}
	return own;
}

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
