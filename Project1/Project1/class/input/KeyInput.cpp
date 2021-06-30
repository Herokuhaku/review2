#include "KeyInput.h"
#include <DxLib.h>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include "../input/KeyInput.h"

#define HEX_CH   6  //16進文字列の要素数

KeyInput::KeyInput()
{
	Init();
}

KeyInput::~KeyInput()
{
}

bool KeyInput::Init(void)
{
	if (!ReadConfig()) {
		keyList_.try_emplace(InputID::Up, KEY_INPUT_UP);
		keyList_.try_emplace(InputID::Down, KEY_INPUT_DOWN);
		keyList_.try_emplace(InputID::Left, KEY_INPUT_LEFT);
		keyList_.try_emplace(InputID::Right, KEY_INPUT_RIGHT);
		keyList_.try_emplace(InputID::Btn1, KEY_INPUT_Z);
		keyList_.try_emplace(InputID::Btn2, KEY_INPUT_X);
		keyList_.try_emplace(InputID::Btn3, KEY_INPUT_C);
		keyList_.try_emplace(InputID::Escape, KEY_INPUT_ESCAPE);
	}
	for (auto id : InputID()) {
		cntData_[id].fill(false);
	}
	return true;
}

void KeyInput::Update(void)
{
	GetHitKeyStateAll(keyData_.data());
	// 更新
	for (auto&& id : InputID())
	{
		cntData_[id][static_cast<int>(Trg::Old)] = cntData_[id][static_cast<int>(Trg::Now)];
		cntData_[id][static_cast<int>(Trg::Now)] = keyData_[keyList_[id]];
	}
}

bool KeyInput::WriteConfig(void)
{
	std::ifstream ifs("class/input/Config.txt");
	int count_ = 0;
	std::vector<int> num;
	if (ifs.fail()) {
		while (num.size() && !keyData_[KEY_INPUT_ESCAPE]) {
			DrawFormatString(0, 0,0xffffff,"%d",num.size());
			for (int key = 0; key < keyData_.size();key++) {
				if (keyData_[key]) {
					num.emplace_back(key);
				}
			}
		}
	}
	return true;
}

bool KeyInput::ReadConfig(void)
{
	std::ifstream ifs("class/input/Config.txt");
	std::string str;
	if (ifs.fail()) {
		return false;
	}
	int id = 0;
	while (getline(ifs, str)) {
		//keyList_.try_emplace(static_cast<InputID>(id++),);
	}

	return true;
}