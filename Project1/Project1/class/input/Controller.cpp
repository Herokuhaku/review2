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

bool Controller::SpecificPress(InputID id)
{
	if (!cntData_[id][static_cast<int>(Trg::Now)]) {
		return false;
	}
	for (auto cntid : cntData_) {
		if (id != cntid.first) {
			if (cntData_[cntid.first][static_cast<int>(Trg::Now)]) {
				return false;
			};
		}
	}
	return true;
}

std::pair<RingInputID*, int> Controller::GetHistroy_(void)
{
	return std::pair<RingInputID*,int>(histroy_,histroycount_-1);
}

//RingBuf* Controller::RingBuf::Create(int no)
//{
//	int count = 0;
//	auto beginB = new RingBuf{ count, nullptr, nullptr };
//	auto beforeB = beginB;
//	auto nowB = beginB;
//	for (int i = 0; i < no; i++) {
//		count++;
//		nowB = new RingBuf{ count,beforeB,nullptr };
//		beforeB->after = nowB;
//		beforeB = nowB;
//	}
//	beginB->before = nowB;
//	nowB->after = beginB;
//	return beginB;
//}
//
//void Controller::RingBuf::Destroy(RingBuf* buf)
//{
//	if (buf->before == nullptr) {
//		return;
//	}
//	buf->before->after = nullptr;
//	while (buf->after != nullptr) {
//		buf = buf->after;
//		delete buf->before;
//	}
//	delete buf;
//}
