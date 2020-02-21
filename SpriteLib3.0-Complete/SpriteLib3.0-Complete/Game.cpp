#include "Game.h"
#include "ContactListener.h"

#include <random>

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

	for (int i = 0; i < m_scenes.size(); ++i)
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

	/*if (m_activeScene == m_scenes[2])
	{
		GoGoGame* scene = (GoGoGame*)m_activeScene;
		auto button = scene->GetButton();
		auto platform = scene->GetPlat();

		if (ECS::GetComponent<PhysicsBody>(button).GetPressed())
		{
	
			if (ECS::GetComponent<Transform>(platform).GetPosition().y <= -92.f && ECS::GetComponent<Transform>(platform).GetPosition().y <= 10.f)
			{
				SetUp(true);
			}
			if (ECS::GetComponent<Transform>(platform).GetPosition().y >= 10.f && ECS::GetComponent<Transform>(platform).GetPosition().y >= -92.f)
			{
				SetUp(false);
			}

			if (GetUp())
			{
				m_register->get<Transform>(platform).SetPositionY(ECS::GetComponent<Transform>(platform).GetPosition().y + (40 * Timer::deltaTime));
			}
			if (!GetUp())
			{
				m_register->get<Transform>(platform).SetPositionY(ECS::GetComponent<Transform>(platform).GetPosition().y - (40 * Timer::deltaTime));
			}
		}
		

	}*/

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
		auto blueBody = ECS::GetComponent<PhysicsBody>(EntityIdentifier::MainPlayer()).GetBody();
		auto waterBody = ECS::GetComponent<PhysicsBody>(EntityIdentifier::MainPlayer2()).GetBody();

		b2Vec2 blueVel = blueBody->GetLinearVelocity();
		b2Vec2 waterVel = waterBody->GetLinearVelocity();

		float blueSpeed = 0.f, waterSpeed = 0.f;

		if (Input::GetKey(Key::A))
		{
			blueSpeed = -8.f;
		}
		if (Input::GetKey(Key::D))
		{
			blueSpeed = 8.f;
		}
		if (Input::GetKey(Key::LeftArrow))
		{
			waterSpeed = -8.f;
		}
		if (Input::GetKey(Key::RightArrow))
		{
			waterSpeed = 8.f;
		}


		float blueChange = blueSpeed - blueVel.x;
		float waterChange = waterSpeed - waterVel.x;
		float blueForce = (blueBody->GetMass() * blueChange);
		float waterForce = (waterBody->GetMass() * waterChange);

		blueBody->ApplyForce(b2Vec2(blueForce, 0), blueBody->GetWorldCenter(), true);
		waterBody->ApplyForce(b2Vec2(waterForce, 0), waterBody->GetWorldCenter(), true);

		//ZOOMING
		auto cam = scene->GetCam();

		if (Input::GetKey(Key::Z))
		{
			ECS::GetComponent<Camera>(cam).Zoom(2.f);
		}
		if (Input::GetKey(Key::X))
		{
			ECS::GetComponent<Camera>(cam).Zoom(-2.f);
		}

		
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
		auto blueBody = ECS::GetComponent<PhysicsBody>(EntityIdentifier::MainPlayer()).GetBody();
		auto waterBody = ECS::GetComponent<PhysicsBody>(EntityIdentifier::MainPlayer2()).GetBody();

		if (listener.GetBJump() || listener.GetBGrounded())
		{
			if (Input::GetKeyDown(Key::W))
			{
				float impulse = blueBody->GetMass() * 18;
				blueBody->ApplyLinearImpulse(b2Vec2(0, impulse), blueBody->GetWorldCenter(), true);
				listener.SetBGrounded(false);
			}
		}

		if (listener.GetWJump() || listener.GetWGrounded())
		{
			if (Input::GetKeyDown(Key::UpArrow))
			{
				float impulse = waterBody->GetMass() * 10;
				waterBody->ApplyLinearImpulse(b2Vec2(0, impulse), waterBody->GetWorldCenter(), true);
				listener.SetWGrounded(false);
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

bool Game::GetUp()
{
	return this->goingUp;
}

void Game::SetUp(bool up)
{
	this->goingUp = up;
}
