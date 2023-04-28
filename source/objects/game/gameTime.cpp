#include "gameTime.h"
#include"../../libs/scene.h"
#include"board.h"

GameTime::GameTime(Scene* sc)
	:Object(sc)
	,farstTime()
	,elapsedTime()
	,finalDisp()
	,timeStop{false}
{}

GameTime::~GameTime(){

}

void GameTime::Init(){
	GetDateTime(&farstTime);

	
}

void GameTime::Update(){

	DATEDATA nowTime;
	GetDateTime(&nowTime);
	Board* boardP=GetScene()->Invoke<Board>();	
	
	bool stop = boardP->GetPazzleClear();

	
	if (stop)
		Stop();
	else
		Start();


	//calc

	int nowSec = TimeDataToSec(nowTime);
	int farstSec = TimeDataToSec(farstTime);

	elapsedTime= SecToTimeData(nowSec - farstSec);

	if(!stop || timeStop)
	 finalDisp = elapsedTime;//•`‰æ—p‚É“ü‚ê‚é
}

void GameTime::Draw(){

	int hour = finalDisp.Hour;
	int min  = finalDisp.Min;
	int sec  = finalDisp.Sec;

	DrawFormatString(SCREEN_WIDTH/1.5,100,0x0,"%3dŽžŠÔ %3d•ª %3d•b",hour,min,sec);
}

void GameTime::Stop(){
	timeStop = true;

	DATEDATA nowTime;
	GetDateTime(&nowTime);

	int nowT = TimeDataToSec(nowTime);
	int myTime = TimeDataToSec(finalDisp);

	farstTime = SecToTimeData(nowT - myTime);

}

void GameTime::Start(){
	timeStop = false;

}

int GameTime::TimeDataToSec(DATEDATA data){
	int anserTime = 0;
	
	anserTime  = data.Hour;
	anserTime *= 60;
	anserTime += data.Min;
	anserTime *= 60;
	anserTime += data.Sec;
	
	return anserTime;
}

DATEDATA GameTime::SecToTimeData(int sec){
	DATEDATA anser;
	int min= sec / 60;
	int hou = min / 60;
	anser.Sec	= sec-min*60;
	anser.Min	= min-hou*60;
	anser.Hour	=hou;

	return anser;
}
