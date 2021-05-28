#pragma once
#include <memory>
#include <array>

class BaseScene;
using UniqueScene = std::unique_ptr<BaseScene>;

class BaseScene
{
public:
	BaseScene();
	virtual ~BaseScene();
	
	virtual bool Init(void) = 0;

	virtual UniqueScene Update(double delta,UniqueScene own) = 0;
	virtual void Draw(double delta) = 0;
private:
protected:
	std::array<int,2> click_;
};

