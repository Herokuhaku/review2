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
	// �X�V����
	UniqueScene Update(double delta, UniqueScene own);
	// �����̃X�N���[����Draw
	void DrawOwnScreen(double delta);
	// �����̃V�[��ID
	Scene GetSceneID(void)override { return Scene::Menu; };
private:
	UniqueScene oldScene_;
	EndGame* end_;
};

