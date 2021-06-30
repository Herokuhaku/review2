#pragma once
#include "BaseScene.h"
#include "../EndGame.h"

class MenuScene :
    public BaseScene
{
public:
	MenuScene(UniqueScene old);
	~MenuScene();
	bool Init(void);
	// 更新処理
	UniqueScene Update(double delta, UniqueScene own);
	// 自分のスクリーンにDraw
	void DrawOwnScreen(double delta);
	// 自分のシーンID
	Scene GetSceneID(void)override { return Scene::Menu; };
private:
	UniqueScene oldScene_;
	EndGame* end_;
};

