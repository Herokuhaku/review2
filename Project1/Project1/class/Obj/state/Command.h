#pragma once
#include <string>
#include "../Object.h"
#include "../../../Tiled/rapidxml.hpp"
#include "../../../Tiled/rapidxml_utils.hpp"

struct Command {
	bool operator()(Object* obj, rapidxml::xml_node<>* node) {
		bool rtnflag_ = false;
		std::string command_;
		int grace_ = 1;
		for (auto atr = node->first_attribute(); atr != nullptr; atr = atr->next_attribute()) {
			std::string name = atr->value();
			std::string val = atr->value();
			InputID key;
			auto his = obj->controller_->GetHistroy_();
			if (name == "key") {
				key = Conv(val);
			}
			else if (name == "grace") {
				for (int i = 0; i < atoi(val.c_str()); i++) {
					if ((*his.first)[his.second - i - grace_] == key) {
						rtnflag_ = true;
					}
				}
			}
		}
		return rtnflag_;
	}
private:
};