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
	// 初期化
	virtual bool Init(void) = 0;
	// 更新
	virtual void Update(void) = 0;
	// コントロールする機種
	virtual CntType GetCntType(void) = 0;
	// 設定したmapを格納しているcntData_を返す
	const CntData& GetCntData(void) {
		return cntData_;
	}
	// 今押しているか
	bool Press(InputID id);
	// 押した瞬間
	bool Pressed(InputID id);
	// 離した瞬間
	bool Released(InputID id);
private:
protected:
	CntData cntData_;
	std::map<InputID, unsigned int> keyList_ = {};
};

