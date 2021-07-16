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
	// xboxコントローラーの情報
	XINPUT_STATE input_ = {};
	// 今現在のpadの数
	static int count_;
	// 自分のpadid
	int padid_;
};

