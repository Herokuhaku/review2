#pragma once
#include <map>
#include <vector>
#include <string>
#include "../common/Vector2.h"

using AnimVector = std::vector<std::pair<int, int>>;

enum class STATE
{
	up,	// 通常
	left,
	right,
	down,
	MAX
};

class Animation
{
public:
	Animation(std::string key);
	~Animation();
	bool Init(void);
	bool Update(void);
	bool Draw(Float2 pos,Int2 size,float mag = 1.0f);
	bool state(const std::string state);
	std::string GetKey(void);
private:
	std::string key_;
	std::string state_;

	int animframe_;			// フレーム数
	int animcount_;			// 何回まわったか
	//std::map<STATE, AnimVector>animMap_;// アニメーションのマップ

	//unsigned int animframe_;			// フレーム数
	//unsigned int animcount_;			// 何回まわったか
};

