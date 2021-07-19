#pragma once
#include <string>
#include "../Object.h"
#include "../../../Tiled/rapidxml.hpp"
#include "../../../Tiled/rapidxml_utils.hpp"

struct Jump {
	bool operator()(Object* obj, rapidxml::xml_node<>* node) {
		if (obj->jump_) {
			return false;
		}
		for (auto atr = node->first_attribute(); atr != nullptr; atr = atr->next_attribute()) {
			std::string name = atr->name();
			double tmp = std::atof(atr->value());
			if (name == "time") {
				obj->time_ = tmp;
			}
		}
		{
		obj->jump_ = true;
			return true;
		}
		return false;
	}
};