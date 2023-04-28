#include "menuScene.h"
#include"../objects/menu/menuSceneChanger.h"
#include"../libs/scenemanager.h"

#include"../objects/common/pauseWindow.h"

MenuScene::MenuScene(){
	Create<MenuSceneChange>("MenuSceneChange");


	Scene* commonScene= SceneManager::GetCommonScene();
	PauseWindow* pauseP= commonScene->Invoke<PauseWindow>();
	if (pauseP == nullptr) 
		commonScene->Create<PauseWindow>();
	

}

MenuScene::~MenuScene(){

}
