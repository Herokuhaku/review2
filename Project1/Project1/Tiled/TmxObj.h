#pragma once
#include <vector>
#include <string>
#include <map>
#include "rapidxml.hpp"
#include "rapidxml_utils.hpp"
#include "../class/common/Vector2.h"

using MapData = std::map<std::string,std::vector<int>>;

class TmxObj
{
public:
	TmxObj();
	~TmxObj();
	// Tsxを読み込む
	bool LoadTsx(std::string fileName);
	// Tmxを読み込む
	bool LoadTmx(std::string fileName);
	// 読み込んだマップをmapdata_に格納する
	bool SetMap(void);
private:
	// versionを確認する
	bool CheckTiledVersion(rapidxml::xml_node<>* node);
	// バージョンが対応しているかどうか 0 : 対応していない　1 : 対応している
	std::map<std::string,int> version_;

	// TMX
	//
	// tmxのドキュメント
	rapidxml::xml_document<>tmxDoc_;
	// アトリビュートを取り出した後格納する変数
	std::map<std::string, std::string> tmxitem_;
	// マップチップの開始番号
	unsigned int firstGID_;
	// レイヤーの数
	unsigned int layerSize_;
	// レイヤーの縦横サイズ(チップ)
	Int2 worldArea_;
	// タイル1枚の縦横サイズ
	Int2 tileSize_;
	// csvの読み込み
	MapData mapdata_;

	// TSX
	//
	// tsxのドキュメント
	rapidxml::xml_document<>tsxDoc_;
	// アトリビュートを取り出した後格納する変数
	std::map<std::string, std::string> tsxitem_;
};

