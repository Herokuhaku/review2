#include "Object.h"
#include <DxLib.h>
#include "../common/ImageMng.h"
#include "../Scene/SceneMng.h"
#include "../input/KeyInput.h"
#include "../input/PadInput.h"

Object::Object():speed_(2)
{
	gravity_ = 9.8f;
	gravitybool_ = true;
	jumppow_ = 0;
	jump_ = false;
	//count_ = 0;
	//v0 = 13;
	//v1 = v0*3;
	//grav_ = 0.9;
}

Object::~Object()
{
}

void Object::Draw(void)
{
	//(pos_.x, pos_.y,lpImageMng.GetAnimID(state_,animframe_), true);
}

void Object::GravityUpdate(double delta)
{
	auto window = [&](Float2& v) {
		return (v >= Float2(0, 0) && v <= Float2(lpSceneMng.GetScreenSize().x, lpSceneMng.GetScreenSize().y));
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
					pos_.y = (chip * tmx_->GetTileSize()-1).y;
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
			jumppow_ = (time_ * log(time_)) * v1;
		}
		else {
			// ����͂������
			jumppow_ = (time_ * log(time_))*5;
		}
		//jumppow_ = (0.5 * gravity_ * time_ * time_) - v0 * time_;
		
		time_ += delta;
		vec.y += jumppow_;
		// �����Ԃ�����
		bool flag_ = false;
		for (auto list : colvec_["up"]) {
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
			//time_ = v0 / gravity_ * 2;
			//jumppow_ = (0.5 * gravity_ * time_ * time_) - v0 * time_;
			//jumppow_ = (time_ * log(time_))*5;

			jumppow_ = (time_ * log(time_)) * 2;
			vec.y = 0;
		}
		// �n�ʂɂ�����
		flag_ = false;
		for (auto list : colvec_["down"]) {
			check_ = colpos_ + list + vec;
			flag_ |= tmx_->GetMapDataCheck(check_);
		}
		// ����
		if (flag_) {
			pos_.y = ((static_cast<int>(pos_.y) / static_cast<int>(tmx_->GetTileSize().y))+1) * static_cast<int>(tmx_->GetTileSize().y);
			jumppow_ = 0;
			time_ = 0;
			jump_ = false;
		}
		flag_ = false;
		// �W�����v����(�����鏈�����܂�)
		for (auto list : colvec_["down"]) {
			check_ = colpos_ + list + vec;
			flag_ |= tmx_->GetMapDataCheck(check_);
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
			check_.y+=speed_ *2;
			flag_ &= !tmx_->GetMapDataCheck(check_);
		}
		if (flag_) {
			//time_ = v0 / gravity_  *2;
			//jumppow_ = (0.5 * gravity_ * time_ * time_) - v0 * time_;
			time_ = 1;
			jumppow_ = (time_ * log(time_));
			jump_ = true;
		}
	}
}