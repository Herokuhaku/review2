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
		obj->gracetime_ = 1;
		bool rtnflag = false;
		for (auto atr = node->first_attribute(); atr != nullptr; atr = atr->next_attribute()) {
			std::string name = atr->name();
			std::string val = atr->value();
			if (name == "commandname") {
				command_ = val;
			}
			else if (name == "key") {
				auto his = obj->controller_->GetHistroy_();
				auto key = Converter(val);
				if (obj->controller_->SpecificPress(key) && (*his.first)[his.second].first == key) {
					obj->commandcount_ = obj->grace_;
					rtnflag = true;
				}
			}
			else if (name == "gracetime") {
				if (stod(val) <= 0) {
					rtnflag = false;
				}
			}
		}
		return rtnflag;
	}
private:
};