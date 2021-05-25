#pragma once
#include "BaseScene.h"

class GameScene:
	public BaseScene
{
public:
	GameScene();
	~GameScene();

	bool Init(void)override;
	void Update(double delta)override;
	void Draw(double delta)override;
private:
	int image_;
};

