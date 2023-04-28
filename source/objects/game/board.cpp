#include "board.h"
#include"../../libs/keyManager.h"
#include"../../libs/scenemanager.h"
#include"../../objects/common/difficultToGameSend.h"

namespace BoardConfig{
	//�s�[�X�̑傫���i�ˋN�������j
	const int PICE_SIZE = 64;
	//�s�[�X�̓ˋN(�ւ���)��������
	const int PICE_NAIL = 12;
	//�J�n����ʒuX
	const int FAST_X=100;
	//�J�n����ʒuY
	const int FAST_Y=100;
	//�s�[�X�̉�����
	const int PAZZLE_WIDTH  = 5;
	//�s�[�X�̏c����
	const int PAZZLE_HEIGHT = 5;

	//�A�j���[�V�����摜�̍ő吔
	const int ANIM_GRAPH_MAX = 4;
	//const int ANIM_GRAPH_MAX = 104;

	static float animationSpeed = 0.1;//����

	//���g�p - - - - - - - - - - - - - - - - - 
	//const Vec2 Piece_Size = {64,64};
}

namespace {
	using namespace BoardConfig;
	std::string pass = "data/texture/pieceImages/snow_img_byNvidiaCanvas.png";
	std::string passAnimation = "data/texture/pieceImages/__gif/";
	std::string maskPass = "data/texture/masks/puzzle/";

//�}�X�N�摜�̖���
	static const int maxMaskNum = 64;

	//keyDown keyUp keyINPUT ���Ǘ�����
	KeyManager* keys = nullptr;

	//Easy�̃}�X�N�e�[�u��
	const int Easy_Table[25] =
	{
		0 ,7 ,6 ,5 ,15,
		22,26,24,37,43,
		20,39,34,30,47,
		17,28,38,36,41,
		50,55,57,54,60
	};

	const int Nomal_Table[50] =
	{
		3 ,11,9 ,5 ,11,6 ,5 ,8 ,11,12,
		23,32,36,27,31,27,38,24,34,41,
		20,34,27,25,30,33,30,28,25,47,
		23,26,26,24,28,25,29,38,26,44,
		49,52,54,59,55,55,57,58,56,63

	};

	const int Hard_Table[100] =
	{
		3 ,5 ,8 ,10,6 ,12,5 ,9 ,12,15,
		17,31,28,33,27,32,29,27,33,44,
		22,29,26,31,38,32,28,25,29,44,
		20,39,27,36,32,29,39,32,34,48,
		17,35,38,26,30,27,37,31,40,42,
		21,38,37,40,30,26,38,36,32,48,
		19,37,38,36,37,38,37,38,37,47,
		24,25,29,25,28,32,28,32,38,45,
		21,30,25,29,39,37,40,30,37,46,
		49,59,59,57,54,56,58,54,53,64
	};
}

Board::Board(Scene* sc)
	:Object(sc)
	,hImage{-1}
	,GraphAnimationCount{0}
	,hImagesAnimation()
	,hImages()
	,pieces()
	,grabIndex{-1,-1}
	,keystop{false}
	//,difficultyRatio{1.}
	,difficultyRatio{1.5}
	,grapOffset{0,0}
	,dispRank()
	,pazzleWidth{ PAZZLE_WIDTH }
	,pazzleHeight{ PAZZLE_HEIGHT }
	,dispPieceSize{PICE_SIZE}
	,fastPos{FAST_X,FAST_Y}
	,noTouch{false}
{}

Board::~Board(){
	delete keys;
	DeleteGraph(hImage);
	for (auto& hMsk : hMasks) {
		DeleteMask(hMsk);
	}
	hMasks.clear();

	for (auto& hImg : hImages) {
		DeleteGraph(hImg);
	}
	hImages.clear();
	for (auto& hImgAnim : hImagesAnimation)
		DeleteGraph(hImgAnim);
}

