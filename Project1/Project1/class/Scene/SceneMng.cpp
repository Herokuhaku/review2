#include <DxLib.h>
#include "SceneMng.h"
#include "TitleScene.h"
#include "GameScene.h"

void SceneMng::Run(void)
{
	if(!initflag_ && !SysInit()) {
		return;
	}
	// Sceneのインスタンス
	scene = std::make_unique<TitleScene>();
	now = std::chrono::system_clock::now();

	while (!ProcessMessage() && !CheckHitKey(KEY_INPUT_ESCAPE)) {
		old = now;
		now = std::chrono::system_clock::now();
		auto delta = std::chrono::duration_cast<std::chrono::microseconds>(now - old).count() / 1000000.0;
		scene->Update(delta);

		ClsDrawScreen();
		scene->Draw(delta);
		ScreenFlip();
		if (MOUSE_INPUT_LEFT & GetMouseInput())
		{
			scene = std::make_unique<GameScene>();
		}
		if (MOUSE_INPUT_RIGHT & GetMouseInput())
		{
			scene = std::make_unique<TitleScene>();
		}
	}
}

void SceneMng::Update(void)
{
}

void SceneMng::Draw(void)
{
}

SceneMng::SceneMng()
{
	initflag_ = SysInit();
}

SceneMng::~SceneMng()
{
}

bool SceneMng::SysInit(void)
{
	SetGraphMode(1024, 768, 32);
	ChangeWindowMode(true);
	SetWindowText(L"1916213_佐藤弘哲");
	if (DxLib_Init() == -1) {
		return false;
	}
	return true;
}
