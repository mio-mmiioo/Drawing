#pragma once
#include "../Scene.h"

class MatchingScene : public Scene
{
public:
	MatchingScene();
	~MatchingScene() override;
	void Update() override;
	void Draw() override;
};
