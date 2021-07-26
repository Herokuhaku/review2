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
	objlist_.emplace_back(std::make_unique<Player>(CntType::Key, tmxobj_, objlist_.size(),Float2(1,1)));
	objlist_.emplace_back(std::make_unique<Player>(CntType::Pad,tmxobj_, objlist_.size(), Float2(lpSceneMng.GetScreenSize().x-65, 1)));
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

	for (auto& obj : objlist_) {
		if (obj->GetPlayerType() == PlayerType::Ogre && (obj->GetNowAnimationName() == "beam")) {
			for (auto& checkobj : objlist_) {
				Float2 opos = obj->GetPos();
				Float2 cpos = checkobj->GetPos();
				float a = (opos.x - cpos.x);
				float b = (opos.y - cpos.y);
				float c = hypot(pow(a,2),pow(b,2));
				// 自分じゃない場合 && 当たり判定を取って当たっているか
				if (obj->GetObjectNum() != checkobj->GetObjectNum() &&
					c <= obj->GetSize().x + checkobj->GetSize().x) {
					checkobj->SetCatch(2);
				}
			}
		}
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

	for (auto obj = objlist_.rbegin(); obj != objlist_.rend(); obj++) {
		(*obj)->Draw();
	}
	bool flag_ = false;
	for (auto& obj : objlist_) {
		if (obj->GetCatch() == 2) {
			flag_ = true;
		}
	}
	if(flag_){
		DrawString(400, 400, "鬼の勝ち！！！", 0xffffff);
	}
}
