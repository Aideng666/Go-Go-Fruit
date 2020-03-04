#pragma once

#include "Scene.h"

class GoGoMenu : public Scene
{
public:
	GoGoMenu(std::string name);

	void InitScene(float windowWidth, float windowHeight);

	void Update() override;
	void RainbowBackground();

protected:
	float m_repeatTime = 5.f;
	float m_lerpVal = 0.f;

	vec4 m_clearColor1 = vec4(0.153f, 0.992f, 0.961f, 1.f);
	vec4 m_clearColor2 = vec4(0.969f, 0.396f, 0.722f, 1.f);
};