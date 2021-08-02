#include "GameScene.h"

#include <DxLib.h>
#include "TitleScene.h"
#include "MenuScene.h"
#include "GameSetScene.h"
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
	finishtime_ = 10; // 300秒でゲーム終了
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
				Float2 circle = obj->GetPos() - checkobj->GetPos();
				auto val = sqrt((circle.x * circle.x) + (circle.y * circle.y));

				// 自分じゃない場合 && 当たり判定を取って当たっているか
				if (obj->GetObjectNum() != checkobj->GetObjectNum() &&
					val <= obj->GetSize().x + checkobj->GetSize().x) {
					checkobj->SetCatch(2);
				}
			}
		}
	}
	// 全員つかまっているか判定 true 全員捕まっている false 一人以上捕まっていない
	bool flag = false;
	int cat = 0;
	for (auto& obj : objlist_) {
		cat = obj->GetCatch();

		if (cat == 1) {
			flag = false;
			break;
		}
		else if(cat == 2){
			flag = true;
		}
	}
	if (flag) {
		return std::make_unique<GameSetScene>(std::move(objlist_),0);
	}
	if (lpSceneMng.GetController()->Pressed(InputID::Escape)) {
		return std::make_unique<MenuScene>(std::move(own));
	}
	finishtime_ -= delta;
	if (finishtime_ <= 0) {
		return std::make_unique<GameSetScene>(std::move(objlist_), 1);
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
	DrawFormatString(0,0,0xffffff,"残り %d 秒",static_cast<int>(finishtime_));
}