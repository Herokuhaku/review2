#pragma once
#include "BaseScene.h"
#include <memory>
#include "../../Tiled/TmxObj.h"
#include "../Obj/Object.h"

class GameScene:
	public BaseScene
{
public:
	GameScene();
	~GameScene();

private:
	bool Init(void)override;
	UniqueScene Update(double delta, UniqueScene own)override;
	//	void Draw(double delta)override;
	Scene GetSceneID(void)override { return Scene::Game; };
	void DrawOwnScreen(double delta);

	TmxObj tmxobj_;
	Object* obj_;
};

