#include <DxLib.h>
#include "SceneMng.h"
#include "TitleScene.h"
#include "GameScene.h"

void SceneMng::Run(void)
{
	if(!initflag_ && !SysInit()) {
		return;
	}
	// Scene�̃C���X�^���X
	scene_ = std::make_unique<TitleScene>();
	now_ = std::chrono::system_clock::now();

	while (!ProcessMessage() && !CheckHitKey(KEY_INPUT_ESCAPE)) {
		
		ClsDrawScreen();
		// deltatime�̐ݒ�
		old_ = now_;
		now_ = std::chrono::system_clock::now();
		auto delta = std::chrono::duration_cast<std::chrono::microseconds>(now_ - old_).count() / 1000000.0;
		// 	

		scene_->Draw(delta);
		scene_ = scene_->Update(delta, std::move(scene_));

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

SceneMng::SceneMng():screenSize_(1024,768)
{
	initflag_ = SysInit();
}

SceneMng::~SceneMng()
{
}

bool SceneMng::SysInit(void)
{
	SetGraphMode(screenSize_.x,screenSize_.y, 32);
	ChangeWindowMode(true);
	SetWindowText(L"1916213_�����O�N");
	if (DxLib_Init() == -1) {
		return false;
	}
	return true;
}
