#include "explanationSceneChanger.h"
#include"../../libs/keyManager.h"
#include"../../libs/scenemanager.h"
#include"../button.h"
#include"../common/sound.h"

namespace {
	std::string passFont = "data/font/SoukouMincho.ttf";
	Sound* sound = nullptr;
}

ExplanationSceneChanger::ExplanationSceneChanger(Scene* sc)
	:Object(sc)
	,keys(nullptr)
	,backButton(nullptr)
	,hFont{-1}
	,keystop{true}
{
}

ExplanationSceneChanger::~ExplanationSceneChanger(){
	delete keys;
	delete backButton;
	DeleteFontToHandle(hFont);
}

void ExplanationSceneChanger::Init(){
	keys = new KeyManager;
	hFont = LoadFontDataToHandle(passFont.c_str());
	assert(hFont>0);

	//ボタン作成
	int buttonHeightSize = GetFontSize() * 4;
	std::string backStr = "戻る";
	backButton = new Button(VGet(50, 700, 0), VGet(GetDrawFormatStringWidth(backStr.c_str()) * 4, buttonHeightSize, 0), backStr);
	sound = SceneManager::GetCommonScene()->Invoke<Sound>();
}

void ExplanationSceneChanger::Update(){
	SceneChanger();



	bool mouseLeft = GetMouseInput() & MOUSE_INPUT_LEFT;
	bool mouseDown = mouseLeft && !keystop;
	keystop = mouseLeft;

	if (!mouseDown)//クリックしていなかったらここで終了
		return;

	Vec2 mouse = {};
	GetMousePoint(&mouse.x, &mouse.y);

	if (backButton->OnCollision(VGet(mouse), VGet(5, 5, 5))) {
		sound->Play("決定ボタンを押す3.mp3");
		SceneManager::SceneChange("Menu");
	}
}

void ExplanationSceneChanger::Draw(){
#ifdef _DEBUG
	Vec2 size = {};
	GetDrawScreenSize(&size.x,&size.y);
	std::string str = "";
	str += "デバッグ用表示\n";
	str += "Menu\n";
	str += "　next : Space\n";
	str += "\n";
	DrawFormatString(size.x/20,size.y/2,0x0,str.c_str());
#endif

	DrawStringToHandle(300,300,"パズルピースをつかみ中「AとD」キーで回転します。\nマウスで操作できます。\n※時間が無くて用意できませんでした。。。", 0x0,hFont);

	Vec2 mouse = {};
	GetMousePoint(&mouse.x, &mouse.y);

	//戻るボタン
	bool backOnButton = backButton->OnCollision(VGet(mouse), VGet(5, 5, 5));
	backButton->Draw(backOnButton ? 0xc0c0c0 : 0xf, 1.0f, hFont);
}

void ExplanationSceneChanger::SceneChanger(){
#ifdef _DEBUG
	if (keys->Down(KEY_INPUT_SPACE))
		SceneManager::SceneChange("Menu");
#endif
}
