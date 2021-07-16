#pragma once
#include <array>
#include <map>
#include <vector>
#include <string>
#include "inputID.h"
#include "../common/RingInputID.h"

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

struct RingBufeer {
	RingBufeer Create(int no);
	void Destroy(RingBufeer* buf);

	int id;
	RingBufeer* before = nullptr;
	RingBufeer* after = nullptr;
};

using TrgBool = std::array<bool, static_cast<size_t>(Trg::Max)>;
using CntData = std::map<InputID,TrgBool>;

class Controller
{
public:
	bool operator()(double delta) {
		if (this != nullptr) {
			Update(delta);
		}
		return this != nullptr;
	}
	Controller():histroy_(RingInputID(180*3)) {
		histroycount_ = 0;
	};
	virtual ~Controller() {
	};
	// 初期化
	virtual bool Init(void) = 0;
	// 更新
	virtual void Update(double delta) = 0;
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
	std::pair<RingInputID,int> GetHistroy_(void);
	// histroyの中身を初期化する
	void ResetHistroy(void) {
		histroy_.ClearRing();
	};
	
	struct RingBuf {
		RingBuf Create(int no);
		void Destroy(RingBuf* buf);

		int id;
		RingBuf* before = nullptr;
		RingBuf* after = nullptr;
	};

private:
protected:
	CntData cntData_;
	std::map<InputID, unsigned int> keyList_ = {};

	// キーボードの入力履歴
	int histroycount_;
	
	RingInputID histroy_;
};
