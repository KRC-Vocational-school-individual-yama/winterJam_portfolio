#pragma once
#include"../../libs/object.h"
class KeyManager;
class Button;

class PauseWindow :public Object {
public:
	PauseWindow(Scene* sc);
	~PauseWindow()	override;
	void Init()		override;
	void Update()	override;
	void Draw()		override;
private:
	KeyManager* keys;
	std::vector<Button*> buttons;
	int hFont;
	bool uiActive;
	bool keystop;

	void OnOffSwitch();
	void ChangeScene();
};