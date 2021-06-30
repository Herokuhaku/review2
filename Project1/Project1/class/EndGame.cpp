#include "EndGame.h"

#include <DxLib.h>
#include "Scene/SceneMng.h"

EndGame::EndGame(Float2 pos)
{
	pos_ = pos;
	size_ = Float2(200,200);
}

EndGame::~EndGame()
{
}

bool EndGame::Update(void)
{
	Draw();
	Int2 mouse;
	GetMousePoint(&mouse.x,&mouse.y);
	click_ = GetMouseInput();
	if (click_ & MOUSE_INPUT_LEFT) {
		if (pos_.x <= mouse.x && mouse.x <= pos_.x + size_.x &&
			pos_.y <= mouse.y && mouse.y <= pos_.y + size_.y) {
			lpSceneMng.Finish();
			return false;
		}
	}
	return true;
}

bool EndGame::Draw(void)
{
	DrawBox(pos_.x,pos_.y,pos_.x + size_.x,pos_.y + size_.y,0xffffff,true);
	return true;
}
