#include "TmxObj.h"
#include "../_debug/_DebugConOut.h"
#include <DxLib.h>
#include "../class/common/ImageMng.h"
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
	// タイルセットノードの中にあるバージョン情報の取り出し
	auto tiledversion = tileset->first_attribute("tiledversion");
	// バージョン番号の取り出し
	auto data = tiledversion->value();
	// バージョンがkeyに存在するかを確認
	if (!version_.count(data)) {
		return false;
	}
	// 存在していれば中身のboolを確認 trueだったら次へ進む
	if (!version_[data]) {
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
	tsxDoc_.parse<0>(xmlFile.data());
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
			tmxitem_[atr->name()] = atr->value();
			// 次のアトリビュートを呼ぶ
			atr = atr->next_attribute();
		}
	}
	return true;
}
