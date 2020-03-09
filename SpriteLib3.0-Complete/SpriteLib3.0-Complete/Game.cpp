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
	std::string menuName = "Menu";
	std::string exitName = "Exit";
	std::string gameName = "Level 1";
	std::string level2   = "Level 2";

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
	m_scenes.push_back(new LevelTwo(level2));

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

	//Fades the Menu out into Lvl 1
	if (change)
	{
		timer += Timer::deltaTime;

		if (timer >= 1.f)
		{
			SceneEditor::ResetEditor();

			m_activeScene->Unload();

			m_scenes[2]->InitScene(float(BackEnd::GetWindowWidth()), float(BackEnd::GetWindowHeight()));
			m_register = m_scenes[2]->GetScene();
			m_activeScene = m_scenes[2];
			timer = 0.f;
			change = false;
		}
	}

	if (m_activeScene == m_scenes[2])
	{
		if (listener.GetShake())
		{
			GoGoGame* scene = (GoGoGame*)m_activeScene;
			auto cam = scene->GetCam();

			vec4 tempOrtho = ECS::GetComponent<Camera>(cam).GetOrthoPos();
			timer2 += Timer::deltaTime;

			ECS::GetComponent<Camera>(cam).Shake(static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / 0.5f)) - 0.25f);

			if (timer2 >= 0.1f)
			{
				timer2 = 0.f;
				listener.SetShake(false);
			}
		}
	}

	if (m_activeScene == m_scenes[3])
	{
		if (listener.GetShake())
		{
			LevelTwo* scene = (LevelTwo*)m_activeScene;
			auto cam = scene->GetCam();

			vec4 tempOrtho = ECS::GetComponent<Camera>(cam).GetOrthoPos();
			timer2 += Timer::deltaTime;

			ECS::GetComponent<Camera>(cam).Shake(static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / 0.5f)) - 0.25f);

			if (timer2 >= 0.1f)
			{
				timer2 = 0.f;
				listener.SetShake(false);
			}
		}
	}


