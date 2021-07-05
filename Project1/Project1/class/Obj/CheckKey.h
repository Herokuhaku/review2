#pragma once
#include <string>
#include "Object.h"
#include "../../Tiled/rapidxml.hpp"
#include "../../Tiled/rapidxml_utils.hpp"

struct CheckKey {
	bool operator()(Object* obj, rapidxml::xml_node<>* node) {
		for (auto atr = node->first_attribute(); atr != nullptr; atr = atr->next_attribute()) {
			std::string name = atr->value();
			int tmp = 0;
			if (name == "CntKey") {
				//obj->controller_->
				//obj->pos_.x += std::atoi(atr->value());
			}
			else if (name == "Left") {
				tmp = obj->controller_->Press(InputID::Left);
				if (tmp == 1) {
					int i = 0;
				}
				return tmp;
				//obj->pos_.y += std::atoi(atr->value());
			}
			else if (name == "Right") {
				tmp = obj->controller_->Press(InputID::Right);	
				if (tmp == 1) {
					int i = 0;
				}
				return tmp;
			}
		}
		return false;
	}
};
