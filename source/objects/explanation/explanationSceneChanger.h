#pragma once
#include"../../libs/object.h"
class KeyManager;
class Button;

class ExplanationSceneChanger :public Object {
public:
	ExplanationSceneChanger(Scene* sc);
	~ExplanationSceneChanger()override;
	void Init()		override;
	void Update()	override;
	void Draw()		override;
private:
	KeyManager* keys;
	Button* backButton;
	int hFont;
	bool keystop;

	void SceneChanger();
};
