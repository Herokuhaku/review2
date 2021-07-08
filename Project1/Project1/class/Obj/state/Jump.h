#pragma once
#include <string>
#include "../Object.h"
#include "../../../Tiled/rapidxml.hpp"
#include "../../../Tiled/rapidxml_utils.hpp"

struct Jump {
	bool operator()(Object* obj, rapidxml::xml_node<>* node) {
		for (auto atr = node->first_attribute(); atr != nullptr; atr = atr->next_attribute()) {
			std::string name = atr->name();
			int tmp = std::atoi(atr->value());
			if (!obj->jump_) {
				obj->jump_ = true;
				obj->time_ = 0.1;
				return true;
			}
		}
		return false;
	}
};