#include "Player.h"
#include "../common/ImageMng.h"
#include "../common/AnimationMng.h"
#include "../input/KeyInput.h"
#include "../input/PadInput.h"

Player::Player()
{
}

Player::Player(CntType cntType,std::shared_ptr<TmxObj> tmx)
{
	Init(cntType);
	tmx_ = tmx;
}

Player::~Player()
{
}

bool Player::Init(CntType cntType)
{
	if (!LoadAnimation()) {
		return false;
	}
	if (cntType == CntType::Key) {
		controller_ = std::make_unique<KeyInput>();
	}
	else if (cntType == CntType::Pad) {
		controller_ = std::make_unique<PadInput>();
	}

	speed_ = 5;
	pos_ = Float2();
	return true;
}

bool Player::LoadAnimation(void)
{
	bool rtnflag = true;
	anim_ = std::make_unique<Animation>("GreenPlayer");

	rtnflag &= lpAnimationMng.SetXml(anim_->GetKey(), "Tiled/AnimImage.tsx");

	// 正面のアニメーション
	rtnflag &= lpAnimationMng.SetItem(anim_->GetKey(),"down");
	// 左向きのアニメーション
	rtnflag &= lpAnimationMng.SetItem(anim_->GetKey(), "left");
	// 上向きのアニメーション
	rtnflag &= lpAnimationMng.SetItem(anim_->GetKey(), "up");
	// 右向きのアニメーション
	rtnflag &= lpAnimationMng.SetItem(anim_->GetKey(), "right");

	anim_->state("down");
	size_ = lpAnimationMng.GetImageSize(anim_->GetKey());

	return rtnflag;
}

void Player::Update(void)
{
// キー処理
	if ((*controller_)()) {
		Float2 vec(0,0);

		// 移動測定処理 and アニメーションの変更
		if (controller_->Press(InputID::Left)) {
			anim_->state("left");
			vec.x -= speed_;
		}
		if (controller_->Press(InputID::Right)) {
			anim_->state("right");
			vec.x += speed_;
		}
		if (controller_->Press(InputID::Up)) {
			anim_->state("up");

			vec.y -= speed_;
		}
		if (controller_->Press(InputID::Down)) {
			anim_->state("down");
			vec.y += speed_;
		}
		vec = vec.Normalized() * speed_;
		// 当たり判定処理
		if (tmx_->GetMapDataCheck(pos_) >= pos_.x + vec.x) {

		}
		// 移動
		pos_ = pos_ + vec;
	}

	anim_->Update();
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
	anim_->Draw(pos_,size_,2);
	//Object::Draw();
	//DrawGraph(pos_.x, pos_.y,animMap_[state_][animframe_].first, true);
	//DrawGraph(pos_.x,pos_.y, lpImageMng.GetID("GreenPlayer")[(*itr_).first], true);
}
