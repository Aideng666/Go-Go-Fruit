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
	std::string level1 = "Level 1";
	std::string level2 = "Level 2";
	std::string level3   = "Level 3";

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
	m_scenes.push_back(new GoGoGame(level1));
	m_scenes.push_back(new LevelTwo(level2));
	m_scenes.push_back(new LevelThree(level3));

	//Sets active scene reference to our scene
	m_scenes[3]->InitScene(float(BackEnd::GetWindowWidth()), float(BackEnd::GetWindowHeight()));
	m_register = m_scenes[3]->GetScene();
	m_activeScene = m_scenes[3];
	PhysicsSystem::Init();
	
	for (int i = 6; i < m_scenes.size(); ++i)
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

		if (level1Cleared)
		{
			LevelSelectMain* scene = (LevelSelectMain*)m_activeScene;
			auto level2 = scene->GetLevel2Template();
			ECS::GetComponent<Sprite>(level2).SetTransparency(1.0f);
		}
		if (level2Cleared)
		{
			LevelSelectMain* scene = (LevelSelectMain*)m_activeScene;
			auto level3 = scene->GetLevel3Template();
			ECS::GetComponent<Sprite>(level3).SetTransparency(1.0f);
		}
	}
}
if (change2)
{
	timer += Timer::deltaTime;

	if (timer >= 1.f)
	{
		SceneEditor::ResetEditor();

		m_activeScene->Unload();

		m_scenes[6]->InitScene(float(BackEnd::GetWindowWidth()), float(BackEnd::GetWindowHeight()));
		m_register = m_scenes[6]->GetScene();
		m_activeScene = m_scenes[6];
		timer = 0.f;
		change2 = false;

		m_activeScene->GetPhysicsWorld().SetContactListener(&listener);
	}
}
if (change3)
{
	timer += Timer::deltaTime;

	if (timer >= 1.f)
	{
		SceneEditor::ResetEditor();

		m_activeScene->Unload();

		m_scenes[7]->InitScene(float(BackEnd::GetWindowWidth()), float(BackEnd::GetWindowHeight()));
		m_register = m_scenes[7]->GetScene();
		m_activeScene = m_scenes[7];
		timer = 0.f;
		change3 = false;

		m_activeScene->GetPhysicsWorld().SetContactListener(&listener);
	}
}
if (change4)
{
	timer += Timer::deltaTime;

	if (timer >= 1.f)
	{
		SceneEditor::ResetEditor();

		m_activeScene->Unload();

		m_scenes[8]->InitScene(float(BackEnd::GetWindowWidth()), float(BackEnd::GetWindowHeight()));
		m_register = m_scenes[8]->GetScene();
		m_activeScene = m_scenes[8];
		timer = 0.f;
		change4 = false;

		m_activeScene->GetPhysicsWorld().SetContactListener(&listener);
	}
}
#pragma endregion

#pragma region Shake Effect
	if (m_activeScene == m_scenes[6])
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

	if (m_activeScene == m_scenes[7])
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

	if (m_activeScene == m_scenes[8])
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
	if (m_activeScene == m_scenes[6])
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
	if (m_activeScene == m_scenes[7])
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
	if (m_activeScene == m_scenes[8])
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
#pragma endregion
	
#pragma region Activation of Buttons
	if (m_activeScene == m_scenes[6])
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

	if (m_activeScene == m_scenes[7])
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

	if (m_activeScene == m_scenes[8])
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
#pragma endregion

#pragma region Jello Bounce
	if (m_activeScene == m_scenes[7])
	{
		LevelTwo* scene = (LevelTwo*)m_activeScene;
		auto jello = scene->GetJello();
		auto turnOn = scene->GetJelloBounce();

		if (listener.GetBounced())
		{				
			turnOn = true;

			if (turnOn)
			{
				auto& animController = ECS::GetComponent<AnimationController>(jello);
				animController.SetActiveAnim(0);
				animController.GetAnimation(0).Reset();
			}		
		}

		if (!(listener.GetBounced()))
		{
			turnOn = false;			
		}		
	}
	if (m_activeScene == m_scenes[8])
	{
		LevelThree* scene = (LevelThree*)m_activeScene;
		auto jello = scene->GetJello();
		auto turnOn = scene->GetJelloBounce();

		if (listener.GetBounced())
		{
			turnOn = true;

			if (turnOn)
			{
				auto& animController = ECS::GetComponent<AnimationController>(jello);
				animController.SetActiveAnim(0);
				animController.GetAnimation(0).Reset();
			}
		}

		if (!(listener.GetBounced()))
		{
			turnOn = false;
		}
	}
