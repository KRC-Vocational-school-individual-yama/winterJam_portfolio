#include "explanationScene.h"
#include"../objects/explanation/explanationSceneChanger.h"

ExplanationScene::ExplanationScene(){
	Create<ExplanationSceneChanger>("ExplanationSceneChanger");


}

ExplanationScene::~ExplanationScene()
{
}
