#include "GameScene.h"
#include <DxLib.h>
#include "TitleScene.h"
#include "Transition/CrossOverScene.h"
#include "../common/ImageMng.h"

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
	tmxobj_.LoadTmx("Tiled/stage001.tmx");
	obj_ = new Object();
	lpImageMng.GetID("image/no_002.png", "Game");
	return true;
}

UniqueScene GameScene::Update(double delta, UniqueScene own)
{
	click_[1] = click_[0];
	click_[0] = GetMouseInput();
	if (!click_[0] && (click_[1] & MOUSE_INPUT_LEFT)){
		return std::make_unique<CrossOverScene>(3.0, std::move(own), std::make_unique<TitleScene>());
	}
	DrawOwnScreen(delta);

	obj_->Update();

	return std::move(own);
}
//
//void GameScene::Draw(double delta)
//{
//}

void GameScene::DrawOwnScreen(double delta)
{
	SetDrawScreen(screen_);
	ClsDrawScreen();
	//DrawGraph(0, 0, lpImageMng.GetID("Game")[0], true);
	Int2 area = tmxobj_.GetWorldArea();
	Int2 tilesize = tmxobj_.GetTileSize();
	unsigned int firstgid = tmxobj_.GetFirstGid();

	//for (auto& map : tmxobj_.GetMapData())
	//{
	//	int x = 0, y = 0;
	//	for (auto& data : map.second) {
	//		int id = data - firstgid;
	//		if (id >= 0) {
	//			DrawGraph((x % area.x) * tilesize.x, (y % area.y) * tilesize.y, lpImageMng.GetID("map")[id], true);
	//		}
	//		x++;
	//		if (x % area.x == 0 && x != 0) { y++;}
	//	}
	//}
	
	for (auto& map : tmxobj_.GetMapData()) {
		for (int y = 0; y < area.y; y++) {
			for (int x = 0; x < area.x; x++) {
				int id = tmxobj_.GetMapData(map.first, x, y) - firstgid;
				if (id >= 0) {
					DrawGraph((x % area.x) * tilesize.x, (y % area.y) * tilesize.y, lpImageMng.GetID("map")[id], true);
				}
			}
		}
	}
	obj_->Draw();
}
