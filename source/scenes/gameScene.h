#pragma once

#include"../libs/scene.h"

/// <summary>
/// ƒQ[ƒ€‚ÌƒV[ƒ“@—Bˆê‚Ì—V‚Ñ‚ª‚ ‚éŠ
/// </summary>
class GameScene :public Scene {
public:
	GameScene();
	~GameScene();
	void Update()override;
	void Draw()override;
private:
};