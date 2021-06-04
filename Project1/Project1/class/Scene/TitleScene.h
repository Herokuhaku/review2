#pragma once
#include "BaseScene.h"
class TitleScene :
	public BaseScene
{
public:
	TitleScene();
	~TitleScene();
private:
	bool Init(void)override;
	UniqueScene Update(double delta, UniqueScene own)override;
	//void Draw(double delta)override;
	Scene GetSceneID(void)override { return Scene::Title; };
	void DrawOwnScreen(double delta);
private:
};

