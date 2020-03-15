#pragma once

#include "Scene.h"

class LevelTwo : public Scene
{
public:
	LevelTwo(std::string name);

	void InitScene(float windowWidth, float windowHeight);

	int GetBg1();
	int GetBg2();
	int GetElevator();
	int GetButton();
	int GetRedButton();

	bool GetButtonOn1();
	bool GetButtonOn2();

	int GetJello();
	bool GetJelloBounce();

private:
	int m_bg;
	int m_bg2;
	int m_elevator1;
	int m_button1;
	int m_redButton;

	bool turnOn1;
	bool turnOn2;

	int m_jello;
	bool turnJello;
};