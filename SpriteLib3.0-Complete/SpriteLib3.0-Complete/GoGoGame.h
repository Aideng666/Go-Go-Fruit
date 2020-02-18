#pragma once

#include "Scene.h"

class GoGoGame : public Scene
{
public:
	GoGoGame(std::string name);

	void InitScene(float windowWidth, float windowHeight);
	int GetBackground();
	int GetButton();
	int GetPlat();

private:
	int m_background;
	int m_button;
	int m_movingPlat;
};

