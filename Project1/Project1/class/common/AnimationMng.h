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

	// Anim‚ğItem‚©‚çİ’è‚·‚é(XmlItem)
	bool CheckAnim(std::string key, std::string state);
	bool SetXml(std::string key, std::string f_name);
	bool SetItem(std::string key, const std::string state);
	bool SetAnim(std::string key, const std::string state, AnimVector& data);

	int GetAnimID(std::string key, std::string state, int animframe);
	int GetAnimFrame(std::string key, std::string state, int animframe);
	int GetAnimSize(std::string key, std::string state);

	Int2 GetImageSize(std::string key);
private:
	std::map<std::string, std::map<std::string, AnimVector>> animMap_;

	TmxObj tmx_;
	std::map<std::string, XmlItem> xmlitem_;
};

