#pragma once
#include <map>
#include <string>
#include "Vector2.h"
#include "../../Tiled/TmxObj.h"
#include "../Animation/Animation.h"

#define lpAnimationMng AnimationMng::GetInstance()

class AnimationMng
{
public:
	static AnimationMng& GetInstance() {
		static AnimationMng sInstance;
		return sInstance;
	}

	// AnimÇItemÇ©ÇÁê›íËÇ∑ÇÈ(XmlItem)
	bool CheckAnim(std::string key, STATE state);
	bool SetXml(std::string key, std::string f_name);
	bool SetItem(std::string key, const STATE state, std::string dir);
	bool SetAnim(std::string key, const STATE state, AnimVector& data);

	int GetAnimID(std::string key, STATE state, int animframe);
	int GetAnimFrame(std::string key, STATE state, int animframe);
	int GetAnimSize(std::string key, STATE state);

	Int2 GetImageSize(std::string key);
private:
	std::map<std::string, std::map<STATE, AnimVector>> animMap_;

	TmxObj tmx_;
	std::map<std::string, XmlItem> xmlitem_;
};

