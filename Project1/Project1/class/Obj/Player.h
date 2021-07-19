#pragma once
#include "Object.h"

#include "state/state.h"
#include <list>

constexpr int GraphHd = 0;
constexpr int InvLimit = 1;

class Player :
	public Object
{
public:
	Player();
	Player(CntType cntType, std::shared_ptr<TmxObj> tmx,size_t objno);
	~Player();
	void Update(double delta)override;
	void Draw(void);
private:
	bool Init(CntType cntType)override;

	// アニメーションに使う画像を読み込む
	bool LoadAnimation(void);

	std::vector<char> statevec_;
	rapidxml::xml_document<> stateDoc;
	rapidxml::xml_node<>* statenode_;
	AttachMent* attach_;
};