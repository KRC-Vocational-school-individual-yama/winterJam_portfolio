#pragma once
#include"../../libs/object.h"
class Board;
class Button;
/// <summary>
/// クリア判定のクラス
/// </summary>
class ClearJudgment :public Object {
public:
	ClearJudgment(Scene* sc);
	~ClearJudgment()override;
	void Init()		override;
	void Update()	override;
	void Draw()		override;

private:
	Board* board;
	std::vector<Button*> buttons;
	bool Clear_Flag;
	int hFont;
	bool keystop;



};