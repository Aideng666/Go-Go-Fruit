#pragma once

#include "Scene.h"

class GoGoTitle : public Scene
{
public:
	GoGoTitle(std::string name);
	void InitScene(float windowWidth, float windowHeight);

	void Update();

	void FadeBackground();
	bool GetFade();
	void SetFade(bool fade);

	int GetImage() { return m_image; }
	int GetBlueStripe() { return m_blueStripe; }
	int GetRedStripe() { return m_redStripe; }
	int GetText() { return m_text; }

	int GetLoading() { return m_loading; }

private:
	float m_repeatTime = 1.f;
	float m_lerpVal = 0.f;
	bool fade;
	float timer = 0.f;
	vec4 m_clearColor2 = vec4(0.f, 0.f, 0.f, 1.f);
	vec4 m_clearColor1 = vec4(0.7058823529f, 0.9803921569f, 1.f, 1.f);

	int m_image;
	int m_blueStripe;
	int m_redStripe;
	int m_text;

	int m_loading;
};