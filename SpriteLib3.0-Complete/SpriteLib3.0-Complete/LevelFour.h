#pragma once

#include "Scene.h"

class LevelFour : public Scene
{
public:
	LevelFour(std::string name);
	void InitScene(float windowWidth, float windowHeight);

	int GetBg1();
	int GetBg2();

private:
	int m_background;
	int m_background2;
};

