#include "AnimationMng.h"
#include "ImageMng.h"

bool AnimationMng::CheckAnim(std::string key, std::string state)
{
	if (animMap_[key].find(state) != animMap_[key].end()) {
		return true;
	}
	return false;
}

bool AnimationMng::SetXml(std::string key, std::string f_name)
{
	XmlItem tmpxml = tmx_.LoadXmlItem(f_name);
	for (auto tmp : tmpxml.data_) {
		xmlitem_[key].data_.try_emplace(tmp.first, tmp.second);
	}
	for (auto tmp : tmpxml.item_) {
		xmlitem_[key].item_.try_emplace(tmp.first, tmp.second);
	}
	for (auto tmp : tmpxml.loop_) {
		xmlitem_[key].loop_.try_emplace(tmp.first, tmp.second);
	}

	return true;
}

bool AnimationMng::SetItem(std::string key, const std::string state)
{
	AnimVector data;
	int frame = 0;
	for (auto& item : xmlitem_[key].data_[state]) {
		frame += item.second;
		data.emplace_back(lpImageMng.GetID(xmlitem_[key].item_["name"])[item.first], frame);
	}
	if (xmlitem_[key].loop_[state] == -1) {
		data.emplace_back(-1, -1);
	}
	SetAnim(key, state, data);

	return true;
}

bool AnimationMng::SetAnim(std::string key, const std::string state, AnimVector& data)
{
	return animMap_[key].try_emplace(state, std::move(data)).second;
}

int AnimationMng::GetAnimID(std::string key, std::string state, int animframe)
{
	return animMap_[key][state][animframe].first;
}

int AnimationMng::GetAnimFrame(std::string key, std::string state, int animframe)
{
	return animMap_[key][state][animframe].second;
}

int AnimationMng::GetAnimSize(std::string key, std::string state)
{
	return static_cast<int>(animMap_[key][state].size());
}

Int2 AnimationMng::GetImageSize(std::string key)
{
	return Int2(std::atoi(xmlitem_[key].item_["width"].c_str()), std::atoi(xmlitem_[key].item_["height"].c_str()));
}