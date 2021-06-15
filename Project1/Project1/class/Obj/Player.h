#pragma once
#include "Object.h"
class Player :
	public Object
{
public:
	Player();
	Player(CntType cntType);
	~Player();
	void Update(void)override;
	void Draw(void);
private:
	bool Init(CntType cntType)override;
};