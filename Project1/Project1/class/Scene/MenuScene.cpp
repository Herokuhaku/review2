#include "MenuScene.h"

#include <DxLib.h>
#include "SceneMng.h"
#include "../common/ImageMng.h"
#include "Transition/BlackAndWhiteScene.h"
#include "TitleScene.h"

MenuScene::MenuScene(UniqueScene old)
{
    oldScene_ = std::move(old);
    Init();
    DrawOwnScreen(0.0f);
}

MenuScene::~MenuScene()
{
    delete end_;
}

bool MenuScene::Init(void)
{
    end_ = new EndGame(Int2(lpSceneMng.GetScreenSize()/2));
    return true;
}

UniqueScene MenuScene::Update(double delta, UniqueScene own)
{   
    end_->Update();
    DrawOwnScreen(delta);

    //click_[1] = click_[0];
    //click_[0] = GetMouseInput();
    //if (!click_[0] && (click_[1] & MOUSE_INPUT_LEFT)) {
    //    return std::make_unique<BlackAndWhiteScene>(3.0, std::move(own), std::make_unique<TitleScene>());
    //}


    if (lpSceneMng.GetController()->Pressed(InputID::Escape)) {
        return std::move(oldScene_);
    }

    return std::move(own);
}

void MenuScene::DrawOwnScreen(double delta)
{
    SetDrawScreen(screen_);
    ClearDrawScreen();

    oldScene_->Draw(delta);
    //DrawCircle(0,0,15,0xffffff,true);
}
