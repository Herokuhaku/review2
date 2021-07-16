#pragma once
#include "Controller.h"
class KeyInput :
	public Controller
{
public:
	KeyInput();
	~KeyInput();
	bool Init(void)override;
	void Update(double delta)override;
	CntType GetCntType(void)override{
		return CntType::Key;
	}
private:
	std::array<char, 256> keyData_ = {};
};