#pragma endregion

#pragma region Level Check

	if (listener.GetLevelCheck())
	{		
		levelTimer += Timer::deltaTime;

		if (m_activeScene == m_scenes[6])
		{			
			listener.SetLevelCleared(true, 0);
			level1Cleared = true;			
		}
		if (m_activeScene == m_scenes[7])
		{		
			listener.SetLevelCleared(true, 1);
			level2Cleared = true;			
		}
		if (m_activeScene == m_scenes[8])
		{	
			listener.SetLevelCleared(true, 2);
			level3Cleared = true;			
		}

		for (int i = 0; i < 3; i++)
		{
			if (listener.GetLevelCleared(i))
			{
				if (levelTimer >= 3.f)
				{
					SceneEditor::ResetEditor();

					m_activeScene->Unload();

					m_scenes[3 + i]->InitScene(float(BackEnd::GetWindowWidth()), float(BackEnd::GetWindowHeight()));
					m_register = m_scenes[3 + i]->GetScene();
					m_activeScene = m_scenes[3 + i];
					
					if (level1Cleared)
					{
						LevelSelectMain* scene = (LevelSelectMain*)m_activeScene;
						auto level2 = scene->GetLevel2Template();
						ECS::GetComponent<Sprite>(level2).SetTransparency(1.0f);
					}
					if (level2Cleared)
					{
						LevelSelect2* scene = (LevelSelect2*)m_activeScene;
						auto level3 = scene->GetLevel3Template();
						ECS::GetComponent<Sprite>(level3).SetTransparency(1.0f);
					}

					levelTimer = 0.f;
					listener.SetLevelCheck(false);
				}				
			}
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
	for (int i = 6; i < m_scenes.size(); ++i)
	{
		if (m_activeScene == m_scenes[i])
		{
			auto blueBody = ECS::GetComponent<PhysicsBody>(EntityIdentifier::MainPlayer()).GetBody();
			auto waterBody = ECS::GetComponent<PhysicsBody>(EntityIdentifier::MainPlayer2()).GetBody();
			b2Vec2 blueVel = blueBody->GetLinearVelocity();
			b2Vec2 waterVel = waterBody->GetLinearVelocity();
			float blueSpeed = 0.f, waterSpeed = 0.f;
	
			auto& waterAnim = ECS::GetComponent<AnimationController>(EntityIdentifier::MainPlayer2());


			if (Input::GetKey(Key::A))
			{
				blueSpeed = -12.f;
			}
			if (Input::GetKey(Key::D))
			{
				blueSpeed = 12.f;
			}
			if (Input::GetKey(Key::LeftArrow))
			{
				waterSpeed = -12.f;
				waterAnim.SetActiveAnim(0);
			}
			if (Input::GetKey(Key::RightArrow))
			{
				waterSpeed = 12.f;
				waterAnim.SetActiveAnim(1);
			}
	
			float blueChange = blueSpeed - blueVel.x;
			float waterChange = waterSpeed - waterVel.x;
			float blueForce = (blueBody->GetMass() * blueChange);
			float waterForce = (waterBody->GetMass() * waterChange);
	
			blueBody->ApplyForce(b2Vec2(blueForce, 0), blueBody->GetWorldCenter(), true);
			waterBody->ApplyForce(b2Vec2(waterForce, 0), waterBody->GetWorldCenter(), true);
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

	if (Input::GetKeyDown(Key::T))
	{
		std::cout << "Current Time: " << levelTimer << "\n";
	}

#pragma region SCREEN MANIPULATION
//Space on title screen goes to play screen
if (Input::GetKeyDown(Key::Space) && m_activeScene == m_scenes[0])
{
	sndPlaySound("MenuSelect.wav", SND_FILENAME | SND_ASYNC);

	SceneEditor::ResetEditor();

	m_activeScene->Unload();

	m_scenes[1]->InitScene(float(BackEnd::GetWindowWidth()), float(BackEnd::GetWindowHeight()));
	m_register = m_scenes[1]->GetScene();
	m_activeScene = m_scenes[1];
}
//Space on play goes to game
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
if (Input::GetKeyDown(Key::RightArrow) && m_activeScene == m_scenes[3])
{
	sndPlaySound("MenuClick.wav", SND_FILENAME | SND_ASYNC);

	SceneEditor::ResetEditor();

	m_activeScene->Unload();

	m_scenes[4]->InitScene(float(BackEnd::GetWindowWidth()), float(BackEnd::GetWindowHeight()));
	m_register = m_scenes[4]->GetScene();
	m_activeScene = m_scenes[4];

	if (level1Cleared)
	{
		LevelSelect2* scene = (LevelSelect2*)m_activeScene;
		auto level2 = scene->GetLevel2Template();
		ECS::GetComponent<Sprite>(level2).SetTransparency(1.0f);
	}

	if (level2Cleared)
	{
		LevelSelect2* scene = (LevelSelect2*)m_activeScene;
		auto level3 = scene->GetLevel3Template();
		ECS::GetComponent<Sprite>(level3).SetTransparency(1.0f);
	}
}
//Level Select 1 to Level Select 3
else if (Input::GetKeyDown(Key::LeftArrow) && m_activeScene == m_scenes[3])
{
	sndPlaySound("MenuClick.wav", SND_FILENAME | SND_ASYNC);

	SceneEditor::ResetEditor();

	m_activeScene->Unload();

	m_scenes[5]->InitScene(float(BackEnd::GetWindowWidth()), float(BackEnd::GetWindowHeight()));
	m_register = m_scenes[5]->GetScene();
	m_activeScene = m_scenes[5];

	if (level1Cleared)
	{
		LevelSelect3* scene = (LevelSelect3*)m_activeScene;
		auto level2 = scene->GetLevel2Template();
		ECS::GetComponent<Sprite>(level2).SetTransparency(1.0f);
	}

	if (level2Cleared)
	{
		LevelSelect3* scene = (LevelSelect3*)m_activeScene;
		auto level3 = scene->GetLevel3Template();
		ECS::GetComponent<Sprite>(level3).SetTransparency(1.0f);
	}
}
//Level Select 2 to Level Select 1
else if (Input::GetKeyDown(Key::LeftArrow) && m_activeScene == m_scenes[4])
{
	sndPlaySound("MenuClick.wav", SND_FILENAME | SND_ASYNC);

	SceneEditor::ResetEditor();

	m_activeScene->Unload();

	m_scenes[3]->InitScene(float(BackEnd::GetWindowWidth()), float(BackEnd::GetWindowHeight()));
	m_register = m_scenes[3]->GetScene();
	m_activeScene = m_scenes[3];

	if (level1Cleared)
	{
		LevelSelectMain* scene = (LevelSelectMain*)m_activeScene;
		auto level2 = scene->GetLevel2Template();
		ECS::GetComponent<Sprite>(level2).SetTransparency(1.0f);
	}

	if (level2Cleared)
	{
		LevelSelectMain* scene = (LevelSelectMain*)m_activeScene;
		auto level3 = scene->GetLevel3Template();
		ECS::GetComponent<Sprite>(level3).SetTransparency(1.0f);
	}
}
//Level Select 2 to Level Select 3
else if (Input::GetKeyDown(Key::RightArrow) && m_activeScene == m_scenes[4])
{
	sndPlaySound("MenuClick.wav", SND_FILENAME | SND_ASYNC);

	SceneEditor::ResetEditor();

	m_activeScene->Unload();

	m_scenes[5]->InitScene(float(BackEnd::GetWindowWidth()), float(BackEnd::GetWindowHeight()));
	m_register = m_scenes[5]->GetScene();
	m_activeScene = m_scenes[5];

	if (level1Cleared)
	{
		LevelSelect3* scene = (LevelSelect3*)m_activeScene;
		auto level2 = scene->GetLevel2Template();
		ECS::GetComponent<Sprite>(level2).SetTransparency(1.0f);
	}

	if (level2Cleared)
	{
		LevelSelect3* scene = (LevelSelect3*)m_activeScene;
		auto level3 = scene->GetLevel3Template();
		ECS::GetComponent<Sprite>(level3).SetTransparency(1.0f);
	}
}
//Level Select 3 to Level Select 1
else if (Input::GetKeyDown(Key::RightArrow) && m_activeScene == m_scenes[5])
{
	sndPlaySound("MenuClick.wav", SND_FILENAME | SND_ASYNC);

	SceneEditor::ResetEditor();

	m_activeScene->Unload();

	m_scenes[3]->InitScene(float(BackEnd::GetWindowWidth()), float(BackEnd::GetWindowHeight()));
	m_register = m_scenes[3]->GetScene();
	m_activeScene = m_scenes[3];

	if (level1Cleared)
	{
		LevelSelectMain* scene = (LevelSelectMain*)m_activeScene;
		auto level2 = scene->GetLevel2Template();
		ECS::GetComponent<Sprite>(level2).SetTransparency(1.0f);
	}

	if (level2Cleared)
	{
		LevelSelect3* scene = (LevelSelect3*)m_activeScene;
		auto level3 = scene->GetLevel3Template();
		ECS::GetComponent<Sprite>(level3).SetTransparency(1.0f);
	}
}
//Level Select 3 to Level Select 2
else if (Input::GetKeyDown(Key::LeftArrow) && m_activeScene == m_scenes[5])
{
	sndPlaySound("MenuClick.wav", SND_FILENAME | SND_ASYNC);

	SceneEditor::ResetEditor();

	m_activeScene->Unload();

	m_scenes[4]->InitScene(float(BackEnd::GetWindowWidth()), float(BackEnd::GetWindowHeight()));
	m_register = m_scenes[4]->GetScene();
	m_activeScene = m_scenes[4];

	if (level1Cleared)
	{
		LevelSelect2* scene = (LevelSelect2*)m_activeScene;
		auto level2 = scene->GetLevel2Template();
		ECS::GetComponent<Sprite>(level2).SetTransparency(1.0f);
	}

	if (level2Cleared)
	{
		LevelSelect2* scene = (LevelSelect2*)m_activeScene;
		auto level3 = scene->GetLevel3Template();
		ECS::GetComponent<Sprite>(level3).SetTransparency(1.0f);
	}
}
//Level Select to Level 1
if (Input::GetKeyDown(Key::Space) && m_activeScene == m_scenes[3])
{
	sndPlaySound("MenuSelect.wav", SND_FILENAME | SND_ASYNC);

	LevelSelectMain* scene = (LevelSelectMain*)m_activeScene;

	scene->SetFade(true);

	change2 = true;

	ECS::DestroyEntity(scene->GetMenu());
	ECS::DestroyEntity(scene->GetRight());
	ECS::DestroyEntity(scene->GetLeft());
	//ECS::DestroyEntity(scene->GetPlay());
	ECS::DestroyEntity(scene->GetLevel1Template());
	ECS::DestroyEntity(scene->GetLevel2Template());
	ECS::DestroyEntity(scene->GetLevel3Template());
}
//Level Select 2 to Level 2
if (Input::GetKeyDown(Key::Space) && m_activeScene == m_scenes[4] && level1Cleared)
{
	sndPlaySound("MenuSelect.wav", SND_FILENAME | SND_ASYNC);

	LevelSelect2* scene = (LevelSelect2*)m_activeScene;

	scene->SetFade(true);

	change3 = true;

	ECS::DestroyEntity(scene->GetMenu());
	ECS::DestroyEntity(scene->GetRight());
	ECS::DestroyEntity(scene->GetLeft());
	//ECS::DestroyEntity(scene->GetPlay());
	ECS::DestroyEntity(scene->GetLevel1Template());
	ECS::DestroyEntity(scene->GetLevel2Template());
	ECS::DestroyEntity(scene->GetLevel3Template());
}
//Level Select 3 to Level 3
if (Input::GetKeyDown(Key::Space) && m_activeScene == m_scenes[5] && level2Cleared)
{
	sndPlaySound("MenuSelect.wav", SND_FILENAME | SND_ASYNC);

	LevelSelect3* scene = (LevelSelect3*)m_activeScene;

	scene->SetFade(true);

	change4 = true;

	ECS::DestroyEntity(scene->GetMenu());
	ECS::DestroyEntity(scene->GetRight());
	ECS::DestroyEntity(scene->GetLeft());
	//ECS::DestroyEntity(scene->GetPlay());
	ECS::DestroyEntity(scene->GetLevel1Template());
	ECS::DestroyEntity(scene->GetLevel2Template());
	ECS::DestroyEntity(scene->GetLevel3Template());
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
//Level 1 to Level Select
if (Input::GetKeyDown(Key::Backspace) && m_activeScene == m_scenes[6])
{
	sndPlaySound("MenuDeselect.wav", SND_FILENAME | SND_ASYNC);

	SceneEditor::ResetEditor();

	m_activeScene->Unload();

	m_scenes[3]->InitScene(float(BackEnd::GetWindowWidth()), float(BackEnd::GetWindowHeight()));
	m_register = m_scenes[3]->GetScene();
	m_activeScene = m_scenes[3];

	if (level1Cleared)
	{
		LevelSelectMain* scene = (LevelSelectMain*)m_activeScene;
		auto level2 = scene->GetLevel2Template();
		ECS::GetComponent<Sprite>(level2).SetTransparency(1.0f);
	}
	if (level2Cleared)
	{
		LevelSelectMain* scene = (LevelSelectMain*)m_activeScene;
		auto level3 = scene->GetLevel3Template();
		ECS::GetComponent<Sprite>(level3).SetTransparency(1.0f);
	}
}
//Level 2 to Level Select
if (Input::GetKeyDown(Key::Backspace) && m_activeScene == m_scenes[7])
{
	sndPlaySound("MenuDeselect.wav", SND_FILENAME | SND_ASYNC);

	SceneEditor::ResetEditor();

	m_activeScene->Unload();

	m_scenes[4]->InitScene(float(BackEnd::GetWindowWidth()), float(BackEnd::GetWindowHeight()));
	m_register = m_scenes[4]->GetScene();
	m_activeScene = m_scenes[4];

	if (level1Cleared)
	{
		LevelSelect2* scene = (LevelSelect2*)m_activeScene;
		auto level2 = scene->GetLevel2Template();
		ECS::GetComponent<Sprite>(level2).SetTransparency(1.0f);
	}

	if (level2Cleared)
	{
		LevelSelect2* scene = (LevelSelect2*)m_activeScene;
		auto level2 = scene->GetLevel2Template();
		auto level3 = scene->GetLevel3Template();
		ECS::GetComponent<Sprite>(level2).SetTransparency(1.0f);
		ECS::GetComponent<Sprite>(level3).SetTransparency(1.0f);
	}
}
//Level 3 to Level Select
if (Input::GetKeyDown(Key::Backspace) && m_activeScene == m_scenes[8])
{
	sndPlaySound("MenuDeselect.wav", SND_FILENAME | SND_ASYNC);

	SceneEditor::ResetEditor();

	m_activeScene->Unload();

	m_scenes[5]->InitScene(float(BackEnd::GetWindowWidth()), float(BackEnd::GetWindowHeight()));
	m_register = m_scenes[5]->GetScene();
	m_activeScene = m_scenes[5];

	if (level2Cleared)
	{
		LevelSelect3* scene = (LevelSelect3*)m_activeScene;
		auto level2 = scene->GetLevel2Template();
		auto level3 = scene->GetLevel3Template();
		ECS::GetComponent<Sprite>(level2).SetTransparency(1.0f);
		ECS::GetComponent<Sprite>(level3).SetTransparency(1.0f);
	}

	if (level3Cleared)
	{
		LevelSelect3* scene = (LevelSelect3*)m_activeScene;
		auto level2 = scene->GetLevel2Template();
		auto level3 = scene->GetLevel3Template();
		ECS::GetComponent<Sprite>(level2).SetTransparency(1.0f);
		ECS::GetComponent<Sprite>(level3).SetTransparency(1.0f);
	}
}
#pragma endregion

#pragma region Commands for Win Cons
//TEST PURPOSES
if (Input::GetKeyDown(Key::One))
{
	level1Cleared = true;

	if (level1Cleared)
	{
		SceneEditor::ResetEditor();

		m_activeScene->Unload();

		m_scenes[3]->InitScene(float(BackEnd::GetWindowWidth()), float(BackEnd::GetWindowHeight()));
		m_register = m_scenes[3]->GetScene();
		m_activeScene = m_scenes[3];

		LevelSelectMain* scene = (LevelSelectMain*)m_activeScene;
		auto level2 = scene->GetLevel2Template();
		ECS::GetComponent<Sprite>(level2).SetTransparency(1.0f);
	}
}

if (Input::GetKeyDown(Key::Two))
{
	level2Cleared = true;

	if (level2Cleared)
	{
		SceneEditor::ResetEditor();

		m_activeScene->Unload();

		m_scenes[4]->InitScene(float(BackEnd::GetWindowWidth()), float(BackEnd::GetWindowHeight()));
		m_register = m_scenes[4]->GetScene();
		m_activeScene = m_scenes[4];

		LevelSelect2* scene = (LevelSelect2*)m_activeScene;
		auto level2 = scene->GetLevel2Template();
		auto level3 = scene->GetLevel3Template();
		ECS::GetComponent<Sprite>(level2).SetTransparency(1.0f);
		ECS::GetComponent<Sprite>(level3).SetTransparency(1.0f);
	}
}

if (Input::GetKeyDown(Key::Three))
{
	level3Cleared = true;

	if (level3Cleared)
	{
		SceneEditor::ResetEditor();

		m_activeScene->Unload();

		m_scenes[5]->InitScene(float(BackEnd::GetWindowWidth()), float(BackEnd::GetWindowHeight()));
		m_register = m_scenes[5]->GetScene();
		m_activeScene = m_scenes[5];

		LevelSelect3* scene = (LevelSelect3*)m_activeScene;
		auto level2 = scene->GetLevel2Template();
		auto level3 = scene->GetLevel3Template();
		ECS::GetComponent<Sprite>(level2).SetTransparency(1.0f);
		ECS::GetComponent<Sprite>(level3).SetTransparency(1.0f);
	}
}
#pragma endregion

#pragma region JUMPING CODE
//Jumping
if (m_activeScene == m_scenes[6] || m_activeScene == m_scenes[7] || m_activeScene == m_scenes[8])
{
	auto blueBody = ECS::GetComponent<PhysicsBody>(EntityIdentifier::MainPlayer()).GetBody();
	auto waterBody = ECS::GetComponent<PhysicsBody>(EntityIdentifier::MainPlayer2()).GetBody();
	const float blueJumpForce = 30.f;
	const float waterJumpForce = 22.f;

	if (listener.GetBJump() || listener.GetBGrounded())
	{
		if (Input::GetKeyDown(Key::W))
		{
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
			float impulse = waterBody->GetMass() * waterJumpForce;
			waterBody->ApplyLinearImpulse(b2Vec2(0, impulse), waterBody->GetWorldCenter(), true);
			listener.SetWGrounded(false);
			listener.SetWJump(false);
		}
	}	
}
#pragma endregion

#pragma region DEV TOOLS
//Hotkeys
if (Input::GetKeyDown(Key::NumPad1))
{
	SceneEditor::ResetEditor();

	m_activeScene->Unload();

	m_scenes[6]->InitScene(float(BackEnd::GetWindowWidth()), float(BackEnd::GetWindowHeight()));
	m_register = m_scenes[6]->GetScene();
	m_activeScene = m_scenes[6];

	m_activeScene->GetPhysicsWorld().SetContactListener(&listener);
}
if (Input::GetKeyDown(Key::NumPad2))
{
	SceneEditor::ResetEditor();

	m_activeScene->Unload();

	m_scenes[7]->InitScene(float(BackEnd::GetWindowWidth()), float(BackEnd::GetWindowHeight()));
	m_register = m_scenes[7]->GetScene();
	m_activeScene = m_scenes[7];

	m_activeScene->GetPhysicsWorld().SetContactListener(&listener);
}
if (Input::GetKeyDown(Key::NumPad3))
{
	SceneEditor::ResetEditor();

	m_activeScene->Unload();

	m_scenes[8]->InitScene(float(BackEnd::GetWindowWidth()), float(BackEnd::GetWindowHeight()));
	m_register = m_scenes[8]->GetScene();
	m_activeScene = m_scenes[8];

	m_activeScene->GetPhysicsWorld().SetContactListener(&listener);
}
#pragma endregion

	if (Input::GetKeyDown(Key::G))
	{
		LevelSelectMain* scene = (LevelSelectMain*)m_activeScene;
		auto level2 = scene->GetLevel2Template();
		auto level3 = scene->GetLevel3Template();
		auto lvl2Trans = ECS::GetComponent<Sprite>(level2).GetTransparency();
		auto lvl3Trans = ECS::GetComponent<Sprite>(level3).GetTransparency();

		std::cout << "Level 2 Transparency: " << lvl2Trans << "\n";
		std::cout << "Level 3 Transparency: " << lvl3Trans << "\n";
	}	

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