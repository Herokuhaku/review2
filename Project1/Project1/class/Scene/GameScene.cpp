#include "GameScene.h"
#include <DxLib.h>
#include "TitleScene.h"
#include "MenuScene.h"
#include "SceneMng.h"
#include "Transition/CrossOverScene.h"
#include "../common/ImageMng.h"
#include "../Obj/Player.h"

GameScene::GameScene()
{
	Init();
	DrawOwnScreen(0.0f);
}

GameScene::~GameScene()
{
}

bool GameScene::Init(void)
{
	tmxobj_ = std::make_shared<TmxObj>();
	tmxobj_->LoadTmx("Tiled/stage001.tmx");
	objlist_.emplace_back(std::make_unique<Player>(CntType::Key, tmxobj_, objlist_.size()));
	objlist_.emplace_back(std::make_unique<Player>(CntType::Pad,tmxobj_, objlist_.size()));
	lpImageMng.GetID("image/no_002.png", "Game");
	return true;
}

UniqueScene GameScene::Update(double delta, UniqueScene own)
{
	click_[1] = click_[0];
	click_[0] = GetMouseInput();
	DrawOwnScreen(delta);

	for (const auto& obj : objlist_) {
		obj->Update(delta);
		obj->GravityUpdate(delta);
	}

	if (lpSceneMng.GetController()->Pressed(InputID::Escape)) {
		return std::make_unique<MenuScene>(std::move(own));
	}
	return std::move(own);
}

void GameScene::DrawOwnScreen(double delta)
{
	SetDrawScreen(screen_);
	ClsDrawScreen();
	//DrawGraph(0, 0, lpImageMng.GetID("Game")[0], true);
	const Int2& area = tmxobj_->GetWorldArea();
	const Int2& tilesize = tmxobj_->GetTileSize();
	const unsigned int firstgid = tmxobj_->GetFirstGid();

	for (auto& map : tmxobj_->GetMapData())
	{
		int x = 0, y = 0;
		for (auto& data : map.second) {
			int id = data - firstgid;
			if (id >= 0) {
				DrawGraph((x % area.x) * tilesize.x, (y % area.y) * tilesize.y, lpImageMng.GetID("map")[id], true);
			}
			x++;
			if (x % area.x == 0 && x != 0) { y++;}
		}
	}
	
	//for (auto& map : tmxobj_->GetMapData()) {
	//	for (int y = 0; y < area.y; y++) {
	//		for (int x = 0; x < area.x; x++) {
	//			int id = tmxobj_->GetMapData(map.first, x, y) - firstgid;
	//			if (id >= 0) {
	//				DrawGraph((x % area.x) * tilesize.x, (y % area.y) * tilesize.y, lpImageMng.GetID("map")[id], true);
	//			}
	//		}
	//	}
	//}
	for (auto& obj : objlist_) {
		obj->Draw();
	}
}
