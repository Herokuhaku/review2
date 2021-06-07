#include "TmxObj.h"
#include "../_debug/_DebugConOut.h"
#include <DxLib.h>
#include "../class/common/ImageMng.h"

using rapid_node = rapidxml::xml_node<>*;
using rapid_atr = rapidxml::xml_attribute<>*;

TmxObj::TmxObj()
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

	std::pair<MapData::iterator, bool> layer = mapdata_.try_emplace(laynode->first_attribute("name")->value());
	//auto layer = mapdata_.try_emplace(laynode->first_attribute("name")->value());
	if (layer.second)
	{
		layer.first->second.resize(worldArea_.x * worldArea_.y);
	}
	//auto data = laynode->first_node("data")->value();
	auto data = laynode->first_node("data")->value();
	std::string str = data;
	int strsize = str.size();
	for (int i = 0,wpos = 0,old = 0;str.size() > i;i++) {
		if (str[i] == '\r' || str[i] == '\n' || str[i] == '\r\n' || str[i] == ',') {
		continue;
		}
		else {
			std::string tmp;
			tmp.resize(1);
			tmp[0] = str[i];
			if (str.size() > i + 1 && str[i + 1] != ',' && str[i + 1] != '\r' && str[i + 1] != '\n' && str[i + 1] != '\r\n')
			{
				tmp += str[i + 1];
				i++;
			}
			layer.first->second[wpos] = std::atoi(tmp.c_str());
			wpos++;
		}
	}

	return true;
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
