#pragma once
#include"../../libs/object.h"

/// <summary>
/// ���C���̃Q�[���������ǂ�N���X
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
	//�ҁ[���΂�΂�
	void PieceShuffle();
	//true �����Ȃ�
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
	float difficultyRatio;//��Փx�ɂ��{���ύX
	Vec2 grapOffset = {};//���񂾎��̈ʒu�𓮂����Ȃ��ׂ�offset
	std::vector<int>dispRank;//�傫���Ȃ�قǑO�ɕ`��
	bool noTouch;//

	int pazzleWidth ;	//�s�[�X�̉�����
	int pazzleHeight;	//�s�[�X�̏c����
	int dispPieceSize;	//��Փx�ʃs�[�X�̃T�C�Y
	Vec2 fastPos;		//�J�n����ʒu

	
	//�`��
	int DrawGraphVector(const VECTOR& pos,int GrHandle,int TransFlag);

	int DrawExtendGraphVector(const VECTOR& pos, const VECTOR& size, int GrHandle, int TransFlag);

	int DrawBoxVector(const VECTOR& pos, const VECTOR& size, unsigned int Color, int FillFlag);

	void DrawRotaGraph3FVector(const VECTOR& pos, const VECTOR& size, float rotate, int GrHandle, int TransFlag);

	//��Փx�ύX�ɔ������@�����Z�b�g����֐�
	void SetPazzleDifficulty(const Vec2& _fastPos, const Vec2& _allNum, float _difficulty);
	//�}�X�N�ŉ摜��؂藎�Ƃ�
	void CutGraphToMask(int hImage, std::vector<int>& getGraphs, int _allPazzleNum);
	
	
	//�Q�����z����P������
	int GetIndex(int x, int y);
	int GetIndex(Vec2 index) { return GetIndex(index.x, index.y); }

	//�s�[�X���S�Ă�����Ă��邩�̔���
	bool PieceAllClearJudge();
	//�s�[�X��1������Ă��邩
	bool PieceJudge(const Piece& piece);

	//�`�揇�ύX
	void DispRankChangeToFront(int dispRank);//����
	void DispRankChangeToBack(int dispRank);//�~��

};