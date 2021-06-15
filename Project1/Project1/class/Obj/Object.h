#pragma once
#include "../common/Vector2.h"
#include "../input/Controller.h"

class Object
{
public:
	Object();
	~Object();
	void Update(void);
	void Draw(void);
private:
	bool Init(void);
	Int2 pos_;
	int speed_;
	std::unique_ptr<Controller>controller_;
};