void Board::Init(){
	//dispPieceSize = difficultyRatio * PICE_SIZE;

	keys = new KeyManager;


	//��Փx�I���œ���������
	{
		DifficultToGameSend* sendP = SceneManager::GetCommonScene()->Invoke<DifficultToGameSend>();
		Vec2 getFastPos = {};
		Vec2 getPazzleNum = {};
		float getDifficulty = {};
		sendP->GetData(getFastPos,getPazzleNum,getDifficulty);

		SetPazzleDifficulty(getFastPos,getPazzleNum,getDifficulty);
	}


	//�����ǂݍ��ׂ݂̈́@�܂��ǂݍ���
	hImage = LoadGraph(pass.c_str());
	assert(hImage > 0);
	
	//���p�Y������
	const unsigned int allPazzleNum = pazzleWidth*pazzleHeight;
	hImages.resize(allPazzleNum);
	pieces .resize(allPazzleNum);
	hMasks .resize(maxMaskNum);
	dispRank.resize(allPazzleNum);

	//�}�X�N�̓ǂݍ���
	char buf[255];
	for (int i = 0; i < maxMaskNum; i++) {
		sprintf_s<255>(buf, (maskPass + "%d" + ".png").c_str(), i + 1);
		 int hMsk= LoadMask(buf);
		 assert(hMsk > 0);
		 hMasks.at(i)=hMsk;
	}

	//�}�X�N�ŉ摜��؂藎�Ƃ�
	CutGraphToMask(hImage, hImages,allPazzleNum);


	//�p�Y���A�j���[�V�����ׂ̘̈A�ԓǍ�
	//std::vector<int>animationGraphs(ANIM_GRAPH_MAX,-1);//�A�j���[�V�����摜
	hImagesAnimation.resize(ANIM_GRAPH_MAX,-1);//�A�j���[�V�����摜
	char buf_animation[255];
	for (int i = 0; i < hImagesAnimation.size(); i++) {
		sprintf_s<255>(buf_animation, (passAnimation + "%d" + ".png").c_str(), i +1 );
		int hImg = LoadGraph(buf_animation);
		assert(hImg > 0);
		hImagesAnimation.at(i) = hImg;
	}
	//�A�Ԃ��ꂼ��̃}�X�N�؂�
	std::vector<std::vector<int>> animationGraphs;
	animationGraphs.resize(ANIM_GRAPH_MAX);
	for (int i = 0; i < hImagesAnimation.size(); i++) {
		std::vector<int> temphImages(allPazzleNum, -1);
		CutGraphToMask(hImagesAnimation.at(i), temphImages,allPazzleNum);
		animationGraphs.at(i) = temphImages;
	}


	////�}�X�N�ŉ摜��؂藎�Ƃ�
	//	SetUseMaskScreenFlag(TRUE);//�}�X�N�g�p
	//for (int i = 0; i < hImages.size(); i++) {
	//	int x = i % pazzleWidth;
	//	int y = i / pazzleWidth;
	//	int width  = x * (PICE_SIZE);
	//	int height = y * (PICE_SIZE);
	//
	//	Vec2 maskSize = {};
	//	int index = (i % 2)*4+24;//ToDo:���������Ɍ�ŕς���
	//	GetMaskSize(&maskSize.x, &maskSize.y, hMasks.at(index));
	//	int hScreen = MakeScreen(maskSize.x,maskSize.y, TRUE);
	//	SetDrawScreen(hScreen);
	//
	//	DrawMask(0, 0, hMasks.at(index), DX_MASKTRANS_BLACK);
	//	
	//	int offset = PICE_NAIL;
	//	Vec2 disp = {};
	//	disp.x =  offset - width;
	//	disp.y =  offset - height;
	//	Vec2 pazzleNum = {PICE_SIZE*pazzleWidth,PICE_SIZE*pazzleHeight};
	//	DrawExtendGraph(  disp.x, disp.y
	//					, disp.x + pazzleNum.x, disp.y + pazzleNum.y
	//					,hImage,TRUE);
	//
	//	//�g�����}�X�N�؂蔲����߂�
	//	FillMaskScreen(0);
	//
	//	hImages.at(i) = hScreen;
	//}
	//	//�g�����������ɖ߂�
	//	SetUseMaskScreenFlag(FALSE);
	//	SetDrawScreen(DX_SCREEN_BACK);



	//Piece�̏�����
	for (int i = 0; i < pieces.size(); i++) {
		int x = i % pazzleWidth;
		int y = i / pazzleWidth;
		pieces.at(i).hImages.resize(hImagesAnimation.size(),-1);
		for (int j = 0; j < hImagesAnimation.size(); j++) {
			pieces.at(i).hImages.at(j) = animationGraphs.at(j).at(i);
		}

		pieces.at(i).hImage = hImages.at(i);
		pieces.at(i).rotNum = 0;
		pieces.at(i).rotate = DX_PI_F / 180 * (45 *pieces.at(i).rotNum);
		VECTOR disp = VGet(x * dispPieceSize, y * dispPieceSize, 0);
		pieces.at(i).pos = CalcDrawPos(disp);
		pieces.at(i).index = Vec2{ x,y };
		dispRank.at(i) = i;
	}

	PieceShuffle();
}

