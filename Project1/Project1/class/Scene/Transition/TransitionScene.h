#pragma once
#include "../BaseScene.h"

enum class Transition {
	CrossFade,
	FadeInOut,
	Max
};

class TransitionScene :
	public BaseScene
{
public:
	TransitionScene(double limit,UniqueScene befor,UniqueScene after);
	~TransitionScene();
private:

	// ������
	bool Init(void)override;
	// �X�V
	UniqueScene Update(double delta,UniqueScene own)override;
	virtual bool UpdateTransition(double delta) = 0;
	// �`��
	//virtual void Draw(double delta)override;

	Scene GetSceneID(void)override final{ return Scene::Transition; };
	void DrawOwnScreen(double delta)override = 0;
protected:
	// limit�Ŕ�������
	virtual bool LimitCheck(double delta);
	// �ύX�O�̃V�[��
	UniqueScene before_;
	// �ύX��̃V�[��
	UniqueScene after_;
	// 1�t���[��������̒l
	double count_;
	// �l�̍��v
	double drawsum_;
	// 255���ő�l�Ƃ���(���l�̍ő�l)
	double drawmax_;
	// �V�[���̌p������(�b)
	double limit_;
};

