#pragma once

#include "Scene.h"

class LevelFour : public Scene
{
public:
	LevelFour(std::string name);
	void InitScene(float windowWidth, float windowHeight);

	int GetBg1();
	int GetBg2();

	int GetBlueButton1();
	int GetBlueButton2();
	int GetRedButton();

private:
	int m_background;
	int m_background2;

	int m_button1;
	int m_button2;
	int m_button3;
};

