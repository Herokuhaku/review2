#pragma once
#include <vector>
#include <string>
#include "../Object.h"
#include "../../input/inputID.h"
#include "../../../Tiled/rapidxml.hpp"
#include "../../../Tiled/rapidxml_utils.hpp"

struct CheckCommand {
	bool operator()(Object* obj, rapidxml::xml_node<>* node) {
		std::string command_;
		obj->grace_ = 1;
		for (auto atr = node->first_attribute(); atr != nullptr; atr = atr->next_attribute()) {
			std::string name = atr->name();
			std::string val = atr->value();
			if (name == "commandname") {
				command_ = val;
			}
			else if (name == "key") {
				auto his = obj->controller_->GetHistroy_();
				if ((*his.first)[his.second] == Converter(val)) {
					obj->commandcount_ = obj->grace_;
					return true;
				}
			}
		}
		return false;
	}
private:
};