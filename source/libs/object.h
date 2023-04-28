#pragma once

#include"myDxLib.h"

#include<string>
#include<vector>
#include<list>
class Scene;

class Object {
public:
	Object(Scene* sc)
		:myScene		(sc) 
		,myDestroy		(false)
		,myStopUpdate	(false)
	{}
	virtual ~Object()		=default;
	virtual void Init()		=0;
	virtual void Update()	=0;
	virtual void Draw()		=0;


	/// <summary>
	/// 所属シーン取得
	/// </summary>
	/// <returns></returns>
	Scene* GetScene()			{ return myScene	;}

	/// <summary>
	/// 破棄フラグ　ゲッター
	/// </summary>
	/// <returns></returns>
	const bool GetDestroy()		{ return myDestroy	;}

	/// <summary>
	/// 更新停止フラグ　ゲッター
	/// </summary>
	/// <returns></returns>
	const bool GetStopUpdate() { return myStopUpdate; }

	/// <summary>
	/// 破棄フラグ　セッター
	/// </summary>
	/// <param name="_flag"></param>
	void MyDestroy()			{ myDestroy = true	;}

	/// <summary>
	/// 更新停止フラグ　セッター
	/// </summary>
	/// <param name="true	">stop</param>
	/// <param name="false	">start</param>
	/// <returns></returns>
	void SetMyUpdate(bool flag = false) { myStopUpdate = flag; }

	/// <summary>
	/// Invokeの際  nullptr チェック用
	/// </summary>
	/// <typeparam name="C"></typeparam>
	/// <param name="true	">inClass</param>
	/// <param name="false	">nullptr</param>
	/// <returns></returns>
	template<class C>
	bool CheckClass();
private:
	Scene* myScene		;//所属シーン
	bool myDestroy		;//破棄フラグ
	bool myStopUpdate	;//更新停止フラグ true：停止
};

template<class C>
bool Object::CheckClass(){
	if (GetScene()->Invoke<C>() != nullptr)
		return true;

	return false;
};