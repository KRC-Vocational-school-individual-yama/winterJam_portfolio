#pragma once
#include"../../libs/object.h"

class GameTime :public Object {
public :
	GameTime(Scene* sc);
	~GameTime()		override;
	void Init()		override;
	void Update()	override;
	void Draw()		override;

	void Stop();
	void Start();
private:
	DATEDATA farstTime;//�Q�[���J�n����
	DATEDATA elapsedTime;//�o�ߎ��� �~�߂��烊�Z�b�g
	DATEDATA finalDisp;//�Ō�ɕ`�悷�鎞��
	bool timeStop;

	int TimeDataToSec(DATEDATA data);
	DATEDATA SecToTimeData(int sec);
};

/*
int Year ;	// �N
int Mon�@;	// ��
int Day�@;	// ��
int Hour ;	// ����
int Min�@;	// ��
int Sec�@;	// �b
*/