#pragma once
//#include <string>
//#include <functional>
//#include <map>
//#include "Player.h"
//#include "../../Tiled/rapidxml.hpp"
//#include "../../Tiled/rapidxml_utils.hpp"
#include <functional>
#include <map>
#include "Move.h"
#include "CheckKey.h"

struct AttachMent {
	bool operator()(Object* obj,rapidxml::xml_node<>* node) {

		for (auto attach = node->first_node(); attach != nullptr; attach = attach->next_sibling()) {
			// ���O���Ƃ�
			std::string attachName = attach->first_attribute("name")->value();
			// �������o�^����Ă�����
			if (attach_.find(attachName) != attach_.end()) {
				// ���������삵�Ȃ������玟�ɉ��
				if (!attach_[attachName](obj, attach)) {
					continue;
				}

				//
				auto attachment = attach->first_node();
				if (attachment != nullptr) {
					std::string name = attachment->first_attribute("name")->value();
					if (attach_.count(name)) {
						attach_[name](obj, attachment);
						if (!(*this)(obj,attachment)) {
							return false;
						}
					}
				}
			}
		}
		return true;
	}
private:
	std::map<std::string, std::function<bool(Object* obj, rapidxml::xml_node<>* node)>> attach_ = {
		{"Move",Move()},
		{"CheckKey",CheckKey()}
	};
};