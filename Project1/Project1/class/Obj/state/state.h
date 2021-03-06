#pragma once
//#include <string>
#include <functional>
#include <map>
#include "Move.h"
#include "CheckKey.h"
#include "SetAnime.h"
#include "Jump.h"
#include "ColisionCheck.h"
#include "CheckCommand.h"
#include "Command.h"
#include "../../common/AnimationMng.h"
#include "../../../_debug/_DebugConOut.h"

struct AttachMent {
	bool operator()(Object* obj,rapidxml::xml_node<>* node) {

		for (auto attach = node->first_node(); attach != nullptr; attach = attach->next_sibling()) {
			// 名前をとる
			std::string attachName = attach->first_attribute("name")->value();
			// 動きが登録されていたら
			if (attach_.find(attachName) != attach_.end()) {
				TRACE("%s \n",attachName.c_str());
				// 正しく動作しなかったら次に回る
				if (!attach_[attachName](obj, attach)) {
					continue;
				}

				if (!(*this)(obj, attach)) {
					return false;
				}

			}
		}
		return true;
	}
private:
	std::map<std::string, std::function<bool(Object* obj, rapidxml::xml_node<>* node)>> attach_ = {
		{"Move",Move()},
		{"CheckKey",CheckKey()},
		{"SetAnime",SetAnime()},
		{"ColisionCheck",ColisionCheck()},
		{"Jump",Jump()},
		{"CheckCommand",CheckCommand()},
		{"Command",Command()}
	};
};