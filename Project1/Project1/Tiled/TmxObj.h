#pragma once
#include <string>
#include <map>
#include "rapidxml.hpp"
#include "rapidxml_utils.hpp"

class TmxObj
{
public:
	TmxObj();
	~TmxObj();
	bool LoadTsx(std::string fileName);
	bool LoadTmx(std::string fileName);
private:
	std::map<std::string,int> version_;
	// TMX
	std::map<std::string, std::string> tmxitem_;
	// TSX
	rapidxml::xml_document<>tsxDoc_;
	std::map<std::string, std::string> tsxitem_;
};

