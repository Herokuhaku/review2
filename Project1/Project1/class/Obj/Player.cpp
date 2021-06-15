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
	lpImageMng.GetID("image/green.png", "GreenPlayer",
		Int2(32, 32),
		Int2(3, 4));
	speed_ = 5;
	if (cntType == CntType::Key) {
		controller_ = std::make_unique<KeyInput>();
	}
	else if (cntType == CntType::Pad) {
		controller_ = std::make_unique<PadInput>();
	}

	AnimVector data;
	// ���ʂ̃A�j���[�V����
	data.reserve(5);
	for (int i = 1; i < 4; i++) {
		data.emplace_back(lpImageMng.GetID("GreenPlayer")[i -1],i * 7);
	}
	SetAnim(STATE::DOWN,data);

	// �������̃A�j���[�V����
	data.reserve(3);
	for (int i = 1; i < 4; i++) {
		data.emplace_back(lpImageMng.GetID("GreenPlayer")[i+ static_cast<__int64>(3) -1], i * 7);
	}
	SetAnim(STATE::LEFT, data);

	// �E�����̃A�j���[�V����
	data.reserve(3);
	for (int i = 1; i < 4; i++) {
		data.emplace_back(lpImageMng.GetID("GreenPlayer")[i+ static_cast<__int64>(6) -1], i * 7);
	}
	SetAnim(STATE::RIGHT, data);

	// �������̃A�j���[�V����
	data.reserve(3);
	for (int i = 1; i < 4; i++) {
		data.emplace_back(lpImageMng.GetID("GreenPlayer")[i+ static_cast<__int64>(9) -1], i * 7);
	}
	SetAnim(STATE::UP, data);

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
