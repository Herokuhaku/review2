#pragma once
#include <string>
#include "Object.h"
#include "../../Tiled/rapidxml.hpp"
#include "../../Tiled/rapidxml_utils.hpp"

struct Move {
	bool operator()(Object* obj, rapidxml::xml_node<>* node) {
		for (auto atr = node->first_attribute(); atr != nullptr; atr = atr->next_attribute()) {
			std::string name = atr->name();
			int tmp = std::atoi(atr->value());
			if (name == "x") {
				obj->pos_.x += tmp;
				return true;
			}
			else if (name == "y") {
				obj->pos_.y += tmp;
				return true;
			}
		}
		return false;
	}
};