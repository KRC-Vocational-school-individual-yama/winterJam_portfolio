#pragma once

#include"../libs/scene.h"

/// <summary>
/// �Q�[���̃V�[���@�B��̗V�т����鏊
/// </summary>
class GameScene :public Scene {
public:
	GameScene();
	~GameScene();
	void Update()override;
	void Draw()override;
private:
};