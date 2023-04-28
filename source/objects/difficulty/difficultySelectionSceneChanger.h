#pragma once
#include"../../libs/object.h"
class KeyManager;
class Button;

class DifficultySelectionSceneChanger :public Object {
public:
	DifficultySelectionSceneChanger(Scene*sc);
	~DifficultySelectionSceneChanger()override;
	void Init()		override;
	void Update()	override;
	void Draw()		override;
private:
	KeyManager* keys;
	std::vector<Button*> buttons;
	Button* backButton;
	int hFont;
	bool keystop;

	void SceneChange();
};
