#include "Player.h"

#include "../Scene/SceneMng.h"
#include "../common/ImageMng.h"
#include "../common/AnimationMng.h"
#include "../common/Raycast.h"
#include "../input/KeyInput.h"
#include "../input/PadInput.h"
#include "../../_debug/_DebugDispOut.h"
#include <functional>
Player::Player()
{
}

Player::Player(CntType cntType,std::shared_ptr<TmxObj> tmx, size_t objno, Float2 pos)
{
	tmx_ = tmx;
	objectnumber_ = static_cast<int>(objno);
	pos_ = pos;
	Init(cntType);
}

Player::~Player()
{
	delete attach_;
}

bool Player::Init(CntType cntType)
{
	if (objectnumber_ == 0) {
		pltype_ = PlayerType::Ogre;
		catchflag_ = 0;
	}
	else {
		pltype_ = PlayerType::RunAway;

		catchflag_ = 1;
	}

	if (!LoadAnimation()) {
		return false;
	}
	if (cntType == CntType::Key) {
		controller_ = std::make_unique<KeyInput>();
	}
	else if (cntType == CntType::Pad) {
		controller_ = std::make_unique<PadInput>();
	}



	// キャラ動作読み込み
	rapidxml::file<> attach = "Tiled/PlayAction.tsx";
	statevec_ = attach.vecData();
	stateDoc.parse<0>(statevec_.data());
	statenode_ = stateDoc.first_node("objectList");
	attach_ = new AttachMent();

	playcommand_ = false;
	mag_ = 2;
	speed_ = 5;
	colpos_ = Float2();
	// 当たり判定をとるときに上下左右で使う点のオフセット
	std::list<Float2> flist;
	Float2 s = (size_) / 2;

	flist.emplace_back(Float2(-s.x, -s.y));
	flist.emplace_back(Float2(s.x, -s.y));
	colvec_.try_emplace("up", flist);
	flist.clear();

	flist.emplace_back(Float2(s.x, -s.y));
	flist.emplace_back(Float2(s.x, s.y));
	colvec_.try_emplace("right", flist);
	flist.clear();

	flist.emplace_back(Float2(s.x, s.y));
	flist.emplace_back(Float2(-s.x, s.y));
	colvec_.try_emplace("down", flist);
	flist.clear();

	flist.emplace_back(Float2(-s.x, s.y));
	flist.emplace_back(Float2(-s.x, -s.y));
	colvec_.try_emplace("left", flist);
	flist.clear();


	//lpImageMng.GetID("image/batu.png","failed");
	return true;
}


bool Player::LoadAnimation(void)
{
	bool rtnflag = true;
	auto check = [&rtnflag](bool flag) {
		rtnflag &= flag;
	};
	std::array<std::string,5> list = { "down" ,"left","up","right","beam"};

	// アニメーションクラスを作成(引数はアニメーションのキーになる)

	//check(lpAnimationMng.SetXml(anim_->GetKey(), "Tiled/AnimImage.tsx"));
	if (pltype_ == PlayerType::Ogre) {
		anim_ = std::make_unique<Animation>("GreenMove_demon");
		check(lpAnimationMng.SetXml(anim_->GetKey(), "Tiled/AnimImage_demon.tsx"));
	}
	else {
		anim_ = std::make_unique<Animation>("GreenMove");
		check(lpAnimationMng.SetXml(anim_->GetKey(), "Tiled/AnimImage.tsx"));
	}
	for (auto& data : list) {
		check(lpAnimationMng.SetItem(anim_->GetKey(), data));
	}
	anim_->state("down");
	size_ = lpAnimationMng.GetImageSize(anim_->GetKey());

	return rtnflag;
}

void Player::Update(double delta)
{
	// キー処理
	if (!(*controller_)(delta)) {
		return;
	}
	// プレイヤーの行動処理
	for (auto node = statenode_->first_node(); node != nullptr;node = node->next_sibling()) {
		AttachMent()(this,node);
	}

	//

	for (auto input : InputID()) {
		if (controller_->Pressed(input)) {
			(*commandhis_)[hisnum_++].first = input;
		}
	}

	anim_->Update();
}

void Player::Draw(void)
{
	Float2 check(colpos_);
	anim_->Draw(pos_,size_,mag_);

	int pos = 0;
	std::string	before = "none";
	std::string name = "none";
	auto& his = (*commandhis_);

	for (int i = 0; i < his.size(); i++) {
		name = Converter(his[i].first);
		if (name != "none") {
			DrawFormatString(pos, 700, 0xffffff, "%s  ", name.c_str());
			pos += static_cast<int>(GetFontSize() * name.size()) + 5;
		}
	}
	if (pltype_ == PlayerType::RunAway) {
		DrawString(pos_.x+size_.x/2, pos_.y-size_.y/2,"逃げ", 0xffffff);
	}
	else if (pltype_ == PlayerType::Ogre){
		DrawString(pos_.x+size_.x/2, pos_.y-size_.y/2, "鬼", 0xffffff);
	}

	if (catchflag_ == 2) {
		DrawGraph(pos_.x+size_.x/2,pos_.y+size_.y/2,lpImageMng.GetID("failed")[0],true);
	}
	//DrawCircle(pos_.x + size_.x, pos_.y + size_.y, 3, 0xffffff, true);
	//for (auto list : colvec_) {
	//	for (auto pos : colvec_[list.first]) {
	//		check = colpos_ + pos;
	//		DrawCircle(check.x,check.y,2,0xffffff,true);
	//	}
	//}
}

void Player::Draw(float mag)
{
	Float2 check(pos_.x - (size_.x * mag) / 2, pos_.y);
	anim_->Draw(check, size_, mag);
}
