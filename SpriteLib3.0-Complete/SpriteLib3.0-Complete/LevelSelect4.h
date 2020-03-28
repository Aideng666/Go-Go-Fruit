#pragma once
#include "Scene.h"

class LevelSelect4 : public Scene
{
public:
	LevelSelect4(std::string name);
	void InitScene(float windowWidth, float windowHeight);
	void Update();

	void RainbowBackground();

private:
	float m_repeatTime2 = 5.f;
	float m_lerpVal2 = 0.f;
	vec4 m_clearColor3 = vec4(0.153f, 0.992f, 0.961f, 1.f);
	vec4 m_clearColor4 = vec4(0.969f, 0.396f, 0.722f, 1.f);
};