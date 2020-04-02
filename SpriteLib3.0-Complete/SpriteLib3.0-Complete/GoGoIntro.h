#pragma once

#include "Scene.h"

class GoGoIntro : public Scene
{
public:
	GoGoIntro(std::string name);
	void InitScene(float windowWidth, float windowHeight);

	int GetBg1();
	int GetBg2();

	void PlayIntro();

private: 
	int m_bg;
	int m_bg2;
};
