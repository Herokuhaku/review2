#pragma once
#include <string>
#include "../Object.h"
#include "../../input/inputID.h"
#include "../../../Tiled/rapidxml.hpp"
#include "../../../Tiled/rapidxml_utils.hpp"

struct Command {
	bool operator()(Object* obj, rapidxml::xml_node<>* node) {
		bool rtnflag_ = false;
		std::string command_;

		InputID key = InputID::Max;
		for (auto atr = node->first_attribute(); atr != nullptr; atr = atr->next_attribute()) {
			std::string name = atr->name();
			std::string val = atr->value();
			auto his = obj->controller_->GetHistroy_();
			if (name == "key") {
				key = Converter(val);
			}
			else if (name == "gracetime") {
				int count = 0;
				double time = 0;
				double alltime = std::stod(val);
				while (time < alltime) {
					// �ړI�̃L�[�������Ă�����
					if (his.first[his.second - count - obj->grace_].first == key) {
						rtnflag_ = true;
						while (his.first[his.second - count - obj->grace_].first == key) {
							count++;
							time += his.first[his.second - count - obj->grace_].second;
						}
						obj->gracetime_ += time;
						obj->grace_ += count;
						break;
					}
					// �L�[�Ƃ͈Ⴄ���A�O�t���[���Ɠ�����������
					else if (his.first[his.second - obj->grace_ + 1].first == his.first[his.second - count - obj->grace_].first) {
						count++;
						time += his.first[his.second - count - obj->grace_].second;
						continue;
					}
					// �j���[�g������������
					else if (his.first[his.second - count - obj->grace_].first == InputID::Neutral) {
						count++;
						time += his.first[his.second - count - obj->grace_].second;
						continue;
					}
					else if (his.first[his.second - count - obj->grace_].first == InputID::Max) {
						break;
					}
					// �S���ʂ̃L�[�������痚��������
					else {
						(*obj).controller_->ResetHistroy();
						rtnflag_ = false;
						break;
					}
					count++;
					time += his.first[his.second - count - obj->grace_].second;
				}
			}
			//else if (name == "grace") {
			//	for (int i = 0; i < atoi(val.c_str()); i++) {
			//		// �ړI�̃L�[�������Ă�����
			//		if (his.first[his.second - i - obj->grace_].first == key) {
			//			rtnflag_ = true;
			//			while (his.first[his.second-i-obj->grace_].first == key) {
			//				i++;
			//			}
			//			obj->grace_ += i;
			//			break;
			//		}
			//		else if(his.first[his.second  - obj->grace_+1].first == his.first[his.second - i - obj->grace_].first){
			//			continue;
			//		}
			//		else if (his.first[his.second - i - obj->grace_].first == InputID::Neutral) {
			//			continue;
			//		}
			//		else {
			//			(*obj).controller_->ResetHistroy();
			//			rtnflag_ = false;
			//		}
			//	}
			//	if (!rtnflag_) {
			//		// �P�\�܂łɂȂ�������R�}���h�𖳌�������
			//		(*obj).controller_->ResetHistroy();
			//	}
			//}
			else if (name == "check") {
				if (val == "clear") {
					(*obj).anim_->state(command_);
					(*obj).controller_->ResetHistroy();
					//(*obj).playcommand_ = true;
					return true;
				}
			}else if (name == "commandname") {
				command_ = val;
			}
		}
		return rtnflag_;
	}
private:
};