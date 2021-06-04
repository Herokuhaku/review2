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
	// tileset�m�[�h�̎��o��
	auto tileset = tsxDoc_.first_node("tileset");
	// �^�C���Z�b�g�m�[�h�̒��ɂ���o�[�W�������̎��o��
	auto tiledversion = tileset->first_attribute("tiledversion");
	// �o�[�W�����ԍ��̎��o��
	auto data = tiledversion->value();
	// �o�[�W������key�ɑ��݂��邩���m�F
	if (!version_.count(data)) {
		return false;
	}
	// ���݂��Ă���Β��g��bool���m�F true�������玟�֐i��
	if (!version_[data]) {
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
	tsxDoc_.parse<0>(xmlFile.data());
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
			tmxitem_[atr->name()] = atr->value();
			// ���̃A�g���r���[�g���Ă�
			atr = atr->next_attribute();
		}
	}
	return true;
}
