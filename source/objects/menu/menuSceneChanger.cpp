#include "menuSceneChanger.h"
#include"../../libs/scenemanager.h"
#include"../../libs/keyManager.h"
#include"../button.h"
#include"../common/sound.h"

namespace {
	Sound* sound=nullptr;
}

MenuSceneChange::MenuSceneChange(Scene* sc)
	:Object(sc)
	, keys(nullptr)
	, buttons()
	,hFont{-1}
	, keystop{ true }
{
}

MenuSceneChange::~MenuSceneChange() {
	delete keys;
	for (auto& button : buttons)
		delete button;
	buttons.clear();
	DeleteFontToHandle(hFont);

}

void MenuSceneChange::Init() {
	keys = new KeyManager();

	//VECTOR pos =VGet(SCREEN_WIDTH/2,300,0);
	//int buttonWidth=GetDrawFormatStringWidth("　難易度選択へ　");
	//VECTOR size = VGet(buttonWidth*4,GetFontSize()*4,0);
	//button = new Button(pos,size, "難易度選択へ");

	const int maxNum = 3;
	std::vector<std::string> names(maxNum, "");
	buttons.resize(maxNum);
	names.at(0) = "難易度選択へ";
	names.at(1) = "説明を見る";
	names.at(2) = "ゲームを終わる";

	//ボタン作成
	for (int i = 0; i < names.size(); i++) {
		int buttonWidth = GetDrawFormatStringWidth(names.at(2).c_str()) * 4;
		int buttonHeightSize = GetFontSize() * 4;
		int buttonWidthPos = SCREEN_WIDTH / 2 - buttonWidth / 2;
		VECTOR pos = VGet(buttonWidthPos, 300 + i * (buttonHeightSize * 2), 0);
		VECTOR size = VGet(buttonWidth, buttonHeightSize, 0);

		buttons.at(i) = new Button(pos, size, names.at(i));
	}


	hFont= LoadFontDataToHandle("data/font/SoukouMincho.ttf");
	assert(hFont>0);

	sound = SceneManager::GetCommonScene()->Invoke<Sound>();
}

void MenuSceneChange::Update() {

	SceneChange();
#ifdef _DEBUG
	//デバッグ用


#endif
}

void MenuSceneChange::Draw() {
	//button->Draw(0xf);
	Vec2 mouse = {};
	GetMousePoint(&mouse.x, &mouse.y);
	for (Button* button : buttons) {

		bool onButton = button->OnCollision(VGet(mouse), VGet(5, 5, 5));

		button->Draw(onButton ? 0xc0c0c0 : 0xf,1.0f,hFont);
	}

#ifdef _DEBUG
	Vec2 size = {};
	GetDrawScreenSize(&size.x, &size.y);
	std::string str = "";
	str += "デバッグ用操作\n";
	str += "now Menu\n";
	str += "next :difficulty = space\n";
	str += "next :explanation = tab\n";
	str += "next :gameEnd = Ekey\n";
	DrawFormatString(size.x / 20, size.y / 2, 0x0, str.c_str());
#endif
}

void MenuSceneChange::SceneChange() {
#ifdef _DEBUG
	if (keys->Down(KEY_INPUT_SPACE))
		SceneManager::SceneChange("DifficultySelection");
	if (keys->Down(KEY_INPUT_TAB))
		SceneManager::SceneChange("Explanation");
	if (keys->Down(KEY_INPUT_E))
		SceneManager::SetGameEnd();
#endif


	bool mouseLeft = GetMouseInput() & MOUSE_INPUT_LEFT;
	bool mouseDown = mouseLeft && !keystop;//マウスクリックの１フレーム
	keystop = mouseLeft;

	if (!mouseDown)
		return;

	Vec2 mouse = {};
	GetMousePoint(&mouse.x, &mouse.y);

	std::vector<std::string>sceneStr(buttons.size(), "");
	sceneStr.at(0) = "DifficultySelection";
	sceneStr.at(1) = "Explanation";
	sceneStr.at(2) = "";

	for (int i = 0; i < buttons.size(); i++) {
		Button* button = buttons.at(i);
		if (!button->OnCollision(VGet(mouse.x, mouse.y, 0), VGet(5, 5, 5)))
			continue;

		if (i == 2) {//例外　ゲーム終了の為
			SceneManager::SetGameEnd();
		}
		else {
			SceneManager::SceneChange(sceneStr.at(i));
		}

		sound->Play("決定ボタンを押す3.mp3");
		
	}




}

