#pragma once
#include "BaseScene.h"
class TitleScene :
	public BaseScene
{
public:
	TitleScene();
	~TitleScene();
	void Update(double delta)override;
	void Draw(double delta)override;
private:
};

