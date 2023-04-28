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
		 if (scene == "boot")						return new BootScene();					//�f�o�b�O�p
	else if (scene == "Title")					return new TitleScene();				// �^�C�g��
	else if (scene == "Menu")					return new MenuScene();					// �I����ʁi�^�C�g���̎��@
	else if (scene == "DifficultySelection")	return new DifficultySelectionScene();	// ��Փx�I���V�[��
	else if (scene == "Game")					return new GameScene();					// �p�Y���Q�[���V�[��
	else if (scene == "Explanation")			return new ExplanationScene();			// �����V�[��
	else {
		MessageBox(NULL, ("���̃V�[���͂���܂���\n" + scene + "\n" + "�����������Ƒ��s�ł��܂�").c_str(), "SceneFactory", MB_ICONERROR | MB_OK);
		assert(false);
		return nullptr;
	}

}
