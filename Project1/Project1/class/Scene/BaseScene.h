#pragma once
class BaseScene
{
public:
	BaseScene();
	virtual ~BaseScene();
	
	virtual bool Init(void) = 0;

	virtual void Update(double delta) = 0;
	virtual void Draw(double delta) = 0;
private:
};

