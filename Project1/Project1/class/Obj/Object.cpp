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
	jumppow_ = 50;
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
	if (!gravitybool_) {
		return;
	}
	Float2 vec(0,0);
	if (tmx_) {
		auto checkMove = [&](Float2&& moveVec) {
			Raycast::Ray ray = { { pos_ + size_ }, moveVec };
			for (auto col : tmx_->GetColList()) {
				if (raycast_.CheckCollision(ray, col)) {
					return false;
				}
			}
			return true;
		};
		if (checkMove(Float2{ 0.0,(gravity_ + (size_.y/2)) })) {
			vec.y += gravity_;
		}
	}
	bool plus = true;
	if (0 < vec.y) {
		auto window = [&](Float2& v) {
			return (v >= Float2(0, 0) && v <= Float2(lpSceneMng.GetScreenSize().x, lpSceneMng.GetScreenSize().y));
		};
		Float2 check(colpos_);
		for (auto list : colvec_["down"]) {
			check = colpos_ + list + (vec);
			if (!window(check) || tmx_->GetMapDataCheck(check)) {
				plus = false;
			}
		}
	}
	if (plus) {
		pos_.y += vec.y;
	}
	else if(!jump_){
		jump_ = false;
	}

	if (jump_) {
		pos_.y += jumppow_;
	}
}
