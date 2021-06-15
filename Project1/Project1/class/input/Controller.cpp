#include "Controller.h"

bool Controller::Press(InputID id)
{
	return cntData_[id][static_cast<int>(Trg::Now)];
}

bool Controller::Pressed(InputID id)
{
	return cntData_[id][static_cast<int>(Trg::Now)] && !cntData_[id][static_cast<int>(Trg::Old)];
}

bool Controller::Released(InputID id)
{
	return !cntData_[id][static_cast<int>(Trg::Now)] && cntData_[id][static_cast<int>(Trg::Old)];
}