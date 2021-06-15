#pragma once
#include <array>
#include <map>
#include "inputID.h"

enum class Trg {
	Now,
	Old,
	Max
};

enum class CntType {
	Key,
	Pad,
	Max
};

using TrgBool = std::array<bool, static_cast<size_t>(Trg::Max)>;
using CntData = std::map<InputID,TrgBool>;

class Controller
{
public:
	bool operator()() {
		if (this != nullptr) {
			Update();
		}
		return this != nullptr;
	}
	Controller() {};
	virtual ~Controller() {};
	virtual bool Init(void) = 0;
	virtual void Update(void) = 0;
	virtual CntType GetCntType(void) = 0;
	const CntData& GetCntData(void) {
		return cntData_;
	}
	bool Press(InputID id);
	bool Pressed(InputID id);
	bool Released(InputID id);
private:
protected:
	CntData cntData_;
	std::map<InputID, unsigned int> keyList_ = {};
};

