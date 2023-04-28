#pragma once
#include"../../libs/object.h"
class KeyManager;
class Button;

class MenuSceneChange :public Object {
public:
	MenuSceneChange(Scene* sc);
	~MenuSceneChange()	override;
	void Init()			override;
	void Update()		override;
	void Draw()			override;

private:
	KeyManager* keys;
	std::vector<Button*>buttons;
	int hFont;
	bool keystop;



	void SceneChange();
};