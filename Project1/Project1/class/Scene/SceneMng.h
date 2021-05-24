#pragma once
class SceneMng
{
public:
	static SceneMng& GetInstance(void) {
		static SceneMng sInstance_;
		return sInstance_;
	}

	void Update(void);
	void Draw(void);
private:
	SceneMng();
	~SceneMng();
};