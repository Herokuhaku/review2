#pragma once
#include <chrono>
#include <memory>

#define lpSceneMng SceneMng::GetInstance()

class BaseScene;

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
private:
	SceneMng();
	~SceneMng();
	bool SysInit(void);
	bool initflag_;
	std::unique_ptr<BaseScene> scene;
	std::chrono::system_clock::time_point now, old;
};