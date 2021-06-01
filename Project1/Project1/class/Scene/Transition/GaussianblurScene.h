#pragma once
#include "TransitionScene.h"
class GaussianblurScene :
	public TransitionScene
{
public:
	GaussianblurScene(double limit, UniqueScene before, UniqueScene after);
	~GaussianblurScene();
	// çXêV
	bool UpdateTransition(double delta)override;
	//void Draw(double delta)final;
	void DrawOwnScreen(double delta)override;
private:
};

