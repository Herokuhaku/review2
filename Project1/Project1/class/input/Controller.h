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

struct RingBuf {
	InputID id;
	RingBuf* before = nullptr;
	RingBuf* after = nullptr;
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
	Controller() {
		histroy_ = new RingInputID(60);
		histroycount_ = 0;
	};
	virtual ~Controller() {};
	// ������
	virtual bool Init(void) = 0;
	// �X�V
	virtual void Update(void) = 0;
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
	std::pair<RingInputID*,int> GetHistroy_(void);
	// histroy�̒��g������������
	void ResetHistroy(void) { histroy_->ClearRing(); };
	
	RingBuf* Create(int no);

private:
protected:
	CntData cntData_;
	std::map<InputID, unsigned int> keyList_ = {};

	// �L�[�{�[�h�̓��͗���
	int histroycount_;
	
	RingInputID* histroy_;
};

