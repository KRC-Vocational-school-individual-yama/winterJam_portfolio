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
	/// 終了するキーを押したか
	/// </summary>
	/// <param name="true	">押した</param>
	/// <param name="false	">押してない</param>
	/// <returns></returns>
	bool EndKeyInput()		;

private:
		//シーン切り替えの入力受付
	void ChangeScene()		;

	KeyManager* keys;
	bool keystop;
	int hFont;
	int hFontTitle;
	int hImageTitle;
};