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
			else if (name == "grace") {
				for (int i = 0; i < atoi(val.c_str()); i++) {
					// 目的のキーを押していたら
					if ((*his.first)[his.second - i - obj->grace_] == key) {
						rtnflag_ = true;
						while ((*his.first)[his.second-i-obj->grace_] == key) {
							i++;
						}
						obj->grace_ += i;
						break;
					}
					else if((*his.first)[his.second  - obj->grace_+1] == (*his.first)[his.second - i - obj->grace_]){
						continue;
					}
					else if ((*his.first)[his.second - i - obj->grace_] == InputID::Neutral) {
						continue;
					}
					else {
						(*obj).controller_->ResetHistroy();
						rtnflag_ = false;
					}
				}
				if (!rtnflag_) {
					// 猶予までになかったらコマンドを無効化する
					(*obj).controller_->ResetHistroy();
				}
			}
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