#include "KeyInput.h"
#include <DxLib.h>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include "../input/KeyInput.h"

KeyInput::KeyInput()
{
	Init();
}

KeyInput::~KeyInput()
{
}

bool KeyInput::Init(void)
{
		keyList_.try_emplace(InputID::Up, KEY_INPUT_W);
		keyList_.try_emplace(InputID::Down, KEY_INPUT_S);
		keyList_.try_emplace(InputID::Left, KEY_INPUT_A);
		keyList_.try_emplace(InputID::Right, KEY_INPUT_D);
		keyList_.try_emplace(InputID::Btn1, KEY_INPUT_Z);
		keyList_.try_emplace(InputID::Btn2, KEY_INPUT_X);
		keyList_.try_emplace(InputID::Btn3, KEY_INPUT_C);
		keyList_.try_emplace(InputID::Escape, KEY_INPUT_ESCAPE);
		keyList_.try_emplace(InputID::Jump, KEY_INPUT_SPACE);
	for (auto id : InputID()) {
		cntData_[id].fill(false);
	}
	return true;
}

void KeyInput::Update(double delta)
{
	GetHitKeyStateAll(keyData_.data());
	// çXêV
	for (auto&& id : InputID())
	{
		cntData_[id][static_cast<int>(Trg::Old)] = cntData_[id][static_cast<int>(Trg::Now)];
		cntData_[id][static_cast<int>(Trg::Now)] = keyData_[keyList_[id]];
	}
	// óöóì¸óÕ
	bool flag = false;
	for (auto&& id : InputID()) {
		if (cntData_[id][static_cast<int>(Trg::Now)]) {
			(*histroy_)[histroycount_].second = delta;
			(*histroy_)[histroycount_++].first = id;
			flag = true;
		}
	}

	if (!flag) {
		(*histroy_)[histroycount_].second = delta;
		(*histroy_)[histroycount_++].first = InputID::Neutral;
	}

}