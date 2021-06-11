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
	// key ��imageMap�ɃA�N�Z�Xkey��������΍��
	const VecInt& GetID(std::string key);
	const VecInt& GetID(std::string f_name,std::string key);
	// �t�@�C���̃p�X,�L�[,�c���̃T�C�Y,�c���̃`�b�v��
	const VecInt& GetID(std::string f_name,std::string key,Int2 divSize,Int2 divCnt);
	// key ��imageMap�ɃA�N�Z�Xkey�������Ă��㏑�����č��
	const VecInt& ChangeID(std::string key);
	const VecInt& ChangeID(std::string f_name, std::string key);
	const VecInt& ChangeID(std::string f_name, std::string key, Int2 divSize, Int2 divCnt);
private:
	ImageMng();
	~ImageMng();
	std::map<std::string, VecInt> imageMap_;
};

