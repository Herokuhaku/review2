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
	//xmlitem_ = tmx_.LoadXmlItem("Tiled/AnimImage.tsx");

	//itr_ = xmlitem_.data_["right"].begin();

	anim_ = std::make_unique<Animation>("GreenPlayer");

	speed_ = 5;
	if (cntType == CntType::Key) {
		controller_ = std::make_unique<KeyInput>();
	}
	else if (cntType == CntType::Pad) {
		controller_ = std::make_unique<PadInput>();
	}

	lpImageMng.SetXml("Tiled/AnimImage.tsx");

	// 正面のアニメーション
	lpImageMng.SetItem(anim_->GetKey(),STATE::DOWN,"down");	
	// 左向きのアニメーション
	lpImageMng.SetItem(anim_->GetKey(), STATE::LEFT,"left");
	// 上向きのアニメーション
	lpImageMng.SetItem(anim_->GetKey(), STATE::UP,"up");
	// 右向きのアニメーション
	lpImageMng.SetItem(anim_->GetKey(), STATE::RIGHT,"right");

	anim_->state(STATE::UP);
	return true;
}

void Player::Update(void)
{
	if ((*controller_)()) {
		//Int2 vec(0,0);
		if (controller_->Press(InputID::Left)) {
			anim_->state(STATE::LEFT);
			//pos_.x -= speed_;
			pos_.x -= speed_;
		}
		if (controller_->Press(InputID::Right)) {
			anim_->state(STATE::RIGHT);
			pos_.x += speed_;
		}
		if (controller_->Press(InputID::Up)) {
			anim_->state(STATE::UP);
			pos_.y -= speed_;
		}
		if (controller_->Press(InputID::Down)) {
			anim_->state(STATE::DOWN);
			pos_.y += speed_;
		}
		//pos_ += vec.Normalized()*speed_;
	}

	//auto data = (*itr_).second;
	//if (animCount++ > data) {
	//	animCount = 0;
	//	++itr_;

	//	if (itr_ == xmlitem_.data_["right"].end()) {
	//		++animPlayCount;
	//		if (xmlitem_.loop_["right"] != -1) {
	//			itr_ = xmlitem_.data_["right"].begin();
	//		}
	//		else {
	//			itr_ = xmlitem_.data_["right"].end();
	//		}
	//	}
	//}
}

void Player::Draw(void)
{
	anim_->Draw(pos_);
	//Object::Draw();
	//DrawGraph(pos_.x, pos_.y,animMap_[state_][animframe_].first, true);
	//DrawGraph(pos_.x,pos_.y, lpImageMng.GetID("GreenPlayer")[(*itr_).first], true);
}
