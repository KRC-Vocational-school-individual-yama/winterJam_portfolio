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
	DATEDATA farstTime;//ゲーム開始時間
	DATEDATA elapsedTime;//経過時間 止めたらリセット
	DATEDATA finalDisp;//最後に描画する時間
	bool timeStop;

	int TimeDataToSec(DATEDATA data);
	DATEDATA SecToTimeData(int sec);
};

/*
int Year ;	// 年
int Mon　;	// 月
int Day　;	// 日
int Hour ;	// 時間
int Min　;	// 分
int Sec　;	// 秒
*/