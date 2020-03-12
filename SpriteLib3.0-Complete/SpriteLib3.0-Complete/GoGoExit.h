#pragma once

#include "Scene.h"

class GoGoExit : public Scene
{
public:
	GoGoExit(std::string name);

	void InitScene(float windowWidth, float windowHeight);

	int GetSpike1();
	int GetSpike2();

private:
	int m_spike1;
	int m_spike2;
};
