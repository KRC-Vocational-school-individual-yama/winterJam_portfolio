#pragma once
#include"../../libs/object.h"

/// <summary>
/// 難易度選択のデータをボードクラスに送るためのクラス
/// </summary>
class DifficultToGameSend :public Object {
public:
	DifficultToGameSend(Scene* sc)
		:Object(sc)
		,difficulty{0.f}
		,fastPos{0,0}
		,allNum{0,0}
	{}
	~DifficultToGameSend()override{}
	void Init()		override{}
	void Update()	override{}
	void Draw()		override{}

	void SetData(Vec2 _fastPos,Vec2 _allNum,float _difficulty) {
		fastPos = _fastPos;
		allNum = _allNum;
		difficulty = _difficulty;
	}
	void GetData(Vec2& _fastPos,Vec2& _allNum,float& _difficulty) {
		_fastPos = fastPos;
		_allNum = allNum;
		_difficulty = difficulty;
	}
private:
	float difficulty;
	Vec2  fastPos;
	Vec2  allNum;
};