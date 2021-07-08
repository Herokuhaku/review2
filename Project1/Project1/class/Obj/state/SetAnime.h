#pragma once
#include <string>
#include "../Object.h"
#include "../../../Tiled/rapidxml.hpp"
#include "../../../Tiled/rapidxml_utils.hpp"


struct SetAnime {
	bool operator()(Object* obj, rapidxml::xml_node<>* node) {
		for (auto atr = node->first_attribute(); atr != nullptr; atr = atr->next_attribute()) {
			std::string name = atr->name();
			std::string tmp = atr->value();
			if (name == "state") {
				(*obj).anim_->state(tmp);
				return true;
			}
		}
		return false;
	}
};
