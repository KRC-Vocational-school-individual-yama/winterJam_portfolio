#pragma once
#include"../../libs/object.h"
#include<unordered_map>

class Sound :public Object {
public:
	Sound(Scene*sc);
	~Sound()			override;
	void Init()		override{}
	void Update()	override{}
	void Draw()		override{}

	int Load(std::string pass);
	int Play(std::string pass);
	int Get(std::string pass);
private:
	std::unordered_map<std::string, int>sounds;
};