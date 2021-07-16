#include "SceneMng.h"

#include <DxLib.h>
#include "TitleScene.h"
#include "GameScene.h"
#include "../../_debug/_DebugDispOut.h"

void SceneMng::Run(void)
{
	if(!initflag_ && !SysInit()) {
		return;
	}
	// Sceneのインスタンス
	scene_ = std::make_unique<TitleScene>();
	now_ = std::chrono::system_clock::now();

	while (!ProcessMessage() && !finish_) {



		_dbgAddDraw();
		// deltatimeの設定
		old_ = now_;
		now_ = std::chrono::system_clock::now();
		auto delta = std::chrono::duration_cast<std::chrono::microseconds>(now_ - old_).count() / 1000000.0;
		// 	
		(*controller_)(delta);
		//scene_->Draw(delta);
		scene_ = scene_->Update(delta, std::move(scene_));
		SetDrawScreen(DX_SCREEN_BACK);
		ClsDrawScreen();
		scene_->Draw(delta);
		DrawFormatString(0, 0, 0xffff00,"%f",GetFPS());
		ScreenFlip();
	}
}

void SceneMng::Update(void)
{
}

void SceneMng::Draw(void)
{
}

const Int2 SceneMng::GetScreenSize(void)const
{
	return screenSize_;
}

std::shared_ptr<Controller> SceneMng::GetController(void)
{
	if (controller_ == nullptr) {
		controller_ = std::make_shared<KeyInput>();
	}
	return controller_;
}

SceneMng::SceneMng():screenSize_(1024,768)
{
	initflag_ = SysInit();
}

SceneMng::~SceneMng()
{
}

bool SceneMng::SysInit(void)
{
	SetGraphMode(screenSize_.x,screenSize_.y, 32,60);
	ChangeWindowMode(true);
	SetWindowText("1916213_佐藤弘哲");
	if (DxLib_Init() == -1) {
		return false;
	}
	SetDrawScreen(DX_SCREEN_BACK);

	controller_ = std::make_shared<KeyInput>();
	finish_ = false;
	return true;
}
