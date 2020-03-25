#ifndef __GAME_H__
#define __GAME_H__

#include "BackEnd.h"
#include "GoGoTitle.h"
#include "GoGoMenu.h"
#include "GoGoExit.h"
#include "LevelSelectMain.h"
#include "LevelSelect2.h"
#include "LevelSelect3.h"
#include "GoGoGame.h"
#include "LevelTwo.h"
#include "LevelThree.h"
#include "LevelFour.h"

//Our main class for running our game
class Game
{
public:
	//Empty constructor
	Game() { };
	//Deconstructor for game
	//*Unloads window
	~Game();

	//Initiaiizes game
	//*Seeds random
	//*Initializes SDL
	//*Creates Window
	//*Initializes GLEW
	//*Create Main Camera Entity
	//*Creates all other entities and adds them to register
	void InitGame();

	//Runs the game
	//*While window is open
	//*Clear window
	//*Update 
	//*Draw
	//*Poll events
	//*Flip window
	//*Accept input
	bool Run();
	
	//Updates the game
	//*Update timer
	//*Update the rendering system
	//*Update the animation system
	void Update();

	//Runs the GUI
	//*Uses ImGUI for this
	void GUI();

	//Check events
	//*Checks the results of the events that have been polled
	void CheckEvents();

	/*Input Functions*/
	void AcceptInput();
	void GamepadInput();

	void GamepadStroke(XInputController* con);
	void GamepadUp(XInputController* con);
	void GamepadDown(XInputController* con);
	void GamepadStick(XInputController* con);
	void GamepadTrigger(XInputController* con);
	void KeyboardHold();
	void KeyboardDown();
	void KeyboardUp();

	//Mouse input
	void MouseMotion(SDL_MouseMotionEvent evnt);
	void MouseClick(SDL_MouseButtonEvent evnt);
	void MouseWheel(SDL_MouseWheelEvent evnt);

	Scene* GetActiveScene();

private:
	//The window
	Window *m_window = nullptr;
	
	//Scene name
	std::string m_name;
	//Clear colour for clearing windows
	vec4 m_clearColor;

	//The main register for our ECS
	entt::registry* m_register = nullptr;

	//Scenes
	Scene* m_activeScene = nullptr;
	std::vector<Scene*> m_scenes;


	
	//Imgui stuff
	bool m_guiActive = false;

	//Hooks for events
	bool m_close = false;
	bool m_motion = false;
	bool m_click = false;
	bool m_wheel = false;

	XInputManager input;

	float timer = 0.f;
	float timer2 = 0.f;
	float timer3 = 0.f;
	float num = 0.f; 
	bool reset;
	bool change;
	bool change2, change3, change4;
	bool orth;
	bool changeRand = true;
	bool spikeDestroyed = false;

	bool level1Cleared = false;
	bool level2Cleared = false;
	bool level3Cleared = false;

	float levelTimer = 0.f;
	float jelloTimer = 0.f;
};



#endif // !__GAME_H__