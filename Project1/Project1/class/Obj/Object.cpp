#include "Object.h"
#include <DxLib.h>
#include "../common/ImageMng.h"
#include "../Scene/SceneMng.h"
#include "../input/KeyInput.h"
#include "../input/PadInput.h"

Object::Object():speed_(2),commandhis_(new RingInputID(180))
{
	pltype_ = PlayerType::Non;
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

void Object::Draw(float mag)
{
}

void Object::GravityUpdate(double delta)
{

	colpos_ = pos_ + size_;
	// windowのサイズに入っているかどうか
	auto window = [&](Float2& v) {
		return (v >= v.ZERO && v <= Float2(lpSceneMng.GetScreenSize().x, lpSceneMng.GetScreenSize().y));
	};
	// ベクトルの当たり判定用
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
	// ジャンプ中
	if (jump_) {
		// ジャンプ上りは速く(-は上方向　( < 0))
		if (jumppow_ < 0) {
			jumppow_ = static_cast<float>((time_ * log(time_)) * v1);
		}
		else {
			// 下りはゆっくり
			jumppow_ = static_cast<float>((time_ * log(time_))*gravity_);
		}
		//jumppow_ = (0.5 * gravity_ * time_ * time_) - v0 * time_;
		
		time_ += delta;
		vec.y += jumppow_;
		// 頭をぶつけたら
		bool flag_ = false;
		for (auto& list : colvec_["up"]) {
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
			if (time_ < 1) {
				time_ = 1.1;
			}
			jumppow_ = static_cast<float>((time_ * log(time_)) * gravity_);
			vec.y += 1;
		}
		// 地面についたら
		flag_ = false;
		for (auto list : colvec_["down"]) {
			check_ = colpos_ + list + vec;
			flag_ |= tmx_->GetMapDataCheck(check_);
		}


		// 判定
		if (flag_) {
			pos_.y = static_cast<float>(((static_cast<int>(pos_.y) / static_cast<int>(tmx_->GetTileSize().y))+1) * static_cast<int>(tmx_->GetTileSize().y));
			jumppow_ = 0;
			time_ = 0;
			jump_ = false;
			//vec.y = 0;
		}
		flag_ = false;
		// ジャンプ処理(落ちる処理も含む)
		for (auto& list : colvec_["down"]) {
			check_ = colpos_ + list + vec;
			flag_ |= tmx_->GetMapDataCheck(check_);
		}
		// 落ちているか判定
		if (time_ > 1) {
			flag_ |= !checkMove(vec);
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

PlayerType Object::GetPlayerType(void)
{
	return pltype_;
}

void Object::SetAnimationState(std::string str)
{
	anim_->state(str);
}

std::string Object::GetNowAnimationName(void)
{
	return anim_->GetState();
}

int Object::GetObjectNum(void)
{
	return objectnumber_;
}

Float2 Object::GetPos(void)
{
	return pos_;
}

void Object::SetPos(Float2 pos)
{
	pos_ = pos;
}

Float2 Object::GetSize(void)
{
	return size_;
}

void Object::SetCatch(int num)
{
	catchflag_ = num;
}

int Object::GetCatch(void)
{
	return catchflag_;
}

void Object::ClearCommandHistory(void)
{
	commandhis_->ClearRing();
}
