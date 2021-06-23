#pragma once
#include <map>
#include "../common/Vector2.h"
#include "../input/Controller.h"
#include "../../Tiled/TmxObj.h"
#include "../Animation/Animation.h"

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
	virtual void Update(void) = 0;
	// 描画
	virtual void Draw(void);
protected:
	//TmxObj tmx_;
	//XmlItem xmlitem_;

	Int2 pos_;
	Int2 size_;
	int speed_;
	std::unique_ptr<Controller>controller_;
	// 
	std::unique_ptr<Animation> anim_;
};

