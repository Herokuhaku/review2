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
	// ‰Šú‰»
	virtual bool Init(void) = 0;
	// XV
	virtual void Update(void) = 0;
	// ƒRƒ“ƒgƒ[ƒ‹‚·‚é‹@í
	virtual CntType GetCntType(void) = 0;
	// İ’è‚µ‚½map‚ğŠi”[‚µ‚Ä‚¢‚écntData_‚ğ•Ô‚·
	const CntData& GetCntData(void) {
		return cntData_;
	}
	// ¡‰Ÿ‚µ‚Ä‚¢‚é‚©
	bool Press(InputID id);
	// ‰Ÿ‚µ‚½uŠÔ
	bool Pressed(InputID id);
	// —£‚µ‚½uŠÔ
	bool Released(InputID id);
private:
protected:
	CntData cntData_;
	std::map<InputID, unsigned int> keyList_ = {};
};

