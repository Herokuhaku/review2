#include "Object.h"
#include <DxLib.h>
#include "../common/ImageMng.h"
#include "../Scene/SceneMng.h"
#include "../input/KeyInput.h"
#include "../input/PadInput.h"

Object::Object():speed_(2),commandhis_(new RingInputID(180))
{
	v1 = 25;
	gravity_ = v1;
	gravitybool_ = true;
	jumppow_ = 0;
	jump_ = false;
	grace_ = 0;
	gracetime_ = 0;
	commandcount_ = 0;
	//commandhis_ = RingInputID(180);
	hisnum_ = 0;
}

Object::~Object()
{
	delete commandhis_;
}

void Object::Draw(void)
{
	//(pos_.x, pos_.y,lpImageMng.GetAnimID(state_,animframe_), true);
}

void Object::GravityUpdate(double delta)
{

	colpos_ = pos_ + size_;
	// window�̃T�C�Y�ɓ����Ă��邩�ǂ���
	auto window = [&](Float2& v) {
		return (v >= v.ZERO && v <= Float2(lpSceneMng.GetScreenSize().x, lpSceneMng.GetScreenSize().y));
	};
	// �x�N�g���̓����蔻��p
	auto checkMove = [&](Float2 moveVec) {
		Raycast::Ray ray = { Float2(pos_.x + size_.x,pos_.y + size_.y), moveVec };
		//_dbgDrawLine(ray.p.x, ray.p.y, ray.p.x + ray.v.x, ray.p.y + ray.v.y, 0x00ff00);
		for (auto col : tmx_->GetColList()) {
			//_dbgDrawBox(col.first.x, col.first.y,
			//col.first.x + col.second.x, col.first.y + col.second.y, 0xffffff, false);
			if (raycast_.CheckCollision(ray, col)) {
				return false;
			}
		}
		return true;
	};


	// ���܂������̑Ή�
	Float2 check_(colpos_);
	bool flag_ = false;
	for (auto list : colvec_["down"]) {
		check_ = colpos_ + list;
		flag_ |= tmx_->GetMapDataCheck(check_);
	}
	if (flag_) {
		for (auto list : colvec_["down"]) {
			check_ = colpos_ + list;
			if (tmx_->GetMapDataCheck(check_)) {
				do {
					Int2 chip = (Int2(pos_) / tmx_->GetTileSize());
					pos_.y = static_cast<float>((chip * tmx_->GetTileSize()-1).y);
					colpos_ = pos_ + size_;
					check_ = colpos_ + list;
				} while (tmx_->GetMapDataCheck(check_));
			}
		}
	}
	if (!gravitybool_) {
		return;
	}
	Float2 vec(0,0);

	bool plus = true;
	// �W�����v��
	if (jump_) {
		// �W�����v���͑���(-�͏�����@( < 0))
		if (jumppow_ < 0) {
			jumppow_ = static_cast<float>((time_ * log(time_)) * v1);
		}
		else {
			// ����͂������
			jumppow_ = static_cast<float>((time_ * log(time_))*gravity_);
		}
		//jumppow_ = (0.5 * gravity_ * time_ * time_) - v0 * time_;
		
		time_ += delta;
		vec.y += jumppow_;
		// �����Ԃ�����
		bool flag_ = false;
		for (auto& list : colvec_["up"]) {
			check_ = colpos_ + list + vec;
			if (window(check_)) {
				flag_ |= tmx_->GetMapDataCheck(check_);
			}
			else {
				// �E�B���h�E����o��ꍇ�̓t���O�𗧂Ăė����鏈���Ɉڍs����
				flag_ = true;
			}
		}
		// ����
		if (flag_) {
			if (time_ < 1) {
				time_ = 1.1;
			}
			jumppow_ = static_cast<float>((time_ * log(time_)) * gravity_);
			vec.y += 1;
		}
		// �n�ʂɂ�����
		flag_ = false;
		for (auto list : colvec_["down"]) {
			check_ = colpos_ + list + vec;
			flag_ |= tmx_->GetMapDataCheck(check_);
		}


		// ����
		if (flag_) {
			pos_.y = static_cast<float>(((static_cast<int>(pos_.y) / static_cast<int>(tmx_->GetTileSize().y))+1) * static_cast<int>(tmx_->GetTileSize().y));
			jumppow_ = 0;
			time_ = 0;
			jump_ = false;
			//vec.y = 0;
		}
		flag_ = false;
		// �W�����v����(�����鏈�����܂�)
		for (auto& list : colvec_["down"]) {
			check_ = colpos_ + list + vec;
			flag_ |= tmx_->GetMapDataCheck(check_);
		}
		// �����Ă��邩����
		if (time_ > 1) {
			flag_ |= !checkMove(vec);
		}
		if (!flag_) {
 			pos_ += vec;
		}
	}
	else {
		// �W�����v���Ă��Ȃ��̂ɑ��ꂪ�Ȃ�������B
		flag_ = true;
		for (auto list : colvec_["down"]) {
			check_ = colpos_ + list;
			//check_.y +=speed_ *2;
			flag_ &= !tmx_->GetMapDataCheck(check_);
		}
		if (flag_) {
			//time_ = v0 / gravity_  *2;
			//jumppow_ = (0.5 * gravity_ * time_ * time_) - v0 * time_;
			time_ = 1;
			jumppow_ = static_cast<float>((time_ * log(time_)));
			jump_ = true;
		}
	}
	if (vec.y > lpSceneMng.GetScreenSize().y) {
		time_ = 1;
	}
}