void Board::Update() {
	GraphAnimationCount += animationSpeed;
	if (GraphAnimationCount >= ANIM_GRAPH_MAX )
		animationSpeed = -animationSpeed;
	if (GraphAnimationCount <= 0)
		animationSpeed = -animationSpeed;

	if (noTouch)
		return;

	Vec2 mouse = Vec2::zero();
	GetMousePoint(&mouse.x, &mouse.y);
	bool mouseLeft = GetMouseInput() & MOUSE_INPUT_LEFT;
	bool grab = mouseLeft && !keystop;//����
	bool grabNow = mouseLeft && keystop;//���ݒ�
	bool letGo = !mouseLeft && keystop;//������
	keystop = mouseLeft;//1�t���[���̕ۑ�



		if (grab) {//����
			for (int i = 0; i <pieces.size(); i++) {//�`�揇�ŏ�������
				int pieceIndex = dispRank.at(i);
				Piece& piece = pieces.at(pieceIndex);
				VECTOR size = VGet(dispPieceSize, dispPieceSize, 0);
				GetGraphSizeF(piece.hImages.at(0), &size.x, &size.y);
				size *= VGet(difficultyRatio, difficultyRatio, 0);
				bool col = SquareCollision(piece.pos, size, mouse, VGet(5, 5, 5));

				if (col) {

					grabIndex = piece.index;

					grapOffset = mouse - piece.pos;

				}
			}

		}

		if (grabNow) {//���ݒ�
			int index = GetIndex(grabIndex);//�P�����z��ɉ��H
			if (0 <= index && index < pieces.size()) {//�v�f���͈͓��ɂ��邩

				Piece& pice = pieces.at(index);


				pice.pos = mouse - grapOffset;//���W�X�V

				DispRankChangeToFront(index);

				//��]
				{
					if (keys->Down(KEY_INPUT_LSHIFT) || keys->Down(KEY_INPUT_A)) {
						pice.rotNum--;
						pice.rotate = DX_PI_F / 180 * (45 * pice.rotNum);
					}
					else if (keys->Down(KEY_INPUT_RSHIFT) || keys->Down(KEY_INPUT_D)) {
						pice.rotNum++;
						pice.rotate = DX_PI_F / 180 * (45 * pice.rotNum);
					}
				}

			}
		}


		if (letGo) {//������
			grabIndex = { -1,-1 };//�͈͊O���w��
		}
	

#ifdef _DEBUG
	//�f�o�b�O�p
	{
		//�f�o�b�O�p ��Փx�ύX
		if (CheckHitKey(KEY_INPUT_1)) {
			difficultyRatio = 1.0;
			dispPieceSize = difficultyRatio * PICE_SIZE;
		}
		else if (CheckHitKey(KEY_INPUT_2)) {
			difficultyRatio = 1.5;
			dispPieceSize = difficultyRatio * PICE_SIZE;
		}
		else if (CheckHitKey(KEY_INPUT_3)) {
			difficultyRatio = 2.0;
			dispPieceSize = difficultyRatio * PICE_SIZE;
		}

		//�f�o�b�O�p �΂�΂�
		if (CheckHitKey(KEY_INPUT_R)) {
			Vec2 screen = {};
			GetDrawScreenSize(&screen.x, &screen.y);

			for (int i = pieces.size() - 1; i >= 0; i--) {
				Piece& piece = pieces.at(i);

				piece.pos.x = GetRand(screen.x - dispPieceSize);
				piece.pos.y = GetRand(screen.y - dispPieceSize);
				piece.rotNum = GetRand(8);
				piece.rotate = DX_PI_F / 180 * (piece.rotNum * 45);
				dispRank.at(i) = i;
			}

		}
		if (CheckHitKey(KEY_INPUT_T)) {
			for (int i = pieces.size() - 1; i >= 0; i--) {

				int x = i % pazzleWidth;
				int y = i / pazzleWidth;
				Piece& piece = pieces.at(i);
				pieces.at(i).rotNum = 0;
				pieces.at(i).rotate = DX_PI_F / 180 * (45 * pieces.at(i).rotNum);
				VECTOR disp = VGet(x * dispPieceSize, y * dispPieceSize, 0);
				pieces.at(i).pos = CalcDrawPos(disp);
				dispRank.at(i) = i;
}
		}

	}
#endif 

	//�s�[�X�̈ʒu�Ɖ�]�������Ă���΁@�z����
	for (auto& piece : pieces) {


		if (!PieceJudge(piece))//�ʒu�ƌ����������Ă��邩
			continue;
		
		piece.pos = CalcDrawPos( piece.index * Vec2{dispPieceSize,dispPieceSize});
		DispRankChangeToBack(GetIndex(piece.index));
		
	}

	//��ʊO�Ƀs�[�X���s���Ȃ��悤�ɂ���
	for (auto& piece : pieces) {
		Vec2 screenSize = {};
		GetDrawScreenSize(&screenSize.x,&screenSize.y);
		float graphSize = 0;
		GetGraphSizeF(piece.hImages.at(0),&graphSize,&graphSize);
		graphSize *= difficultyRatio;
		piece.pos.x = std::clamp(piece.pos.x, 0.f, (float)screenSize.x - graphSize );
		piece.pos.y = std::clamp(piece.pos.y, 0.f, (float)screenSize.y - graphSize );
	}


}

