#include "pauseWindow.h"
#include"../../libs/keyManager.h"
#include"../../libs/scenemanager.h"
#include"../button.h"
#include"../game/gameTime.h"
#include"sound.h"
#include"../game/board.h"

namespace {
	Sound* sound = nullptr;
	Board* board=nullptr;
}

PauseWindow::PauseWindow(Scene* sc)
	:Object(sc)
	,keys(nullptr)
	,buttons()
	,hFont{-1}
	,uiActive{false}
	,keystop{true}
{
}

PauseWindow::~PauseWindow(){
	DeleteFontToHandle(hFont);
	delete keys;
	for (auto& button : buttons)
		delete button;
}

void PauseWindow::Init(){

	hFont = LoadFontDataToHandle("data/font/SoukouMincho.ttf");
	assert(hFont > 0);

	keys = new KeyManager();

	const int maxButton = 3;
	std::vector<std::string> names(maxButton, "");
	buttons.resize(maxButton);
	names.at(0) = "ゲームを続ける";
	names.at(1) = "";// "説明を見る";
	names.at(2) = "メニューへ戻る";

	for (int i = 0; i < names.size(); i++) {
		int buttonWidth = GetDrawFormatStringWidth(names.at(0).c_str()) *4;
		int buttonHeightSize = GetFontSize() * 4;
		int buttonWidthPos = SCREEN_WIDTH / 2 - buttonWidth / 2;
		VECTOR pos = VGet(buttonWidthPos, 300 + i * (buttonHeightSize * 2), 0);
		VECTOR size = VGet(buttonWidth,buttonHeightSize,0);

		buttons.at(i) = new Button(pos, size, names.at(i));
	}
	sound = SceneManager::GetCommonScene()->Invoke<Sound>();
}

void PauseWindow::Update(){
	std::string nowSceneName= SceneManager::GetCurrentSceneName();

	if("Game" == nowSceneName)
		OnOffSwitch();

	board = SceneManager::GetCurrentScene()->Invoke<Board>();
	if(board)
		if(!board->GetPazzleClear())
	//オブジェクトの更新を止める
	{
		std::list<Object*> objectList;
		/*auto*/ objectList = SceneManager::GetCurrentScene()->Invokes<Object>();
		for (Object* object : objectList) {
			if(object)
			object->SetMyUpdate(uiActive);
		}
	}

	GameTime* timeP= SceneManager::GetCurrentScene()->Invoke<GameTime>();
	if (!uiActive) {//UIを開いたら行う
		if (timeP) 
			timeP->Start();
		

		return;
	}
	if (timeP)
		timeP->Stop();


	ChangeScene();



	bool mouseLeft = GetMouseInput() & MOUSE_INPUT_LEFT;
	bool mouseDown = mouseLeft && !keystop;
	keystop = mouseLeft;

	if (!mouseDown)//クリックしていなかったらここで終了
		return;
	Vec2 mouse = {};
	GetMousePoint(&mouse.x, &mouse.y);
	for (int i = 0; i < buttons.size(); i++) {
		Button* button = buttons.at(i);

		if (button->OnCollision(VGet(mouse.x, mouse.y, 0), VGet(5, 5, 5))) {
			std::string name = button->GetMyName();

			Vec2  fastPos = { 100,100 };
			Vec2  pazzleAllNum = { 5,5 };
			float difficulty = 1.f;//倍率


			if ("ゲームを続ける" == name) {
				uiActive = false;
				sound->Play("決定ボタンを押す3.mp3");
			}
			else if ("説明を見る" == name) {
				//ToDo:あとで
			}
			else if ("メニューへ戻る" == name) {
				uiActive = false;
				SceneManager::SceneChange("Menu");
				//SceneManager::SceneChange("DifficultySelection");
				sound->Play("決定ボタンを押す3.mp3");

			}

		}

	}


}

void PauseWindow::Draw(){
	if (!uiActive)return;
	
	Vec2 size = {};
	GetDrawScreenSize(&size.x,&size.y);


	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255/1.25);

	DrawBox(0,0,size.x,size.y,0x0,TRUE);//UIを開いたときの薄い黒
	
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

#ifdef _DEBUG //デバッグ用
	std::string str = "";
	str += "ここは　説明　UI \n";
	DrawFormatString(size.x/20,size.y/2,0xdddddd,str.c_str());

	str = "";
	str += "デバッグ表示\n";
	str += "ゲームを続ける =TKey\n";
	str += "説明を見る　　 =GKey\n";
	str += "メニューへ戻る =BKey\n";
	DrawFormatString(size.x/20,size.y/3,0xdddddd,str.c_str());
#endif

	Vec2 mouse = {};
	GetMousePoint(&mouse.x, &mouse.y);
	std::vector<int> difficultColor(3, 0xc0c0c0);
	int difCol = 0x4169e1;
	difficultColor.at(0) = difCol;
	difficultColor.at(1) = difCol;
	difficultColor.at(2) = difCol;

	for (int i = 0; i < buttons.size(); i++) {
		if (i == 1)continue;
		Button* button = buttons.at(i);

		//ボタンの半透明 背景 描画　急造です。
		{
			VECTOR pos = VGet(0, 0, 0), size = VGet(0, 0, 0);
			button->GetTransform(pos, size);

			SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255 / 2);

			DrawBox(pos.x, pos.y, pos.x + size.x, pos.y + size.y, 0, TRUE);

			SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
		}




		bool onButton = button->OnCollision(VGet(mouse), VGet(5, 5, 5));

		button->Draw(onButton ? difficultColor.at(i) : 0xebebeb, 5,hFont);
	}


}

void PauseWindow::OnOffSwitch(){
	if (keys->Down(KEY_INPUT_ESCAPE)) 
		uiActive= uiActive ? false : true;
}

void PauseWindow::ChangeScene(){
	//if (!uiActive)return;

	if (keys->Down(KEY_INPUT_B)) {
		uiActive = false;
		SceneManager::SceneChange("Menu");
	}

}
