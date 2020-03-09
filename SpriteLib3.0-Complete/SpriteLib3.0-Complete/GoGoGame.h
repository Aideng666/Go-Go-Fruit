#pragma once

#include "Scene.h"

class GoGoGame : public Scene
{
public:
	GoGoGame(std::string name);

	void InitScene(float windowWidth, float windowHeight);
	int GetBackground();
	int GetBackground2();
	int GetButton();
	int GetCam();
	int GetElevator();

	bool GetButtonOn();

private:
	int m_background;
	int m_background2;
	int m_button;
	int m_cam;
	int m_elevator;

	bool turnOn = false;
};