void Board::Draw(){



	VECTOR dispV=VGet(0,0,0);
	float size= dispPieceSize;
	float piceNailSize = PICE_NAIL*difficultyRatio;

	//���摜�@�`��
	{
		Vec2 fast = fastPos + Vec2{(int)piceNailSize,(int)piceNailSize};
		VECTOR gridSize= {size * pazzleWidth,size * pazzleHeight,0};
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255 / 2);
		
		//DrawExtendGraph(fast.x,fast.y,fast.x+ gridSize.x, fast.y+ gridSize.y, hImage, TRUE);
		DrawExtendGraph(fast.x,fast.y,fast.x+ gridSize.x, fast.y+ gridSize.y, hImagesAnimation.at(0), TRUE);

		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	}


	//�O���b�h�`��
	for (int i = 0; i < pieces.size(); i++) {
		int x = i % pazzleWidth;
		int y = i / pazzleWidth;

		dispV = CalcDrawPos(VGet(x * size+ piceNailSize, y * size + piceNailSize, 0));
		DrawBoxVector(dispV, VGet(size,size,size), 0x0, FALSE);
	}

	//�s�[�X�`��
	for (int i = 0; i < pieces.size();i++) {
		const Piece& disp = pieces.at(dispRank.at(i));
		int graphSize = 0;//���������炿�傢���艟��
		GetGraphSize(disp.hImage, &graphSize, &graphSize);
		float graphCalcSize = graphSize * difficultyRatio;
		VECTOR sizes = VGet(graphCalcSize,graphCalcSize,0);


		//�s�[�X�`��-------
		//DrawExtendGraphVector(disp.pos, sizes, disp.hImage, TRUE);
		DrawRotaGraph3FVector(disp.pos,sizes, disp.rotate, disp.hImage, TRUE);
		DrawRotaGraph3FVector(disp.pos,sizes, disp.rotate, disp.hImages.at((int)GraphAnimationCount%disp.hImages.size()), TRUE);
		//�s�[�X�`��-------
	}

	
}

