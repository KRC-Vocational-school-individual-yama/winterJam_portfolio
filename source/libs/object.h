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
	/// �����V�[���擾
	/// </summary>
	/// <returns></returns>
	Scene* GetScene()			{ return myScene	;}

	/// <summary>
	/// �j���t���O�@�Q�b�^�[
	/// </summary>
	/// <returns></returns>
	const bool GetDestroy()		{ return myDestroy	;}

	/// <summary>
	/// �X�V��~�t���O�@�Q�b�^�[
	/// </summary>
	/// <returns></returns>
	const bool GetStopUpdate() { return myStopUpdate; }

	/// <summary>
	/// �j���t���O�@�Z�b�^�[
	/// </summary>
	/// <param name="_flag"></param>
	void MyDestroy()			{ myDestroy = true	;}

	/// <summary>
	/// �X�V��~�t���O�@�Z�b�^�[
	/// </summary>
	/// <param name="true	">stop</param>
	/// <param name="false	">start</param>
	/// <returns></returns>
	void SetMyUpdate(bool flag = false) { myStopUpdate = flag; }

	/// <summary>
	/// Invoke�̍�  nullptr �`�F�b�N�p
	/// </summary>
	/// <typeparam name="C"></typeparam>
	/// <param name="true	">inClass</param>
	/// <param name="false	">nullptr</param>
	/// <returns></returns>
	template<class C>
	bool CheckClass();
private:
	Scene* myScene		;//�����V�[��
	bool myDestroy		;//�j���t���O
	bool myStopUpdate	;//�X�V��~�t���O true�F��~
};

template<class C>
bool Object::CheckClass(){
	if (GetScene()->Invoke<C>() != nullptr)
		return true;

	return false;
};