#include "EndGame.h"

#include <DxLib.h>
#include "Scene/SceneMng.h"

EndGame::EndGame(Float2 pos, Float2 size)
{
	size_ = size;
	pos_ = pos - (size_ / 2);
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
	if (pos_.x <= mouse.x && mouse.x <= pos_.x + size_.x &&
		pos_.y <= mouse.y && mouse.y <= pos_.y + size_.y) {
		DrawBox(pos_.x,pos_.y,pos_.x + size_.x,pos_.y + size_.y,0xff0000,false);
		DrawBox(pos_.x+1, pos_.y+1, pos_.x + size_.x-1, pos_.y + size_.y-1, 0xff0000, false);
		if (click_ & MOUSE_INPUT_LEFT) {
			lpSceneMng.Finish();
			return false;
		}
	}
	return true;
}

bool EndGame::Draw(void)
{
	DrawBox(pos_.x,pos_.y,pos_.x + size_.x,pos_.y + size_.y,0xffffff,true);
	DrawString(pos_.x + (GetFontSize()*2),pos_.y + (size_.y/2) - (GetFontSize()/2),"ƒQ[ƒ€‚ðI—¹‚·‚é",0x0,true);
	return true;
}
