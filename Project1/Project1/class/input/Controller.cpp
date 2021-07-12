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

std::pair<RingInputID*, int> Controller::GetHistroy_(void)
{
	return std::pair<RingInputID*,int>(histroy_,histroycount_-1);
}

RingBuf* Controller::Create(int no)
{
	//int count = 0;
	//auto beginB = new RingBuf{ count, nullptr, nullptr };
	//auto beforeB = beginB;
	//auto nowB = beginB;
	//for (int i = 0; i < no; i++) {
	//	count++;
	//	nowB = new RingBuf{ count,beforeB,nullptr };
	//	beforeB->next = nowB;
	//	beforeB = nowB;
	//}
	//beginB->before = nowB;
	//nowB->next = beginB;
	//return beginB;
	return nullptr;
}

//RingBuf* Controller::Create(int no)
//{
//
//}
//
//Controller::RingBuf* Controller::Create(int no)
//{
//	int count = 0;
//	auto beginB = new RingBuf{ count, nullptr, nullptr };
//	auto beforeB = beginB;
//	auto nowB = beginB;
//	for (int i = 0; i < no; i++) {
//		count++;
//		nowB = new RingBuf{ count,beforeB,nullptr };
//		beforeB->next = nowB;
//		beforeB = nowB;
//	}
//	beginB->before = nowB;
//	nowB->next = beginB;
//	return beginB;
//}
