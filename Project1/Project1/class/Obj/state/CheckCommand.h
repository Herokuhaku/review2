#pragma once
#include <vector>
#include <string>
#include "../Object.h"
#include "../../../Tiled/rapidxml.hpp"
#include "../../../Tiled/rapidxml_utils.hpp"

struct CheckCommand {
	bool operator()(Object* obj, rapidxml::xml_node<>* node) {
		std::string command_;
		int grace_ = 1;
		for (auto atr = node->first_attribute(); atr != nullptr; atr = atr->next_attribute()) {
			std::string name = atr->value();
			std::string val = atr->value();
			if (name == "commandname") {
				command_ = val;
			}
			else if (name == "key") {
				auto his = obj->controller_->GetHistroy_();
				if ((*his.first)[his.second] == Conv(val)) {
					obj->commandcount_ = grace_;
					return true;
				}
			}
		}
		return false;
	}
private:
};