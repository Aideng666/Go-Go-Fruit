#pragma once

#include "Scene.h"

class GoGoGame : public Scene
{
public:
	GoGoGame(std::string name);

	void InitScene(float windowWidth, float windowHeight);
	int GetBackground();
	int GetBlueberry();
	int GetWatermelon();

private:
	int m_background;
	int m_blueberry;
	int m_watermelon;
};

