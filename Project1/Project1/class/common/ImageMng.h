#pragma once
#include <vector>
#include <string>
#include <map>
#include "Vector2.h"
#include "../Animation/Animation.h"

#define lpImageMng ImageMng::GetInstance()

class ImageMng
{
public:
	static ImageMng& GetInstance() {
		static ImageMng sInstance;
		return sInstance;
	}
	// key でimageMapにアクセスkeyが無ければ作る
	const VecInt& GetID(std::string key);
	const VecInt& GetID(std::string f_name,std::string key);
	// ファイルのパス,キー,縦横のサイズ,縦横のチップ数
	const VecInt& GetID(std::string f_name,std::string key,Int2 divSize,Int2 divCnt);
	// key でimageMapにアクセスkeyがあっても上書きして作る
	const VecInt& ChangeID(std::string key);
	const VecInt& ChangeID(std::string f_name, std::string key);
	const VecInt& ChangeID(std::string f_name, std::string key, Int2 divSize, Int2 divCnt);

	// AnimをItemから設定する(XmlItem)
	bool CheckAnim(std::string key,STATE state);
	bool SetXml(std::string f_name);
	bool SetItem(std::string key,const STATE state, std::string dir);
	bool SetAnim(std::string key,const STATE state, AnimVector& data);
	
	int GetAnimID(std::string key,STATE state,int animframe);
	int GetAnimFrame(std::string key,STATE state, int animframe);
	int GetAnimSize(std::string key,STATE state);
private:
	ImageMng();
	~ImageMng();
	std::map<std::string, VecInt> imageMap_;
	std::map<std::string,std::map<STATE, AnimVector>> animMap_;

	TmxObj tmx_;
	XmlItem xmlitem_;
};

