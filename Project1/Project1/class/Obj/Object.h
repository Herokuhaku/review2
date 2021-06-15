#pragma once
#include <map>
#include "../common/Vector2.h"
#include "../input/Controller.h"

using AnimVector = std::vector<std::pair<int, unsigned int>>;

enum class STATE
{
	UP,	// 通常
	LEFT,
	RIGHT,
	DOWN,
	MAX
};

class Object
{
public:
	Object();
	~Object();
	virtual bool Init(CntType cntType) = 0;
	virtual void Update(void) = 0;
	virtual void Draw(void);
	bool state(const STATE state);	
	bool SetAnim(const STATE state, AnimVector& data);
protected:
	Int2 pos_;
	int speed_;
	STATE _state;

	std::unique_ptr<Controller>controller_;
	// 
	std::map<STATE, AnimVector>_animMap;// アニメーションのマップ

	//std::string _animKey;				// 名前
	unsigned int _animFrames;			// フレーム数
	unsigned int _animCount;			// 何回まわったか
};

