#pragma once
#include "Scene.h"

class LevelFive : public Scene
{
public:
	LevelFive(std::string name);
	void InitScene(float windowWidth, float windowHeight);

	int GetBg1();
	int GetBg2();

	int GetTopBlueButton();
	int GetBotBlueButton();
	int GetRedButton();
	int GetJello();
	int GetFruitBowl();

private:
	int m_background;
	int m_background2;
	
	int m_button1;
	int m_button2;
	int m_button3;
	int m_jello;
	int m_fruitBowl;
};