#pragma once
#include <DxLib.h>
#include <string>
#include "../../Scene/SceneMng.h"
#include "../Object.h"
#include "../../../_debug/_DebugDispOut.h"
#include "../../../Tiled/rapidxml.hpp"
#include "../../../Tiled/rapidxml_utils.hpp"

struct ColisionCheck {
	bool operator()(Object* obj, rapidxml::xml_node<>* node) {
		Float2 vec(0, 0);	
		Int2 windowSize = lpSceneMng.GetScreenSize();
		auto window = [&](Float2 v) {
		return (v >= Float2::ZERO && v <= Float2(windowSize));
		};
		Float2 size;
		float speed = 0;
		auto checkMove = [&](Float2 moveVec) {
			Raycast::Ray ray = { { obj->pos_ + obj->size_ }, moveVec };
			for (auto col : obj->tmx_->GetColList()) {
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
				speed = static_cast<float>(atoi(tmp.c_str()));
			}
			if (name == "width") {
				vec.x = static_cast<float>(atoi(tmp.c_str()));
				
			}
		}
		vec.x += speed;
		if (checkMove(vec) && window(obj->pos_ + obj->size_ + vec)) {
			return true;
		}
		return false;
	}
};


