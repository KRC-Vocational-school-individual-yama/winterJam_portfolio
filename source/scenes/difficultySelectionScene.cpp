#include "difficultySelectionScene.h"
#include"../libs/scenemanager.h"
#include"../objects/difficulty/difficultySelectionSceneChanger.h"
#include"../objects/common/difficultToGameSend.h"

DifficultySelectionScene::DifficultySelectionScene(){

	Scene* commonScene = SceneManager::GetCommonScene();
	DifficultToGameSend* sendP = commonScene->Invoke<DifficultToGameSend>();
	if (sendP == nullptr)
		commonScene->Create<DifficultToGameSend>();

	Create<DifficultySelectionSceneChanger>();
}

DifficultySelectionScene::~DifficultySelectionScene()
{
}
