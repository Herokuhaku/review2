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
};