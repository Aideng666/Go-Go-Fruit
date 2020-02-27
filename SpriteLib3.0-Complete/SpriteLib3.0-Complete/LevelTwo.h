#pragma once

#include "Scene.h"

class LevelTwo : public Scene
{
public:
	LevelTwo(std::string name);

	void InitScene(float windowWidth, float windowHeight);

	int GetCam();

private:

	int m_cam;

};

