#include "Player.h"
#include "../common/ImageMng.h"
#include "../input/KeyInput.h"
#include "../input/PadInput.h"

Player::Player()
{
}

Player::Player(CntType cntType)
{
	Init(cntType);
}

Player::~Player()
{
}

bool Player::Init(CntType cntType)
{
	xmlitem_ = tmx_.LoadXmlItem("Tiled/AnimImage.tsx");

	speed_ = 5;
	if (cntType == CntType::Key) {
		controller_ = std::make_unique<KeyInput>();
	}
	else if (cntType == CntType::Pad) {
		controller_ = std::make_unique<PadInput>();
	}
	// 正面のアニメーション
	SetItem(STATE::DOWN,"down");	
	// 左向きのアニメーション
	SetItem(STATE::LEFT,"left");
	// 上向きのアニメーション
	SetItem(STATE::UP,"up");
	// 右向きのアニメーション
	SetItem(STATE::RIGHT,"right");

	state(STATE::UP);

	return true;
}

void Player::Update(void)
{
	if ((*controller_)()) {
		if (controller_->Press(InputID::Left)) {
			state(STATE::LEFT);
			pos_.x -= speed_;
		}
		if (controller_->Press(InputID::Right)) {
			state(STATE::RIGHT);
			pos_.x += speed_;
		}
		if (controller_->Press(InputID::Up)) {
			state(STATE::UP);
			pos_.y -= speed_;
		}
		if (controller_->Press(InputID::Down)) {
			state(STATE::DOWN);
			pos_.y += speed_;
		}
	}
}

void Player::Draw(void)
{
	Object::Draw();
	//DrawGraph(pos_.x,pos_.y, lpImageMng.GetID("GreenPlayer")[0], true);
}
