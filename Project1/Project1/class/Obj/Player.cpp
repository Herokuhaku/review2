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
	// ���ʂ̃A�j���[�V����
	SetItem(STATE::DOWN,"down");	
	// �������̃A�j���[�V����
	SetItem(STATE::LEFT,"left");
	// ������̃A�j���[�V����
	SetItem(STATE::UP,"up");
	// �E�����̃A�j���[�V����
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
