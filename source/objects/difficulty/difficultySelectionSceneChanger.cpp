#include "difficultySelectionSceneChanger.h"
#include"../../libs/scenemanager.h"
#include"../../libs/keyManager.h"
#include"../button.h"
#include"../common/difficultToGameSend.h"
#include"../common/sound.h"

namespace {
	Sound* sound = nullptr;
}

DifficultySelectionSceneChanger::DifficultySelectionSceneChanger(Scene* sc)
	:Object(sc)
	,keys(nullptr)
	,buttons()
	,backButton(nullptr)
	,hFont{-1}
	,keystop{true}
{
}

DifficultySelectionSceneChanger::~DifficultySelectionSceneChanger(){
	DeleteFontToHandle(hFont);
	delete keys;
	delete backButton;
	for (auto& button : buttons)
		delete button;
}

void DifficultySelectionSceneChanger::Init(){
	keys = new KeyManager;

	const int maxNum = 3;
	std::vector<std::string> names(maxNum, "");
	buttons.resize(maxNum);
	names.at(0) = "Easy";
	names.at(1) = "Normal";
	names.at(2) = "Hard";

	//ボタン作成
	int buttonHeightSize = GetFontSize() * 4;
	for (int i = 0; i < names.size(); i++) {
		int buttonWidth = GetDrawFormatStringWidth(names.at(1).c_str()) * 4;
		
		int buttonWidthPos = SCREEN_WIDTH / 2 - buttonWidth / 2;
		VECTOR pos = VGet(buttonWidthPos, 300 + i * (buttonHeightSize * 2), 0);
		VECTOR size = VGet(buttonWidth, buttonHeightSize, 0);

		buttons.at(i) = new Button(pos, size, names.at(i));
	}
	std::string backStr = "戻る";
	backButton = new Button(VGet(50,700,0),VGet(GetDrawFormatStringWidth(backStr.c_str())*4, buttonHeightSize,0),backStr);


	hFont = LoadFontDataToHandle("data/font/SoukouMincho.ttf");
	assert(hFont > 0);

	sound = SceneManager::GetCommonScene()->Invoke<Sound>();
}

void DifficultySelectionSceneChanger::Update(){
	//デバッグ用
	SceneChange();




	bool mouseLeft = GetMouseInput() & MOUSE_INPUT_LEFT;
	bool mouseDown = mouseLeft && !keystop;
	keystop = mouseLeft;

	if (!mouseDown)//クリックしていなかったらここで終了
		return;

	Vec2 mouse = {};
	GetMousePoint(&mouse.x, &mouse.y);

	for (int i = 0; i < buttons.size(); i++) {
		Button* button = buttons.at(i);

		if (button->OnCollision(VGet(mouse.x,mouse.y,0),VGet(5,5,5))) {
			std::string name = button->GetMyName();

			Vec2  fastPos = {100,100};
			Vec2  pazzleAllNum = {5,5};
			float difficulty = 1.f;//倍率


			if ("Easy" == name) {
				fastPos = {100,100};
				pazzleAllNum = {5,5};
				difficulty = 2.f;
			}
			else if ("Normal" == name) {
				fastPos = { 100,100 };
				pazzleAllNum = { 10,5 };
				difficulty = 1.5f;
			}
			else if ("Hard" == name) {
				fastPos = { 100,50 };
				pazzleAllNum = { 10,10 };
				difficulty = 1.f;
			}

			DifficultToGameSend* diffSend= SceneManager::GetCommonScene()->Invoke<DifficultToGameSend>();
			diffSend->SetData(fastPos,pazzleAllNum,difficulty);


			sound->Play("決定ボタンを押す3.mp3");
			SceneManager::SceneChange("Game");
		}

	}

	if (backButton->OnCollision(VGet(mouse), VGet(5, 5, 5))){
		sound->Play("決定ボタンを押す3.mp3");
		SceneManager::SceneChange("Menu");
	}


}

void DifficultySelectionSceneChanger::Draw(){
	Vec2 mouse = {};
	GetMousePoint(&mouse.x, &mouse.y);

	std::vector<int> difficultColor(3, -1);
	difficultColor.at(0) = 0xfa8072;
	difficultColor.at(1) = 0x3cb371;
	difficultColor.at(2) = 0x9400d3;


	for(int i=0;i<buttons.size();i++){
		Button* button = buttons.at(i);

		bool onButton = button->OnCollision(VGet(mouse),VGet(5,5,5));

		button->Draw(onButton? difficultColor.at(i) : 0xf,5,hFont);
	}

	//戻るボタン
	bool backOnButton=backButton->OnCollision(VGet(mouse),VGet(5,5,5));
	backButton->Draw(backOnButton? 0xc0c0c0 :0xf,1.0f,hFont);

#ifdef _DEBUG
	//デバッグ用
	Vec2 size = {};
	GetDrawScreenSize(&size.x, &size.y);
	std::string str = "";
	str += "デバッグ用表示\n";
	str += "now difficultySelect\n";
	str += "　next : game = space";
	str += "　back : menu = escape";
	DrawFormatString(size.x/20, size.y/2, 0x0, str.c_str());
#endif
}

void DifficultySelectionSceneChanger::SceneChange(){

	if (keys->Down(KEY_INPUT_ESCAPE)) {
		SceneManager::SceneChange("Menu");
	}

#ifdef _DEBUG
	if (keys->Down(KEY_INPUT_SPACE)) {
		SceneManager::SceneChange("Game");

		Vec2  fastPos = { 100,100 };
		Vec2  pazzleAllNum = { 5,5 };
		float difficulty = 1.f;//倍率

		DifficultToGameSend* diffSend = SceneManager::GetCommonScene()->Invoke<DifficultToGameSend>();
		diffSend->SetData(fastPos, pazzleAllNum, difficulty);
	}
#endif

}