VECTOR Board::CalcDrawPos(const VECTOR& pos){
	VECTOR anser=VGet(0,0,0);

	anser.x = fastPos.x + pos.x;
	anser.y = fastPos.y + pos.y;
	anser.z =  pos.y;

	return anser;
}

bool Board::GetPazzleClear(){
	return PieceAllClearJudge();
}

void Board::SetPazzleDifficulty(const Vec2& _fastPos, const Vec2& _allNum, float _difficulty){
	fastPos.x = _fastPos.x;
	fastPos.y = _fastPos.y;
	pazzleWidth = _allNum.x;
	pazzleHeight= _allNum.y;
	difficultyRatio = _difficulty;
	dispPieceSize = difficultyRatio * PICE_SIZE;
}

void Board::CutGraphToMask(int hImage, std::vector<int>& getGraphs, int _allPazzleNum){

	//�}�X�N�ŉ摜��؂藎�Ƃ�
	SetUseMaskScreenFlag(TRUE);//�}�X�N�g�p
	for (int i = 0; i < (pazzleWidth*pazzleHeight); i++) {
		int x = i % pazzleWidth;
		int y = i / pazzleWidth;
		int width = x * (PICE_SIZE);
		int height = y * (PICE_SIZE);
		int index = 0;//ToDo:���������Ɍ�ŕς���
		if (_allPazzleNum == 25)
		{
			index = Easy_Table[i];
		}
		else if (_allPazzleNum == 50)
		{
			index = Nomal_Table[i];
		}
		else if (_allPazzleNum == 100)
		{
			index = Hard_Table[i] - 1;
		}
		Vec2 maskSize = {};

		GetMaskSize(&maskSize.x, &maskSize.y, hMasks.at(index));
		int hScreen = MakeScreen(maskSize.x, maskSize.y, TRUE);
		SetDrawScreen(hScreen);

		DrawMask(0, 0, hMasks.at(index), DX_MASKTRANS_BLACK);

		int offset = PICE_NAIL;
		Vec2 disp = {};
		disp.x = offset - width;
		disp.y = offset - height;
		Vec2 pazzleNum = { PICE_SIZE * pazzleWidth,PICE_SIZE * pazzleHeight };
		DrawExtendGraph(disp.x, disp.y
			, disp.x + pazzleNum.x, disp.y + pazzleNum.y
			, hImage, TRUE);

		//�g�����}�X�N�؂蔲����߂�
		FillMaskScreen(0);

		getGraphs.at(i) = hScreen;
	}
	//�g�����������ɖ߂�
	SetUseMaskScreenFlag(FALSE);
	SetDrawScreen(DX_SCREEN_BACK);

}
void Board::PieceShuffle(){
	noTouch = false;
	Vec2 screen = {};
	GetDrawScreenSize(&screen.x, &screen.y);

	for (int i = pieces.size() - 1; i >= 0; i--) {
		Piece& piece = pieces.at(i);

		piece.pos.x = GetRand(screen.x - dispPieceSize);
		piece.pos.y = GetRand(screen.y - dispPieceSize);
		piece.rotNum = GetRand(8);
		piece.rotate = DX_PI_F / 180 * (piece.rotNum * 45);
		dispRank.at(i) = i;
	}
}

int Board::DrawGraphVector(const VECTOR& pos, int GrHandle, int TransFlag){
	return DrawGraph(pos.x,pos.y,GrHandle, TransFlag);
}

int Board::DrawExtendGraphVector(const VECTOR& pos, const VECTOR& size, int GrHandle, int TransFlag){
	return DrawExtendGraph(pos.x,pos.y,pos.x+size.x,pos.y+size.y,GrHandle,TransFlag);
}

int Board::DrawBoxVector(const VECTOR& pos, const VECTOR& size, unsigned int Color, int FillFlag){
	return DrawBox(pos.x,pos.y,pos.x+size.x,pos.y+size.y,Color,FillFlag);
}
void Board::DrawRotaGraph3FVector(const VECTOR& pos, const VECTOR& size, float rotate, int GrHandle, int TransFlag) {

	int graphX = 0, graphY = 0;
	GetGraphSize(GrHandle, &graphX, &graphY);
	//���q��float�^�ɂ����float�ŋA���Ă���i�����j
	float Fsize_x = size.x, Fsize_y = size.y;
	float size_x = Fsize_x / graphX;
	float size_y = Fsize_y / graphY;
	DrawRotaGraph3F(pos.x + size.x / 2.f, pos.y + size.y / 2.f, graphX / 2.f, graphY / 2.f, size_x, size_y, rotate, GrHandle, TransFlag);
}

