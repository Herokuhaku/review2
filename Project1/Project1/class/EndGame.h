#pragma once
#include "common/Vector2.h"

class EndGame
{
public:
	EndGame(Float2 pos);
	~EndGame();
	bool Update(void);
	bool Draw(void);
private:
	Float2 pos_;
	Float2 size_;

	int click_;
};

