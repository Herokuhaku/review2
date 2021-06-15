#pragma once
#include "Controller.h"
class KeyInput :
	public Controller
{
public:
	KeyInput();
	~KeyInput();
	bool Init(void)override;
	void Update(void)override;
	bool WriteConfig(void);
	bool ReadConfig(void);
	CntType GetCntType(void)override{
		return CntType::Key;
	}
private:
	std::array<char, 256> keyData_ = {};
};