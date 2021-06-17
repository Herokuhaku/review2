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
	// xmlを読み込んでitemだけ返す
	bool LoadXmlItem(std::string fileName);
	// 読み込んだマップをmapdata_に格納する
	bool SetMap(void);

	// Get関数
	// Mapdataをそのまま返す
	const MapData& GetMapData(void)const { return mapdata_; };
	// Mapdataの中から指定したlayerのdataを返す
	const VecInt& GetMapData(std::string lay);
	// mapdataの中から指定した位置のmapdataの中身を返す
	const int GetMapData(std::string lay,int x,int y);
	// posからmapdataの位置を計算してmapdataの中身を返す
	const int GetMapData(std::string lay,Int2 pos);
	// 縦横サイズ(チップ)を返す
	const Int2& GetWorldArea(void)const {return worldArea_;};
	// 縦横サイズ(チップ1つのサイズ)
	const Int2& GetTileSize(void)const {return tileSize_;};
	// マップチップの開始番号を返す
	const unsigned int GetFirstGid(void)const { return firstGID_; };
	// レイヤーの数を返す
	const unsigned int GetLayerSize(void)const { return layerSize_; };
private:
	// versionを確認する
	bool CheckTiledVersion(rapidxml::xml_node<>* node);
	// バージョンが対応しているかどうか 0 : 対応していない　1 : 対応している
	std::map<std::string,int> version_;

	// アイテム
	std::map<std::string, std::string> item_;
	std::map<std::string,int> loop_;
	std::map<std::string, std::vector<std::pair<int,int>>> data_;
	std::pair<int, int> pairdata_;

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
	// マップデータの格納先
	MapData mapdata_;

	// TSX
	//
	// tsxのドキュメント
	rapidxml::xml_document<>tsxDoc_;
	// アトリビュートを取り出した後格納する変数
	std::map<std::string, std::string> tsxitem_;
};

