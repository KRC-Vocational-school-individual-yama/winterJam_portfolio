#pragma once
#include"../../libs/object.h"
class KeyManager;

class TitleObject :public Object {
public:
	TitleObject(Scene* sc)	;
	~TitleObject()	override;
	void Init()		override;
	void Update()	override;
	void Draw()		override;

	/// <summary>
	/// �I������L�[����������
	/// </summary>
	/// <param name="true	">������</param>
	/// <param name="false	">�����ĂȂ�</param>
	/// <returns></returns>
	bool EndKeyInput()		;

private:
		//�V�[���؂�ւ��̓��͎�t
	void ChangeScene()		;

	KeyManager* keys;
	bool keystop;
	int hFont;
	int hFontTitle;
	int hImageTitle;
};