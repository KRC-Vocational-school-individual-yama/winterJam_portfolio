#pragma once
#include"../../libs/object.h"

/// <summary>
/// メインのゲームをつかさどるクラス
/// </summary>
class Board :public Object {
public:
	Board(Scene*sc);
	~Board()		override;
	void Init()		override;
	void Update()	override;
	void Draw()		override;

	VECTOR CalcDrawPos(const VECTOR& pos);
	bool GetPazzleClear();
	//ぴーすばらばら
	void PieceShuffle();
	//true さわれない
	void PieceNoTouch(bool _flag) { noTouch = _flag; }

private:
	struct Piece {
		std::vector<int>hImages;
		int hImage;
		float rotate;
		int rotNum;
		VECTOR pos;
		Vec2 index;
	};

	int hImage;
	float GraphAnimationCount;
	std::vector<int>hImagesAnimation;
	std::vector<int>hImages;
	std::vector<Piece>pieces;
	Vec2 grabIndex;
	bool keystop;
	std::vector<int>hMasks;
	float difficultyRatio;//難易度による倍率変更
	Vec2 grapOffset = {};//つかんだ時の位置を動かさない為のoffset
	std::vector<int>dispRank;//大きくなるほど前に描画
	bool noTouch;//

	int pazzleWidth ;	//ピースの横枚数
	int pazzleHeight;	//ピースの縦枚数
	int dispPieceSize;	//難易度別ピースのサイズ
	Vec2 fastPos;		//開始左上位置

	
	//描画
	int DrawGraphVector(const VECTOR& pos,int GrHandle,int TransFlag);

	int DrawExtendGraphVector(const VECTOR& pos, const VECTOR& size, int GrHandle, int TransFlag);

	int DrawBoxVector(const VECTOR& pos, const VECTOR& size, unsigned int Color, int FillFlag);

	void DrawRotaGraph3FVector(const VECTOR& pos, const VECTOR& size, float rotate, int GrHandle, int TransFlag);

	//難易度変更に備えた　情報をセットする関数
	void SetPazzleDifficulty(const Vec2& _fastPos, const Vec2& _allNum, float _difficulty);
	//マスクで画像を切り落とす
	void CutGraphToMask(int hImage, std::vector<int>& getGraphs, int _allPazzleNum);
	
	
	//２次元配列を１次元に
	int GetIndex(int x, int y);
	int GetIndex(Vec2 index) { return GetIndex(index.x, index.y); }

	//ピースが全てそろっているかの判定
	bool PieceAllClearJudge();
	//ピースが1つそろっているか
	bool PieceJudge(const Piece& piece);

	//描画順変更
	void DispRankChangeToFront(int dispRank);//昇順
	void DispRankChangeToBack(int dispRank);//降順

};