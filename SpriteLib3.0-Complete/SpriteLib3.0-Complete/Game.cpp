#include "Game.h"
#include "ContactListener.h"

#include <random>
#include "Utilities.h"

ContactListener listener;

Game::~Game()
{
	//If window isn't equal to nullptr
	if (m_window != nullptr)
	{
		//Delete window
		delete m_window;
		//set window to nullptr
		m_window = nullptr;
	}

	//Goes through the scenes and deletes them
	for (unsigned i = 0; i < m_scenes.size(); i++)
	{
		if (m_scenes[i] != nullptr)
		{
			delete m_scenes[i];
			m_scenes[i] = nullptr;
		}
	}
}

void Game::InitGame()
{
	std::string titleName = "Title";
	std::string menuName = "Menu";
	std::string exitName = "Exit";
	std::string levelSelect1 = "Level Select 1";
	std::string levelSelect2 = "Level Select 2";
	std::string levelSelect3 = "Level Select 3";
	std::string levelSelect4 = "Level Select 4";
	std::string levelSelect5 = "Level Select 5";
	std::string level1 = "Level 1";
	std::string level2 = "Level 2";
	std::string level3   = "Level 3";
	std::string level4 = "Level 4";
	std::string level5 = "Level 5";
	std::string introName = "Intro";

	m_name = menuName;
	m_clearColor = vec4(0.f, 0.f, 0.f, 1.f);

	//Initializes the backend with window width and height values
	BackEnd::InitBackEnd(m_name);

	//Grabs the initialized window
	m_window = BackEnd::GetWindow();

	//Creates a new scene.
	m_scenes.push_back(new GoGoTitle(titleName));
	m_scenes.push_back(new GoGoMenu(menuName));
	m_scenes.push_back(new GoGoExit(exitName));
	m_scenes.push_back(new LevelSelectMain(levelSelect1));
	m_scenes.push_back(new LevelSelect2(levelSelect2));
	m_scenes.push_back(new LevelSelect3(levelSelect3));
	m_scenes.push_back(new LevelSelect4(levelSelect4));
	m_scenes.push_back(new LevelSelect5(levelSelect5));
	m_scenes.push_back(new GoGoGame(level1));
	m_scenes.push_back(new LevelTwo(level2));
	m_scenes.push_back(new LevelThree(level3));
	m_scenes.push_back(new LevelFour(level4));
	m_scenes.push_back(new LevelFive(level5));
	m_scenes.push_back(new GoGoIntro(introName));

	//Sets active scene reference to our scene
	m_scenes[0]->InitScene(float(BackEnd::GetWindowWidth()), float(BackEnd::GetWindowHeight()));
	m_register = m_scenes[0]->GetScene();
	m_activeScene = m_scenes[0];
	PhysicsSystem::Init();
	
	for (int i = 8; i < 13; ++i)
	{
		m_scenes[i]->GetPhysicsWorld().SetContactListener(&listener);
	}
}

bool Game::Run()
{
	//While window is still open
	while (m_window->isOpen())
	{
		//Clear window with activescene clearColor
		m_window->Clear(m_activeScene->GetClearColor());
		//Updates the game
		Update();
		//Draws the game
		BackEnd::Draw(m_register);

		//Draws ImGUI
		if (m_guiActive)
			GUI();

		//Flips the windows
		m_window->Flip();

		//Polls events and then checks them
		BackEnd::PollEvents(m_register, &m_close, &m_motion, &m_click, &m_wheel);
		CheckEvents();

		//does the window have keyboard focus?
		if (Input::m_windowFocus)
		{
			//Accept all input
			AcceptInput();
		}
	}

	return true;
}

void Game::Update()
{
	//Update timer
	Timer::Update();
	//Update the backend
	BackEnd::Update(m_register);

	//Update Physics System
	PhysicsSystem::Update(m_register, m_activeScene->GetPhysicsWorld());

	//Updates the active scene
	m_activeScene->Update();

#pragma region Fade Effect
//Fades Title to Intro
if (changeT)
{
	timer += Timer::deltaTime;

	if (timer >= 1.f)
	{
		SceneEditor::ResetEditor();

		m_activeScene->Unload();

		m_scenes[13]->InitScene(float(BackEnd::GetWindowWidth()), float(BackEnd::GetWindowHeight()));
		m_register = m_scenes[13]->GetScene();
		m_activeScene = m_scenes[13];
		timer = 0.f;
		changeT = false;
	}
}
//Fades the Menu
if (change)
{
	timer += Timer::deltaTime;

	if (timer >= 1.f)
	{
		SceneEditor::ResetEditor();

		m_activeScene->Unload();

		m_scenes[3]->InitScene(float(BackEnd::GetWindowWidth()), float(BackEnd::GetWindowHeight()));
		m_register = m_scenes[3]->GetScene();
		m_activeScene = m_scenes[3];
		timer = 0.f;
		change = false;

		LevelSelectMain* scene = (LevelSelectMain*)m_activeScene;

		if (level1Cleared)
		{
			auto level2 = scene->GetSelect2();
			ECS::GetComponent<Sprite>(level2).SetTransparency(1.0f);
			auto medal = scene->GetMedal();
			ECS::GetComponent<Sprite>(medal).SetTransparency(1.0f);
			auto lock = scene->GetLock1();
			ECS::GetComponent<Sprite>(lock).SetTransparency(0.0f);
		}
		if (level2Cleared)
		{
			auto level3 = scene->GetSelect3();
			ECS::GetComponent<Sprite>(level3).SetTransparency(1.0f);
			auto medal = scene->GetMedal2();
			ECS::GetComponent<Sprite>(medal).SetTransparency(1.0f);
			auto lock = scene->GetLock1();
			ECS::GetComponent<Sprite>(lock).SetTransparency(0.0f);
			auto lock2 = scene->GetLock2();
			ECS::GetComponent<Sprite>(lock2).SetTransparency(0.0f);
		}
		if (level3Cleared)
		{
			auto level4 = scene->GetSelect4();
			ECS::GetComponent<Sprite>(level4).SetTransparency(1.0f);
			auto medal = scene->GetMedal3();
			ECS::GetComponent<Sprite>(medal).SetTransparency(1.0f);
			auto lock = scene->GetLock1();
			ECS::GetComponent<Sprite>(lock).SetTransparency(0.0f);
			auto lock2 = scene->GetLock2();
			ECS::GetComponent<Sprite>(lock2).SetTransparency(0.0f);
			auto lock3 = scene->GetLock3();
			ECS::GetComponent<Sprite>(lock3).SetTransparency(0.0f);
		}
		if (level4Cleared)
		{
			auto level5 = scene->GetSelect5();
			ECS::GetComponent<Sprite>(level5).SetTransparency(1.0f);
			auto medal = scene->GetMedal4();
			ECS::GetComponent<Sprite>(medal).SetTransparency(1.0f);
			auto lock = scene->GetLock1();
			ECS::GetComponent<Sprite>(lock).SetTransparency(0.0f);
			auto lock2 = scene->GetLock2();
			ECS::GetComponent<Sprite>(lock2).SetTransparency(0.0f);
			auto lock3 = scene->GetLock3();
			ECS::GetComponent<Sprite>(lock3).SetTransparency(0.0f);
			auto lock4 = scene->GetLock4();
			ECS::GetComponent<Sprite>(lock4).SetTransparency(0.0f);
		}
		if (level5Cleared)
		{
			auto medal = scene->GetMedal5();
			ECS::GetComponent<Sprite>(medal).SetTransparency(1.0f);
		}
	}
}
//Fades into Level 1
if (change2)
{
	LevelSelectMain* scene = (LevelSelectMain*)m_activeScene;
	ECS::GetComponent<Sprite>(scene->GetLoading()).SetTransparency(1.f);

	timer += Timer::deltaTime;

	if (timer >= 2.f)
	{
		SceneEditor::ResetEditor();

		m_activeScene->Unload();

		m_scenes[8]->InitScene(float(BackEnd::GetWindowWidth()), float(BackEnd::GetWindowHeight()));
		m_register = m_scenes[8]->GetScene();
		m_activeScene = m_scenes[8];
		timer = 0.f;
		change2 = false;
		loading = false;

		m_activeScene->GetPhysicsWorld().SetContactListener(&listener);
	}
}
//Fades into Level 2
if (change3)
{
	LevelSelect2* scene = (LevelSelect2*)m_activeScene;
	ECS::GetComponent<Sprite>(scene->GetLoading()).SetTransparency(1.f);

	timer += Timer::deltaTime;

	if (timer >= 2.f)
	{
		SceneEditor::ResetEditor();

		m_activeScene->Unload();

		m_scenes[11]->InitScene(float(BackEnd::GetWindowWidth()), float(BackEnd::GetWindowHeight()));
		m_register = m_scenes[11]->GetScene();
		m_activeScene = m_scenes[11];
		timer = 0.f;
		change3 = false;
		loading = false;

		m_activeScene->GetPhysicsWorld().SetContactListener(&listener);
	}
}
//Fades into Level 3
if (change4)
{
	LevelSelect3* scene = (LevelSelect3*)m_activeScene;
	ECS::GetComponent<Sprite>(scene->GetLoading()).SetTransparency(1.f);

	timer += Timer::deltaTime;

	if (timer >= 2.f)
	{
		SceneEditor::ResetEditor();

		m_activeScene->Unload();

		m_scenes[9]->InitScene(float(BackEnd::GetWindowWidth()), float(BackEnd::GetWindowHeight()));
		m_register = m_scenes[9]->GetScene();
		m_activeScene = m_scenes[9];
		timer = 0.f;
		change4 = false;
		loading = false;

		m_activeScene->GetPhysicsWorld().SetContactListener(&listener);
	}
}
//Fades into Level 4
if (change5)
{
	LevelSelect4* scene = (LevelSelect4*)m_activeScene;
	ECS::GetComponent<Sprite>(scene->GetLoading()).SetTransparency(1.f);

	timer += Timer::deltaTime;

	if (timer >= 2.f)
	{
		SceneEditor::ResetEditor();

		m_activeScene->Unload();

		m_scenes[12]->InitScene(float(BackEnd::GetWindowWidth()), float(BackEnd::GetWindowHeight()));
		m_register = m_scenes[12]->GetScene();
		m_activeScene = m_scenes[12];
		timer = 0.f;
		change5 = false;
		loading = false;

		m_activeScene->GetPhysicsWorld().SetContactListener(&listener);
	}
}
//Fades into Level 5
if (change6)
{
	LevelSelect5* scene = (LevelSelect5*)m_activeScene;
	ECS::GetComponent<Sprite>(scene->GetLoading()).SetTransparency(1.f);

	timer += Timer::deltaTime;

	if (timer >= 2.f)
	{
		SceneEditor::ResetEditor();

		m_activeScene->Unload();

		m_scenes[10]->InitScene(float(BackEnd::GetWindowWidth()), float(BackEnd::GetWindowHeight()));
		m_register = m_scenes[10]->GetScene();
		m_activeScene = m_scenes[10];
		timer = 0.f;
		change6 = false;
		loading = false;

		m_activeScene->GetPhysicsWorld().SetContactListener(&listener);
	}
}
#pragma endregion

#pragma region Shake Effect
	if (m_activeScene == m_scenes[8])
	{
			GoGoGame* scene = (GoGoGame*)m_activeScene;
			auto cam = scene->GetCam();
			auto body = ECS::GetComponent<PhysicsBody>(EntityIdentifier::MainPlayer2()).GetBody();


			if (changeRand)
			{
			num = static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / 1.f)) - 0.5f;
			changeRand = false;
			}
		if (listener.GetShake()) 
		{
			timer2 += Timer::deltaTime;

			if (!reset)
			{
			ECS::GetComponent<Camera>(cam).Shake(num);
			reset = true;
			}
			else
			{
			ECS::GetComponent<Camera>(cam).Shake(-num);
			reset = false;
			changeRand = true;
			}

			if (timer2 >= 0.1f)
			{
				timer2 = 0.f;
				listener.SetShake(false);
			}
		}
	}

	if (m_activeScene == m_scenes[9])
	{
		LevelTwo* scene = (LevelTwo*)m_activeScene;
		auto cam = scene->GetCam();
		auto body = ECS::GetComponent<PhysicsBody>(EntityIdentifier::MainPlayer2()).GetBody();


		if (changeRand)
		{
			num = static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / 1.f)) - 0.5f;
			changeRand = false;
		}
		if (listener.GetShake())
		{
			timer2 += Timer::deltaTime;

			if (!reset)
			{
				ECS::GetComponent<Camera>(cam).Shake(num);
				reset = true;
			}
			else
			{
				ECS::GetComponent<Camera>(cam).Shake(-num);
				reset = false;
				changeRand = true;
			}

			if (timer2 >= 0.1f)
			{
				timer2 = 0.f;
				listener.SetShake(false);
			}
		}
	}

	if (m_activeScene == m_scenes[10])
	{
		LevelThree* scene = (LevelThree*)m_activeScene;
		auto cam = scene->GetCam();

		if (!orth)
		{
			vec4 tempOrtho = ECS::GetComponent<Camera>(cam).GetOrthoPos();
			orth = true;
		}

		if (changeRand)
		{
			num = static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / 0.5f)) - 0.25f;
			changeRand = false;
		}
		if (listener.GetShake())
		{
			timer2 += Timer::deltaTime;

			if (!reset)
			{
				ECS::GetComponent<Camera>(cam).Shake(num);
				reset = true;
			}
			else
			{
				ECS::GetComponent<Camera>(cam).Shake(-num);
				reset = false;
				changeRand = true;
			}

			if (timer2 >= 0.1f)
			{
				timer2 = 0.f;
				listener.SetShake(false);
			}
		}
	}
	if (m_activeScene == m_scenes[11])
	{
		LevelFour* scene = (LevelFour*)m_activeScene;
		auto cam = scene->GetCam();
		auto body = ECS::GetComponent<PhysicsBody>(EntityIdentifier::MainPlayer2()).GetBody();


		if (changeRand)
		{
			num = static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / 1.f)) - 0.5f;
			changeRand = false;
		}
		if (listener.GetShake())
		{
			timer2 += Timer::deltaTime;

			if (!reset)
			{
				ECS::GetComponent<Camera>(cam).Shake(num);
				reset = true;
			}
			else
			{
				ECS::GetComponent<Camera>(cam).Shake(-num);
				reset = false;
				changeRand = true;
			}

			if (timer2 >= 0.1f)
			{
				timer2 = 0.f;
				listener.SetShake(false);
			}
		}
	}
	if (m_activeScene == m_scenes[12])
	{
		LevelFive* scene = (LevelFive*)m_activeScene;
		auto cam = scene->GetCam();
		auto body = ECS::GetComponent<PhysicsBody>(EntityIdentifier::MainPlayer2()).GetBody();


		if (changeRand)
		{
			num = static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / 1.f)) - 0.5f;
			changeRand = false;
		}
		if (listener.GetShake())
		{
			timer2 += Timer::deltaTime;

			if (!reset)
			{
				ECS::GetComponent<Camera>(cam).Shake(num);
				reset = true;
			}
			else
			{
				ECS::GetComponent<Camera>(cam).Shake(-num);
				reset = false;
				changeRand = true;
			}

			if (timer2 >= 0.1f)
			{
				timer2 = 0.f;
				listener.SetShake(false);
			}
		}
	}
#pragma endregion

