#include "scenechanger.h"

#include<Windows.h>
#include<assert.h>

#include"bootScene.h"
#include"scene.h"

#include"../scenes/titleScene.h"
#include"../scenes/gameScene.h"
#include"../scenes/menuScene.h"
#include"../scenes/difficultySelectionScene.h"
#include"../scenes/explanationScene.h"


Scene* SceneChanger::Changer(std::string scene) {
		 if (scene == "boot")						return new BootScene();					//デバッグ用
	else if (scene == "Title")					return new TitleScene();				// タイトル
	else if (scene == "Menu")					return new MenuScene();					// 選択画面（タイトルの次　
	else if (scene == "DifficultySelection")	return new DifficultySelectionScene();	// 難易度選択シーン
	else if (scene == "Game")					return new GameScene();					// パズルゲームシーン
	else if (scene == "Explanation")			return new ExplanationScene();			// 説明シーン
	else {
		MessageBox(NULL, ("次のシーンはありません\n" + scene + "\n" + "無視を押すと続行できます").c_str(), "SceneFactory", MB_ICONERROR | MB_OK);
		assert(false);
		return nullptr;
	}

}
