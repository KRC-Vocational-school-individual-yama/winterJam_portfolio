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

	//�{�^���쐬
	int buttonHeightSize = GetFontSize() * 4;
	std::string backStr = "�߂�";
	backButton = new Button(VGet(50, 700, 0), VGet(GetDrawFormatStringWidth(backStr.c_str()) * 4, buttonHeightSize, 0), backStr);
	sound = SceneManager::GetCommonScene()->Invoke<Sound>();
}

void ExplanationSceneChanger::Update(){
	SceneChanger();



	bool mouseLeft = GetMouseInput() & MOUSE_INPUT_LEFT;
	bool mouseDown = mouseLeft && !keystop;
	keystop = mouseLeft;

	if (!mouseDown)//�N���b�N���Ă��Ȃ������炱���ŏI��
		return;

	Vec2 mouse = {};
	GetMousePoint(&mouse.x, &mouse.y);

	if (backButton->OnCollision(VGet(mouse), VGet(5, 5, 5))) {
		sound->Play("����{�^��������3.mp3");
		SceneManager::SceneChange("Menu");
	}
}

void ExplanationSceneChanger::Draw(){
#ifdef _DEBUG
	Vec2 size = {};
	GetDrawScreenSize(&size.x,&size.y);
	std::string str = "";
	str += "�f�o�b�O�p�\��\n";
	str += "Menu\n";
	str += "�@next : Space\n";
	str += "\n";
	DrawFormatString(size.x/20,size.y/2,0x0,str.c_str());
#endif

	DrawStringToHandle(300,300,"�p�Y���s�[�X�����ݒ��uA��D�v�L�[�ŉ�]���܂��B\n�}�E�X�ő���ł��܂��B\n�����Ԃ������ėp�ӂł��܂���ł����B�B�B", 0x0,hFont);

	Vec2 mouse = {};
	GetMousePoint(&mouse.x, &mouse.y);

	//�߂�{�^��
	bool backOnButton = backButton->OnCollision(VGet(mouse), VGet(5, 5, 5));
	backButton->Draw(backOnButton ? 0xc0c0c0 : 0xf, 1.0f, hFont);
}

void ExplanationSceneChanger::SceneChanger(){
#ifdef _DEBUG
	if (keys->Down(KEY_INPUT_SPACE))
		SceneManager::SceneChange("Menu");
#endif
}
