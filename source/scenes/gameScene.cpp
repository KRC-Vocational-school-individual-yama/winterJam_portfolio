#include "gameScene.h"

#include<DxLib.h>
#include"../libs/scenemanager.h"

#include"../objects/game/board.h"
#include"../objects/game/gameTime.h"
#include"../objects/game/ClearJudgment.h"


GameScene::GameScene()
{
	SetBackgroundColor(0xe5,0xff,0xff);

	Create<Board>("Board");
	Create<GameTime>("GameTime");
	Create<ClearJudgment>();
	
}

GameScene::~GameScene(){
}

void GameScene::Update(){
	Scene::Update();

	//bool backKey = CheckHitKey(KEY_INPUT_ESCAPE);
	//static bool keystop=true;
	//if (backKey && !keystop) {
	//	SceneManager::SceneChange("Title");
	//}keystop = backKey;
}

void GameScene::Draw() {
	Scene::Draw();

#ifdef _DEBUG
	DrawFormatString(100,100,0x0,"GameScene\nEscape‚Å–ß‚é");
#endif
}