#pragma region Parallax Background
	if (m_activeScene == m_scenes[1] && !spikeDestroyed)
	{
		GoGoMenu* scene = (GoGoMenu*)m_activeScene;
		auto entity = scene->GetSpike1();
		auto entity2 = scene->GetSpike2();
		vec2 position = m_register->get<Transform>(entity).GetPosition();
		vec2 position2 = m_register->get<Transform>(entity2).GetPosition();
		int spikeWidth = m_register->get<Sprite>(entity).GetWidth();

		float spikeSpeed = 20.f;

		if (position.y + spikeWidth <= 0)
		{
			position.y = position2.y + spikeWidth;
		}
		if (position2.y + spikeWidth <= 0)
		{
			position2.y = position.y + spikeWidth;
		}
		
		m_register->get<Transform>(entity).SetPositionY(position.y - (spikeSpeed * Timer::deltaTime));
		m_register->get<Transform>(entity2).SetPositionY(position2.y - (spikeSpeed * Timer::deltaTime));			
	}
	if (m_activeScene == m_scenes[2])
	{
		GoGoExit* scene = (GoGoExit*)m_activeScene;
		auto entity = scene->GetSpike1();
		auto entity2 = scene->GetSpike2();
		vec2 position = m_register->get<Transform>(entity).GetPosition();
		vec2 position2 = m_register->get<Transform>(entity2).GetPosition();
		int spikeWidth = m_register->get<Sprite>(entity).GetWidth();

		float spikeSpeed = 20.f;

		if (position.y + spikeWidth <= 0)
		{
			position.y = position2.y + spikeWidth;
		}
		if (position2.y + spikeWidth <= 0)
		{
			position2.y = position.y + spikeWidth;
		}

		m_register->get<Transform>(entity).SetPositionY(position.y - (spikeSpeed * Timer::deltaTime));
		m_register->get<Transform>(entity2).SetPositionY(position2.y - (spikeSpeed * Timer::deltaTime));
	}
	if (m_activeScene == m_scenes[8])
	{
		GoGoGame* scene = (GoGoGame*)m_activeScene;
		auto entity = scene->GetBackground();
		auto entity2 = scene->GetBackground2();
		vec2 position = m_register->get<Transform>(entity).GetPosition();
		vec2 position2 = m_register->get<Transform>(entity2).GetPosition();
		int bgWidth = m_register->get<Sprite>(entity).GetWidth();
		
		float bgSpeed = 30.f;

		if (position.x + bgWidth <= 0)
		{
			position.x = position2.x + bgWidth;
		}
		if (position2.x + bgWidth <= 0)
		{
			position2.x = position.x + bgWidth;
		}

		m_register->get<Transform>(entity).SetPositionX(position.x - (bgSpeed * Timer::deltaTime));
		m_register->get<Transform>(entity2).SetPositionX(position2.x - (bgSpeed * Timer::deltaTime));
	}
	if (m_activeScene == m_scenes[9])
	{
		LevelTwo* scene = (LevelTwo*)m_activeScene;
		auto entity = scene->GetBg1();
		auto entity2 = scene->GetBg2();
		vec2 position = m_register->get<Transform>(entity).GetPosition();
		vec2 position2 = m_register->get<Transform>(entity2).GetPosition();
		int bgWidth = m_register->get<Sprite>(entity).GetWidth();

		float bgSpeed = 30.f;

		if (position.x + bgWidth <= 0)
		{
			position.x = position2.x + bgWidth;
		}
		if (position2.x + bgWidth <= 0)
		{
			position2.x = position.x + bgWidth;
		}

		m_register->get<Transform>(entity).SetPositionX(position.x - (bgSpeed * Timer::deltaTime));
		m_register->get<Transform>(entity2).SetPositionX(position2.x - (bgSpeed * Timer::deltaTime));
	}
	if (m_activeScene == m_scenes[10])
	{
		LevelThree* scene = (LevelThree*)m_activeScene;
		auto entity = scene->GetBackground();
		auto entity2 = scene->GetBackground2();
		vec2 position = m_register->get<Transform>(entity).GetPosition();
		vec2 position2 = m_register->get<Transform>(entity2).GetPosition();

		int bgWidth = m_register->get<Sprite>(entity).GetWidth();

		float bgSpeed = 30.f;

		if (position.x + bgWidth <= 0)
		{
			position.x = position2.x + bgWidth;
		}
		if (position2.x + bgWidth <= 0)
		{
			position2.x = position.x + bgWidth;
		}

		m_register->get<Transform>(entity).SetPositionX(position.x - (bgSpeed * Timer::deltaTime));
		m_register->get<Transform>(entity2).SetPositionX(position2.x - (bgSpeed * Timer::deltaTime));
	}
	if (m_activeScene == m_scenes[11])
	{
		LevelFour* scene = (LevelFour*)m_activeScene;
		auto entity = scene->GetBg1();
		auto entity2 = scene->GetBg2();
		vec2 position = m_register->get<Transform>(entity).GetPosition();
		vec2 position2 = m_register->get<Transform>(entity2).GetPosition();

		int bgWidth = m_register->get<Sprite>(entity).GetWidth();

		float bgSpeed = 30.f;

		if (position.x + bgWidth <= 0)
		{
			position.x = position2.x + bgWidth;
		}
		if (position2.x + bgWidth <= 0)
		{
			position2.x = position.x + bgWidth;
		}

		m_register->get<Transform>(entity).SetPositionX(position.x - (bgSpeed * Timer::deltaTime));
		m_register->get<Transform>(entity2).SetPositionX(position2.x - (bgSpeed * Timer::deltaTime));
	}
	if (m_activeScene == m_scenes[12])
	{
		LevelFive* scene = (LevelFive*)m_activeScene;
		auto entity = scene->GetBg1();
		auto entity2 = scene->GetBg2();
		vec2 position = m_register->get<Transform>(entity).GetPosition();
		vec2 position2 = m_register->get<Transform>(entity2).GetPosition();

		int bgWidth = m_register->get<Sprite>(entity).GetWidth();

		float bgSpeed = 30.f;

		if (position.x + bgWidth <= 0)
		{
			position.x = position2.x + bgWidth;
		}
		if (position2.x + bgWidth <= 0)
		{
			position2.x = position.x + bgWidth;
		}

		m_register->get<Transform>(entity).SetPositionX(position.x - (bgSpeed * Timer::deltaTime));
		m_register->get<Transform>(entity2).SetPositionX(position2.x - (bgSpeed * Timer::deltaTime));
	}
#pragma endregion
	
#pragma region Activation of Buttons
	if (m_activeScene == m_scenes[8])
	{
		GoGoGame* scene = (GoGoGame*)m_activeScene;
		auto elevator = scene->GetElevator();
		auto button = scene->GetButton();
		auto body = ECS::GetComponent<PhysicsBody>(elevator).GetBody();
		auto trans = ECS::GetComponent<Transform>(elevator);
	
		//If the blue button is being pressed, the elevator moves up to the higher platforms
		//If the button is not being pressed the elevator moves back down towards the bottom
		if (listener.GetPressed() && trans.GetPosition().y < 4.4f)
		{
			body->SetLinearVelocity(b2Vec2(0, 2));
		}
		else if (!(listener.GetPressed()) && trans.GetPosition().y > -62.f)
		{
			body->SetLinearVelocity(b2Vec2(0, -2));
		}
		else
		{
			body->SetLinearVelocity(b2Vec2(0, 0));
		}

		auto turnOn = scene->GetButtonOn();

		//Animates the blue button and corresponding platform if presssed 
		if (listener.GetPressed())
		{	
			turnOn = true;

			if (turnOn)
			{
				auto& animController = ECS::GetComponent<AnimationController>(button);
				animController.SetActiveAnim(1);
				animController.GetAnimation(1).Reset();
				animController.SetActiveAnim(0);

				auto& animPlat = ECS::GetComponent<AnimationController>(elevator);
				animPlat.SetActiveAnim(0);
				animPlat.GetAnimation(0).Reset();
				animPlat.SetActiveAnim(1);
			}

		}	
		//Animates the blue button and corresponding platform if not pressed
		if (!(listener.GetPressed()))
		{
			turnOn = false;
			
			if (!turnOn)
			{
				auto& animController = ECS::GetComponent<AnimationController>(button);
				animController.SetActiveAnim(0);
				animController.GetAnimation(0).Reset();
				animController.SetActiveAnim(1);

				auto& animPlat = ECS::GetComponent<AnimationController>(elevator);
				animPlat.SetActiveAnim(0);
				animPlat.GetAnimation(1).Reset();
				animPlat.SetActiveAnim(0);
			}	
		}
	}

	if (m_activeScene == m_scenes[9])
	{
		LevelTwo* scene = (LevelTwo*)m_activeScene;
		auto elevator = scene->GetElevator();
		auto button = scene->GetButton();
		auto body = ECS::GetComponent<PhysicsBody>(elevator).GetBody();
		auto trans = ECS::GetComponent<Transform>(elevator);
		auto redButton = scene->GetRedButton();
		auto redPlat = scene->GetElevator2();
		auto body2 = ECS::GetComponent<PhysicsBody>(redPlat).GetBody();
		auto trans2 = ECS::GetComponent<Transform>(redPlat);

		auto turnOn1 = scene->GetButtonOn1();
		auto turnOn2 = scene->GetButtonOn2();

		if (listener.GetPressed() && trans.GetPosition().y < 51.5f)
		{
			body->SetLinearVelocity(b2Vec2(0, 3));
		}
		else if (!(listener.GetPressed()) && trans.GetPosition().y > -86.f)
		{
			body->SetLinearVelocity(b2Vec2(0, -3));
		}
		else
		{
			body->SetLinearVelocity(b2Vec2(0, 0));
		}

		if (listener.GetPressed())
		{
			turnOn1 = true;

			if (turnOn1)
			{
				auto& animController = ECS::GetComponent<AnimationController>(button);
				animController.SetActiveAnim(1);
				animController.GetAnimation(1).Reset();
				animController.SetActiveAnim(0);

				auto& animPlat = ECS::GetComponent<AnimationController>(elevator);
				animPlat.SetActiveAnim(0);
				animPlat.GetAnimation(0).Reset();
				animPlat.SetActiveAnim(1);
			}
		}
		if (!(listener.GetPressed()))
		{
			turnOn1 = false;

			if (!turnOn1)
			{
				auto& animController = ECS::GetComponent<AnimationController>(button);
				animController.SetActiveAnim(0);
				animController.GetAnimation(0).Reset();
				animController.SetActiveAnim(1);

				auto& animPlat = ECS::GetComponent<AnimationController>(elevator);
				animPlat.SetActiveAnim(1);
				animPlat.GetAnimation(1).Reset();
				animPlat.SetActiveAnim(0);
			}
		}

		if (listener.GetRedPressed() && trans2.GetPosition().y < 51.5f)
		{
			body2->SetLinearVelocity(b2Vec2(0, 3));
		}
		else if (!(listener.GetRedPressed()) && trans2.GetPosition().y > -86.f)
		{
			body2->SetLinearVelocity(b2Vec2(0, -3));
		}
		else
		{
			body2->SetLinearVelocity(b2Vec2(0, 0));
		}

		if (listener.GetRedPressed())
		{
			turnOn2 = true;

			if (turnOn2)
			{
				auto& animController = ECS::GetComponent<AnimationController>(redButton);
				animController.SetActiveAnim(0);
				animController.GetAnimation(0).Reset();
				animController.SetActiveAnim(1);

				auto& animPlat = ECS::GetComponent<AnimationController>(redPlat);
				animPlat.SetActiveAnim(0);
				animPlat.GetAnimation(0).Reset();
				animPlat.SetActiveAnim(1);
			}
		}
		if (!(listener.GetRedPressed()))
		{
			turnOn2 = false;

			if (!turnOn2)
			{
				auto& animController = ECS::GetComponent<AnimationController>(redButton);
				animController.SetActiveAnim(1);
				animController.GetAnimation(1).Reset();
				animController.SetActiveAnim(0);

				auto& animPlat = ECS::GetComponent<AnimationController>(redPlat);
				animPlat.SetActiveAnim(1);
				animPlat.GetAnimation(1).Reset();
				animPlat.SetActiveAnim(0);
			}
		}
	}

	if (m_activeScene == m_scenes[10])
	{
		LevelThree* scene = (LevelThree*)m_activeScene;
		auto elevator = scene->GetElevator();
		auto elevator2 = scene->GetElevator2();
		auto body = ECS::GetComponent<PhysicsBody>(elevator).GetBody();
		auto trans = ECS::GetComponent<Transform>(elevator);
		auto body2 = ECS::GetComponent<PhysicsBody>(elevator2).GetBody();
		auto trans2 = ECS::GetComponent<Transform>(elevator2);
		auto button1 = scene->GetButton();
		auto button2 = scene->GetButton2();

		//If the blue button is being pressed, the elevator moves up to the higher platforms
		//If the button is not being pressed the elevator moves back down towards the bottom
		if (listener.GetPressed() && trans.GetPosition().y < -3.f)
		{
			body->SetLinearVelocity(b2Vec2(0, 2));
		}
		else if (!(listener.GetPressed()) && trans.GetPosition().y > -74.f)
		{
			body->SetLinearVelocity(b2Vec2(0, -2));
		}
		else
		{
			body->SetLinearVelocity(b2Vec2(0, 0));
		}

		if (listener.Get2Pressed() && trans2.GetPosition().y < 65.f)
		{
			body2->SetLinearVelocity(b2Vec2(0, 2));
		}
		else if (!(listener.Get2Pressed()) && trans2.GetPosition().y > 1.f)
		{
			body2->SetLinearVelocity(b2Vec2(0, -2));
		}
		else
		{
			body2->SetLinearVelocity(b2Vec2(0, 0));
		}

		auto turnOn1 = scene->GetButtonOn1();
		auto turnOn2 = scene->GetButtonOn2();

		if (listener.GetPressed())
		{
			turnOn1 = true;

			if (turnOn1)
			{
				auto& animController = ECS::GetComponent<AnimationController>(button1);
				animController.SetActiveAnim(1);
				animController.GetAnimation(1).Reset();
				animController.SetActiveAnim(0);

				auto& animPlat = ECS::GetComponent<AnimationController>(elevator);
				animPlat.SetActiveAnim(0);
				animPlat.GetAnimation(0).Reset();
				animPlat.SetActiveAnim(1);
			}
		}
		if (!(listener.GetPressed()))
		{
			turnOn1 = false;

			if (!turnOn1)
			{
				auto& animController = ECS::GetComponent<AnimationController>(button1);
				animController.SetActiveAnim(0);
				animController.GetAnimation(0).Reset();
				animController.SetActiveAnim(1);

				auto& animPlat = ECS::GetComponent<AnimationController>(elevator);
				animPlat.SetActiveAnim(1);
				animPlat.GetAnimation(1).Reset();
				animPlat.SetActiveAnim(0);
			}

			if (listener.Get2Pressed())
			{
				turnOn2 = true;

				if (turnOn2)
				{
					auto& animController = ECS::GetComponent<AnimationController>(button2);
					animController.SetActiveAnim(1);
					animController.GetAnimation(1).Reset();
					animController.SetActiveAnim(0);

					auto& animPlat = ECS::GetComponent<AnimationController>(elevator2);
					animPlat.SetActiveAnim(0);
					animPlat.GetAnimation(0).Reset();
					animPlat.SetActiveAnim(1);
				}
			}
			if (!(listener.Get2Pressed()))
			{
				turnOn2 = false;

				if (!turnOn2)
				{
					auto& animController = ECS::GetComponent<AnimationController>(button2);
					animController.SetActiveAnim(0);
					animController.GetAnimation(0).Reset();
					animController.SetActiveAnim(1);

					auto& animPlat = ECS::GetComponent<AnimationController>(elevator2);
					animPlat.SetActiveAnim(1);
					animPlat.GetAnimation(1).Reset();
					animPlat.SetActiveAnim(0);
				}
			}
		}
	}
	if (m_activeScene == m_scenes[11])
	{
		LevelFour* scene = (LevelFour*)m_activeScene;
		auto elevator = scene->GetBlueElevator();
		auto button = scene->GetBlueButton1();
		auto body = ECS::GetComponent<PhysicsBody>(elevator).GetBody();
		auto trans = ECS::GetComponent<Transform>(elevator);
		auto redButton = scene->GetRedButton();
		auto redPlat = scene->GetRedElevator();
		auto body2 = ECS::GetComponent<PhysicsBody>(redPlat).GetBody();
		auto trans2 = ECS::GetComponent<Transform>(redPlat);
		auto bluePlat2 = scene->GetBlueElevator2();
		auto blueButton2 = scene->GetBlueButton2();
		auto body3 = ECS::GetComponent<PhysicsBody>(bluePlat2).GetBody();
		auto trans3 = ECS::GetComponent<Transform>(bluePlat2);

		auto turnOn1 = scene->GetButtonOn1();
		auto turnOn2 = scene->GetButtonOn2();
		auto turnOn3 = scene->GetButtonOn3();

		if (listener.GetPressed() && trans.GetPosition().y < 51.5f)
		{
			body->SetLinearVelocity(b2Vec2(0, 4));
		}
		else if (!(listener.GetPressed()) && trans.GetPosition().y > -86.f)
		{
			body->SetLinearVelocity(b2Vec2(0, -4));
		}
		else
		{
			body->SetLinearVelocity(b2Vec2(0, 0));
		}

		if (listener.GetPressed())
		{
			turnOn1 = true;

			if (turnOn1)
			{
				auto& animController = ECS::GetComponent<AnimationController>(button);
				animController.SetActiveAnim(1);
				animController.GetAnimation(1).Reset();
				animController.SetActiveAnim(0);

				auto& animPlat = ECS::GetComponent<AnimationController>(elevator);
				animPlat.SetActiveAnim(0);
				animPlat.GetAnimation(0).Reset();
				animPlat.SetActiveAnim(1);
			}
		}
		if (!(listener.GetPressed()))
		{
			turnOn1 = false;

			if (!turnOn1)
			{
				auto& animController = ECS::GetComponent<AnimationController>(button);
				animController.SetActiveAnim(0);
				animController.GetAnimation(0).Reset();
				animController.SetActiveAnim(1);

				auto& animPlat = ECS::GetComponent<AnimationController>(elevator);
				animPlat.SetActiveAnim(1);
				animPlat.GetAnimation(1).Reset();
				animPlat.SetActiveAnim(0);
			}
		}

		if (listener.GetRedPressed() && trans2.GetPosition().y < 51.5f)
		{
			body2->SetLinearVelocity(b2Vec2(0, 4));
		}
		else if (!(listener.GetRedPressed()) && trans2.GetPosition().y > -86.f)
		{
			body2->SetLinearVelocity(b2Vec2(0, -4));
		}
		else
		{
			body2->SetLinearVelocity(b2Vec2(0, 0));
		}

		if (listener.GetRedPressed())
		{
			turnOn2 = true;

			if (turnOn2)
			{
				auto& animController = ECS::GetComponent<AnimationController>(redButton);
				animController.SetActiveAnim(0);
				animController.GetAnimation(0).Reset();
				animController.SetActiveAnim(1);

				auto& animPlat = ECS::GetComponent<AnimationController>(redPlat);
				animPlat.SetActiveAnim(0);
				animPlat.GetAnimation(0).Reset();
				animPlat.SetActiveAnim(1);
			}
		}
		if (!(listener.GetRedPressed()))
		{
			turnOn2 = false;

			if (!turnOn2)
			{
				auto& animController = ECS::GetComponent<AnimationController>(redButton);
				animController.SetActiveAnim(1);
				animController.GetAnimation(1).Reset();
				animController.SetActiveAnim(0);

				auto& animPlat = ECS::GetComponent<AnimationController>(redPlat);
				animPlat.SetActiveAnim(1);
				animPlat.GetAnimation(1).Reset();
				animPlat.SetActiveAnim(0);
			}
		}
		if (listener.Get2Pressed() && trans3.GetPosition().x < 12.5f)
		{
			body3->SetLinearVelocity(b2Vec2(4, 0));
		}
		else if (!(listener.Get2Pressed()) && trans3.GetPosition().x > -83.f)
		{
			body3->SetLinearVelocity(b2Vec2(-4, 0));
		}
		else
		{
			body3->SetLinearVelocity(b2Vec2(0, 0));
		}

		if (listener.Get2Pressed())
		{
			turnOn3 = true;

			if (turnOn3)
			{
				auto& animController = ECS::GetComponent<AnimationController>(blueButton2);
				animController.SetActiveAnim(1);
				animController.GetAnimation(1).Reset();
				animController.SetActiveAnim(0);

				auto& animPlat = ECS::GetComponent<AnimationController>(bluePlat2);
				animPlat.SetActiveAnim(0);
				animPlat.GetAnimation(0).Reset();
				animPlat.SetActiveAnim(1);
			}
		}
		if (!(listener.Get2Pressed()))
		{
			turnOn3 = false;

			if (!turnOn3)
			{
				auto& animController = ECS::GetComponent<AnimationController>(blueButton2);
				animController.SetActiveAnim(0);
				animController.GetAnimation(0).Reset();
				animController.SetActiveAnim(1);

				auto& animPlat = ECS::GetComponent<AnimationController>(bluePlat2);
				animPlat.SetActiveAnim(1);
				animPlat.GetAnimation(1).Reset();
				animPlat.SetActiveAnim(0);
			}
		}
	}
	if (m_activeScene == m_scenes[12])
	{
		LevelFive* scene = (LevelFive*)m_activeScene;
		auto elevator = scene->GetElevator1();
		auto button = scene->GetBlueButton1();
		auto body = ECS::GetComponent<PhysicsBody>(elevator).GetBody();
		auto trans = ECS::GetComponent<Transform>(elevator);
		auto redButton = scene->GetRedButton();
		auto redPlat = scene->GetElevator2();
		auto body2 = ECS::GetComponent<PhysicsBody>(redPlat).GetBody();
		auto trans2 = ECS::GetComponent<Transform>(redPlat);
		auto bluePlat2 = scene->GetElevator3();
		auto blueButton2 = scene->GetBlueButton2();
		auto body3 = ECS::GetComponent<PhysicsBody>(bluePlat2).GetBody();
		auto trans3 = ECS::GetComponent<Transform>(bluePlat2);

		auto turnOn1 = scene->GetButtonOn1();
		auto turnOn2 = scene->GetButtonOn2();
		auto turnOn3 = scene->GetButtonOn3();

		if (listener.GetPressed() && trans.GetPosition().y < -30.f)
		{
			body->SetLinearVelocity(b2Vec2(0, 2));
		}
		else if (!(listener.GetPressed()) && trans.GetPosition().y > -86.f)
		{
			body->SetLinearVelocity(b2Vec2(0, -2));
		}
		else
		{
			body->SetLinearVelocity(b2Vec2(0, 0));
		}

		if (listener.GetPressed())
		{
			turnOn1 = true;

			if (turnOn1)
			{
				auto& animController = ECS::GetComponent<AnimationController>(button);
				animController.SetActiveAnim(1);
				animController.GetAnimation(1).Reset();
				animController.SetActiveAnim(0);

				auto& animPlat = ECS::GetComponent<AnimationController>(elevator);
				animPlat.SetActiveAnim(0);
				animPlat.GetAnimation(0).Reset();
				animPlat.SetActiveAnim(1);
			}
		}
		if (!(listener.GetPressed()))
		{
			turnOn1 = false;

			if (!turnOn1)
			{
				auto& animController = ECS::GetComponent<AnimationController>(button);
				animController.SetActiveAnim(0);
				animController.GetAnimation(0).Reset();
				animController.SetActiveAnim(1);

				auto& animPlat = ECS::GetComponent<AnimationController>(elevator);
				animPlat.SetActiveAnim(1);
				animPlat.GetAnimation(1).Reset();
				animPlat.SetActiveAnim(0);
			}
		}

		if (listener.GetRedPressed() && trans2.GetPosition().x > 83.f)
		{
			body2->SetLinearVelocity(b2Vec2(-1, 0));
		}
		else if (!(listener.GetRedPressed()) && trans2.GetPosition().x < 107.f)
		{
			body2->SetLinearVelocity(b2Vec2(1, 0));
		}
		else
		{
			body2->SetLinearVelocity(b2Vec2(0, 0));
		}

		if (listener.GetRedPressed())
		{
			turnOn2 = true;

			if (turnOn2)
			{
				auto& animController = ECS::GetComponent<AnimationController>(redButton);
				animController.SetActiveAnim(0);
				animController.GetAnimation(0).Reset();
				animController.SetActiveAnim(1);

				auto& animPlat = ECS::GetComponent<AnimationController>(redPlat);
				animPlat.SetActiveAnim(0);
				animPlat.GetAnimation(0).Reset();
				animPlat.SetActiveAnim(1);
			}
		}
		if (!(listener.GetRedPressed()))
		{
			turnOn2 = false;

			if (!turnOn2)
			{
				auto& animController = ECS::GetComponent<AnimationController>(redButton);
				animController.SetActiveAnim(1);
				animController.GetAnimation(1).Reset();
				animController.SetActiveAnim(0);

				auto& animPlat = ECS::GetComponent<AnimationController>(redPlat);
				animPlat.SetActiveAnim(1);
				animPlat.GetAnimation(1).Reset();
				animPlat.SetActiveAnim(0);
			}
		}
		if (listener.Get2Pressed() && trans3.GetPosition().x < -83.f)
		{
			body3->SetLinearVelocity(b2Vec2(1, 0));
		}
		else if (!(listener.Get2Pressed()) && trans3.GetPosition().x > -107.f)
		{
			body3->SetLinearVelocity(b2Vec2(-1, 0));
		}
		else
		{
			body3->SetLinearVelocity(b2Vec2(0, 0));
		}

		if (listener.Get2Pressed())
		{
			turnOn3 = true;

			if (turnOn3)
			{
				auto& animController = ECS::GetComponent<AnimationController>(blueButton2);
				animController.SetActiveAnim(1);
				animController.GetAnimation(1).Reset();
				animController.SetActiveAnim(0);

				auto& animPlat = ECS::GetComponent<AnimationController>(bluePlat2);
				animPlat.SetActiveAnim(0);
				animPlat.GetAnimation(0).Reset();
				animPlat.SetActiveAnim(1);
			}
		}
		if (!(listener.Get2Pressed()))
		{
			turnOn3 = false;

			if (!turnOn3)
			{
				auto& animController = ECS::GetComponent<AnimationController>(blueButton2);
				animController.SetActiveAnim(0);
				animController.GetAnimation(0).Reset();
				animController.SetActiveAnim(1);

				auto& animPlat = ECS::GetComponent<AnimationController>(bluePlat2);
				animPlat.SetActiveAnim(1);
				animPlat.GetAnimation(1).Reset();
				animPlat.SetActiveAnim(0);
			}
		}
	}
