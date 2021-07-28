#pragma once
#include "BaseScene.h"

#include <memory>
#include <list>
#include "../Obj/Object.h"
#include "../common/Vector2.h"
class GameSetScene :
	public BaseScene
{
public:
	GameSetScene(std::list<std::unique_ptr<Object>> objlist,bool gameset);
	~GameSetScene();
private:
	bool Init(void)override;
	UniqueScene Update(double delta, UniqueScene own)override;
	//void Draw(double delta)override;
	Scene GetSceneID(void)override { return Scene::GameSet; };
	void DrawOwnScreen(double delta);
	std::list<std::unique_ptr<Object>> objlist_;
	Float2 center_;
	// 0:‹S‚ÌŸ‚¿ 1:“¦‚°‚ÌŸ‚¿
	bool gameset_;
};


