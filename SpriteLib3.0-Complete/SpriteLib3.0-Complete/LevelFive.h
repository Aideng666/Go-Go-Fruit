#pragma once
#include "Scene.h"

class LevelFive : public Scene
{
public:
	LevelFive(std::string name);
	void InitScene(float windowWidth, float windowHeight);

	int GetBg1();
	int GetBg2();

	int GetCam();
	int GetBlueButton1();
	int GetBlueButton2();
	int GetRedButton();
	int GetJello();
	int GetFruitBowl();
	int GetElevator1();
	int GetElevator2();
	int GetElevator3();

	bool GetButtonOn1();
	bool GetButtonOn2();
	bool GetButtonOn3();

private:
	int m_background;
	int m_background2;
	
	int m_cam;
	int m_button1;
	int m_button2;
	int m_button3;
	int m_jello;
	int m_fruitBowl;
	int m_elevator1;
	int m_elevator2;
	int m_elevator3;

	bool turnOn1;
	bool turnOn2;
	bool turnOn3;

};