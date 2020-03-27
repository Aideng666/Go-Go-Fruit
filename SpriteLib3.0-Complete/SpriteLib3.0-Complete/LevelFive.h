#pragma once
#include "Scene.h"

class LevelFive : public Scene
{
public:
	LevelFive(std::string name);
	void InitScene(float windowWidth, float windowHeight);

	int GetBg1();
	int GetBg2();

private:
	int m_background;
	int m_background2;
};