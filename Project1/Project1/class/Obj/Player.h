#pragma once
#include "Object.h"

#include <list>

constexpr int GraphHd = 0;
constexpr int InvLimit = 1;

class Player :
	public Object
{
public:
	Player();
	Player(CntType cntType, std::shared_ptr<TmxObj> tmx);
	~Player();
	void Update(void)override;
	void Draw(void);
private:
	bool Init(CntType cntType)override;

	// アニメーションに使う画像を読み込む
	bool LoadAnimation(void);
	// 
	//std::list<std::array<int, 2>> test_;
	//std::list<std::pair<int,int>>::iterator itr_;
	//std::array<int, 2> t;
	//std::map<std::string,std::pair<int,std::list<std::array<int, 2>>>> animTbl_;
	//int animCount = 0;
	//int animPlayCount = 0;
};