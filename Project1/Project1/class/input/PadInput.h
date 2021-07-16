#pragma once
#include "Controller.h"
#include <DxLib.h>
class PadInput :
	public Controller
{
public:
	PadInput();
	~PadInput();
	bool Init(void)override;

	void Update(double delta)override;
	void StickUpdate(void);
	CntType GetCntType(void)override{
		return CntType::Pad;
	}
private:
	// xbox�R���g���[���[�̏��
	XINPUT_STATE input_ = {};
	// �����݂�pad�̐�
	static int count_;
	// ������padid
	int padid_;
};

