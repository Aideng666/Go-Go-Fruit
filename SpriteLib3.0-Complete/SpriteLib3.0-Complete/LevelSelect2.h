#pragma once

#include "Scene.h"

class LevelSelect2 : public Scene
{
public:
	LevelSelect2(std::string name);
	void InitScene(float windowWidth, float windowHeight);
	void Update();

	void FadeBackground();
	bool GetFade();
	void SetFade(bool fade);

	int GetMenu();
	int GetRight();
	int GetLeft();
	int GetPlay();

	int GetLevel1Template();
	int GetLevel2Template();
	int GetLevel3Template();

private:
	float m_repeatTime = 1.f;
	float m_lerpVal = 0.f;
	bool fade;
	int m_menu;
	int m_right;
	int m_left;
	int m_play;
	float timer = 0.f;
	vec4 m_clearColor2 = vec4(0.f, 0.f, 0.f, 1.f);
	vec4 m_clearColor1 = vec4(0.7058823529f, 0.9803921569f, 1.f, 1.f);

	int level1Template;
	int level2Template;
	int level3Template;
};