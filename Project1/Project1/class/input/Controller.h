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
private:
protected:
	CntData cntData_;
	std::map<InputID, unsigned int> keyList_ = {};
};

