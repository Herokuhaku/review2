#pragma once
#include "BaseScene.h"

class GameScene:
	public BaseScene
{
public:
	GameScene();
	~GameScene();

	bool Init(void)override;
	UniqueScene Update(double delta, UniqueScene own)override;
//	void Draw(double delta)override;
	Scene GetSceneID(void)override { return Scene::Game; };
	void DrawOwnScreen(double delta);
private:
	int image_;
};

