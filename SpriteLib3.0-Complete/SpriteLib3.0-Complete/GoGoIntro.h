#pragma once

#include "Scene.h"

class GoGoIntro : public Scene
{
public:
	GoGoIntro(std::string name);
	void InitScene(float windowWidth, float windowHeight);
	void Update();

	int GetBg1();
	int GetBg2();

	bool GetEnd();

	void SetStart(bool start);

	void PlayIntro();

private: 
	int m_bg;
	int m_bg2;
	int melon;
	int berry;
	int text;
	int bowl;

	int text1;
	int text2;
	int text3;

	float timer = 0.f;

	bool start;
	bool step1;
	bool step2;
	bool step3;
	bool step4;
	bool step5;
	bool step6;
	bool step7;
	bool step8;
	bool end;

};
