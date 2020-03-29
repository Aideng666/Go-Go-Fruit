#pragma once
#include "Scene.h"

class LevelSelect5 : public Scene
{
public:
	LevelSelect5(std::string name);
	void InitScene(float windowWidth, float windowHeight);
	void Update();

	void RainbowBackground();
	void FadeBackground();
	bool GetFade();
	void SetFade(bool fade);

	int GetMenu();
	int GetSelect1();
	int GetSelect2();
	int GetSelect3();
	int GetSelect4();
	int GetSelect5();
	int GetLabel1();
	int GetLabel2();
	int GetLabel3();
	int GetLabel4();
	int GetLabel5();
	int GetText();
	int GetBorder();
	int GetPlay();
	int GetMedal(), GetMedal2(), GetMedal3(), GetMedal4(), GetMedal5();

private:
	float m_repeatTime = 1.f;
	float m_lerpVal = 0.f;
	float m_repeatTime2 = 5.f;
	float m_lerpVal2 = 0.f;
	bool fade;
	int m_menu;
	int select1;
	int select2;
	int select3;
	int select4;
	int select5;
	int label1;
	int label2;
	int label3;
	int label4;
	int label5;
	int m_text;
	int m_border;
	int m_play;
	int m_medal, m_medal2, m_medal3, m_medal4, m_medal5;
	float timer = 0.f;
	vec4 m_clearColor2 = vec4(0.f, 0.f, 0.f, 1.f);
	vec4 m_clearColor1 = vec4(0.7058823529f, 0.9803921569f, 1.f, 1.f);
	vec4 m_clearColor3 = vec4(0.863f, 0.812f, 1.f, 1.f);
	vec4 m_clearColor4 = vec4(1.f, 0.796f, 0.835f, 1.f);
};