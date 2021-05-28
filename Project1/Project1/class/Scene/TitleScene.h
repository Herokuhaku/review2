#pragma once
#include "BaseScene.h"
class TitleScene :
	public BaseScene
{
public:
	TitleScene();
	~TitleScene();
	bool Init(void)override;
	UniqueScene Update(double delta, UniqueScene own)override;
	void Draw(double delta)override;
private:
	int image_;
};

