#pragma once

#include"../libs/scene.h"

/// <summary>
/// ゲームのシーン　唯一の遊びがある所
/// </summary>
class GameScene :public Scene {
public:
	GameScene();
	~GameScene();
	void Update()override;
	void Draw()override;
private:
};