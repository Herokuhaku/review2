#pragma once
#include "TransitionScene.h"
class CrossOverScene :
	public TransitionScene
{
public:
	CrossOverScene(double limit,UniqueScene before,UniqueScene after);
	~CrossOverScene();
	// �X�V
	bool UpdateTransition(double delta)override;
	void Draw(double delta)final;
private:
};