#pragma endregion

#pragma region Jello Bounce
	if (m_activeScene == m_scenes[9])
	{
		LevelTwo* scene = (LevelTwo*)m_activeScene;
		auto jelloAnim = scene->GetJello();
		auto& jelloController = ECS::GetComponent<AnimationController>(jelloAnim);

		if (listener.GetBounced())
		{
			jelloController.SetActiveAnim(0);
			jelloController.GetAnimation(0).Reset();
			jelloTimer = 0.f;
		}
		if (!(listener.GetBounced()))
		{
			jelloTimer += Timer::deltaTime;
		}
		if (jelloTimer >= 2.f)
		{
			jelloController.SetActiveAnim(1);
		}
	}
	if (m_activeScene == m_scenes[10])
	{
		LevelThree* scene = (LevelThree*)m_activeScene;
		auto jello = scene->GetJello();
		auto& animController = ECS::GetComponent<AnimationController>(jello);

		if (listener.GetBounced())
		{
			animController.SetActiveAnim(0);
			animController.GetAnimation(0).Reset();
			jelloTimer = 0.f;
		}
		if (!(listener.GetBounced()))
		{
			jelloTimer += Timer::deltaTime;
		}
		if (jelloTimer >= 2.f)
		{
			animController.SetActiveAnim(1);
		}
	}
	if (m_activeScene == m_scenes[12])
	{
		LevelFive* scene = (LevelFive*)m_activeScene;
		auto jello = scene->GetJello();
		auto& animController = ECS::GetComponent<AnimationController>(jello);

		if (listener.GetBounced())
		{
			animController.SetActiveAnim(0);
			animController.GetAnimation(0).Reset();
			jelloTimer = 0.f;
		}
		if (!(listener.GetBounced()))
		{
			jelloTimer += Timer::deltaTime;
		}
		if (jelloTimer >= 2.f)
		{
			animController.SetActiveAnim(1);
		}
	}
#pragma endregion

