#include "TmxObj.h"
#include "../_debug/_DebugConOut.h"
#include <DxLib.h>
#include "../class/common/ImageMng.h"

using rapid_node = rapidxml::xml_node<>*;
using rapid_atr = rapidxml::xml_attribute<>*;

TmxObj::TmxObj():firstGID_(0),layerSize_(0)
{
	version_["1.6.0"] = 1;
}

TmxObj::~TmxObj()
{
}

bool TmxObj::LoadTsx(std::string fileName)
{
	rapidxml::file<> xmlFile = fileName.c_str();
	tsxDoc_.parse<0>(xmlFile.data());
	// tilesetノードの取り出し
	auto tileset = tsxDoc_.first_node("tileset");

	// バージョンがkeyに存在するかを確認
	if (!CheckTiledVersion(tileset)){
		return false;
	}
	for (auto n = tsxDoc_.first_node(); n != nullptr; n = n->first_node())
	{
		// ノードがあれば名前を書きだす
		if (n) {
			if (n->name_size()) {
				TRACE("%s→ ", n->name());
			}
		}
		// アトリビュートを取り出す
		auto atr = n->first_attribute();
		// アトリビュートが存在する場合入る
		while (atr) {
			// 名前を書きだす
			if (atr->name_size()) {
				TRACE("%s ", atr->name());
			}
			// 要素を書き出す
			TRACE("%s ", atr->value());
			// mapのkeyに名前使って値を入れる
			tsxitem_[atr->name()] = atr->value();
			// 次のアトリビュートを呼ぶ
			atr = atr->next_attribute();
		}
	}

	// 全体のチップサイズ / 横のチップサイズ = 縦のチップサイズ
	std::string source = tsxitem_["source"].substr(tsxitem_["source"].find_first_of("/") + 1);
	int count = std::atoi(tsxitem_["tilecount"].c_str()) / std::atoi(tsxitem_["columns"].c_str());

	lpImageMng.GetID(
		source,
		tsxitem_["name"],
		Int2(std::atoi(tsxitem_["tilewidth"].c_str()), std::atoi(tsxitem_["tileheight"].c_str())),
		Int2(std::atoi(tsxitem_["columns"].c_str()),count));

	return true;
}

bool TmxObj::LoadTmx(std::string fileName)
{
	rapidxml::file<> xmlFile = fileName.c_str();
	tmxDoc_.parse<0>(xmlFile.data());

	auto mapnode = tmxDoc_.first_node("map");
	// バージョンがkeyに存在するかを確認
	if (!CheckTiledVersion(mapnode)){
		return false;
	}

	// tsxがあるファイルまでのパスを取る
	std::string sourcestr = fileName.substr(0,fileName.find_last_of("/")+1);
	sourcestr += mapnode->first_node("tileset")->first_attribute("source")->value();
	// TSXが読み込めたかどうか
	if (!LoadTsx(sourcestr)){
		return false;
	}
	auto mapatr = [&](std::string str) {return std::atoi(mapnode->first_attribute(str.c_str())->value()); };

	worldArea_ = Int2(mapatr("width"),mapatr("height"));
	tileSize_ = Int2(mapatr("tilewidth"), mapatr("tileheight"));
	layerSize_ = mapatr("nextlayerid")-1;
	firstGID_ = std::atoi(mapnode->first_node("tileset")->first_attribute("firstgid")->value());

	if (!SetMap()) {
		return false;
	}
	return true;
}

XmlItem TmxObj::LoadXmlItem(std::string fileName)
{
	rapidxml::file<> xmlFile = fileName.c_str();
	tsxDoc_.parse<0>(xmlFile.data());
	// imageノードの取り出し
	auto image = tsxDoc_.first_node();
	// imageの情報
	if (image != nullptr) {
		for (auto atr = image->first_attribute(); atr != nullptr; atr = atr->next_attribute()) {
			// mapのkeyに名前使って値を入れる
			xml_.item_[atr->name()] = atr->value();
		}
		std::string dirname;
		// アニメーション情報
		for (auto animation = image->first_node("animation"); animation != nullptr; animation = animation->next_sibling()) {
			if (animation) {
				for (auto atr = animation->first_attribute(); atr != nullptr; atr = atr->next_attribute()) {
					std::string name = atr->name();
					if (name == "dirname") {
						dirname = atr->value();
					}
					else if (name == "loop") {
						xml_.loop_[dirname] = std::atoi(atr->value());
					}
				}
			}
			std::pair<int, int> tmppair;
			for (auto datasib = animation->first_node(); datasib != nullptr; datasib = datasib->next_sibling()) {
				if (datasib) {
					for (auto atr = datasib->first_attribute(); atr != nullptr; atr = atr->next_attribute()) {
						std::string name = atr->name();
						if (name == "count") {
							tmppair.first = std::atoi(atr->value());
						}
						else if (name == "frame") {
							tmppair.second = std::atoi(atr->value());
						}
					}
					xml_.data_[dirname].emplace_back(tmppair);
				}
			}
		}
	}

	// 全体のチップサイズ / 横のチップサイズ = 縦のチップサイズ
	std::string source = xml_.item_["source"].substr(xml_.item_["source"].find_first_of("/") + 1);

	lpImageMng.GetID(
		source,
		xml_.item_["name"],
		Int2(std::atoi(xml_.item_["width"].c_str()), std::atoi(xml_.item_["height"].c_str())),
		Int2(std::atoi(xml_.item_["divwidth"].c_str()), std::atoi(xml_.item_["divheight"].c_str())));

	return xml_;
}

