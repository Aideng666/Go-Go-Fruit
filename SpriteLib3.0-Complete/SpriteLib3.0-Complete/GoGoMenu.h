#pragma once

#include "Scene.h"

class GoGoMenu : public Scene
{
public:
	GoGoMenu(std::string name);

	void InitScene(float windowWidth, float windowHeight);
	void Update();

	void FadeBackground();

	bool GetFade();
	int GetMenu();
	void SetFade(bool fade);

	int GetSpike1();
	int GetSpike2();

protected:

	float m_repeatTime = 1.f;
	float m_lerpVal = 0.f;

	int m_menu;
	int m_spike1;
	int m_spike2;
	bool fade;
	bool swap;
	float timer = 0.f;

	vec4 m_clearColor2 = vec4(0.f, 0.f, 0.f, 1.f);
	vec4 m_clearColor1 = vec4(0.7058823529f, 0.9803921569f, 1.f, 1.f);

};