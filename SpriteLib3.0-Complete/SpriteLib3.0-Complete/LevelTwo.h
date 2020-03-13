#pragma once

#include "Scene.h"

class LevelTwo : public Scene
{
public:
	LevelTwo(std::string name);

	void InitScene(float windowWidth, float windowHeight);

	int GetBg1();
	int GetBg2();

private:
	int m_bg;
	int m_bg2;
};

