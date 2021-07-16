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
	// ������
	virtual bool Init(void) = 0;
	// �X�V
	virtual void Update(double delta) = 0;
	// �R���g���[������@��
	virtual CntType GetCntType(void) = 0;
	// �ݒ肵��map���i�[���Ă���cntData_��Ԃ�
	const CntData& GetCntData(void) {
		return cntData_;
	}
	// �������Ă��邩
	bool Press(InputID id);
	// �������u��
	bool Pressed(InputID id);
	// �������u��
	bool Released(InputID id);
	// ���͗����ƍŐV�̈ʒu��Ԃ�
	std::pair<RingInputID,int> GetHistroy_(void);
	// histroy�̒��g������������
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

	// �L�[�{�[�h�̓��͗���
	int histroycount_;
	
	RingInputID histroy_;
};