#pragma region Level Check
	//Level 1 beat
	if (m_activeScene == m_scenes[8])
	{
		if (listener.GetLevelCheck())
		{
			level1Cleared = true;
			GoGoGame* scene = (GoGoGame*)m_activeScene;
			auto fruitBowl = scene->GetFruitBowl();
			auto& fbAnim = ECS::GetComponent<AnimationController>(fruitBowl);
			fbAnim.SetActiveAnim(0);

			levelTimer += Timer::deltaTime;

			if (levelTimer >= 3.f)
			{
				SceneEditor::ResetEditor();

				m_activeScene->Unload();

				m_scenes[3]->InitScene(float(BackEnd::GetWindowWidth()), float(BackEnd::GetWindowHeight()));
				m_register = m_scenes[3]->GetScene();
				m_activeScene = m_scenes[3];

				listener.SetWin(false);
				levelTimer = 0.f;
				listener.SetLevelCheck(false);

				if (level1Cleared)
				{
					LevelSelectMain* scene = (LevelSelectMain*)m_activeScene;
					auto medal = scene->GetMedal();
					ECS::GetComponent<Sprite>(medal).SetTransparency(1.0f);
					auto level2 = scene->GetSelect2();
					ECS::GetComponent<Sprite>(level2).SetTransparency(1.0f);
					auto lock = scene->GetLock1();
					ECS::GetComponent<Sprite>(lock).SetTransparency(0.0f);
				}
			}
		}	
	}
	
	//Level 2 beat
	if (m_activeScene == m_scenes[11])
	{
		if (listener.GetLevelCheck())
		{
			level2Cleared = true;
			LevelFour* scene = (LevelFour*)m_activeScene;
			auto fruitBowl = scene->GetFruitBowl();
			auto& fbAnim = ECS::GetComponent<AnimationController>(fruitBowl);
			fbAnim.SetActiveAnim(0);

			levelTimer += Timer::deltaTime;

			if (levelTimer >= 3.f)
			{
				SceneEditor::ResetEditor();

				m_activeScene->Unload();

				m_scenes[4]->InitScene(float(BackEnd::GetWindowWidth()), float(BackEnd::GetWindowHeight()));
				m_register = m_scenes[4]->GetScene();
				m_activeScene = m_scenes[4];

				listener.SetWin(false);
				levelTimer = 0.f;
				listener.SetLevelCheck(false);

				if (level2Cleared)
				{
					LevelSelect2* scene = (LevelSelect2*)m_activeScene;
					auto medal = scene->GetMedal();
					ECS::GetComponent<Sprite>(medal).SetTransparency(1.0f);
					auto medal2 = scene->GetMedal2();
					ECS::GetComponent<Sprite>(medal2).SetTransparency(1.0f);
					auto level2 = scene->GetSelect2();
					ECS::GetComponent<Sprite>(level2).SetTransparency(1.0f);
					auto level3 = scene->GetSelect3();
					ECS::GetComponent<Sprite>(level3).SetTransparency(1.0f);
					auto lock = scene->GetLock1();
					ECS::GetComponent<Sprite>(lock).SetTransparency(0.0f);
					auto lock2 = scene->GetLock2();
					ECS::GetComponent<Sprite>(lock2).SetTransparency(0.0f);
				}
			}
		}
	}

	//Level 3 beat
	if (m_activeScene == m_scenes[9])
	{
		if (listener.GetLevelCheck())
		{
			level3Cleared = true;
			LevelTwo* scene = (LevelTwo*)m_activeScene;
			auto fruitBowl = scene->GetFruitBowl();
			auto& fbAnim = ECS::GetComponent<AnimationController>(fruitBowl);
			fbAnim.SetActiveAnim(0);

			levelTimer += Timer::deltaTime;

			if (levelTimer >= 3.f)
			{
				SceneEditor::ResetEditor();

				m_activeScene->Unload();

				m_scenes[5]->InitScene(float(BackEnd::GetWindowWidth()), float(BackEnd::GetWindowHeight()));
				m_register = m_scenes[5]->GetScene();
				m_activeScene = m_scenes[5];

				listener.SetWin(false);
				levelTimer = 0.f;
				listener.SetLevelCheck(false);

				if (level3Cleared)
				{
					LevelSelect3* scene = (LevelSelect3*)m_activeScene;
					auto medal = scene->GetMedal();
					ECS::GetComponent<Sprite>(medal).SetTransparency(1.0f);
					auto medal2 = scene->GetMedal2();
					ECS::GetComponent<Sprite>(medal2).SetTransparency(1.0f);
					auto medal3 = scene->GetMedal3();
					ECS::GetComponent<Sprite>(medal3).SetTransparency(1.0f);
					auto level2 = scene->GetSelect2();
					ECS::GetComponent<Sprite>(level2).SetTransparency(1.0f);
					auto level3 = scene->GetSelect3();
					ECS::GetComponent<Sprite>(level3).SetTransparency(1.0f);
					auto level4 = scene->GetSelect4();
					ECS::GetComponent<Sprite>(level4).SetTransparency(1.0f);
					auto lock = scene->GetLock1();
					ECS::GetComponent<Sprite>(lock).SetTransparency(0.0f);
					auto lock2 = scene->GetLock2();
					ECS::GetComponent<Sprite>(lock2).SetTransparency(0.0f);
					auto lock3 = scene->GetLock3();
					ECS::GetComponent<Sprite>(lock3).SetTransparency(0.0f);
				}
			}
		}
	}

	//Level 4 Beat
	if (m_activeScene == m_scenes[12])
	{
		if (listener.GetLevelCheck())
		{
			level4Cleared = true;
			LevelFive* scene = (LevelFive*)m_activeScene;
			auto fruitBowl = scene->GetFruitBowl();
			auto& fbAnim = ECS::GetComponent<AnimationController>(fruitBowl);
			fbAnim.SetActiveAnim(0);

			levelTimer += Timer::deltaTime;

			if (levelTimer >= 3.f)
			{
				SceneEditor::ResetEditor();

				m_activeScene->Unload();

				m_scenes[6]->InitScene(float(BackEnd::GetWindowWidth()), float(BackEnd::GetWindowHeight()));
				m_register = m_scenes[6]->GetScene();
				m_activeScene = m_scenes[6];

				listener.SetWin(false);
				levelTimer = 0.f;
				listener.SetLevelCheck(false);

				if (level4Cleared)
				{
					LevelSelect4* scene = (LevelSelect4*)m_activeScene;
					auto medal = scene->GetMedal();
					ECS::GetComponent<Sprite>(medal).SetTransparency(1.0f);
					auto level5 = scene->GetSelect5();
					ECS::GetComponent<Sprite>(level5).SetTransparency(1.0f);
					auto medal2 = scene->GetMedal2();
					ECS::GetComponent<Sprite>(medal2).SetTransparency(1.0f);
					auto medal3 = scene->GetMedal3();
					ECS::GetComponent<Sprite>(medal3).SetTransparency(1.0f);
					auto medal4 = scene->GetMedal4();
					ECS::GetComponent<Sprite>(medal4).SetTransparency(1.0f);
					auto level2 = scene->GetSelect2();
					ECS::GetComponent<Sprite>(level2).SetTransparency(1.0f);
					auto level3 = scene->GetSelect3();
					ECS::GetComponent<Sprite>(level3).SetTransparency(1.0f);
					auto level4 = scene->GetSelect4();
					ECS::GetComponent<Sprite>(level4).SetTransparency(1.0f);
					auto lock = scene->GetLock1();
					ECS::GetComponent<Sprite>(lock).SetTransparency(0.0f);
					auto lock2 = scene->GetLock2();
					ECS::GetComponent<Sprite>(lock2).SetTransparency(0.0f);
					auto lock3 = scene->GetLock3();
					ECS::GetComponent<Sprite>(lock3).SetTransparency(0.0f);
					auto lock4 = scene->GetLock4();
					ECS::GetComponent<Sprite>(lock4).SetTransparency(0.0f);
				}
			}
		}
	}

	//Level 5 Beat
	if (m_activeScene == m_scenes[10])
	{
		if (listener.GetLevelCheck())
		{
			level5Cleared = true;
			LevelThree* scene = (LevelThree*)m_activeScene;
			auto fruitBowl = scene->GetFruitBowl();
			auto& fbAnim = ECS::GetComponent<AnimationController>(fruitBowl);
			fbAnim.SetActiveAnim(0);

			levelTimer += Timer::deltaTime;

			if (levelTimer >= 3.f)
			{
				SceneEditor::ResetEditor();

				m_activeScene->Unload();

				m_scenes[7]->InitScene(float(BackEnd::GetWindowWidth()), float(BackEnd::GetWindowHeight()));
				m_register = m_scenes[7]->GetScene();
				m_activeScene = m_scenes[7];

				listener.SetWin(false);
				levelTimer = 0.f;
				listener.SetLevelCheck(false);

				if (level5Cleared)
				{
					LevelSelect5* scene = (LevelSelect5*)m_activeScene;
					auto medal = scene->GetMedal();
					ECS::GetComponent<Sprite>(medal).SetTransparency(1.0f);
					auto medal2 = scene->GetMedal2();
					ECS::GetComponent<Sprite>(medal2).SetTransparency(1.0f);
					auto medal3 = scene->GetMedal3();
					ECS::GetComponent<Sprite>(medal3).SetTransparency(1.0f);
					auto medal4 = scene->GetMedal4();
					ECS::GetComponent<Sprite>(medal4).SetTransparency(1.0f);
					auto medal5 = scene->GetMedal5();
					ECS::GetComponent<Sprite>(medal5).SetTransparency(1.0f);
					auto level2 = scene->GetSelect2();
					ECS::GetComponent<Sprite>(level2).SetTransparency(1.0f);
					auto level3 = scene->GetSelect3();
					ECS::GetComponent<Sprite>(level3).SetTransparency(1.0f);
					auto level4 = scene->GetSelect4();
					ECS::GetComponent<Sprite>(level4).SetTransparency(1.0f);
					auto level5 = scene->GetSelect5();
					ECS::GetComponent<Sprite>(level5).SetTransparency(1.0f);
					auto lock = scene->GetLock1();
					ECS::GetComponent<Sprite>(lock).SetTransparency(0.0f);
					auto lock2 = scene->GetLock2();
					ECS::GetComponent<Sprite>(lock2).SetTransparency(0.0f);
					auto lock3 = scene->GetLock3();
					ECS::GetComponent<Sprite>(lock3).SetTransparency(0.0f);
					auto lock4 = scene->GetLock4();
					ECS::GetComponent<Sprite>(lock4).SetTransparency(0.0f);
				}
			}
		}
	}
#pragma endregion

#pragma region Intro
	//ends the game intro
	if (m_activeScene == m_scenes[13])
	{
		GoGoIntro* scene = (GoGoIntro*)m_activeScene;

		if (scene->GetEnd())
		{
			SceneEditor::ResetEditor();

			m_activeScene->Unload();

			m_scenes[1]->InitScene(float(BackEnd::GetWindowWidth()), float(BackEnd::GetWindowHeight()));
			m_register = m_scenes[1]->GetScene();
			m_activeScene = m_scenes[1];
		}
	}
#pragma endregion

#pragma region Tutorial Animations
	if (m_activeScene == m_scenes[8])
	{
		GoGoGame* scene = (GoGoGame*)m_activeScene;
		auto cloud = scene->GetCloud1();
		auto cloud2 = scene->GetCloud2();
		auto& animController = ECS::GetComponent<AnimationController>(cloud);
		auto& animController2 = ECS::GetComponent<AnimationController>(cloud2);

		animController.SetActiveAnim(2);
		animController2.SetActiveAnim(2);

		if (tutorialCheckW1 && tutorialCheckW2)
		{
			animController.SetActiveAnim(0);
		}
		if (tutorialCheckB1 && tutorialCheckB2)
		{
			animController2.SetActiveAnim(0);
		}
	}
#pragma endregion

}

void Game::GUI()
{
	UI::Start(BackEnd::GetWindowWidth(), BackEnd::GetWindowHeight());

	ImGui::Text("Place your different tabs below.");

	if (ImGui::BeginTabBar(""))
	{
		BackEnd::GUI(m_register, m_activeScene);

		ImGui::EndTabBar();
	}

	UI::End();
}

void Game::CheckEvents()
{
	if (m_close)
		m_window->Close();

	if (m_motion)
		MouseMotion(BackEnd::GetMotionEvent());

	if (m_click)
		MouseClick(BackEnd::GetClickEvent());

	if (m_wheel)
		MouseWheel(BackEnd::GetWheelEvent());
}

void Game::AcceptInput()
{
	XInputManager::Update();

	//Just calls all the other input functions 
	GamepadInput();

	KeyboardHold();
	KeyboardDown();
	KeyboardUp();

	//Resets the key flags
	//Must be done once per frame for input to work
	Input::ResetKeys();
}

void Game::GamepadInput()
{
	XInputController* tempCon;
	//Gamepad button stroked (pressed)
	for (int i = 0; i < 3; i++)
	{
		if (XInputManager::ControllerConnected(i))
		{
			tempCon = XInputManager::GetController(i);
			tempCon->SetStickDeadZone(0.1f);

			//If the controller is connected, we run the different input types
			GamepadStroke(tempCon);
			GamepadUp(tempCon);
			GamepadDown(tempCon);
			GamepadStick(tempCon);
			GamepadTrigger(tempCon);
		}
	}
}

#pragma region Gamepad Functions
void Game::GamepadStroke(XInputController* con)
{
	//Active scene now captures this input and can use it
	//Look at base Scene class for more info.
	m_activeScene->GamepadStroke(con);
}

void Game::GamepadUp(XInputController* con)
{
	//Active scene now captures this input and can use it
	//Look at base Scene class for more info.
	m_activeScene->GamepadUp(con);
}

void Game::GamepadDown(XInputController* con)
{
	//Active scene now captures this input and can use it
	//Look at base Scene class for more info.
	m_activeScene->GamepadDown(con);
}

void Game::GamepadStick(XInputController* con)
{
	//Active scene now captures this input and can use it
	//Look at base Scene class for more info.
	m_activeScene->GamepadStick(con);
}

void Game::GamepadTrigger(XInputController* con)
{
	//Active scene now captures this input and can use it
	//Look at base Scene class for more info.
	m_activeScene->GamepadTrigger(con);
}
#pragma endregion

void Game::KeyboardHold()
{
#pragma region MOVEMENT SYSTEM
	//MOVEMENT
	for (int i = 8; i < 13; ++i)
	{
		if (m_activeScene == m_scenes[i])
		{
			auto blueBody = ECS::GetComponent<PhysicsBody>(EntityIdentifier::MainPlayer()).GetBody();
			auto waterBody = ECS::GetComponent<PhysicsBody>(EntityIdentifier::MainPlayer2()).GetBody();
			b2Vec2 blueVel = blueBody->GetLinearVelocity();
			b2Vec2 waterVel = waterBody->GetLinearVelocity();
			float blueSpeed = 0.f, waterSpeed = 0.f;
	
			auto& blueAnim = ECS::GetComponent<AnimationController>(EntityIdentifier::MainPlayer());
			auto& waterAnim = ECS::GetComponent<AnimationController>(EntityIdentifier::MainPlayer2());

			if (Input::GetKey(Key::A))
			{
				blueSpeed = -12.f;
				blueAnim.SetActiveAnim(0);
				dir = LEFT;
				tutorialCheckB1 = true;
			}
			if (Input::GetKey(Key::D))
			{
				blueSpeed = 12.f;
				blueAnim.SetActiveAnim(1);
				dir = RIGHT;
				tutorialCheckB1 = true;
			}
			if (Input::GetKey(Key::LeftArrow))
			{
				waterSpeed = -12.f;
				waterAnim.SetActiveAnim(2);
				dir2 = LEFT2;
				tutorialCheckW1 = true;
			}
			if (Input::GetKey(Key::RightArrow))
			{
				waterSpeed = 12.f;
				waterAnim.SetActiveAnim(3);
				dir2 = RIGHT2;
				tutorialCheckW1 = true;
			}
	
			float blueChange = blueSpeed - blueVel.x;
			float waterChange = waterSpeed - waterVel.x;
			float blueForce = (blueBody->GetMass() * blueChange);
			float waterForce = (waterBody->GetMass() * waterChange);

			if (!(listener.GetWin()))
			{
				blueBody->ApplyForce(b2Vec2(blueForce, 0), blueBody->GetWorldCenter(), true);
				waterBody->ApplyForce(b2Vec2(waterForce, 0), waterBody->GetWorldCenter(), true);
			}
		}
	}
#pragma endregion
}