#pragma region Parallax Background
	if (m_activeScene == m_scenes[2])
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

	if (m_activeScene == m_scenes[3])
	{
		LevelTwo* scene = (LevelTwo*)m_activeScene;
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
	if (m_activeScene == m_scenes[2])
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
	if (m_activeScene == m_scenes[3])
	{
		LevelTwo* scene = (LevelTwo*)m_activeScene;
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
		if (listener.GetPressed() && trans.GetPosition().y < -14.5f)
		{
			body->SetLinearVelocity(b2Vec2(0, 2));
		}
		else if (!(listener.GetPressed()) && trans.GetPosition().y > -85.f)
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
		else if (!(listener.Get2Pressed()) && trans2.GetPosition().y > -9.5f)
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
	for (int i = 2; i < m_scenes.size(); ++i)
	{
		if (m_activeScene == m_scenes[i])
		{
			auto blueBody = ECS::GetComponent<PhysicsBody>(EntityIdentifier::MainPlayer()).GetBody();
			auto waterBody = ECS::GetComponent<PhysicsBody>(EntityIdentifier::MainPlayer2()).GetBody();
			b2Vec2 blueVel = blueBody->GetLinearVelocity();
			b2Vec2 waterVel = waterBody->GetLinearVelocity();
			float blueSpeed = 0.f, waterSpeed = 0.f;

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
				waterSpeed = -10.f;
			}
			if (Input::GetKey(Key::RightArrow))
			{
				waterSpeed = 10.f;
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
	//Zooming
	/*//ZOOMING
	
	if (Input::GetKey(Key::Z))
	{
		ECS::GetComponent<Camera>(camera).Zoom(2.f);
	}
	if (Input::GetKey(Key::X))
	{
		ECS::GetComponent<Camera>(camera).Zoom(-2.f);
	}*/


	GoGoGame* scene = (GoGoGame*)m_activeScene;
	auto camera = scene->GetCam();

	if (Input::GetKey(Key::K))
	{

		float number = static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / 1.f)) - 0.5f;
		std::cout << number << std::endl;

		ECS::GetComponent<Camera>(camera).Shake(number);

		/*vec2 viewpointCenter = (vec2(BackEnd::GetWindowWidth() / 2, BackEnd::GetWindowHeight() / 2));
		float radius = 30.f;
		float angle = rand() % 360;
		vec2 offset = (vec2(sin(angle) * radius, cos(angle) * radius));*/
		/*ECS::GetComponent<Camera>(camera).SetOrthoSize(vec4(ECS::GetComponent<Camera>(camera).GetOrthoSize().x + 10, ECS::GetComponent<Camera>(camera).GetOrthoSize().y - 10, ECS::GetComponent<Camera>(camera).GetOrthoSize().z + 10, ECS::GetComponent<Camera>(camera).GetOrthoSize().w - 10));

			//Updates Left, Right, Top , and Bottom
		ECS::GetComponent<Camera>(camera).SetOrthoPos(vec4(ECS::GetComponent<Camera>(camera).GetOrthoPos().x + ECS::GetComponent<Camera>(camera).m_localPosition.x, ECS::GetComponent<Camera>(camera).GetOrthoPos().y, ECS::GetComponent<Camera>(camera).GetOrthoPos().z, ECS::GetComponent<Camera>(camera).GetOrthoPos().w));
		ECS::GetComponent<Camera>(camera).SetOrthoPos(vec4(ECS::GetComponent<Camera>(camera).GetOrthoPos().x, ECS::GetComponent<Camera>(camera).GetOrthoPos().y + ECS::GetComponent<Camera>(camera).m_localPosition.x, ECS::GetComponent<Camera>(camera).GetOrthoPos().z, ECS::GetComponent<Camera>(camera).GetOrthoPos().w));
		ECS::GetComponent<Camera>(camera).SetOrthoPos(vec4(ECS::GetComponent<Camera>(camera).GetOrthoPos().x, ECS::GetComponent<Camera>(camera).GetOrthoPos().y, ECS::GetComponent<Camera>(camera).GetOrthoPos().z + ECS::GetComponent<Camera>(camera).m_localPosition.y, ECS::GetComponent<Camera>(camera).GetOrthoPos().w));
		ECS::GetComponent<Camera>(camera).SetOrthoPos(vec4(ECS::GetComponent<Camera>(camera).GetOrthoPos().x, ECS::GetComponent<Camera>(camera).GetOrthoPos().y, ECS::GetComponent<Camera>(camera).GetOrthoPos().z, ECS::GetComponent<Camera>(camera).GetOrthoPos().w + ECS::GetComponent<Camera>(camera).m_localPosition.y));

		ECS::GetComponent<Camera>(camera).Orthographic(ECS::GetComponent<Camera>(camera).GetAspect(), ECS::GetComponent<Camera>(camera).GetOrthoPos().x, ECS::GetComponent<Camera>(camera).GetOrthoPos().y, ECS::GetComponent<Camera>(camera).GetOrthoPos().z, ECS::GetComponent<Camera>(camera).GetOrthoPos().w, ECS::GetComponent<Camera>(camera).GetNear(), ECS::GetComponent<Camera>(camera).GetFar());*/
	}
}

void Game::KeyboardDown()
{
	//Exit fullscreen
	if (Input::GetKeyDown(Key::Escape))
	{
		exit(1);
	}

#pragma region SCREEN MANIPULATION
//Space on play goes to game
if (Input::GetKeyDown(Key::Space) && m_activeScene == m_scenes[0])
{
	sndPlaySound("MenuSelect.wav", SND_FILENAME | SND_ASYNC);

	GoGoMenu* scene = (GoGoMenu*)m_activeScene;

	scene->SetFade(true);

	change = true;

	ECS::DestroyEntity(scene->GetMenu());

}
//Up arrow goes to exit
if (Input::GetKeyDown(Key::UpArrow) && m_activeScene == m_scenes[0])
{
	sndPlaySound("MenuClick.wav", SND_FILENAME | SND_ASYNC);

	SceneEditor::ResetEditor();

	m_activeScene->Unload();

	m_scenes[1]->InitScene(float(BackEnd::GetWindowWidth()), float(BackEnd::GetWindowHeight()));
	m_register = m_scenes[1]->GetScene();
	m_activeScene = m_scenes[1];
}
//Down arrow on menu goes to exit
else if (Input::GetKeyDown(Key::DownArrow) && m_activeScene == m_scenes[0])
{
	sndPlaySound("MenuClick.wav", SND_FILENAME | SND_ASYNC);

	SceneEditor::ResetEditor();

	m_activeScene->Unload();

	m_scenes[1]->InitScene(float(BackEnd::GetWindowWidth()), float(BackEnd::GetWindowHeight()));
	m_register = m_scenes[1]->GetScene();
	m_activeScene = m_scenes[1];
}
//Up arrow on exit goes to menu
else if (Input::GetKeyDown(Key::UpArrow) && m_activeScene == m_scenes[1])
{
	sndPlaySound("MenuClick.wav", SND_FILENAME | SND_ASYNC);

	SceneEditor::ResetEditor();

	m_activeScene->Unload();

	m_scenes[0]->InitScene(float(BackEnd::GetWindowWidth()), float(BackEnd::GetWindowHeight()));
	m_register = m_scenes[0]->GetScene();
	m_activeScene = m_scenes[0];
}
//Down arrow on exit goes to menu
else if (Input::GetKeyDown(Key::DownArrow) && m_activeScene == m_scenes[1])
{
	sndPlaySound("MenuClick.wav", SND_FILENAME | SND_ASYNC);

	SceneEditor::ResetEditor();

	m_activeScene->Unload();

	m_scenes[0]->InitScene(float(BackEnd::GetWindowWidth()), float(BackEnd::GetWindowHeight()));
	m_register = m_scenes[0]->GetScene();
	m_activeScene = m_scenes[0];
}
//Exits the game
if (Input::GetKeyDown(Key::Space) && m_activeScene == m_scenes[1])
{
	sndPlaySound("MenuSelect.wav", SND_FILENAME | SND_ASYNC);
	exit(1);
}
#pragma endregion


#pragma region JUMPING CODE
//Jumping
if (m_activeScene == m_scenes[2] || m_activeScene == m_scenes[3])
{
	GoGoGame* scene = (GoGoGame*)m_activeScene;
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
		}
	}

	if (listener.GetWJump() || listener.GetWGrounded())
	{
		if (Input::GetKeyDown(Key::UpArrow))
		{
			float impulse = waterBody->GetMass() * waterJumpForce;
			waterBody->ApplyLinearImpulse(b2Vec2(0, impulse), waterBody->GetWorldCenter(), true);
			listener.SetWGrounded(false);
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

	m_scenes[2]->InitScene(float(BackEnd::GetWindowWidth()), float(BackEnd::GetWindowHeight()));
	m_register = m_scenes[2]->GetScene();
	m_activeScene = m_scenes[2];
}
if (Input::GetKeyDown(Key::NumPad2))
{
	SceneEditor::ResetEditor();

	m_activeScene->Unload();

	m_scenes[3]->InitScene(float(BackEnd::GetWindowWidth()), float(BackEnd::GetWindowHeight()));
	m_register = m_scenes[3]->GetScene();
	m_activeScene = m_scenes[3];
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

