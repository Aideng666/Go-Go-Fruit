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

	bool GetButtonOn1();
	bool GetButtonOn2();

private:
	int m_bg;
	int m_bg2;
	int m_elevator1;
	int m_button1;

	bool turnOn1;
	bool turnOn2;
};

