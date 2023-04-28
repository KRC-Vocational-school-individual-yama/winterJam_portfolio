#include"ClearJudgment.h"
#include"board.h"
#include"../button.h"
#include"../../libs/scenemanager.h"
#include"gameTime.h"

ClearJudgment::ClearJudgment(Scene* sc)
	:Object(sc)
	,buttons()
	, hFont{ -1 }
	, keystop{ true }

{	
}

ClearJudgment::~ClearJudgment()
{
	for (auto& button : buttons)
		delete button;
}

void ClearJudgment::Init()
{
	hFont = LoadFontDataToHandle("data/font/SoukouMincho.ttf");
	assert(hFont > 0);

	board = GetScene()->Invoke<Board>();

	const int maxNum = 4;
	std::vector<std::string> names(maxNum, "");
	buttons.resize(maxNum);
	names.at(0) = "メニューへ戻る";
	names.at(1) = "難易度選択";
	names.at(2) = "もう一度";
	names.at(3) = "ゲームを終わる";

	//ボタン作成
	int buttonHeightSize = GetFontSize() * 4;
	for (int i = 0; i < names.size(); i++)
	{
		int buttonWidth = GetDrawFormatStringWidth(names.at(1).c_str()) * 4;
		
		int buttonWidthPos = SCREEN_WIDTH / 2 - buttonWidth / 2;
		VECTOR pos = VGet(buttonWidthPos, 300 + i * (buttonHeightSize * 2), 0);
		VECTOR size = VGet(buttonWidth, buttonHeightSize, 0);

		buttons.at(i) = new Button(pos, size, names.at(i));
	}


}

void ClearJudgment::Update()
{
	Clear_Flag = board->GetPazzleClear();
	if (!Clear_Flag)
	{
		return;
	}
	GetScene()->AllUpdateStop();
	this->SetMyUpdate(false);
	board->SetMyUpdate(false);
	board->PieceNoTouch(true);

	bool mouseLeft = GetMouseInput() & MOUSE_INPUT_LEFT;
	bool mouseDown = mouseLeft && !keystop;
	keystop = mouseLeft;
	if (!mouseDown)
		return;
	Vec2 mouse = {};
	GetMousePoint(&mouse.x, &mouse.y);
	for (int i = 0; i < buttons.size(); i++){
		Button* button = buttons.at(i);
		if (button->OnCollision(VGet(mouse.x, mouse.y, 0), VGet(5, 5, 5))) {
			std::string name = button->GetMyName();

			Vec2 fastPos = { 100,100 };
			Vec2 pazzleAllNum = { 5,5 };
			float difficulty = 1.f;
			if ("メニューへ戻る" == name) {
				SceneManager::SceneChange("Menu");
			}
			else if ("ゲームを終わる" == name) {
				SceneManager::SetGameEnd();
			}
			else if ("難易度選択" == name){
				SceneManager::SceneChange("DifficultySelection");
			}
			else if ("もう一度" == name){
				board->PieceShuffle();
				Clear_Flag = false;
			}
			
		}	   
	}




}

void ClearJudgment::Draw()
{
	if (!Clear_Flag)
	{
		return;
	}
	Vec2 mouse = {};
	GetMousePoint(&mouse.x, &mouse.y);
	Vec2 size = {};
	GetDrawScreenSize(&size.x, &size.y);


	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255 / 1.25);

	DrawBox(0, 0, size.x, size.y, 0x0, TRUE);//UIを開いたときの薄い黒

	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

	std::vector<int> difficultColor(buttons.size(), -1);
	int difCol = 0x4169e1;
	difficultColor.at(0) = difCol;
	difficultColor.at(1) = difCol;
	difficultColor.at(2) = difCol;
	difficultColor.at(3) = difCol;
	for (int i = 0; i < buttons.size(); i++) {
		Button* button = buttons.at(i);
		bool onButton = button->OnCollision(VGet(mouse), VGet(5, 5, 5));
		button->Draw(onButton ? 0x0c0c0c: 0xffffff, 1.0f, hFont);
	}

}
