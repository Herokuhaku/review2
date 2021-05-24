#include "main.h"
#include <DxLib.h>
#include <chrono>
#include <memory>
#include "class/Scene/TitleScene.h"
#include "class/Scene/SceneMng.h"

int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_  HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nShowCmd)
{
	SetGraphMode(1024,768, 32);
	ChangeWindowMode(true);
	SetWindowText(L"1916213_ç≤ì°çOìN");
	if (DxLib_Init() == -1) {
		return -1;
	}
	std::unique_ptr<BaseScene> scene;
	scene = std::make_unique<TitleScene>();
	std::chrono::system_clock::time_point now, old;
	now = std::chrono::system_clock::now();
	SceneMng::GetInstance().Draw();
	while (!ProcessMessage() && !CheckHitKey(KEY_INPUT_ESCAPE)){
		old = now;
		now = std::chrono::system_clock::now();
		auto delta = std::chrono::duration_cast<std::chrono::microseconds>(now - old).count() / 1000000.0;
		scene->Update(delta);

		ClsDrawScreen();
		scene->Draw(delta);
		ScreenFlip();
	}

	return 1;
}