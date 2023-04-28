#include "bootScene.h"

#include"scenemanager.h"
#include"bootTestObject.h"



BootScene::BootScene() {
	Create<BootTestObject>();

//	SceneManager::GetCommonScene()->Create<Debug>();
}
BootScene::~BootScene(){
}

