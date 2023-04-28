#include "titleScene.h"

#include"../libs/scenemanager.h"
#include"../objects/title/titleobject.h"
#include"../objects/common/sound.h"

TitleScene::TitleScene(){
	//SetBackgroundColor(0xff,0xff,0x84);
	SetBackgroundColor(0xe5, 0xff, 0xff);

	Create<TitleObject>();
	SceneManager::GetCommonScene()->Create<Sound>("Sound");


}
TitleScene::~TitleScene(){
}