int Board::GetIndex(int x, int y){
	return x+y*pazzleWidth;
}

bool Board::PieceAllClearJudge(){
	bool anser = true;

	for (const Piece& piece:pieces) {
		anser = PieceJudge(piece) && anser;
	}

	return anser;
}

bool Board::PieceJudge(const Piece& piece){

	//VECTOR allPiecePos = VGet(fastPos);
	//VECTOR allPieceSize = VGet(pazzleWidth * dispPieceSize, pazzleHeight * dispPieceSize, 0);
	
	VECTOR justPos = Vec2{ dispPieceSize,dispPieceSize }*piece.index + fastPos;
	VECTOR justSize = VGet(dispPieceSize/3, dispPieceSize/3, 0);

	VECTOR piecePos = piece.pos;
	VECTOR pieceSize = VGet(dispPieceSize/3, dispPieceSize/3, 0);

	if (!SquareCollision(justPos, justSize, piecePos, pieceSize))
		return false;

	if (piece.rotNum % 8 != 0)
		return false;


	return true;

}

void Board::DispRankChangeToFront(int _dispRank){
	auto it= std::find(dispRank.begin(), dispRank.end(), _dispRank);
	if (it == dispRank.end())
		return;

	//����ւ�
	int endNum= dispRank.at(dispRank.size()-1);
	int nowNum = (*it);
	
	(*it) = endNum;
	dispRank.at(dispRank.size() - 1) = nowNum;

	//int nowNum = (*it);
	//int endNum = dispRank.at(0);
	////.at(�Ō�)���󂯂�
	//for (int i = 0; i < dispRank.size()-1; i++) {
	//	dispRank.at(i) = dispRank.at(i+1);
	//}
	//dispRank.at(dispRank.size()-1) = -1;
	//
	////�T����������l�߂镪�𐔂���
	//int loopCount = 0;
	//for (int i = 0; dispRank.at(i) != nowNum; i++) {
	//	loopCount = i;
	//	if (loopCount >= dispRank.size() - 1) {
	//		loopCount = dispRank.size() - 1;
	//		endNum = dispRank.at(0);
	//		break;
	//	}
	//}
	//
	////�l�߂�
	//for (int i = loopCount + 1; i < dispRank.size() - 1; i++) {
	//	dispRank.at(i) = dispRank.at(i + 1);
	//}
	//dispRank.at(dispRank.size() - 2) = endNum;
	//
	//dispRank.at(dispRank.size() - 1) = nowNum;
}

void Board::DispRankChangeToBack(int _dispRank){
	auto it = std::find(dispRank.begin(), dispRank.end(), _dispRank);
	if (it == dispRank.end())
		return;

	//����ւ�
	//int nowNum = (*it);
	//int endNum = dispRank.at(0);
	//
	//(*it) = endNum;
	//dispRank.at(0)=nowNum;



	
	int nowNum = (*it);
	int endNum = dispRank.at(dispRank.size() - 1);
	//.at(0)���󂯂�
	for (int i = dispRank.size() - 1; i >= 1; i--) {
		dispRank.at(i) = dispRank.at(i - 1);
	}
	dispRank.at(0) = -1;
	//�T����������l�߂镪�𐔂���
	int loopCount=0;
	for (int i = 0; dispRank.at(i) != nowNum; i++) {
		loopCount = i;
		if (loopCount >= dispRank.size() - 1){
			loopCount= dispRank.size() - 1;
			endNum = dispRank.at(dispRank.size()-1);
			break;
		}
	}
	//�l�߂�
	for (int i = loopCount+1; i < dispRank.size()-1; i++) {
		dispRank.at(i) = dispRank.at(i + 1);
	}
	dispRank.at(dispRank.size() - 1) = endNum;

	dispRank.at(0) = nowNum;

}
