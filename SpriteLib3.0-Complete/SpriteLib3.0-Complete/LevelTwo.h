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

private:

	int m_cam;
	int m_button;
	int m_button2;
	int m_elevator;
	int m_elevator2;
	int m_background;
	int m_background2;
};