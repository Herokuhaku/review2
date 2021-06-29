#pragma once
#include <list>
#include <string>
#include <map>
#include "rapidxml.hpp"
#include "rapidxml_utils.hpp"
#include "../class/common/Vector2.h"
#include "../class/common/Collision.h"
//
//// ���㒸�_ , Float2(��,����)
//using ColList = std::list<std::pair<Float2, Float2>>;
// map<���C���[��,�i�[���Ă���u���b�N�̔z��>
using MapData = std::map<std::string,std::vector<int>>;
// first : �A�j���[�V�����̔ԍ�(�摜�ɂ����ĉ��Ԗڂ�),
//second : �A�j���[�V�����̃t���[����(���t���[���`�悷�邩)
using AnimData = std::pair<int, int>;
// AnimData �� vector�Ŋi�[�����f�[�^
using AnimVecData = std::list<AnimData>;

// �A�j���[�V�������邽�߂ɕK�v��Xml������o�����A�C�e��
struct XmlItem
{
	// �A�C�e���̖��O , �v�f
	std::map<std::string, std::string> item_;
	// �A�j���[�V�����̖��O,���[�v���邩 -1 : ���Ȃ� 1 : ����
	std::map<std::string, int> loop_;
	// key : �A�j���[�V�����̖��O
	std::map<std::string, AnimVecData> data_;
};

class TmxObj
{
public:
	TmxObj();
	~TmxObj();
	// Tsx��ǂݍ���
	bool LoadTsx(std::string fileName);
	// Tmx��ǂݍ���
	bool LoadTmx(std::string fileName);
	// xml��ǂݍ����item�����Ԃ�
	XmlItem LoadXmlItem(std::string fileName);
	// �ǂݍ��񂾃}�b�v��mapdata_�Ɋi�[����
	bool SetMap(void);

	// Get�֐�
	// Mapdata�����̂܂ܕԂ�
	const MapData& GetMapData(void)const { return mapdata_; };
	// Mapdata�̒�����w�肵��layer��data��Ԃ�
	const VecInt& GetMapData(std::string lay);
	// mapdata�̒�����w�肵���ʒu��mapdata�̒��g��Ԃ�
	const int GetMapData(std::string lay,int x,int y);
	// pos����mapdata�̈ʒu���v�Z����mapdata�̒��g��Ԃ�
	const int GetMapData(std::string lay,Float2 pos);
	// pos����mapdata�̈ʒu���v�Z���Ă�����block�����邩��Ԃ�
	const bool GetMapDataCheck(Float2 pos);
	// �c���T�C�Y(�`�b�v)��Ԃ�
	const Int2& GetWorldArea(void)const {return worldArea_;};
	// �c���T�C�Y(�`�b�v1�̃T�C�Y)
	const Int2& GetTileSize(void)const {return tileSize_;};
	// �}�b�v�`�b�v�̊J�n�ԍ���Ԃ�
	const unsigned int GetFirstGid(void)const { return firstGID_; };
	// ���C���[�̐���Ԃ�
	const unsigned int GetLayerSize(void)const { return layerSize_; };
	// �R���W�������X�g��Ԃ�
	const ColList& GetColList(void);
private:
	// version���m�F����
	bool CheckTiledVersion(rapidxml::xml_node<>* node);
	// �o�[�W�������Ή����Ă��邩�ǂ��� 0 : �Ή����Ă��Ȃ��@1 : �Ή����Ă���
	std::map<std::string,int> version_;

	// �A�C�e��
	XmlItem xml_;
	//std::map<std::string, std::string> item_;
	//std::map<std::string,int> loop_;
	//std::map<std::string, std::vector<std::pair<int,int>>> data_;

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
	// �}�b�v�f�[�^�̊i�[��
	MapData mapdata_;
	// �R���W�������i�[�������X�g
	ColList collist_;

	// TSX
	//
	// tsx�̃h�L�������g
	rapidxml::xml_document<>tsxDoc_;
	// �A�g���r���[�g�����o������i�[����ϐ�
	std::map<std::string, std::string> tsxitem_;
};