void Game::KeyboardDown()
{
	//Exit fullscreen
	if (Input::GetKeyDown(Key::Escape))
	{
		exit(1);
	}

#pragma region SCREEN MANIPULATION
//Space on title screen goes to play screen
if (Input::GetKeyDown(Key::Space) && m_activeScene == m_scenes[0])
{
	sndPlaySound("MenuSelect.wav", SND_FILENAME | SND_ASYNC);

	GoGoTitle* scene = (GoGoTitle*)m_activeScene;

	scene->SetFade(true);

	changeT = true;

	ECS::DestroyEntity(scene->GetImage());
	ECS::DestroyEntity(scene->GetText());
	ECS::DestroyEntity(scene->GetBlueStripe());
	ECS::DestroyEntity(scene->GetRedStripe());

	ECS::GetComponent<Sprite>(scene->GetLoading()).SetTransparency(1.0f);
}
//Space on play goes to intro
else if (Input::GetKeyDown(Key::Space) && m_activeScene == m_scenes[1])
{
	sndPlaySound("MenuSelect.wav", SND_FILENAME | SND_ASYNC);

	GoGoMenu* scene = (GoGoMenu*)m_activeScene;

	scene->SetFade(true);

	change = true;

	ECS::DestroyEntity(scene->GetMenu());
	spikeDestroyed = true;
	ECS::DestroyEntity(scene->GetSpike1());
	ECS::DestroyEntity(scene->GetSpike2());
}
//Space on intro to start intro
else if (Input::GetKeyDown(Key::Space) && m_activeScene == m_scenes[13])
{
	GoGoIntro* scene = (GoGoIntro*)m_activeScene;

	scene->SetStart(true);
}
//Up arrow goes from menu to exit
if (Input::GetKeyDown(Key::UpArrow) && m_activeScene == m_scenes[1])
{
	sndPlaySound("MenuClick.wav", SND_FILENAME | SND_ASYNC);

	SceneEditor::ResetEditor();

	m_activeScene->Unload();

	m_scenes[2]->InitScene(float(BackEnd::GetWindowWidth()), float(BackEnd::GetWindowHeight()));
	m_register = m_scenes[2]->GetScene();
	m_activeScene = m_scenes[2];
}
//Down arrow on menu goes to exit
else if (Input::GetKeyDown(Key::DownArrow) && m_activeScene == m_scenes[1])
{
	sndPlaySound("MenuClick.wav", SND_FILENAME | SND_ASYNC);

	SceneEditor::ResetEditor();

	m_activeScene->Unload();

	m_scenes[2]->InitScene(float(BackEnd::GetWindowWidth()), float(BackEnd::GetWindowHeight()));
	m_register = m_scenes[2]->GetScene();
	m_activeScene = m_scenes[2];
}
//Up arrow on exit goes to menu
else if (Input::GetKeyDown(Key::UpArrow) && m_activeScene == m_scenes[2])
{
	sndPlaySound("MenuClick.wav", SND_FILENAME | SND_ASYNC);

	SceneEditor::ResetEditor();

	m_activeScene->Unload();

	m_scenes[1]->InitScene(float(BackEnd::GetWindowWidth()), float(BackEnd::GetWindowHeight()));
	m_register = m_scenes[1]->GetScene();
	m_activeScene = m_scenes[1];
}
//Down arrow on exit goes to menu
else if (Input::GetKeyDown(Key::DownArrow) && m_activeScene == m_scenes[2])
{
	sndPlaySound("MenuClick.wav", SND_FILENAME | SND_ASYNC);

	SceneEditor::ResetEditor();

	m_activeScene->Unload();

	m_scenes[1]->InitScene(float(BackEnd::GetWindowWidth()), float(BackEnd::GetWindowHeight()));
	m_register = m_scenes[1]->GetScene();
	m_activeScene = m_scenes[1];
}
//Exits the game
if (Input::GetKeyDown(Key::Space) && m_activeScene == m_scenes[2])
{
	sndPlaySound("MenuSelect.wav", SND_FILENAME | SND_ASYNC);
	exit(1);
}
#pragma endregion

#pragma region Level Select Scenes
///////////////////////////////////////////////////////////
				//LEVEL SELECT SCENES\\
///////////////////////////////////////////////////////////

//Level Select 1 to Level Select 2
if (Input::GetKeyDown(Key::RightArrow) && m_activeScene == m_scenes[3] && !loading)
{
	sndPlaySound("MenuClick.wav", SND_FILENAME | SND_ASYNC);

	SceneEditor::ResetEditor();

	m_activeScene->Unload();

	m_scenes[4]->InitScene(float(BackEnd::GetWindowWidth()), float(BackEnd::GetWindowHeight()));
	m_register = m_scenes[4]->GetScene();
	m_activeScene = m_scenes[4];

	LevelSelect2* scene = (LevelSelect2*)m_activeScene;

	if (level1Cleared)
	{
		auto level1 = scene->GetSelect1();
		ECS::GetComponent<Sprite>(level1).SetTransparency(1.0f);
		auto level2 = scene->GetSelect2();
		ECS::GetComponent<Sprite>(level2).SetTransparency(1.0f);	
		auto medal2 = scene->GetMedal2();
		ECS::GetComponent<Sprite>(medal2).SetTransparency(1.0f);
		auto lock = scene->GetLock1();
		ECS::GetComponent<Sprite>(lock).SetTransparency(0.0f);
	}
	if (level2Cleared)
	{
		auto level3 = scene->GetSelect3();
		auto medal2 = scene->GetMedal();
		ECS::GetComponent<Sprite>(level3).SetTransparency(1.0f);
		ECS::GetComponent<Sprite>(medal2).SetTransparency(1.0f);
		auto lock = scene->GetLock2();
		ECS::GetComponent<Sprite>(lock).SetTransparency(0.0f);
	}
	if (level3Cleared)
	{
		auto level4 = scene->GetSelect4();
		auto medal3 = scene->GetMedal3();
		ECS::GetComponent<Sprite>(level4).SetTransparency(1.0f);
		ECS::GetComponent<Sprite>(medal3).SetTransparency(1.0f);
		auto lock = scene->GetLock3();
		ECS::GetComponent<Sprite>(lock).SetTransparency(0.0f);
	}
	if (level4Cleared)
	{
		auto level5 = scene->GetSelect5();
		auto medal4 = scene->GetMedal4();
		ECS::GetComponent<Sprite>(level5).SetTransparency(1.0f);
		ECS::GetComponent<Sprite>(medal4).SetTransparency(1.0f);
		auto lock = scene->GetLock4();
		ECS::GetComponent<Sprite>(lock).SetTransparency(0.0f);
	}
	if (level5Cleared)
	{
		auto medal5 = scene->GetMedal5();
		ECS::GetComponent<Sprite>(medal5).SetTransparency(1.0f);
	}
}
//Level Select 1 to Level Select 5
else if (Input::GetKeyDown(Key::LeftArrow) && m_activeScene == m_scenes[3] && !loading)
{
	sndPlaySound("MenuClick.wav", SND_FILENAME | SND_ASYNC);

	SceneEditor::ResetEditor();

	m_activeScene->Unload();

	m_scenes[7]->InitScene(float(BackEnd::GetWindowWidth()), float(BackEnd::GetWindowHeight()));
	m_register = m_scenes[7]->GetScene();
	m_activeScene = m_scenes[7];

	LevelSelect5* scene = (LevelSelect5*)m_activeScene;

	if (level1Cleared)
	{
		auto medal1 = scene->GetMedal2();
		auto level2 = scene->GetSelect2();
		ECS::GetComponent<Sprite>(medal1).SetTransparency(1.0f);
		ECS::GetComponent<Sprite>(level2).SetTransparency(1.0f);
		auto lock = scene->GetLock1();
		ECS::GetComponent<Sprite>(lock).SetTransparency(0.0f);
	}
	if (level2Cleared)
	{
		auto level3 = scene->GetSelect3();
		ECS::GetComponent<Sprite>(level3).SetTransparency(1.0f);
		auto medal = scene->GetMedal3();
		ECS::GetComponent<Sprite>(medal).SetTransparency(1.0f);
		auto lock = scene->GetLock2();
		ECS::GetComponent<Sprite>(lock).SetTransparency(0.0f);
	}	
	if (level3Cleared)
	{
		auto level4 = scene->GetSelect4();
		auto medal = scene->GetMedal4();
		ECS::GetComponent<Sprite>(level4).SetTransparency(1.0f);
		ECS::GetComponent<Sprite>(medal).SetTransparency(1.0f);
		auto lock = scene->GetLock3();
		ECS::GetComponent<Sprite>(lock).SetTransparency(0.0f);
	}
	if (level4Cleared)
	{
		auto level5 = scene->GetSelect5();
		auto medal = scene->GetMedal5();
		ECS::GetComponent<Sprite>(level5).SetTransparency(1.0f);
		ECS::GetComponent<Sprite>(medal).SetTransparency(1.0f);
		auto lock = scene->GetLock4();
		ECS::GetComponent<Sprite>(lock).SetTransparency(0.0f);
	}
	if (level5Cleared)
	{
		auto medal = scene->GetMedal();
		ECS::GetComponent<Sprite>(medal).SetTransparency(1.0f);
	}
}
//Level Select 2 to Level Select 1
else if (Input::GetKeyDown(Key::LeftArrow) && m_activeScene == m_scenes[4] && !loading)
{
	sndPlaySound("MenuClick.wav", SND_FILENAME | SND_ASYNC);

	SceneEditor::ResetEditor();

	m_activeScene->Unload();

	m_scenes[3]->InitScene(float(BackEnd::GetWindowWidth()), float(BackEnd::GetWindowHeight()));
	m_register = m_scenes[3]->GetScene();
	m_activeScene = m_scenes[3];

	LevelSelectMain* scene = (LevelSelectMain*)m_activeScene;

	if (level1Cleared)
	{
		auto level2 = scene->GetSelect2();
		auto medal = scene->GetMedal();
		ECS::GetComponent<Sprite>(level2).SetTransparency(1.0f);
		ECS::GetComponent<Sprite>(medal).SetTransparency(1.0f);
		auto lock = scene->GetLock1();
		ECS::GetComponent<Sprite>(lock).SetTransparency(0.0f);
	}
	if (level2Cleared)
	{
		auto medal = scene->GetMedal2();
		ECS::GetComponent<Sprite>(medal).SetTransparency(1.0f);
		auto level3 = scene->GetSelect3();
		ECS::GetComponent<Sprite>(level3).SetTransparency(1.0f);
		auto lock = scene->GetLock2();
		ECS::GetComponent<Sprite>(lock).SetTransparency(0.0f);
	}
	if (level3Cleared)
	{
		auto level4 = scene->GetSelect4();
		auto medal = scene->GetMedal3();
		ECS::GetComponent<Sprite>(level4).SetTransparency(1.0f);
		ECS::GetComponent<Sprite>(medal).SetTransparency(1.0f);
		auto lock = scene->GetLock3();
		ECS::GetComponent<Sprite>(lock).SetTransparency(0.0f);
	}
	if (level4Cleared)
	{
		auto level5 = scene->GetSelect5();
		auto medal = scene->GetMedal4();
		ECS::GetComponent<Sprite>(level5).SetTransparency(1.0f);
		ECS::GetComponent<Sprite>(medal).SetTransparency(1.0f);
		auto lock = scene->GetLock4();
		ECS::GetComponent<Sprite>(lock).SetTransparency(0.0f);
	}
	if (level5Cleared)
	{
		auto medal = scene->GetMedal5();
		ECS::GetComponent<Sprite>(medal).SetTransparency(1.0f);
	}
}
//Level Select 2 to Level Select 3
else if (Input::GetKeyDown(Key::RightArrow) && m_activeScene == m_scenes[4] && !loading)
{
	sndPlaySound("MenuClick.wav", SND_FILENAME | SND_ASYNC);

	SceneEditor::ResetEditor();

	m_activeScene->Unload();

	m_scenes[5]->InitScene(float(BackEnd::GetWindowWidth()), float(BackEnd::GetWindowHeight()));
	m_register = m_scenes[5]->GetScene();
	m_activeScene = m_scenes[5];

	LevelSelect3* scene = (LevelSelect3*)m_activeScene;

	if (level1Cleared)
	{
		auto medal1 = scene->GetMedal2();
		ECS::GetComponent<Sprite>(medal1).SetTransparency(1.0f);
		auto level2 = scene->GetSelect2();
		ECS::GetComponent<Sprite>(level2).SetTransparency(1.0f);
		auto lock = scene->GetLock1();
		ECS::GetComponent<Sprite>(lock).SetTransparency(0.0f);
	}
	if (level2Cleared)
	{
		auto level2 = scene->GetSelect2();
		ECS::GetComponent<Sprite>(level2).SetTransparency(1.0f);
		auto level3 = scene->GetSelect3();
		ECS::GetComponent<Sprite>(level3).SetTransparency(1.0f);
		auto medal2 = scene->GetMedal3();
		ECS::GetComponent<Sprite>(medal2).SetTransparency(1.0f);
		auto lock = scene->GetLock2();
		ECS::GetComponent<Sprite>(lock).SetTransparency(0.0f);
	}
	if (level3Cleared)
	{
		auto medal = scene->GetMedal();
		ECS::GetComponent<Sprite>(medal).SetTransparency(1.0f);
		auto level4 = scene->GetSelect4();
		ECS::GetComponent<Sprite>(level4).SetTransparency(1.0f);
		auto lock = scene->GetLock3();
		ECS::GetComponent<Sprite>(lock).SetTransparency(0.0f);
	}
	if (level4Cleared)
	{
		auto medal4 = scene->GetMedal4();
		ECS::GetComponent<Sprite>(medal4).SetTransparency(1.0f);
		auto level5 = scene->GetSelect5();
		ECS::GetComponent<Sprite>(level5).SetTransparency(1.0f);
		auto lock = scene->GetLock4();
		ECS::GetComponent<Sprite>(lock).SetTransparency(0.0f);
	}
	if (level5Cleared)
	{
		auto medal5 = scene->GetMedal5();
		ECS::GetComponent<Sprite>(medal5).SetTransparency(1.0f);
	}
}
//Level Select 3 to Level Select 4
else if (Input::GetKeyDown(Key::RightArrow) && m_activeScene == m_scenes[5] && !loading)
{
	sndPlaySound("MenuClick.wav", SND_FILENAME | SND_ASYNC);

	SceneEditor::ResetEditor();

	m_activeScene->Unload();

	m_scenes[6]->InitScene(float(BackEnd::GetWindowWidth()), float(BackEnd::GetWindowHeight()));
	m_register = m_scenes[6]->GetScene();
	m_activeScene = m_scenes[6];

	LevelSelect4* scene = (LevelSelect4*)m_activeScene;

	if (level1Cleared)
	{
		auto medal1 = scene->GetMedal2();
		ECS::GetComponent<Sprite>(medal1).SetTransparency(1.0f);
		auto level2 = scene->GetSelect2();
		ECS::GetComponent<Sprite>(level2).SetTransparency(1.0f);
		auto lock = scene->GetLock1();
		ECS::GetComponent<Sprite>(lock).SetTransparency(0.0f);
	}	
	if (level2Cleared)
	{
		auto level2 = scene->GetSelect2();
		ECS::GetComponent<Sprite>(level2).SetTransparency(1.0f);
		auto level3 = scene->GetSelect3();
		ECS::GetComponent<Sprite>(level3).SetTransparency(1.0f);
		auto medal2 = scene->GetMedal3();
		ECS::GetComponent<Sprite>(medal2).SetTransparency(1.0f);
		auto lock = scene->GetLock2();
		ECS::GetComponent<Sprite>(lock).SetTransparency(0.0f);
	}
	if (level3Cleared)
	{
		auto medal3 = scene->GetMedal4();
		ECS::GetComponent<Sprite>(medal3).SetTransparency(1.0f);
		auto level4 = scene->GetSelect4();
		ECS::GetComponent<Sprite>(level4).SetTransparency(1.0f);
		auto lock = scene->GetLock3();
		ECS::GetComponent<Sprite>(lock).SetTransparency(0.0f);
	}
	if (level4Cleared)
	{
		auto medal = scene->GetMedal();
		ECS::GetComponent<Sprite>(medal).SetTransparency(1.0f);
		auto level5 = scene->GetSelect5();
		ECS::GetComponent<Sprite>(level5).SetTransparency(1.0f);
		auto lock = scene->GetLock4();
		ECS::GetComponent<Sprite>(lock).SetTransparency(0.0f);
	}
	if (level5Cleared)
	{
		auto medal5 = scene->GetMedal5();
		ECS::GetComponent<Sprite>(medal5).SetTransparency(1.0f);
	}
}
//Level Select 3 to Level Select 2
else if (Input::GetKeyDown(Key::LeftArrow) && m_activeScene == m_scenes[5] && !loading)
{
	sndPlaySound("MenuClick.wav", SND_FILENAME | SND_ASYNC);

	SceneEditor::ResetEditor();

	m_activeScene->Unload();

	m_scenes[4]->InitScene(float(BackEnd::GetWindowWidth()), float(BackEnd::GetWindowHeight()));
	m_register = m_scenes[4]->GetScene();
	m_activeScene = m_scenes[4];

	LevelSelect2* scene = (LevelSelect2*)m_activeScene;

	if (level1Cleared)
	{
		auto level2 = scene->GetSelect2();
		ECS::GetComponent<Sprite>(level2).SetTransparency(1.0f);
		auto medal1 = scene->GetMedal2();
		ECS::GetComponent<Sprite>(medal1).SetTransparency(1.0f);
		auto lock = scene->GetLock1();
		ECS::GetComponent<Sprite>(lock).SetTransparency(0.0f);
	}
	if (level2Cleared)
	{
		auto level3 = scene->GetSelect3();
		auto medal = scene->GetMedal();
		ECS::GetComponent<Sprite>(level3).SetTransparency(1.0f);
		ECS::GetComponent<Sprite>(medal).SetTransparency(1.0f);
		auto lock = scene->GetLock2();
		ECS::GetComponent<Sprite>(lock).SetTransparency(0.0f);
	}
	if (level3Cleared)
	{
		auto level4 = scene->GetSelect4();
		auto medal = scene->GetMedal3();
		ECS::GetComponent<Sprite>(level4).SetTransparency(1.0f);
		ECS::GetComponent<Sprite>(medal).SetTransparency(1.0f);
		auto lock = scene->GetLock3();
		ECS::GetComponent<Sprite>(lock).SetTransparency(0.0f);
	}
	if (level4Cleared)
	{
		auto level5 = scene->GetSelect5();
		auto medal = scene->GetMedal4();
		ECS::GetComponent<Sprite>(level5).SetTransparency(1.0f);
		ECS::GetComponent<Sprite>(medal).SetTransparency(1.0f);
		auto lock = scene->GetLock4();
		ECS::GetComponent<Sprite>(lock).SetTransparency(0.0f);
	}
	if (level5Cleared)
	{
		auto medal = scene->GetMedal5();
		ECS::GetComponent<Sprite>(medal).SetTransparency(1.0f);
	}
}
//Level Select 4 to Level Select 5
else if (Input::GetKeyDown(Key::RightArrow) && m_activeScene == m_scenes[6] && !loading)
{
	sndPlaySound("MenuClick.wav", SND_FILENAME | SND_ASYNC);
	
	SceneEditor::ResetEditor();
	
	m_activeScene->Unload();
	
	m_scenes[7]->InitScene(float(BackEnd::GetWindowWidth()), float(BackEnd::GetWindowHeight()));
	m_register = m_scenes[7]->GetScene();
	m_activeScene = m_scenes[7];

	LevelSelect5* scene = (LevelSelect5*)m_activeScene;

	if (level1Cleared)
	{
		auto medal1 = scene->GetMedal2();
		ECS::GetComponent<Sprite>(medal1).SetTransparency(1.0f);
		auto level2 = scene->GetSelect2();
		ECS::GetComponent<Sprite>(level2).SetTransparency(1.0f);
		auto lock = scene->GetLock1();
		ECS::GetComponent<Sprite>(lock).SetTransparency(0.0f);
	}
	if (level2Cleared)
	{
		auto level2 = scene->GetSelect2();
		ECS::GetComponent<Sprite>(level2).SetTransparency(1.0f);
		auto level3 = scene->GetSelect3();
		ECS::GetComponent<Sprite>(level3).SetTransparency(1.0f);
		auto medal2 = scene->GetMedal3();
		ECS::GetComponent<Sprite>(medal2).SetTransparency(1.0f);
		auto lock = scene->GetLock2();
		ECS::GetComponent<Sprite>(lock).SetTransparency(0.0f);
	}
	if (level3Cleared)
	{
		auto level4 = scene->GetSelect4();
		ECS::GetComponent<Sprite>(level4).SetTransparency(1.0f);
		auto medal3 = scene->GetMedal4();
		ECS::GetComponent<Sprite>(medal3).SetTransparency(1.0f);
		auto lock = scene->GetLock3();
		ECS::GetComponent<Sprite>(lock).SetTransparency(0.0f);
	}
	if (level4Cleared)
	{
		auto level5 = scene->GetSelect5();
		ECS::GetComponent<Sprite>(level5).SetTransparency(1.0f);
		auto medal4 = scene->GetMedal5();
		ECS::GetComponent<Sprite>(medal4).SetTransparency(1.0f);
		auto lock = scene->GetLock4();
		ECS::GetComponent<Sprite>(lock).SetTransparency(0.0f);
	}
	if (level5Cleared)
	{
		auto medal = scene->GetMedal();
		ECS::GetComponent<Sprite>(medal).SetTransparency(1.0f);
	}
}
//Level Select 4 to Level Select 3
else if (Input::GetKeyDown(Key::LeftArrow) && m_activeScene == m_scenes[6] && !loading)
{
	sndPlaySound("MenuClick.wav", SND_FILENAME | SND_ASYNC);
	
	SceneEditor::ResetEditor();
	
	m_activeScene->Unload();
	
	m_scenes[5]->InitScene(float(BackEnd::GetWindowWidth()), float(BackEnd::GetWindowHeight()));
	m_register = m_scenes[5]->GetScene();
	m_activeScene = m_scenes[5];

	LevelSelect3* scene = (LevelSelect3*)m_activeScene;

	if (level1Cleared)
	{
		auto level2 = scene->GetSelect2();
		ECS::GetComponent<Sprite>(level2).SetTransparency(1.0f);
		auto medal1 = scene->GetMedal2();
		ECS::GetComponent<Sprite>(medal1).SetTransparency(1.0f);
		auto lock = scene->GetLock1();
		ECS::GetComponent<Sprite>(lock).SetTransparency(0.0f);
	}
	if (level2Cleared)
	{
		auto level3 = scene->GetSelect3();
		auto medal = scene->GetMedal3();
		ECS::GetComponent<Sprite>(level3).SetTransparency(1.0f);
		ECS::GetComponent<Sprite>(medal).SetTransparency(1.0f);
		auto lock = scene->GetLock2();
		ECS::GetComponent<Sprite>(lock).SetTransparency(0.0f);
	}
	if (level3Cleared)
	{
		auto level4 = scene->GetSelect4();
		auto medal = scene->GetMedal();
		ECS::GetComponent<Sprite>(level4).SetTransparency(1.0f);
		ECS::GetComponent<Sprite>(medal).SetTransparency(1.0f);
		auto lock = scene->GetLock3();
		ECS::GetComponent<Sprite>(lock).SetTransparency(0.0f);
	}
	if (level4Cleared)
	{
		auto level5 = scene->GetSelect5();
		auto medal = scene->GetMedal4();
		ECS::GetComponent<Sprite>(level5).SetTransparency(1.0f);
		ECS::GetComponent<Sprite>(medal).SetTransparency(1.0f);
		auto lock = scene->GetLock4();
		ECS::GetComponent<Sprite>(lock).SetTransparency(0.0f);
	}
	if (level5Cleared)
	{
		auto medal = scene->GetMedal5();
		ECS::GetComponent<Sprite>(medal).SetTransparency(1.0f);
	}
}
//Level Select 5 to Level Select 1
else if (Input::GetKeyDown(Key::RightArrow) && m_activeScene == m_scenes[7] && !loading)
{
	sndPlaySound("MenuClick.wav", SND_FILENAME | SND_ASYNC);
	
	SceneEditor::ResetEditor();
	
	m_activeScene->Unload();
	
	m_scenes[3]->InitScene(float(BackEnd::GetWindowWidth()), float(BackEnd::GetWindowHeight()));
	m_register = m_scenes[3]->GetScene();
	m_activeScene = m_scenes[3];

	LevelSelectMain* scene = (LevelSelectMain*)m_activeScene;

	if (level1Cleared)
	{
		auto medal1 = scene->GetMedal();
		ECS::GetComponent<Sprite>(medal1).SetTransparency(1.0f);
		auto level2 = scene->GetSelect2();
		ECS::GetComponent<Sprite>(level2).SetTransparency(1.0f);
		auto lock = scene->GetLock1();
		ECS::GetComponent<Sprite>(lock).SetTransparency(0.0f);
	}
	if (level2Cleared)
	{
		auto level2 = scene->GetSelect2();
		auto level3 = scene->GetSelect3();
		ECS::GetComponent<Sprite>(level2).SetTransparency(1.0f);
		ECS::GetComponent<Sprite>(level3).SetTransparency(1.0f);
		auto medal2 = scene->GetMedal2();
		ECS::GetComponent<Sprite>(medal2).SetTransparency(1.0f);
		auto lock = scene->GetLock2();
		ECS::GetComponent<Sprite>(lock).SetTransparency(0.0f);
	}
	if (level3Cleared)
	{
		auto level4 = scene->GetSelect4();
		ECS::GetComponent<Sprite>(level4).SetTransparency(1.0f);
		auto medal3 = scene->GetMedal3();
		ECS::GetComponent<Sprite>(medal3).SetTransparency(1.0f);
		auto lock = scene->GetLock3();
		ECS::GetComponent<Sprite>(lock).SetTransparency(0.0f);
	}
	if (level4Cleared)
	{
		auto level5 = scene->GetSelect5();
		ECS::GetComponent<Sprite>(level5).SetTransparency(1.0f);
		auto medal4 = scene->GetMedal4();
		ECS::GetComponent<Sprite>(medal4).SetTransparency(1.0f);
		auto lock = scene->GetLock4();
		ECS::GetComponent<Sprite>(lock).SetTransparency(0.0f);
	}
	if (level5Cleared)
	{
		auto medal5 = scene->GetMedal5();
		ECS::GetComponent<Sprite>(medal5).SetTransparency(1.0f);
	}
}
//Level Select 5 to Level Select 4
else if (Input::GetKeyDown(Key::LeftArrow) && m_activeScene == m_scenes[7] && !loading)
{
	sndPlaySound("MenuClick.wav", SND_FILENAME | SND_ASYNC);

	SceneEditor::ResetEditor();

	m_activeScene->Unload();

	m_scenes[6]->InitScene(float(BackEnd::GetWindowWidth()), float(BackEnd::GetWindowHeight()));
	m_register = m_scenes[6]->GetScene();
	m_activeScene = m_scenes[6];

	LevelSelect4* scene = (LevelSelect4*)m_activeScene;

	if (level1Cleared)
	{
		auto level2 = scene->GetSelect2();
		ECS::GetComponent<Sprite>(level2).SetTransparency(1.0f);
		auto medal1 = scene->GetMedal2();
		ECS::GetComponent<Sprite>(medal1).SetTransparency(1.0f);
		auto lock = scene->GetLock1();
		ECS::GetComponent<Sprite>(lock).SetTransparency(0.0f);
	}
	if (level2Cleared)
	{
		auto level3 = scene->GetSelect3();
		ECS::GetComponent<Sprite>(level3).SetTransparency(1.0f);
		auto medal = scene->GetMedal3();
		ECS::GetComponent<Sprite>(medal).SetTransparency(1.0f);
		auto lock = scene->GetLock2();
		ECS::GetComponent<Sprite>(lock).SetTransparency(0.0f);
	}
	if (level3Cleared)
	{
		auto level4 = scene->GetSelect4();
		auto medal = scene->GetMedal4();
		ECS::GetComponent<Sprite>(level4).SetTransparency(1.0f);
		ECS::GetComponent<Sprite>(medal).SetTransparency(1.0f);
		auto lock = scene->GetLock3();
		ECS::GetComponent<Sprite>(lock).SetTransparency(0.0f);
	}
	if (level4Cleared)
	{
		auto level5 = scene->GetSelect5();
		auto medal = scene->GetMedal();
		ECS::GetComponent<Sprite>(level5).SetTransparency(1.0f);
		ECS::GetComponent<Sprite>(medal).SetTransparency(1.0f);
		auto lock = scene->GetLock4();
		ECS::GetComponent<Sprite>(lock).SetTransparency(0.0f);
	}
	if (level5Cleared)
	{
		auto medal = scene->GetMedal5();
		ECS::GetComponent<Sprite>(medal).SetTransparency(1.0f);
	}
}
//Level Select 1 to Level Select 4
else if (Input::GetKeyDown(Key::DownArrow) && m_activeScene == m_scenes[3] && !loading)
{
	sndPlaySound("MenuClick.wav", SND_FILENAME | SND_ASYNC);
	
	SceneEditor::ResetEditor();
	
	m_activeScene->Unload();
	
	m_scenes[6]->InitScene(float(BackEnd::GetWindowWidth()), float(BackEnd::GetWindowHeight()));
	m_register = m_scenes[6]->GetScene();
	m_activeScene = m_scenes[6];
	
	LevelSelect4* scene = (LevelSelect4*)m_activeScene;
	
	if (level1Cleared)
	{
		auto level2 = scene->GetSelect2();
		ECS::GetComponent<Sprite>(level2).SetTransparency(1.0f);
		auto medal1 = scene->GetMedal2();
		ECS::GetComponent<Sprite>(medal1).SetTransparency(1.0f);
		auto lock = scene->GetLock1();
		ECS::GetComponent<Sprite>(lock).SetTransparency(0.0f);
	}
	if (level2Cleared)
	{
		auto level3 = scene->GetSelect3();
		ECS::GetComponent<Sprite>(level3).SetTransparency(1.0f);
		auto medal = scene->GetMedal3();
		ECS::GetComponent<Sprite>(medal).SetTransparency(1.0f);
		auto lock = scene->GetLock2();
		ECS::GetComponent<Sprite>(lock).SetTransparency(0.0f);
	}
	if (level3Cleared)
	{
		auto level4 = scene->GetSelect4();
		auto medal = scene->GetMedal4();
		ECS::GetComponent<Sprite>(level4).SetTransparency(1.0f);
		ECS::GetComponent<Sprite>(medal).SetTransparency(1.0f);
		auto lock = scene->GetLock3();
		ECS::GetComponent<Sprite>(lock).SetTransparency(0.0f);
	}
	if (level4Cleared)
	{
		auto level5 = scene->GetSelect5();
		auto medal = scene->GetMedal();
		ECS::GetComponent<Sprite>(level5).SetTransparency(1.0f);
		ECS::GetComponent<Sprite>(medal).SetTransparency(1.0f);
		auto lock = scene->GetLock4();
		ECS::GetComponent<Sprite>(lock).SetTransparency(0.0f);
	}
	if (level5Cleared)
	{
		auto medal = scene->GetMedal5();
		ECS::GetComponent<Sprite>(medal).SetTransparency(1.0f);
	}
}
//Level Select 4 to Level Select 1
else if (Input::GetKeyDown(Key::UpArrow) && m_activeScene == m_scenes[6] && !loading)
{
sndPlaySound("MenuClick.wav", SND_FILENAME | SND_ASYNC);

SceneEditor::ResetEditor();

m_activeScene->Unload();

m_scenes[3]->InitScene(float(BackEnd::GetWindowWidth()), float(BackEnd::GetWindowHeight()));
m_register = m_scenes[3]->GetScene();
m_activeScene = m_scenes[3];

LevelSelectMain* scene = (LevelSelectMain*)m_activeScene;

if (level1Cleared)
{
	auto level2 = scene->GetSelect2();
	ECS::GetComponent<Sprite>(level2).SetTransparency(1.0f);
	auto medal1 = scene->GetMedal2();
	ECS::GetComponent<Sprite>(medal1).SetTransparency(1.0f);
	auto lock = scene->GetLock1();
	ECS::GetComponent<Sprite>(lock).SetTransparency(0.0f);
}
if (level2Cleared)
{
	auto level3 = scene->GetSelect3();
	ECS::GetComponent<Sprite>(level3).SetTransparency(1.0f);
	auto medal = scene->GetMedal3();
	ECS::GetComponent<Sprite>(medal).SetTransparency(1.0f);
	auto lock = scene->GetLock2();
	ECS::GetComponent<Sprite>(lock).SetTransparency(0.0f);
}
if (level3Cleared)
{
	auto level4 = scene->GetSelect4();
	auto medal = scene->GetMedal4();
	ECS::GetComponent<Sprite>(level4).SetTransparency(1.0f);
	ECS::GetComponent<Sprite>(medal).SetTransparency(1.0f);
	auto lock = scene->GetLock3();
	ECS::GetComponent<Sprite>(lock).SetTransparency(0.0f);
}
if (level4Cleared)
{
	auto level5 = scene->GetSelect5();
	auto medal = scene->GetMedal();
	ECS::GetComponent<Sprite>(level5).SetTransparency(1.0f);
	ECS::GetComponent<Sprite>(medal).SetTransparency(1.0f);
	auto lock = scene->GetLock4();
	ECS::GetComponent<Sprite>(lock).SetTransparency(0.0f);
}
if (level5Cleared)
{
	auto medal = scene->GetMedal5();
	ECS::GetComponent<Sprite>(medal).SetTransparency(1.0f);
}
}
//Level Select 3 to Level Select 5
else if (Input::GetKeyDown(Key::DownArrow) && m_activeScene == m_scenes[5] && !loading)
{
sndPlaySound("MenuClick.wav", SND_FILENAME | SND_ASYNC);

SceneEditor::ResetEditor();

m_activeScene->Unload();

m_scenes[7]->InitScene(float(BackEnd::GetWindowWidth()), float(BackEnd::GetWindowHeight()));
m_register = m_scenes[7]->GetScene();
m_activeScene = m_scenes[7];

LevelSelect5* scene = (LevelSelect5*)m_activeScene;

if (level1Cleared)
{
	auto level2 = scene->GetSelect2();
	ECS::GetComponent<Sprite>(level2).SetTransparency(1.0f);
	auto medal1 = scene->GetMedal2();
	ECS::GetComponent<Sprite>(medal1).SetTransparency(1.0f);
	auto lock = scene->GetLock1();
	ECS::GetComponent<Sprite>(lock).SetTransparency(0.0f);
}
if (level2Cleared)
{
	auto level3 = scene->GetSelect3();
	ECS::GetComponent<Sprite>(level3).SetTransparency(1.0f);
	auto medal = scene->GetMedal3();
	ECS::GetComponent<Sprite>(medal).SetTransparency(1.0f);
	auto lock = scene->GetLock2();
	ECS::GetComponent<Sprite>(lock).SetTransparency(0.0f);
}
if (level3Cleared)
{
	auto level4 = scene->GetSelect4();
	auto medal = scene->GetMedal4();
	ECS::GetComponent<Sprite>(level4).SetTransparency(1.0f);
	ECS::GetComponent<Sprite>(medal).SetTransparency(1.0f);
	auto lock = scene->GetLock3();
	ECS::GetComponent<Sprite>(lock).SetTransparency(0.0f);
}
if (level4Cleared)
{
	auto level5 = scene->GetSelect5();
	auto medal = scene->GetMedal();
	ECS::GetComponent<Sprite>(level5).SetTransparency(1.0f);
	ECS::GetComponent<Sprite>(medal).SetTransparency(1.0f);
	auto lock = scene->GetLock4();
	ECS::GetComponent<Sprite>(lock).SetTransparency(0.0f);
}
if (level5Cleared)
{
	auto medal = scene->GetMedal5();
	ECS::GetComponent<Sprite>(medal).SetTransparency(1.0f);
}
}
//Level Select 5 to Level Select 3
else if (Input::GetKeyDown(Key::UpArrow) && m_activeScene == m_scenes[7] && !loading)
{
sndPlaySound("MenuClick.wav", SND_FILENAME | SND_ASYNC);

SceneEditor::ResetEditor();

m_activeScene->Unload();

m_scenes[5]->InitScene(float(BackEnd::GetWindowWidth()), float(BackEnd::GetWindowHeight()));
m_register = m_scenes[5]->GetScene();
m_activeScene = m_scenes[5];

LevelSelect3* scene = (LevelSelect3*)m_activeScene;

if (level1Cleared)
{
	auto level2 = scene->GetSelect2();
	ECS::GetComponent<Sprite>(level2).SetTransparency(1.0f);
	auto medal1 = scene->GetMedal2();
	ECS::GetComponent<Sprite>(medal1).SetTransparency(1.0f);
	auto lock = scene->GetLock1();
	ECS::GetComponent<Sprite>(lock).SetTransparency(0.0f);
}
if (level2Cleared)
{
	auto level3 = scene->GetSelect3();
	ECS::GetComponent<Sprite>(level3).SetTransparency(1.0f);
	auto medal = scene->GetMedal3();
	ECS::GetComponent<Sprite>(medal).SetTransparency(1.0f);
	auto lock = scene->GetLock2();
	ECS::GetComponent<Sprite>(lock).SetTransparency(0.0f);
}
if (level3Cleared)
{
	auto level4 = scene->GetSelect4();
	auto medal = scene->GetMedal4();
	ECS::GetComponent<Sprite>(level4).SetTransparency(1.0f);
	ECS::GetComponent<Sprite>(medal).SetTransparency(1.0f);
	auto lock = scene->GetLock3();
	ECS::GetComponent<Sprite>(lock).SetTransparency(0.0f);
}
if (level4Cleared)
{
	auto level5 = scene->GetSelect5();
	auto medal = scene->GetMedal();
	ECS::GetComponent<Sprite>(level5).SetTransparency(1.0f);
	ECS::GetComponent<Sprite>(medal).SetTransparency(1.0f);
	auto lock = scene->GetLock4();
	ECS::GetComponent<Sprite>(lock).SetTransparency(0.0f);
}
if (level5Cleared)
{
	auto medal = scene->GetMedal5();
	ECS::GetComponent<Sprite>(medal).SetTransparency(1.0f);
}
}
#pragma endregion

#pragma region Play Game
//Level Select to Level 1
if (Input::GetKeyDown(Key::Space) && m_activeScene == m_scenes[3])
{
	sndPlaySound("MenuSelect.wav", SND_FILENAME | SND_ASYNC);

	LevelSelectMain* scene = (LevelSelectMain*)m_activeScene;

	scene->SetFade(true);

	change2 = true;
	loading = true;
	tutorialCheckB1 = false;
	tutorialCheckB2 = false;
	tutorialCheckW1 = false;
	tutorialCheckW2 = false;

	ECS::DestroyEntity(scene->GetSelect1());
	ECS::DestroyEntity(scene->GetSelect2());
	ECS::DestroyEntity(scene->GetSelect3());
	ECS::DestroyEntity(scene->GetSelect4());
	ECS::DestroyEntity(scene->GetSelect5());
	ECS::DestroyEntity(scene->GetLabel1());
	ECS::DestroyEntity(scene->GetLabel2());
	ECS::DestroyEntity(scene->GetLabel3());
	ECS::DestroyEntity(scene->GetLabel4());
	ECS::DestroyEntity(scene->GetLabel5());
	ECS::DestroyEntity(scene->GetText());
	ECS::DestroyEntity(scene->GetBorder());
	ECS::DestroyEntity(scene->GetPlay());
	ECS::DestroyEntity(scene->GetMedal());
	ECS::DestroyEntity(scene->GetMedal2());
	ECS::DestroyEntity(scene->GetMedal3());
	ECS::DestroyEntity(scene->GetMedal4());
	ECS::DestroyEntity(scene->GetMedal5());
	ECS::DestroyEntity(scene->GetLock1());
	ECS::DestroyEntity(scene->GetLock2());
	ECS::DestroyEntity(scene->GetLock3());
	ECS::DestroyEntity(scene->GetLock4());
}
//Level Select 2 to Level 2
if (Input::GetKeyDown(Key::Space) && m_activeScene == m_scenes[4] && level1Cleared)
{
	sndPlaySound("MenuSelect.wav", SND_FILENAME | SND_ASYNC);

	LevelSelect2* scene = (LevelSelect2*)m_activeScene;

	scene->SetFade(true);

	change3 = true;
	loading = true;

	//ECS::DestroyEntity(scene->GetMenu());
	ECS::DestroyEntity(scene->GetSelect1());
	ECS::DestroyEntity(scene->GetSelect2());
	ECS::DestroyEntity(scene->GetSelect3());
	ECS::DestroyEntity(scene->GetSelect4());
	ECS::DestroyEntity(scene->GetSelect5());
	ECS::DestroyEntity(scene->GetLabel1());
	ECS::DestroyEntity(scene->GetLabel2());
	ECS::DestroyEntity(scene->GetLabel3());
	ECS::DestroyEntity(scene->GetLabel4());
	ECS::DestroyEntity(scene->GetLabel5());
	ECS::DestroyEntity(scene->GetText());
	ECS::DestroyEntity(scene->GetBorder());
	ECS::DestroyEntity(scene->GetPlay());
	ECS::DestroyEntity(scene->GetMedal());
	ECS::DestroyEntity(scene->GetMedal2());
	ECS::DestroyEntity(scene->GetMedal3());
	ECS::DestroyEntity(scene->GetMedal4());
	ECS::DestroyEntity(scene->GetMedal5());
	ECS::DestroyEntity(scene->GetLock1());
	ECS::DestroyEntity(scene->GetLock2());
	ECS::DestroyEntity(scene->GetLock3());
	ECS::DestroyEntity(scene->GetLock4());
}
if (Input::GetKeyDown(Key::Space) && m_activeScene == m_scenes[4] && !level1Cleared)
{
	sndPlaySound("Warning.wav", SND_FILENAME | SND_ASYNC);
}
//Level Select 3 to Level 3
if (Input::GetKeyDown(Key::Space) && m_activeScene == m_scenes[5] && level2Cleared)
{
	sndPlaySound("MenuSelect.wav", SND_FILENAME | SND_ASYNC);

	LevelSelect3* scene = (LevelSelect3*)m_activeScene;

	scene->SetFade(true);

	change4 = true;
	loading = true;

	//ECS::DestroyEntity(scene->GetMenu());
	ECS::DestroyEntity(scene->GetSelect1());
	ECS::DestroyEntity(scene->GetSelect2());
	ECS::DestroyEntity(scene->GetSelect3());
	ECS::DestroyEntity(scene->GetSelect4());
	ECS::DestroyEntity(scene->GetSelect5());
	ECS::DestroyEntity(scene->GetLabel1());
	ECS::DestroyEntity(scene->GetLabel2());
	ECS::DestroyEntity(scene->GetLabel3());
	ECS::DestroyEntity(scene->GetLabel4());
	ECS::DestroyEntity(scene->GetLabel5());
	ECS::DestroyEntity(scene->GetText());
	ECS::DestroyEntity(scene->GetBorder());
	ECS::DestroyEntity(scene->GetPlay());
	ECS::DestroyEntity(scene->GetMedal());
	ECS::DestroyEntity(scene->GetMedal2());
	ECS::DestroyEntity(scene->GetMedal3());
	ECS::DestroyEntity(scene->GetMedal4());
	ECS::DestroyEntity(scene->GetMedal5());
	ECS::DestroyEntity(scene->GetLock1());
	ECS::DestroyEntity(scene->GetLock2());
	ECS::DestroyEntity(scene->GetLock3());
	ECS::DestroyEntity(scene->GetLock4());
}
if (Input::GetKeyDown(Key::Space) && m_activeScene == m_scenes[5] && !level2Cleared)
{
	sndPlaySound("Warning.wav", SND_FILENAME | SND_ASYNC);
}
//Level Select 4 to Level 4
if (Input::GetKeyDown(Key::Space) && m_activeScene == m_scenes[6] && level3Cleared)
{
	sndPlaySound("MenuSelect.wav", SND_FILENAME | SND_ASYNC);

	LevelSelect4* scene = (LevelSelect4*)m_activeScene;

	scene->SetFade(true);

	change5 = true;
	loading = true;

	//ECS::DestroyEntity(scene->GetMenu());
	ECS::DestroyEntity(scene->GetSelect1());
	ECS::DestroyEntity(scene->GetSelect2());
	ECS::DestroyEntity(scene->GetSelect3());
	ECS::DestroyEntity(scene->GetSelect4());
	ECS::DestroyEntity(scene->GetSelect5());
	ECS::DestroyEntity(scene->GetLabel1());
	ECS::DestroyEntity(scene->GetLabel2());
	ECS::DestroyEntity(scene->GetLabel3());
	ECS::DestroyEntity(scene->GetLabel4());
	ECS::DestroyEntity(scene->GetLabel5());
	ECS::DestroyEntity(scene->GetText());
	ECS::DestroyEntity(scene->GetBorder());
	ECS::DestroyEntity(scene->GetPlay());
	ECS::DestroyEntity(scene->GetMedal());
	ECS::DestroyEntity(scene->GetMedal2());
	ECS::DestroyEntity(scene->GetMedal3());
	ECS::DestroyEntity(scene->GetMedal4());
	ECS::DestroyEntity(scene->GetMedal5());
	ECS::DestroyEntity(scene->GetLock1());
	ECS::DestroyEntity(scene->GetLock2());
	ECS::DestroyEntity(scene->GetLock3());
	ECS::DestroyEntity(scene->GetLock4());
}
if (Input::GetKeyDown(Key::Space) && m_activeScene == m_scenes[6] && !level3Cleared)
{
	sndPlaySound("Warning.wav", SND_FILENAME | SND_ASYNC);
}
//Level Select 5 to Level 5
if (Input::GetKeyDown(Key::Space) && m_activeScene == m_scenes[7] && level4Cleared)
{
	sndPlaySound("MenuSelect.wav", SND_FILENAME | SND_ASYNC);

	LevelSelect5* scene = (LevelSelect5*)m_activeScene;

	scene->SetFade(true);

	change6 = true;
	loading = true;

	//ECS::DestroyEntity(scene->GetMenu());
	ECS::DestroyEntity(scene->GetSelect1());
	ECS::DestroyEntity(scene->GetSelect2());
	ECS::DestroyEntity(scene->GetSelect3());
	ECS::DestroyEntity(scene->GetSelect4());
	ECS::DestroyEntity(scene->GetSelect5());
	ECS::DestroyEntity(scene->GetLabel1());
	ECS::DestroyEntity(scene->GetLabel2());
	ECS::DestroyEntity(scene->GetLabel3());
	ECS::DestroyEntity(scene->GetLabel4());
	ECS::DestroyEntity(scene->GetLabel5());
	ECS::DestroyEntity(scene->GetText());
	ECS::DestroyEntity(scene->GetBorder());
	ECS::DestroyEntity(scene->GetPlay());
	ECS::DestroyEntity(scene->GetMedal());
	ECS::DestroyEntity(scene->GetMedal2());
	ECS::DestroyEntity(scene->GetMedal3());
	ECS::DestroyEntity(scene->GetMedal4());
	ECS::DestroyEntity(scene->GetMedal5());
	ECS::DestroyEntity(scene->GetLock1());
	ECS::DestroyEntity(scene->GetLock2());
	ECS::DestroyEntity(scene->GetLock3());
	ECS::DestroyEntity(scene->GetLock4());
}
if (Input::GetKeyDown(Key::Space) && m_activeScene == m_scenes[7] && !level4Cleared)
{
	sndPlaySound("Warning.wav", SND_FILENAME | SND_ASYNC);
}
#pragma endregion

#pragma region Backspace for Scenes
//////////////////////////////////////////////////////////
					//BACKSPACE//
/////////////////////////////////////////////////////////

//Level Select to Main Menu
if (Input::GetKeyDown(Key::Backspace) && m_activeScene == m_scenes[3])
{
	sndPlaySound("MenuDeselect.wav", SND_FILENAME | SND_ASYNC);

	SceneEditor::ResetEditor();

	m_activeScene->Unload();

	m_scenes[1]->InitScene(float(BackEnd::GetWindowWidth()), float(BackEnd::GetWindowHeight()));
	m_register = m_scenes[1]->GetScene();
	m_activeScene = m_scenes[1];

	spikeDestroyed = false;
}
//Level Select 2 to Main Menu
if (Input::GetKeyDown(Key::Backspace) && m_activeScene == m_scenes[4])
{
	sndPlaySound("MenuDeselect.wav", SND_FILENAME | SND_ASYNC);

	SceneEditor::ResetEditor();

	m_activeScene->Unload();

	m_scenes[1]->InitScene(float(BackEnd::GetWindowWidth()), float(BackEnd::GetWindowHeight()));
	m_register = m_scenes[1]->GetScene();
	m_activeScene = m_scenes[1];

	spikeDestroyed = false;
}
//Level Select 3 to Main Menu
if (Input::GetKeyDown(Key::Backspace) && m_activeScene == m_scenes[5])
{
	sndPlaySound("MenuDeselect.wav", SND_FILENAME | SND_ASYNC);

	SceneEditor::ResetEditor();

	m_activeScene->Unload();

	m_scenes[1]->InitScene(float(BackEnd::GetWindowWidth()), float(BackEnd::GetWindowHeight()));
	m_register = m_scenes[1]->GetScene();
	m_activeScene = m_scenes[1];

	spikeDestroyed = false;
}
//Level Select 4 to Main Menu
if (Input::GetKeyDown(Key::Backspace) && m_activeScene == m_scenes[6])
{
	sndPlaySound("MenuDeselect.wav", SND_FILENAME | SND_ASYNC);

	SceneEditor::ResetEditor();

	m_activeScene->Unload();

	m_scenes[1]->InitScene(float(BackEnd::GetWindowWidth()), float(BackEnd::GetWindowHeight()));
	m_register = m_scenes[1]->GetScene();
	m_activeScene = m_scenes[1];

	spikeDestroyed = false;
}
//Level Select 5 to Main Menu
if (Input::GetKeyDown(Key::Backspace) && m_activeScene == m_scenes[7])
{
	sndPlaySound("MenuDeselect.wav", SND_FILENAME | SND_ASYNC);

	SceneEditor::ResetEditor();

	m_activeScene->Unload();

	m_scenes[1]->InitScene(float(BackEnd::GetWindowWidth()), float(BackEnd::GetWindowHeight()));
	m_register = m_scenes[1]->GetScene();
	m_activeScene = m_scenes[1];

	spikeDestroyed = false;
}
//Level 1 to Level Select
if (Input::GetKeyDown(Key::Backspace) && m_activeScene == m_scenes[8] && !(listener.GetWin()))
{
	sndPlaySound("MenuDeselect.wav", SND_FILENAME | SND_ASYNC);

	SceneEditor::ResetEditor();

	m_activeScene->Unload();

	m_scenes[3]->InitScene(float(BackEnd::GetWindowWidth()), float(BackEnd::GetWindowHeight()));
	m_register = m_scenes[3]->GetScene();
	m_activeScene = m_scenes[3];

	listener.SetBlue1Pressed(false);
	listener.SetWin(false);

	LevelSelectMain* scene = (LevelSelectMain*)m_activeScene;

	if (level1Cleared)
	{
		auto level2 = scene->GetSelect2();
		auto medal = scene->GetMedal();
		ECS::GetComponent<Sprite>(level2).SetTransparency(1.0f);
		ECS::GetComponent<Sprite>(medal).SetTransparency(1.0f);
		auto lock = scene->GetLock1();
		ECS::GetComponent<Sprite>(lock).SetTransparency(0.0f);
	}
	if (level2Cleared)
	{
		auto level3 = scene->GetSelect3();
		ECS::GetComponent<Sprite>(level3).SetTransparency(1.0f);
		auto medal = scene->GetMedal2();
		ECS::GetComponent<Sprite>(medal).SetTransparency(1.0f);
		auto lock = scene->GetLock2();
		ECS::GetComponent<Sprite>(lock).SetTransparency(0.0f);
	}
	if (level3Cleared)
	{
		auto level4 = scene->GetSelect4();
		ECS::GetComponent<Sprite>(level4).SetTransparency(1.0f);
		auto medal3 = scene->GetMedal3();
		ECS::GetComponent<Sprite>(medal3).SetTransparency(1.0f);
		auto lock = scene->GetLock3();
		ECS::GetComponent<Sprite>(lock).SetTransparency(0.0f);
	}
	if (level4Cleared)
	{
		auto level5 = scene->GetSelect5();
		ECS::GetComponent<Sprite>(level5).SetTransparency(1.0f);
		auto medal4 = scene->GetMedal4();
		ECS::GetComponent<Sprite>(medal4).SetTransparency(1.0f);
		auto lock = scene->GetLock4();
		ECS::GetComponent<Sprite>(lock).SetTransparency(0.0f);
	}
	if (level5Cleared)
	{
		auto medal5 = scene->GetMedal5();
		ECS::GetComponent<Sprite>(medal5).SetTransparency(1.0f);
	}
}
//Level 2 to Level Select
if (Input::GetKeyDown(Key::Backspace) && m_activeScene == m_scenes[11] && !(listener.GetWin()))
{
	sndPlaySound("MenuDeselect.wav", SND_FILENAME | SND_ASYNC);

	SceneEditor::ResetEditor();

	m_activeScene->Unload();

	m_scenes[4]->InitScene(float(BackEnd::GetWindowWidth()), float(BackEnd::GetWindowHeight()));
	m_register = m_scenes[4]->GetScene();
	m_activeScene = m_scenes[4];

	listener.SetBlue1Pressed(false);
	listener.SetBlue2Pressed(false);
	listener.SetRed1Pressed(false);
	listener.SetWin(false);

	LevelSelect2* scene = (LevelSelect2*)m_activeScene;

	if (level1Cleared)
	{
		auto level2 = scene->GetSelect2();
		ECS::GetComponent<Sprite>(level2).SetTransparency(1.0f);
		auto medal1 = scene->GetMedal2();
		ECS::GetComponent<Sprite>(medal1).SetTransparency(1.0f);
		auto lock = scene->GetLock1();
		ECS::GetComponent<Sprite>(lock).SetTransparency(0.0f);
	}	
	if (level2Cleared)
	{
		auto level2 = scene->GetSelect2();
		auto level3 = scene->GetSelect3();
		auto medal = scene->GetMedal();
		ECS::GetComponent<Sprite>(level2).SetTransparency(1.0f);
		ECS::GetComponent<Sprite>(level3).SetTransparency(1.0f);
		ECS::GetComponent<Sprite>(medal).SetTransparency(1.0f);
		auto lock = scene->GetLock2();
		ECS::GetComponent<Sprite>(lock).SetTransparency(0.0f);
	}
	if (level3Cleared)
	{
		auto level4 = scene->GetSelect4();
		ECS::GetComponent<Sprite>(level4).SetTransparency(1.0f);
		auto medal = scene->GetMedal3();
		ECS::GetComponent<Sprite>(medal).SetTransparency(1.0f);
		auto lock = scene->GetLock3();
		ECS::GetComponent<Sprite>(lock).SetTransparency(0.0f);
	}
	if (level4Cleared)
	{
		auto level5 = scene->GetSelect5();
		ECS::GetComponent<Sprite>(level5).SetTransparency(1.0f);
		auto medal = scene->GetMedal4();
		ECS::GetComponent<Sprite>(medal).SetTransparency(1.0f);
		auto lock = scene->GetLock4();
		ECS::GetComponent<Sprite>(lock).SetTransparency(0.0f);
	}
	if (level5Cleared)
	{
		auto medal = scene->GetMedal5();
		ECS::GetComponent<Sprite>(medal).SetTransparency(1.0f);
	}
}
//Level 3 to Level Select
if (Input::GetKeyDown(Key::Backspace) && m_activeScene == m_scenes[9] && !(listener.GetWin()))
{
	sndPlaySound("MenuDeselect.wav", SND_FILENAME | SND_ASYNC);

	SceneEditor::ResetEditor();

	m_activeScene->Unload();

	m_scenes[5]->InitScene(float(BackEnd::GetWindowWidth()), float(BackEnd::GetWindowHeight()));
	m_register = m_scenes[5]->GetScene();
	m_activeScene = m_scenes[5];

	listener.SetBlue1Pressed(false);
	listener.SetRed1Pressed(false);
	listener.SetWin(false);

	LevelSelect3* scene = (LevelSelect3*)m_activeScene;

	if (level1Cleared)
	{
		auto level1 = scene->GetSelect1();
		ECS::GetComponent<Sprite>(level1).SetTransparency(1.0f);
		auto level2 = scene->GetSelect2();
		ECS::GetComponent<Sprite>(level2).SetTransparency(1.0f);
		auto medal1 = scene->GetMedal2();
		ECS::GetComponent<Sprite>(medal1).SetTransparency(1.0f);
		auto medal2 = scene->GetMedal3();
		ECS::GetComponent<Sprite>(medal2).SetTransparency(1.0f);
		auto lock = scene->GetLock1();
		ECS::GetComponent<Sprite>(lock).SetTransparency(0.0f);
	}
	if (level2Cleared)
	{
		auto level3 = scene->GetSelect3();
		ECS::GetComponent<Sprite>(level3).SetTransparency(1.0f);
		auto lock = scene->GetLock2();
		ECS::GetComponent<Sprite>(lock).SetTransparency(0.0f);
	}
	if (level3Cleared)
	{
		auto medal = scene->GetMedal();
		ECS::GetComponent<Sprite>(medal).SetTransparency(1.0f);
		auto level4 = scene->GetSelect4();
		ECS::GetComponent<Sprite>(level4).SetTransparency(1.0f);
		auto lock = scene->GetLock3();
		ECS::GetComponent<Sprite>(lock).SetTransparency(0.0f);
	}
	if (level4Cleared)
	{
		auto medal = scene->GetMedal4();
		ECS::GetComponent<Sprite>(medal).SetTransparency(1.0f);
		auto level5 = scene->GetSelect5();
		ECS::GetComponent<Sprite>(level5).SetTransparency(1.0f);
		auto lock = scene->GetLock4();
		ECS::GetComponent<Sprite>(lock).SetTransparency(0.0f);
	}
	if (level5Cleared)
	{
		auto medal = scene->GetMedal5();
		ECS::GetComponent<Sprite>(medal).SetTransparency(1.0f);
	}
}
//Level 4 to Level Select
if (Input::GetKeyDown(Key::Backspace) && m_activeScene == m_scenes[12] && !(listener.GetWin()))
{
	sndPlaySound("MenuDeselect.wav", SND_FILENAME | SND_ASYNC);

	SceneEditor::ResetEditor();

	m_activeScene->Unload();

	m_scenes[6]->InitScene(float(BackEnd::GetWindowWidth()), float(BackEnd::GetWindowHeight()));
	m_register = m_scenes[6]->GetScene();
	m_activeScene = m_scenes[6];

	listener.SetBlue1Pressed(false);
	listener.SetBlue2Pressed(false);
	listener.SetRed1Pressed(false);
	listener.SetWin(false);

	LevelSelect4* scene = (LevelSelect4*)m_activeScene;

	if (level1Cleared)
	{
		auto medal1 = scene->GetMedal2();
		ECS::GetComponent<Sprite>(medal1).SetTransparency(1.0f);
		auto lock = scene->GetLock1();
		ECS::GetComponent<Sprite>(lock).SetTransparency(0.0f);
	}
	if (level2Cleared)
	{
		auto medal1 = scene->GetMedal3();
		ECS::GetComponent<Sprite>(medal1).SetTransparency(1.0f);
		auto level2 = scene->GetSelect2();
		ECS::GetComponent<Sprite>(level2).SetTransparency(1.0f);
		auto lock = scene->GetLock2();
		ECS::GetComponent<Sprite>(lock).SetTransparency(0.0f);
	}
	if (level3Cleared)
	{
		auto medal1 = scene->GetMedal4();
		ECS::GetComponent<Sprite>(medal1).SetTransparency(1.0f);
		auto level3 = scene->GetSelect3();
		ECS::GetComponent<Sprite>(level3).SetTransparency(1.0f);
		auto level4 = scene->GetSelect4();
		ECS::GetComponent<Sprite>(level4).SetTransparency(1.0f);
		auto lock = scene->GetLock3();
		ECS::GetComponent<Sprite>(lock).SetTransparency(0.0f);
	}
	if (level4Cleared)
	{
		auto medal = scene->GetMedal();
		ECS::GetComponent<Sprite>(medal).SetTransparency(1.0f);
		auto level5 = scene->GetSelect5();
		ECS::GetComponent<Sprite>(level5).SetTransparency(1.0f);
		auto lock = scene->GetLock4();
		ECS::GetComponent<Sprite>(lock).SetTransparency(0.0f);
	}
	if (level5Cleared)
	{
		auto medal = scene->GetMedal5();
		ECS::GetComponent<Sprite>(medal).SetTransparency(1.0f);
	}
}
//Level 5 to Level Select
if (Input::GetKeyDown(Key::Backspace) && m_activeScene == m_scenes[10] && !(listener.GetWin()))
{
	sndPlaySound("MenuDeselect.wav", SND_FILENAME | SND_ASYNC);

	SceneEditor::ResetEditor();

	m_activeScene->Unload();

	m_scenes[7]->InitScene(float(BackEnd::GetWindowWidth()), float(BackEnd::GetWindowHeight()));
	m_register = m_scenes[7]->GetScene();
	m_activeScene = m_scenes[7];

	listener.SetBlue1Pressed(false);
	listener.SetBlue2Pressed(false);
	listener.SetWin(false);

	LevelSelect5* scene = (LevelSelect5*)m_activeScene;

	if (level1Cleared)
	{
		auto medal1 = scene->GetMedal2();
		ECS::GetComponent<Sprite>(medal1).SetTransparency(1.0f);
		auto lock = scene->GetLock1();
		ECS::GetComponent<Sprite>(lock).SetTransparency(0.0f);
	}
	if (level2Cleared)
	{
		auto medal1 = scene->GetMedal3();
		ECS::GetComponent<Sprite>(medal1).SetTransparency(1.0f);
		auto level2 = scene->GetSelect2();
		ECS::GetComponent<Sprite>(level2).SetTransparency(1.0f);
		auto lock = scene->GetLock2();
		ECS::GetComponent<Sprite>(lock).SetTransparency(0.0f);
	}
	if (level3Cleared)
	{
		auto medal1 = scene->GetMedal4();
		ECS::GetComponent<Sprite>(medal1).SetTransparency(1.0f);
		auto level3 = scene->GetSelect3();
		ECS::GetComponent<Sprite>(level3).SetTransparency(1.0f);
		auto lock = scene->GetLock3();
		ECS::GetComponent<Sprite>(lock).SetTransparency(0.0f);
	}
	if (level4Cleared)
	{
		auto medal1 = scene->GetMedal5();
		ECS::GetComponent<Sprite>(medal1).SetTransparency(1.0f);
		auto level4 = scene->GetSelect4();
		ECS::GetComponent<Sprite>(level4).SetTransparency(1.0f);
		auto level5 = scene->GetSelect5();
		ECS::GetComponent<Sprite>(level5).SetTransparency(1.0f);
		auto lock = scene->GetLock4();
		ECS::GetComponent<Sprite>(lock).SetTransparency(0.0f);
	}
	if (level5Cleared)
	{
		auto medal = scene->GetMedal();
		ECS::GetComponent<Sprite>(medal).SetTransparency(1.0f);
		auto level5 = scene->GetSelect5();
		ECS::GetComponent<Sprite>(level5).SetTransparency(1.0f);
	}
}
#pragma endregion

#pragma region JUMPING CODE
//Jumping
if (m_activeScene == m_scenes[8] || m_activeScene == m_scenes[9] || m_activeScene == m_scenes[10] || m_activeScene == m_scenes[11] 
	|| m_activeScene == m_scenes[12])
{
	auto blueBody = ECS::GetComponent<PhysicsBody>(EntityIdentifier::MainPlayer()).GetBody();
	auto waterBody = ECS::GetComponent<PhysicsBody>(EntityIdentifier::MainPlayer2()).GetBody();
	const float blueJumpForce = 30.f;
	const float waterJumpForce = 22.f;

	if (!(listener.GetWin()))
	{
		if (listener.GetBJump() || listener.GetBGrounded())
		{
			if (Input::GetKeyDown(Key::W))
			{
				tutorialCheckB2 = true;
				float impulse = blueBody->GetMass() * blueJumpForce;
				blueBody->ApplyLinearImpulse(b2Vec2(0, impulse), blueBody->GetWorldCenter(), true);
				listener.SetBGrounded(false);
				listener.SetBJump(false);
			}
		}

		if (listener.GetWJump() || listener.GetWGrounded())
		{
			if (Input::GetKeyDown(Key::UpArrow))
			{
				tutorialCheckW2 = true;
				float impulse = waterBody->GetMass() * waterJumpForce;
				waterBody->ApplyLinearImpulse(b2Vec2(0, impulse), waterBody->GetWorldCenter(), true);
				listener.SetWGrounded(false);
				listener.SetWJump(false);
			}
		}	
	}
}
#pragma endregion

}

