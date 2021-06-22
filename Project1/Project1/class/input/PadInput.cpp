#include "PadInput.h"

int PadInput::count_ = 1;

PadInput::PadInput()
{
	Init();
}

PadInput::~PadInput()
{
}

bool PadInput::Init(void)
{
	//keyList_.try_emplace(InputID::Up, XINPUT_BUTTON_DPAD_UP);
	//keyList_.try_emplace(InputID::Down, XINPUT_BUTTON_DPAD_DOWN);
	//keyList_.try_emplace(InputID::Left, XINPUT_BUTTON_DPAD_LEFT);
	//keyList_.try_emplace(InputID::Right, XINPUT_BUTTON_DPAD_RIGHT);
	keyList_.try_emplace(InputID::Up, 0);
	keyList_.try_emplace(InputID::Down, 0);
	keyList_.try_emplace(InputID::Left, 0);
	keyList_.try_emplace(InputID::Right, 0);
	keyList_.try_emplace(InputID::Btn1, XINPUT_BUTTON_LEFT_SHOULDER);
	keyList_.try_emplace(InputID::Btn2, XINPUT_BUTTON_RIGHT_SHOULDER);
	keyList_.try_emplace(InputID::Btn3, XINPUT_BUTTON_A);

	for (auto id : InputID()) {
		cntData_.try_emplace(id, TrgBool{ 0, 0 });
	}

	padid_ = count_++;
	return true;
}


void PadInput::Update(void)
{
	GetJoypadXInputState(padid_, &input_);

	// �{�^���̍X�V
	for (auto id : InputID())
	{
		cntData_[id][static_cast<int>(Trg::Old)] = cntData_[id][static_cast<int>(Trg::Now)];
		cntData_[id][static_cast<int>(Trg::Now)] = input_.Buttons[keyList_[id]];
	}
	// �X�e�B�b�N�̍X�V
	StickUpdate();

	if (cntData_[InputID::Btn3][static_cast<int>(Trg::Old)] == 1) {
		int i = 0;
	}
}

void PadInput::StickUpdate(void)
{
	// ���X�e�B�b�N��X��
	if (input_.ThumbLX > 30000)
	{
		cntData_[InputID::Right][static_cast<int>(Trg::Now)] = 1;
	}
	else if (input_.ThumbLX < -30000)
	{
		cntData_[InputID::Left][static_cast<int>(Trg::Now)] = 1;
	}
	else
	{
		cntData_[InputID::Left][static_cast<int>(Trg::Now)] = 0;
		cntData_[InputID::Right][static_cast<int>(Trg::Now)] = 0;
	}
	// ���X�e�B�b�N��Y��
	if (input_.ThumbLY > 30000)
	{
		cntData_[InputID::Up][static_cast<int>(Trg::Now)] = 1;
	}
	else if (input_.ThumbLY < -30000)
	{
		cntData_[InputID::Down][static_cast<int>(Trg::Now)] = 1;
	}
	else
	{
		cntData_[InputID::Down][static_cast<int>(Trg::Now)] = 0;
		cntData_[InputID::Up][static_cast<int>(Trg::Now)] = 0;
	}
}