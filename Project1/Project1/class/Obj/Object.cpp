#include "Object.h"
#include <DxLib.h>
#include "../common/ImageMng.h"
#include "../input/KeyInput.h"
#include "../input/PadInput.h"

Object::Object()
{
	Init();
}

Object::~Object()
{
}

bool Object::Init(void)
{
	lpImageMng.GetID("image/green.png","GreenPlayer",
		Int2(32,32),
		Int2(3,4));
	speed_ = 5;
	controller_ = std::make_unique<KeyInput>();
	return true;
}

void Object::Update(void)
{
	controller_->Update();
	if (controller_->Press(InputID::Left)) {
		pos_.x -= speed_;
	}
	if (controller_->Press(InputID::Right)) {
		pos_.x += speed_;
	}
	if (controller_->Press(InputID::Up)) {
		pos_.y -= speed_;
	}
	if (controller_->Press(InputID::Down)) {
		pos_.y += speed_;
	}
}

void Object::Draw(void)
{
	DrawGraph(pos_.x,pos_.y, lpImageMng.GetID("GreenPlayer")[0], true);
}
