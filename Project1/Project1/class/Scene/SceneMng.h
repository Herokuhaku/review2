#pragma once
#include <chrono>
#include <memory>
#include <array>
#include "BaseScene.h"
#include "../common/Vector2.h"
#include "../input/KeyInput.h"

#define lpSceneMng SceneMng::GetInstance()

class SceneMng
{
public:
	static SceneMng& GetInstance(void) {
		static SceneMng sInstance_;
		return sInstance_;
	}
	// ���C�����[�v
	void Run(void);
	// �X�V����
	void Update(void);
	// �`��
	void Draw(void);
	// ��ʃT�C�Y�����
	const Int2 GetScreenSize(void)const;
	// �E�B���h�E�������t���O
	void Finish(void) { finish_ = true; };
	// �V�X�e���̃R���g���[���[�����
	std::shared_ptr<Controller> GetController(void);
private:
	SceneMng();
	~SceneMng();
	// �V�X�e���̏�����
	bool SysInit(void);
	// �������t���O
	bool initflag_;
	// ���݂̃V�[��
	UniqueScene scene_;
	// delta�����߂���� now ~ old�̎��Ԃ�delta�Ƃ���
	std::chrono::system_clock::time_point now_, old_;
	// �X�N���[���T�C�Y
	const Int2 screenSize_;
	// �Q�[���I��
	bool finish_;
	int frame_;
	// �V�X�e���ŊǗ����Ă���R���g���[���[
	std::shared_ptr<Controller> controller_;
};