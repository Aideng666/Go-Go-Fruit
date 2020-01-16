#pragma once

#include "Scene.h"
class GoGoGame : public Scene
{
public:

	GoGoGame(std::string name);

	void InitScene(float windowWidth, float windowHeight);
	int GetBackground();

private:
	int m_background;
};

