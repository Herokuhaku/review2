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
	// Tsx��ǂݍ���
	bool LoadTsx(std::string fileName);
	// Tmx��ǂݍ���
	bool LoadTmx(std::string fileName);
	// �ǂݍ��񂾃}�b�v��mapdata_�Ɋi�[����
	bool SetMap(void);
private:
	// version���m�F����
	bool CheckTiledVersion(rapidxml::xml_node<>* node);
	// �o�[�W�������Ή����Ă��邩�ǂ��� 0 : �Ή����Ă��Ȃ��@1 : �Ή����Ă���
	std::map<std::string,int> version_;

	// TMX
	//
	// tmx�̃h�L�������g
	rapidxml::xml_document<>tmxDoc_;
	// �A�g���r���[�g�����o������i�[����ϐ�
	std::map<std::string, std::string> tmxitem_;
	// �}�b�v�`�b�v�̊J�n�ԍ�
	unsigned int firstGID_;
	// ���C���[�̐�
	unsigned int layerSize_;
	// ���C���[�̏c���T�C�Y(�`�b�v)
	Int2 worldArea_;
	// �^�C��1���̏c���T�C�Y
	Int2 tileSize_;
	// csv�̓ǂݍ���
	MapData mapdata_;

	// TSX
	//
	// tsx�̃h�L�������g
	rapidxml::xml_document<>tsxDoc_;
	// �A�g���r���[�g�����o������i�[����ϐ�
	std::map<std::string, std::string> tsxitem_;
};

