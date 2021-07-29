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
					if ((*his.first)[his.second - count - obj->grace_].first == key) {
						rtnflag_ = true;
						while ((*his.first)[his.second - count - obj->grace_].first == key) {
							count++;
							time += (*his.first)[his.second - count - obj->grace_].second;
						}
						obj->gracetime_ += time;
						obj->grace_ += count;
						break;
					}
					// �L�[�Ƃ͈Ⴄ���A�O�t���[���Ɠ����ꍇ
					else if ((*his.first)[his.second - obj->grace_ + 1].first == (*his.first)[his.second - count - obj->grace_].first) {
						count++;
						time += (*his.first)[his.second - count - obj->grace_].second;
						continue;
					}
					// �j���[�g����(�ړI�̃L�[�ł͂Ȃ�)�̏ꍇ
					else if ((*his.first)[his.second - count - obj->grace_].first == InputID::Neutral) {
						count++;
						time += (*his.first)[his.second - count - obj->grace_].second;
						continue;
					}
					// ������Ԃ̏ꍇ
					else if ((*his.first)[his.second - count - obj->grace_].first == InputID::Max) {
						break;
					}
					// �S���ʂ̃L�[�������痚��������
					else {
						(*obj).controller_->ResetHistroy();
						rtnflag_ = false;
						break;
					}
					count++;
					time += (*his.first)[his.second - count - obj->grace_].second;
				}
			}
			else if (name == "check") {
				if (val == "clear") {
					if (command_ == "beam") {
						(*obj).anim_->state(command_);
					}
					else if (command_ == "bullet") {

					}
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