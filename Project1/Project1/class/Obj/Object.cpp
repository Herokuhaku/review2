#include "Object.h"
#include <DxLib.h>
#include "../common/ImageMng.h"
#include "../Scene/SceneMng.h"
#include "../input/KeyInput.h"
#include "../input/PadInput.h"

Object::Object():speed_(2)
{
	gravity_ = 2.0f;
	gravitybool_ = true;
	jumppow_ = 0;
	jump_ = false;
}

Object::~Object()
{
}

void Object::Draw(void)
{
	//(pos_.x, pos_.y,lpImageMng.GetAnimID(state_,animframe_), true);
}

void Object::GravityUpdate(void)
{
	auto window = [&](Float2& v) {
		return (v >= Float2(0, 0) && v <= Float2(lpSceneMng.GetScreenSize().x, lpSceneMng.GetScreenSize().y));
	};

	// 埋まった時の対応
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
	// ジャンプ中
	if (jump_) {
		if (jumppow_ < 15) {
			jumppow_ += gravity_;
		}

		vec.y += jumppow_;
		// 頭をぶつけたら
		bool flag_ = false;
		for (auto list : colvec_["up"]) {
			check_ = colpos_ + list + vec;
			if (window(check_)) {
				flag_ |= tmx_->GetMapDataCheck(check_);
			}
			else {
				// ウィンドウから出る場合はフラグを立てて落ちる処理に移行する
				flag_ = true;
			}
		}
		// 判定
		if (flag_) {
			jumppow_ = 2;
			vec.y = 0;
		}
		// 地面についたら
		flag_ = false;
		for (auto list : colvec_["down"]) {
			check_ = colpos_ + list + vec;
			flag_ |= tmx_->GetMapDataCheck(check_);
		}
		// 判定
		if (flag_) {
			jumppow_ = 0;
			jump_ = false;
		}
		flag_ = false;
		// ジャンプ処理(落ちる処理も含む)
		for (auto list : colvec_["down"]) {
			check_ = colpos_ + list + vec;
			flag_ |= tmx_->GetMapDataCheck(check_);
		}
		if (!flag_) {
			pos_ += vec;
		}
	}
	else {
		// ジャンプしていないのに足場がなかったら。
		flag_ = true;
		for (auto list : colvec_["down"]) {
			check_ = colpos_ + list;
			check_.y+=speed_;
			flag_ &= !tmx_->GetMapDataCheck(check_);
		}
		if (flag_) {
 			jumppow_ = 0;
			jump_ = true;
		}
	}

}