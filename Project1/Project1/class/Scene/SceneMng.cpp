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
	// Scene�̃C���X�^���X
	scene_ = std::make_unique<TitleScene>();
	now_ = std::chrono::system_clock::now();
	frame_ = 0;
	double nextdeltatime = GetNowCount();
	Int2 strsize_ = Int2(screenSize_.x / 3 + 30, screenSize_.y / 3 * 2);
	while (!ProcessMessage() && !finish_) {
		_dbgAddDraw();
		// deltatime�̐ݒ�
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
		//DrawFormatString(0, 0, 0xffff00,"%f",GetFPS());

		// 1�t���[��16.66ms����
		nextdeltatime += 16.66;
		// 1�t���[���̌��E�l 16.66ms (1�b�Ԃ�60�t���[���̏ꍇ) �������������ɓ��B���Ă����炻�̕��҂�
		if (nextdeltatime > GetNowCount()) {
			WaitTimer(static_cast<int>(nextdeltatime) - GetNowCount());
		}
		if (scene_->GetSceneID() != Scene::Game && frame_++/30 % 2 == 0)
		{
			DrawString(strsize_.x,strsize_.y,"���N���b�N�Ŏ��̃V�[���֐i��",0xffffff);
		}

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
	SetWindowText("1916213_�����O�N");
	if (DxLib_Init() == -1) {
		return false;
	}
	SetDrawScreen(DX_SCREEN_BACK);

	controller_ = std::make_shared<KeyInput>();
	finish_ = false;
	return true;
}
