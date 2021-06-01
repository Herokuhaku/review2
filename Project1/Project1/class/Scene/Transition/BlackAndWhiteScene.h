#pragma once
#include "TransitionScene.h"
class BlackAndWhiteScene :
	public TransitionScene
{
public:	
	BlackAndWhiteScene(double limit, UniqueScene before, UniqueScene after);
	~BlackAndWhiteScene();
	//çXêV
	bool UpdateTransition(double delta)override;
	//void Draw(double delta)final;
	void DrawOwnScreen(double delta)override;
private:
};

