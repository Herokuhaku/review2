#pragma once
#include <chrono>
#include <memory>
#include <array>
#include "BaseScene.h"
#include "../common/Vector2.h"

#define lpSceneMng SceneMng::GetInstance()

class SceneMng
{
public:
	static SceneMng& GetInstance(void) {
		static SceneMng sInstance_;
		return sInstance_;
	}

	void Run(void);
	void Update(void);
	void Draw(void);
	const Int2 GetScreenSize(void)const;
private:
	SceneMng();
	~SceneMng();
	bool SysInit(void);
	bool initflag_;
	UniqueScene scene_;
	std::chrono::system_clock::time_point now_, old_;
	const Int2 screenSize_;
};