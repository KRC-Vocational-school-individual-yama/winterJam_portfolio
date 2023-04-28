#include "bootTestObject.h"

#include"scenemanager.h"

BootTestObject::BootTestObject(Scene* sc)
	:Object		(sc)
{}
BootTestObject::~BootTestObject(){

}
void BootTestObject::Init(){

}
void BootTestObject::Update(){
	
	SceneChangeKey();
}
void BootTestObject::Draw() {
	//上の説明
	std::string explanation = "";
	explanation += "今は Debug Scene \n";
	explanation += "「Space key」 で TitleScene\n";
	explanation += "「Space と LeftShift key で GameScene」\n";
	DrawFormatString(100, 50, 0xff66ff,explanation.c_str());

	//編集用の主張
	int size = GetFontSize();
	std::string str = "デバッグ用シーン";
	SetFontSize(96);
	
	DrawFormatString(400 - str.size() * 96 / 4, 600 - 128, 0xffffff, str.c_str());

	SetFontSize(size);
}

void BootTestObject::SceneChangeKey() {
	bool spaceKey	= CheckHitKey(KEY_INPUT_SPACE)||(GetMouseInput()&MOUSE_INPUT_LEFT)||CheckHitKey(KEY_INPUT_RETURN);
	bool lShiftKey	= CheckHitKey(KEY_INPUT_LSHIFT);
	
	if (spaceKey&& !lShiftKey) 
		SceneManager::SceneChange("Title");

	if (spaceKey&& lShiftKey) 
		SceneManager::SceneChange("Game");
}
