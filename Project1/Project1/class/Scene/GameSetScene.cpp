#include "GameSetScene.h"

#include <DxLib.h>
#include "GameScene.h"
#include "TitleScene.h"
#include "SceneMng.h"
#include "../common/ImageMng.h"
#include "Transition/CrossOverScene.h"
#include "Transition/GaussianblurScene.h"
#include "Transition/BlackAndWhiteScene.h"


GameSetScene::GameSetScene(std::list<std::unique_ptr<Object>> objlist,bool gameset)
{
	gameset_ = gameset;
	objlist_ = std::move(objlist);
	Init();
	DrawOwnScreen(0.0f);
}

GameSetScene::~GameSetScene()
{
}

bool GameSetScene::Init(void)
{
	lpImageMng.GetID("image/win.png", "WIN");
	lpImageMng.GetID("image/lose.png", "LOSE");
	lpImageMng.GetID("image/back.png","BackGround");
	//image_ = LoadGraph("image/no_001.png");
	center_ = lpSceneMng.GetScreenSize()/2;
	for (auto& obj : objlist_) {
		if (PlayerType::Ogre == obj->GetPlayerType()) {
			obj->SetPos(Float2(center_.x - (center_.x / 2) - (obj->GetSize().x / 2), center_.y));
		}else if (PlayerType::RunAway == obj->GetPlayerType()) {
			obj->SetPos(Float2(center_.x + (center_.x / 2) - (obj->GetSize().x / 2), center_.y));
		}
		obj->SetAnimationState("down");
		obj->ClearCommandHistory();
	}

	return true;
}

UniqueScene GameSetScene::Update(double delta, UniqueScene own)
{
	click_[1] = click_[0];
	click_[0] = GetMouseInput();
	if (!click_[0] && (click_[1] & MOUSE_INPUT_LEFT)) {
		return std::make_unique<BlackAndWhiteScene>(3, std::move(own), std::make_unique<TitleScene>());
	}
	DrawOwnScreen(delta);
	return std::move(own);
}

void GameSetScene::DrawOwnScreen(double delta)
{
	SetDrawScreen(screen_);
	ClearDrawScreen();
	DrawGraph(0, 0, lpImageMng.GetID("BackGround")[0],true);
	for (auto& obj : objlist_) {
		obj->Draw(5);
	}
	DrawLine(center_.x,0,center_.x,center_.y*2,0xffffff,3);

	Int2 mag = Int2((center_.x / 2), (center_.y / 3 * 2));

	if (!gameset_){
		int x = center_.x - mag.x;
		int y = center_.y - mag.y;
		DrawRotaGraph(x, y, 1.0f, 0.0f, lpImageMng.GetID("WIN")[0], true);
		x = center_.x + mag.x;
		DrawRotaGraph(x, y, 1.0f, 0.0f, lpImageMng.GetID("LOSE")[0], true);
	}
	else {
		int x = center_.x - mag.x;
		int y = center_.y - mag.y;
		DrawRotaGraph(x, y, 1.0f, 0.0f, lpImageMng.GetID("LOSE")[0], true);
		x = center_.x + mag.x;
		DrawRotaGraph(x, y, 1.0f, 0.0f, lpImageMng.GetID("WIN")[0], true);

	}
	//DrawGraph(0, 0, lpImageMng.GetID("GameSet")[0], true);
}
