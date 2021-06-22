#include "ImageMng.h"
#include <DxLib.h>
#include <assert.h>
const VecInt& ImageMng::GetID(std::string key)
{
	return GetID(key,key);
}

const VecInt& ImageMng::GetID(std::string f_name, std::string key)
{
	if (imageMap_.find(key) == imageMap_.end()){
		imageMap_[key].resize(1);
		imageMap_[key][0] = LoadGraph(f_name.c_str());
	}
	return imageMap_[key];
}

const VecInt& ImageMng::GetID(std::string f_name, std::string key, Int2 divSize, Int2 divCnt)
{
	if (imageMap_.find(key) == imageMap_.end()){
		imageMap_[key].resize(static_cast<__int64>(divCnt.x) * divCnt.y);

		int assert_ = LoadDivGraph(f_name.c_str(), divCnt.x * divCnt.y, divCnt.x, divCnt.y, divSize.x,divSize.y, &imageMap_[key][0]);
		assert(assert_ != -1 && "パスの先に画像がありません");
	}
	return imageMap_[key];
}

const VecInt& ImageMng::ChangeID(std::string key)
{
	return ChangeID(key,key);
}

const VecInt& ImageMng::ChangeID(std::string f_name, std::string key)
{
	imageMap_[key].resize(1);
	imageMap_[key][0] = LoadGraph(f_name.c_str());

	return imageMap_[key];
}

const VecInt& ImageMng::ChangeID(std::string f_name, std::string key, Int2 divSize, Int2 divCnt)
{
	imageMap_[key].resize(static_cast<__int64>(divCnt.x) * divCnt.y);

	int assert_ = LoadDivGraph(f_name.c_str(), divCnt.x * divCnt.y, divCnt.x, divCnt.y, divSize.x, divSize.y, &imageMap_[key][0]);
	assert(assert_ != -1 && "パスの先に画像がありません");
	return imageMap_[key];
}

bool ImageMng::CheckAnim(std::string key,STATE state)
{
	if (animMap_[key].find(state) != animMap_[key].end()) {
		return true;
	}
	return false;
}

bool ImageMng::SetXml(std::string f_name)
{
	XmlItem tmpxml = tmx_.LoadXmlItem(f_name);
	for (auto tmp : tmpxml.data_) {
		xmlitem_.data_.try_emplace(tmp.first,tmp.second);
	}
	for (auto tmp : tmpxml.item_) {
		xmlitem_.item_.try_emplace(tmp.first, tmp.second);
	}
	for (auto tmp : tmpxml.loop_) {
		xmlitem_.loop_.try_emplace(tmp.first, tmp.second);
	}

	return true;
}

bool ImageMng::SetItem(std::string key,const STATE state, std::string dir)
{
	AnimVector data;
	int frame = 0;
	for (auto& item : xmlitem_.data_[dir]) {
		frame += item.second;
		data.emplace_back(lpImageMng.GetID(xmlitem_.item_["name"])[item.first], frame);
	}
	if (xmlitem_.loop_[dir] == -1) {
		data.emplace_back(-1, -1);
	}
	SetAnim(key,state, data);

	return true;
}

bool ImageMng::SetAnim(std::string key,const STATE state, AnimVector& data)
{
	return animMap_[key].try_emplace(state, std::move(data)).second;;
}

int ImageMng::GetAnimID(std::string key,STATE state,int animframe)
{
	return animMap_[key][state][animframe].first;
}

int ImageMng::GetAnimFrame(std::string key,STATE state, int animframe)
{
	return animMap_[key][state][animframe].second;
}

int ImageMng::GetAnimSize(std::string key,STATE state)
{
	return animMap_[key][state].size();
}

ImageMng::ImageMng()
{
}

ImageMng::~ImageMng()
{
}
