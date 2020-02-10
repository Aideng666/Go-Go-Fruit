#include "Game.h"

#include <random>


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
	std::string menuName = "Menu";
	std::string exitName = "Exit";
	std::string gameName = "Level 1";

	m_name = menuName;
	m_clearColor = vec4(0.f, 0.f, 0.f, 1.f);

	//Initializes the backend with window width and height values
	BackEnd::InitBackEnd(m_name);

	//Grabs the initialized window
	m_window = BackEnd::GetWindow();

	//Creates a new scene.
	m_scenes.push_back(new GoGoMenu(menuName));
	m_scenes.push_back(new GoGoExit(exitName));
	m_scenes.push_back(new GoGoGame(gameName));

	//Sets active scene reference to our scene
	m_scenes[0]->InitScene(float(BackEnd::GetWindowWidth()), float(BackEnd::GetWindowHeight()));
	m_register = m_scenes[0]->GetScene();
	m_activeScene = m_scenes[0];
	PhysicsSystem::Init();
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

void Game::GamepadStroke(XInputController * con)
{
	//Active scene now captures this input and can use it
	//Look at base Scene class for more info.
	m_activeScene->GamepadStroke(con);
}

void Game::GamepadUp(XInputController * con)
{
	//Active scene now captures this input and can use it
	//Look at base Scene class for more info.
	m_activeScene->GamepadUp(con);
}

void Game::GamepadDown(XInputController * con)
{
	//Active scene now captures this input and can use it
	//Look at base Scene class for more info.
	m_activeScene->GamepadDown(con);
}

void Game::GamepadStick(XInputController * con)
{
	//Active scene now captures this input and can use it
	//Look at base Scene class for more info.
	m_activeScene->GamepadStick(con);
}

void Game::GamepadTrigger(XInputController * con)
{
	//Active scene now captures this input and can use it
	//Look at base Scene class for more info.
	m_activeScene->GamepadTrigger(con);
}

void Game::KeyboardHold()
{
	if (m_activeScene == m_scenes[2])
	{		
		GoGoGame* scene = (GoGoGame*)m_activeScene;
		auto water = scene->GetWatermelon();
		auto blue = scene->GetBlueberry();
		auto blueBody = ECS::GetComponent<PhysicsBody>(blue).GetBody();
		auto waterBody = ECS::GetComponent<PhysicsBody>(water).GetBody();
		b2Vec2 velBlue = blueBody->GetLinearVelocity();
		b2Vec2 velWater = waterBody->GetLinearVelocity();
		float desiredVelBlue = 0.f;
		float desiredVelWater = 0.f;

		if (Input::GetKey(Key::A))
		{
			desiredVelBlue = -10.f;
		}
		if (Input::GetKey(Key::D))
		{
			desiredVelBlue = 10.f;
		}
		if (Input::GetKey(Key::LeftArrow))
		{
			desiredVelWater = -10.f;
		}
		if (Input::GetKey(Key::RightArrow))
		{
			desiredVelWater = 10.f;
		}

		float velChangeBlue = desiredVelBlue - velBlue.x;
		float velChangeWater = desiredVelWater - velWater.x;
		float forceBlue = (blueBody->GetMass() * velChangeBlue);
		blueBody->ApplyForce(b2Vec2(forceBlue, 0), blueBody->GetWorldCenter(), true);
		float forceWater = (waterBody->GetMass() * velChangeWater);
		waterBody->ApplyForce(b2Vec2(forceWater, 0), waterBody->GetWorldCenter(), true);	
	}
}

void Game::KeyboardDown()
{
	if (Input::GetKeyDown(Key::Escape))
	{
		exit(1);
	}

	//Space on play goes to game
	if (Input::GetKeyDown(Key::Space) && m_activeScene == m_scenes[0])
	{
		SceneEditor::ResetEditor();

		m_activeScene->Unload();

		m_scenes[2]->InitScene(float(BackEnd::GetWindowWidth()), float(BackEnd::GetWindowHeight()));
		m_register = m_scenes[2]->GetScene();
		m_activeScene = m_scenes[2];
	}
	//Up arrow goes to exit
	if (Input::GetKeyDown(Key::UpArrow) && m_activeScene == m_scenes[0])
	{
		SceneEditor::ResetEditor();

		m_activeScene->Unload();

		m_scenes[1]->InitScene(float(BackEnd::GetWindowWidth()), float(BackEnd::GetWindowHeight()));
		m_register = m_scenes[1]->GetScene();
		m_activeScene = m_scenes[1];
	}
<<<<<<< HEAD


=======
	//Down arrow on menu goes to exit
	else if (Input::GetKeyDown(Key::DownArrow) && m_activeScene == m_scenes[0])
	{
		SceneEditor::ResetEditor();

		m_activeScene->Unload();

		m_scenes[1]->InitScene(float(BackEnd::GetWindowWidth()), float(BackEnd::GetWindowHeight()));
		m_register = m_scenes[1]->GetScene();
		m_activeScene = m_scenes[1];
	}
	//Up arrow on exit goes to menu
	else if (Input::GetKeyDown(Key::UpArrow) && m_activeScene == m_scenes[1])
	{
		SceneEditor::ResetEditor();

		m_activeScene->Unload();

		m_scenes[0]->InitScene(float(BackEnd::GetWindowWidth()), float(BackEnd::GetWindowHeight()));
		m_register = m_scenes[0]->GetScene();
		m_activeScene = m_scenes[0];
	}
>>>>>>> Temp
	//Down arrow on exit goes to menu
	else if (Input::GetKeyDown(Key::DownArrow) && m_activeScene == m_scenes[1])
	{
		SceneEditor::ResetEditor();

		m_activeScene->Unload();

		m_scenes[0]->InitScene(float(BackEnd::GetWindowWidth()), float(BackEnd::GetWindowHeight()));
		m_register = m_scenes[0]->GetScene();
		m_activeScene = m_scenes[0];
	}
	//Exits the game
	if (Input::GetKeyDown(Key::Space) && m_activeScene == m_scenes[1])
	{
		exit(1);
	}

	//Jumping
	if (m_activeScene == m_scenes[2])
	{
		GoGoGame* scene = (GoGoGame*)m_activeScene;
		auto water = scene->GetWatermelon();
		auto blue = scene->GetBlueberry();
		auto blueBody = ECS::GetComponent<PhysicsBody>(blue).GetBody();
		auto waterBody = ECS::GetComponent<PhysicsBody>(water).GetBody();

		if (Input::GetKeyDown(Key::W))
		{
			if (blueBody->GetLinearVelocity().y < 0.001 && blueBody->GetLinearVelocity().y > -0.001)
			{
				b2Vec2 vel = blueBody->GetLinearVelocity();
				vel.y = 35;
				blueBody->SetLinearVelocity(vel);
			}
		}
		if (Input::GetKeyDown(Key::UpArrow))
		{
			if (waterBody->GetLinearVelocity().y < 0.001 && waterBody->GetLinearVelocity().y > -0.001)
			{
				b2Vec2 vel = waterBody->GetLinearVelocity();
				vel.y = 15;
				waterBody->SetLinearVelocity(vel);
			}
		}
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