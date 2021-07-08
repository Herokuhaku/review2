#pragma once
#include <array>
#include <map>
#include <vector>
#include <string>
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
	Controller():maxcount_(60) {
		keyhistroy_.resize(maxcount_);
		for (auto& his : keyhistroy_) {
			his = InputID::Max;
		}
		histroycount_ = 0;
	};
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
	// 入力履歴と最新の位置を返す
	std::pair<std::vector<InputID>,int> GetHistroy_(void);
private:
protected:
	CntData cntData_;
	std::map<InputID, unsigned int> keyList_ = {};

	// キーボードの入力履歴
	std::vector<InputID> keyhistroy_;
	int histroycount_;
	const int maxcount_;
};

