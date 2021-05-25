#pragma once
#include "BaseScene.h"
class TitleScene :
	public BaseScene
{
public:
	TitleScene();
	~TitleScene();
	bool Init(void)override;
	void Update(double delta)override;
	void Draw(double delta)override;
private:
	int image_;
};