bool TmxObj::SetMap(void)
{
	// mapノード読み込み
	auto mapnode = tmxDoc_.first_node("map");
	if (mapnode == nullptr) {
		TRACE("mapノード取得エラー\n");
		return false;
	}
	// layerノード読み込み
	auto laynode = mapnode->first_node("layer");
	if (laynode == nullptr) {
		TRACE("layerノード取得エラー");
		return false;
	}
	// バージョンがkeyに存在するかを確認
	if (!CheckTiledVersion(mapnode)) {
		return false;
	}

	std::map<std::string, std::pair<MapData::iterator, bool>> layer;
	auto name = [&]() { 
		std::string node = laynode->first_attribute("name")->value();
		return node; };
	//layer[laynode->first_attribute("name")->value()] = mapdata_.try_emplace(laynode->first_attribute("name")->value());
	//auto layer = mapdata_.try_emplace(laynode->first_attribute("name")->value());

	//auto data = laynode->first_node("data")->value();

	do{
		std::string node = laynode->first_attribute("name")->value();
		// 子リジョンだったら別処理
		if (node == "Col") {
			laynode = laynode->next_sibling();
			continue;
		}
		// csvを取り出す
		layer[name()] = mapdata_.try_emplace(laynode->first_attribute("name")->value());
		if (layer[name()].second)
		{
			layer[name()].first->second.resize(static_cast<__int64>(worldArea_.x) * worldArea_.y);
		}

		// csvをintに変えて格納する
		auto data = laynode->first_node("data")->value();
		std::string str = data;
		int strsize = static_cast<int>(str.size());
		for (int i = 0, wpos = 0, old = 0,nexti = 1; str.size() > i; i++,nexti=i+1) {
			if (str[i] == '\r' || str[i] == '\n' || str[i] == '\r\n' || str[i] == ',') {
				continue;
			}
			else {
				std::string tmp;
				tmp.resize(1);
				tmp[0] = str[i];
				if (str.size() > nexti && str[nexti] != ',' && str[nexti] != '\r' && str[nexti] != '\n' && str[nexti] != '\r\n')
				{
					tmp += str[nexti];
					i++;
				}
				layer[name()].first->second[wpos] = std::atoi(tmp.c_str());
				wpos++;
			}
		}
		laynode = laynode->next_sibling();
	} while (laynode);

	auto colnode = mapnode->first_node("objectgroup");
	for (auto objnode = colnode->first_node("object"); objnode != nullptr;objnode = objnode->next_sibling()) {
		collist_.push_back(
			std::pair<Float2,Float2>(
			Float2(objnode->first_attribute("x")->value(), objnode->first_attribute("y")->value()),
			Float2(objnode->first_attribute("width")->value(), objnode->first_attribute("height")->value()))
		);
	}
	return true;
}

const VecInt& TmxObj::GetMapData(std::string lay)
{
	return mapdata_[lay];
}

const int TmxObj::GetMapData(std::string lay,int x,int y)
{
	if (mapdata_.find(lay) == mapdata_.end()) {
		return 0;
	}
	int point = x + (worldArea_.x * y);
	if (point >= 0 && point < mapdata_[lay].size()) {
		return mapdata_[lay][point];
	}
	else {
		return 0;
	}
	return 0;
}

const int TmxObj::GetMapData(std::string lay, Float2 pos)
{
	Int2 chip = (Int2(pos.x,pos.y) / tileSize_);

	return GetMapData(lay,chip.x,chip.y);
}

const bool TmxObj::GetMapDataCheck(Float2 pos)
{
	Int2 p;
	p.x = pos.x;
	p.y = pos.y;

	Int2 chip = (p / tileSize_);
	//Int2 chip = (pos / tileSize_);
	int point = chip.x + (worldArea_.x * chip.y);
	if (point < 0) {
		return true;
	}
	for (auto map : mapdata_) {
		if (map.second.size() > point && mapdata_[map.first][point]) {
			return true;
		}
	}
	return false;
}

const ColList& TmxObj::GetColList(void)
{
	return collist_;
}

bool TmxObj::CheckTiledVersion(rapidxml::xml_node<>* node)
{
	if (node == nullptr) {
		return false;
	}
	// タイルセットノードの中にあるバージョン情報の取り出し
	auto tiledversion = node->first_attribute("tiledversion");
	// バージョン番号の取り出し
	auto data = tiledversion->value();
	auto version = node->first_attribute();

	// バージョンがkeyに存在するかを確認
	if (!version_.count(data)) {
		return false;
	}
	// 存在していれば中身のboolを確認 trueだったら次へ進む
	if (!version_[data]) {
		return false;
	}
	return true;
}