void Game::KeyboardUp()
{
	//Active scene now captures this input and can use it
	//Look at base Scene class for more info.
	m_activeScene->KeyboardUp();

	if (Input::GetKeyUp(Key::F1))
	{
		if (!UI::m_isInit)
		{
			UI::InitImGUI();
		}
		m_guiActive = !m_guiActive;
	}
	
	if (Input::GetKeyUp(Key::P))
	{
		PhysicsBody::SetDraw(!PhysicsBody::GetDraw());
	}

#pragma region Sets Idle Animations
	for (int i = 8; i < 13; ++i)
	{
		if (m_activeScene == m_scenes[i])
		{
			auto& blueAnim = ECS::GetComponent<AnimationController>(EntityIdentifier::MainPlayer());
			auto& waterAnim = ECS::GetComponent<AnimationController>(EntityIdentifier::MainPlayer2());

			if (Input::GetKeyUp(Key::A) && dir == LEFT)
			{
				blueAnim.SetActiveAnim(2);
				blueAnim.GetAnimation(2).Reset();
			}
			if (Input::GetKeyUp(Key::D) && dir == RIGHT)
			{
				blueAnim.SetActiveAnim(3);
				blueAnim.GetAnimation(3).Reset();
			}	

			if (Input::GetKeyUp(Key::LeftArrow) && dir2 == LEFT2)
			{
				waterAnim.SetActiveAnim(1);
				waterAnim.GetAnimation(1).Reset();
			}
			if (Input::GetKeyUp(Key::RightArrow) && dir2 == RIGHT2)
			{
				waterAnim.SetActiveAnim(0);
				waterAnim.GetAnimation(0).Reset();
			}
		}
	}
#pragma endregion

}

