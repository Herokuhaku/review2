#include "TitleScene.h"
#include <DxLib.h>

TitleScene::TitleScene()
{
	Init();
}

TitleScene::~TitleScene()
{
}

bool TitleScene::Init(void)
{
	image_ = LoadGraph(L"image/no_001.png");
	return true;
}

void TitleScene::Update(double delta)
{
	int bgm_ = LoadSoundMem(L"a.mp3");
}

void TitleScene::Draw(double delta)
{
	DrawGraph(0,0,image_,true);
}
