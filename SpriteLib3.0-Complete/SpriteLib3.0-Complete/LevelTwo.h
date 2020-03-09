#pragma once

#include "Scene.h"

class LevelTwo : public Scene
{
public:
	LevelTwo(std::string name);

	void InitScene(float windowWidth, float windowHeight);

	int GetCam();
	int GetButton();
	int GetButton2();
	int GetElevator();
	int GetElevator2();
	int GetBackground();
	int GetBackground2();

	bool GetButtonOn1();
	bool GetButtonOn2();

private:

	int m_cam;
	int m_button;
	int m_button2;
	int m_elevator;
	int m_elevator2;
	int m_background;
	int m_background2;

	bool turnOn1 = false;
	bool turnOn2 = false;
};