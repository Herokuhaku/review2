#pragma once
#include <map>
#include "../common/Vector2.h"
#include "../input/Controller.h"
#include "../../Tiled/TmxObj.h"
#include "../Animation/Animation.h"
#include "../common/Raycast.h"

//using AnimVector = std::vector<std::pair<int,int>>;
//
//enum class STATE
//{
//	UP,	// 通常
//	LEFT,
//	RIGHT,
//	DOWN,
//	MAX
//};

class Object
{
public:
	Object();
	~Object();
	// 初期化
	virtual bool Init(CntType cntType) = 0;
	// 更新
	virtual void Update(double delta) = 0;
	// 描画
	virtual void Draw(void);
	virtual void GravityUpdate(double delta);
protected:
	//TmxObj tmx_;
	//XmlItem xmlitem_;
	Raycast raycast_;
	// 座標
	Float2 pos_;
	// 当たり判定の中心座標
	Float2 colpos_;
	std::map<std::string,std::list<Float2>> colvec_;
	Int2 size_;
	// Drawの倍率
	float mag_;
	float speed_;
	std::unique_ptr<Controller>controller_;
	// 
	std::shared_ptr<TmxObj> tmx_;
	std::unique_ptr<Animation> anim_;
	float gravity_;
	float grav_;
	bool jump_;
	bool upflag_;
	bool gravitybool_;
	float jumppow_;
	float count_;
	float v0;
	float v1;
	double time_;
};

