#include "titleobject.h"

#include"../../libs/scenemanager.h"
#include"../../libs/keyBoard.h"
#include"../../libs/keyManager.h"
#include"../common/sound.h"

namespace {
	Sound* soundP = nullptr;
}

TitleObject::TitleObject(Scene* sc)
	:Object				(sc)
	,keys				(nullptr)
	,keystop			{true}
	,hFont(-1)
	,hFontTitle(-1)
	,hImageTitle		{-1}
{}

TitleObject::~TitleObject(){
	delete keys;
	DeleteFontToHandle(hFont);
	DeleteFontToHandle(hFontTitle);
	DeleteGraph(hImageTitle);
}

void TitleObject::Init(){

	hFont = LoadFontDataToHandle("data/font/SoukouMincho.ttf");
	assert(hFont > 0);
	hFontTitle = CreateFontToHandle("", 128, -1, DX_FONTTYPE_ANTIALIASING_EDGE_4X4, -1, 5);
	assert(hFontTitle > 0);
	
	keys = new KeyManager();
	std::vector<int>keyNumberList;
	keyNumberList.reserve(10);
	keyNumberList.emplace_back(KEY_INPUT_SPACE);
	keyNumberList.emplace_back(KEY_INPUT_RETURN);
	keyNumberList.emplace_back(KEY_INPUT_TAB);
	keyNumberList.emplace_back(KEY_INPUT_ESCAPE);
	keyNumberList.shrink_to_fit();
	keys->SetKey(keyNumberList);


	std::string dispStr = "うご☆パズ";
	Vec2 screenSize = {};
	screenSize.x = GetDrawFormatStringWidthToHandle(hFontTitle,dispStr.c_str());
	screenSize.y = GetFontSizeToHandle(hFontTitle)+8;
	hImageTitle = MakeScreen(screenSize.x,screenSize.y,TRUE);
	SetDrawScreen(hImageTitle);
	//DrawStringToHandle(200, 200, dispStr.c_str(), 0x7fffd4, hFontTitle, 0x7fbfff);
	DrawStringToHandle(0,0, dispStr.c_str(), 0x7fffd4, hFontTitle, 0x7fbfff);
	SetDrawScreen(DX_SCREEN_BACK);
	ClearDrawScreen();

	//DeleteFontToHandle(hFont);
	//hFont = CreateFontToHandle("", 32, -1, DX_FONTTYPE_ANTIALIASING_4X4);
	//assert(hFont > 0);

	soundP= SceneManager::GetCommonScene()->Invoke<Sound>();
	int sound3= soundP->Load("決定ボタンを押す3.mp3");
	int sound1=soundP->Load("決定ボタンを押す1.mp3");
	ChangeVolumeSoundMem(255 * 50 / 100,sound3);
	ChangeVolumeSoundMem(255 * 50 / 100,sound1);

}

void TitleObject::Update(){

	ChangeScene();
}

void TitleObject::Draw(){

	//DrawFormatStringToHandle(200,200,0x7fbfff, hFont, "うご☆パズ");

	//DrawStringToHandle(200,200,"うご☆パズ", 0x7fffd4,hFont, 0x7fbfff);

	Vec2 graphSize = {};
	GetGraphSize(hImageTitle,&graphSize.x,&graphSize.y);
	DrawGraph(SCREEN_WIDTH/2-graphSize.x/2,300,hImageTitle,TRUE);

	DrawStringToHandle(SCREEN_WIDTH/2-0.5*GetDrawFormatStringWidth("何かキーを押して次へ"), 700, "何かキーを押して次へ", 0x6a6a6a, hFont);


#ifdef _DEBUG
	DrawFormatString(50,700,0x1,"デバッグ用\nスペースキー,エンター,マウス左を押してGameScene");
#endif
}



bool TitleObject::EndKeyInput(){
#ifdef _DEBUG
	return keys->Down(KEY_INPUT_ESCAPE);
#else
	return false;
#endif

}
	//bool endKey = keys->Down(KEY_INPUT_ESCAPE);
	//if (endKey&&!endKeyStop) 
	//	return true;
	//
	//endKeyStop = endKey;
	//return false;

void TitleObject::ChangeScene() {
	bool mouseLeft = (GetMouseInput() & MOUSE_INPUT_LEFT);
	bool sceneKey =  keys->Down(KEY_INPUT_SPACE)
				  || keys->Down(KEY_INPUT_RETURN)
				  || (mouseLeft&&!keystop);
	bool anyKey = CheckHitKeyAll();
	//nextScene キー
	if (sceneKey || (anyKey && !keystop)) {
		soundP->Play("決定ボタンを押す1.mp3");
		SceneManager::SceneChange("Menu");
	}
#ifdef _DEBUG
	//back キー
	if (keys->Down(KEY_INPUT_TAB))
		SceneManager::SceneChange("boot");
#endif
	keystop = mouseLeft ||anyKey;
}

