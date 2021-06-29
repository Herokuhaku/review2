#include "Player.h"

#include "../Scene/SceneMng.h"
#include "../common/ImageMng.h"
#include "../common/AnimationMng.h"
#include "../common/Raycast.h"
#include "../input/KeyInput.h"
#include "../input/PadInput.h"
#include "../../_debug/_DebugDispOut.h"
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

	mag_ = 2;
	speed_ = 5;
	pos_ = Float2();
	colpos_ = Float2();
	std::list<Float2> flist;
	//size/2
	Int2 s = (size_) / 2;

	flist.emplace_back(Float2(-s.x, -s.y));
	flist.emplace_back(Float2(s.x,-s.y));
	colvec_.try_emplace("up",flist);
	flist.clear();

	flist.emplace_back(Float2(s.x,-s.y));
	flist.emplace_back(Float2(s.x,s.y));
	colvec_.try_emplace("right", flist);
	flist.clear();

	flist.emplace_back(Float2(s.x,s.y));
	flist.emplace_back(Float2 (-s.x,s.y));
	colvec_.try_emplace("down",flist);
	flist.clear();

	flist.emplace_back(Float2 (-s.x,s.y));
	flist.emplace_back(Float2 (-s.x,-s.y));
	colvec_.try_emplace("left", flist);
	flist.clear();
	return true;
}

bool Player::LoadAnimation(void)
{
	bool rtnflag = true;
	anim_ = std::make_unique<Animation>("GreenPlayer");

	rtnflag &= lpAnimationMng.SetXml(anim_->GetKey(), "Tiled/AnimImage.tsx");

	// ���ʂ̃A�j���[�V����
	rtnflag &= lpAnimationMng.SetItem(anim_->GetKey(),"down");
	// �������̃A�j���[�V����
	rtnflag &= lpAnimationMng.SetItem(anim_->GetKey(), "left");
	// ������̃A�j���[�V����
	rtnflag &= lpAnimationMng.SetItem(anim_->GetKey(), "up");
	// �E�����̃A�j���[�V����
	rtnflag &= lpAnimationMng.SetItem(anim_->GetKey(), "right");

	anim_->state("down");
	size_ = lpAnimationMng.GetImageSize(anim_->GetKey());

	return rtnflag;
}

void Player::Update(void)
{
// �L�[����
	if (!(*controller_)()) {
		return;
	}
	auto checkMove = [&](Float2&& moveVec) {
		Raycast::Ray ray = {{ pos_ + size_ }, moveVec};
		_dbgDrawLine(ray.p.x, ray.p.y, ray.p.x + ray.v.x, ray.p.y + ray.v.y, 0x00ff00);
		for (auto col : tmx_->GetColList()) {
			_dbgDrawBox(col.first.x, col.first.y,
				col.first.x + col.second.x, col.first.y + col.second.y, 0xffffff, false);
			if (raycast_.CheckCollision(ray, col)) {
				return false;
			}
		}
		return true;
	};

	Float2 vec(0,0);

	// �ړ����菈�� and �A�j���[�V�����̕ύX
	if (controller_->Press(InputID::Left)) {
		if (checkMove(Float2{-(speed_ + size_.x),0})) {
			anim_->state("left");
			vec.x -= speed_;
		}
	}
	if (controller_->Press(InputID::Right)) {
		if (checkMove(Float2{ speed_ + size_.x,0 })) {
			anim_->state("right");
			vec.x += speed_;
		}
	}
	if (controller_->Press(InputID::Up)) {
		if (checkMove(Float2{ 0,-(speed_+size_.y) })) {
			anim_->state("up");
			vec.y -= speed_;
		}
	}
	if (controller_->Press(InputID::Down)) {
		if (checkMove(Float2{ 0.0,(speed_ + size_.y) })) {
			anim_->state("down");
			vec.y += speed_;
		}
	}
	vec = vec.Normalized() * speed_;
	// �����蔻�菈��
	auto window = [&](Float2 v) {
		return (v >= Float2(0, 0) && v <= Float2(lpSceneMng.GetScreenSize().x, lpSceneMng.GetScreenSize().y));
	};
	// �x�N�g����0�ł͂Ȃ��Ƃ��@&& �����蔻�������
	if (((vec.x != 0) || (vec.y != 0))) {
		Float2 check(colpos_);
		bool plus = true;
		// �E
		if (0 < vec.x) {
			for (auto list : colvec_["right"]) {
				check = colpos_ + list + vec;
				if (!window(check) || tmx_->GetMapDataCheck(check)) {
					plus = false;
				}
			}
		}
		// ��
		if (0 < vec.y) {
			for (auto list : colvec_["down"]) {
				check = colpos_ + list + vec;
				if (!window(check) || tmx_->GetMapDataCheck(check)) {
					plus = false;
				}
			}
		}
		// ��
		if (0 > vec.x) {
			for (auto list : colvec_["left"]) {
				check = colpos_ + list + vec;
				if (!window(check) || tmx_->GetMapDataCheck(check)) {
					plus = false;
				}
			}
		}
		// ��
		if (0 > vec.y) {
			for (auto list : colvec_["up"]) {
				check = colpos_ + list + vec;
				if (!window(check) || tmx_->GetMapDataCheck(check)) {
					plus = false;
				}
			}
		}
		// �ړ�
		if (plus) {
			pos_ = pos_ + vec;
		}
	}
	// �����蔻��̍��W�ʒu
	colpos_ = pos_ + size_;
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
	Float2 check(colpos_);
	anim_->Draw(pos_,size_,mag_);
	for (auto list : colvec_) {
		for (auto pos : colvec_[list.first]) {
			check = colpos_ + pos;
			DrawCircle(check.x,check.y,2,0xffffff,true);
		}
	}
	//DrawCircle(colpos_.x,colpos_.y,2,0xffffff,true);
	//Object::Draw();
	//DrawGraph(pos_.x, pos_.y,animMap_[state_][animframe_].first, true);
	//DrawGraph(pos_.x,pos_.y, lpImageMng.GetID("GreenPlayer")[(*itr_).first], true);
}
