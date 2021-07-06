#pragma once
#include <string>
#include "Object.h"
#include "../../_debug/_DebugDispOut.h"
#include "../../Tiled/rapidxml.hpp"
#include "../../Tiled/rapidxml_utils.hpp"

struct ColisionCheck {
	bool operator()(Object* obj, rapidxml::xml_node<>* node) {
		Float2 vec(0, 0);
		Float2 size;
		float speed = 0;
		auto checkMove = [&](Float2 moveVec) {
			Raycast::Ray ray = { { obj->pos_ + obj->size_ }, moveVec };
			_dbgDrawLine(ray.p.x, ray.p.y, ray.p.x + ray.v.x, ray.p.y + ray.v.y, 0x00ff00);
			for (auto col : obj->tmx_->GetColList()) {
				_dbgDrawBox(col.first.x, col.first.y,
				col.first.x + col.second.x, col.first.y + col.second.y, 0xffffff, false);
				if (obj->raycast_.CheckCollision(ray, col)) {
					return false;
				}
			}
			return true;
		};

		for (auto atr = node->first_attribute(); atr != nullptr; atr = atr->next_attribute()) {
			std::string name = atr->name();
			std::string tmp = atr->value();
			if (name == "speed") {
				speed = atoi(tmp.c_str());
			}
			if (name == "width") {
				vec.x = atoi(tmp.c_str());
			}
		}

		if (checkMove(vec)) {
			return true;
		}
		return false;
	}
};