void Game::MouseMotion(SDL_MouseMotionEvent evnt)
{
	//Active scene now captures this input and can use it
	//Look at base Scene class for more info.
	m_activeScene->MouseMotion(evnt);

	if (m_guiActive)
	{
		ImGui::GetIO().MousePos = ImVec2(float(evnt.x), float(evnt.y));

		if (!ImGui::GetIO().WantCaptureMouse)
		{

		}
	}

	//Resets the enabled flag
	m_motion = false;
}

void Game::MouseClick(SDL_MouseButtonEvent evnt)
{
	//Active scene now captures this input and can use it
	//Look at base Scene class for more info.
	m_activeScene->MouseClick(evnt);

	if (m_guiActive)
	{
		ImGui::GetIO().MousePos = ImVec2(float(evnt.x), float(evnt.y));
		ImGui::GetIO().MouseDown[0] = (SDL_GetMouseState(NULL, NULL) & SDL_BUTTON(SDL_BUTTON_LEFT));
		ImGui::GetIO().MouseDown[1] = (SDL_GetMouseState(NULL, NULL) & SDL_BUTTON(SDL_BUTTON_RIGHT));
		ImGui::GetIO().MouseDown[2] = (SDL_GetMouseState(NULL, NULL) & SDL_BUTTON(SDL_BUTTON_MIDDLE));
	}

	//Resets the enabled flag
	m_click = false;
}

void Game::MouseWheel(SDL_MouseWheelEvent evnt)
{
	//Active scene now captures this input and can use it
	//Look at base Scene class for more info.
	m_activeScene->MouseWheel(evnt);

	if (m_guiActive)
	{
		ImGui::GetIO().MouseWheel = float(evnt.y);
	}
	//Resets the enabled flag
	m_wheel = false;
}

Scene* Game::GetActiveScene()
{
	return m_activeScene;
}