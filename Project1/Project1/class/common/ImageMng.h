#pragma once
#include <vector>
#include <string>
#include <map>
#include "Vector2.h"

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
private:
	ImageMng();
	~ImageMng();
	std::map<std::string, VecInt> imageMap_;
};

