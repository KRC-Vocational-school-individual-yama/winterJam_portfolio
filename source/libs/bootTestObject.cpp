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
	//��̐���
	std::string explanation = "";
	explanation += "���� Debug Scene \n";
	explanation += "�uSpace key�v �� TitleScene\n";
	explanation += "�uSpace �� LeftShift key �� GameScene�v\n";
	DrawFormatString(100, 50, 0xff66ff,explanation.c_str());

	//�ҏW�p�̎咣
	int size = GetFontSize();
	std::string str = "�f�o�b�O�p�V�[��";
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
