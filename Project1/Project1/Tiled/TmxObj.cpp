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
	// tileset�m�[�h�̎��o��
	auto tileset = tsxDoc_.first_node("tileset");

	// �o�[�W������key�ɑ��݂��邩���m�F
	if (!CheckTiledVersion(tileset)){
		return false;
	}
	for (auto n = tsxDoc_.first_node(); n != nullptr; n = n->first_node())
	{
		// �m�[�h������Ζ��O����������
		if (n) {
			if (n->name_size()) {
				TRACE("%s�� ", n->name());
			}
		}
		// �A�g���r���[�g�����o��
		auto atr = n->first_attribute();
		// �A�g���r���[�g�����݂���ꍇ����
		while (atr) {
			// ���O����������
			if (atr->name_size()) {
				TRACE("%s ", atr->name());
			}
			// �v�f�������o��
			TRACE("%s ", atr->value());
			// map��key�ɖ��O�g���Ēl������
			tsxitem_[atr->name()] = atr->value();
			// ���̃A�g���r���[�g���Ă�
			atr = atr->next_attribute();
		}
	}

	// �S�̂̃`�b�v�T�C�Y / ���̃`�b�v�T�C�Y = �c�̃`�b�v�T�C�Y
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
	// �o�[�W������key�ɑ��݂��邩���m�F
	if (!CheckTiledVersion(mapnode)){
		return false;
	}

	// tsx������t�@�C���܂ł̃p�X�����
	std::string sourcestr = fileName.substr(0,fileName.find_last_of("/")+1);
	sourcestr += mapnode->first_node("tileset")->first_attribute("source")->value();
	// TSX���ǂݍ��߂����ǂ���
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
	// map�m�[�h�ǂݍ���
	auto mapnode = tmxDoc_.first_node("map");
	if (mapnode == nullptr) {
		TRACE("map�m�[�h�擾�G���[\n");
		return false;
	}
	// layer�m�[�h�ǂݍ���
	auto laynode = mapnode->first_node("layer");
	if (laynode == nullptr) {
		TRACE("layer�m�[�h�擾�G���[");
		return false;
	}
	// �o�[�W������key�ɑ��݂��邩���m�F
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
	// �^�C���Z�b�g�m�[�h�̒��ɂ���o�[�W�������̎��o��
	auto tiledversion = node->first_attribute("tiledversion");
	// �o�[�W�����ԍ��̎��o��
	auto data = tiledversion->value();
	auto version = node->first_attribute();

	// �o�[�W������key�ɑ��݂��邩���m�F
	if (!version_.count(data)) {
		return false;
	}
	// ���݂��Ă���Β��g��bool���m�F true�������玟�֐i��
	if (!version_[data]) {
		return false;
	}
	return true;
}
