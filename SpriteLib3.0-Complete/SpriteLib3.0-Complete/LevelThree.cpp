#include "LevelThree.h"
#include <iostream>

LevelThree::LevelThree(std::string name)
	: Scene(name)
{
	m_gravity = b2Vec2(float32(0.f), float32(-9.f));
	m_physicsWorld->SetGravity(m_gravity);
}

void LevelThree::InitScene(float windowWidth, float windowHeight)
{
	m_sceneReg = new entt::registry;

	ECS::AttachRegister(m_sceneReg);

	float aspectRatio = windowWidth / windowHeight;

	//Game Camera
	{
		auto entity = ECS::CreateEntity();
		EntityIdentifier::MainCamera(entity);

		ECS::AttachComponent<Camera>(entity);
		vec4 temp = ECS::GetComponent<Camera>(entity).GetOrthoSize();
		ECS::GetComponent<Camera>(entity).SetWindowSize(vec2(float(windowWidth), float(windowHeight)));
		ECS::GetComponent<Camera>(entity).Orthographic(aspectRatio, temp.x, temp.y, temp.z, temp.w, -100.f, 100.f);

		unsigned int bitHolder = EntityIdentifier::CameraBit();
		ECS::SetUpIdentifier(entity, bitHolder, "Game Camera");
		ECS::SetIsMainCamera(entity, true);

		m_cam = entity;
	}

//Add flowers and grass
#pragma region Aesthetics + Environment
	//Background Level Image
	{
		auto entity = ECS::CreateEntity();

		ECS::AttachComponent<Sprite>(entity);
		ECS::AttachComponent<Transform>(entity);

		std::string fileName = "Level3.png";

		ECS::GetComponent<Sprite>(entity).LoadSprite(fileName, 357, 212.7125);
		ECS::GetComponent<Transform>(entity).SetPosition(vec3(0.f, 6.f, 20.f));

		unsigned int bitHolder = EntityIdentifier::SpriteBit() | EntityIdentifier::TransformBit();
		ECS::SetUpIdentifier(entity, bitHolder, "Level 3");
	}
	//Sky Background
	{
		std::string fileName = "Sky.png";

		auto entity = ECS::CreateEntity();
		ECS::AttachComponent<Sprite>(entity);
		ECS::AttachComponent<Transform>(entity);
		ECS::GetComponent<Sprite>(entity).LoadSprite(fileName, 360, 360);
		ECS::GetComponent<Transform>(entity).SetPosition(vec3(0.f, -80.f, 10.f));
		unsigned int bitHolder = EntityIdentifier::SpriteBit() | EntityIdentifier::TransformBit();
		ECS::SetUpIdentifier(entity, bitHolder, "Sky Background");

		auto entity2 = ECS::CreateEntity();
		ECS::AttachComponent<Sprite>(entity2);
		ECS::AttachComponent<Transform>(entity2);
		ECS::GetComponent<Sprite>(entity2).LoadSprite(fileName, 360, 360);
		ECS::GetComponent<Transform>(entity2).SetPosition(vec3(360.f, -80.f, 10.f));
		unsigned int bitHolder2 = EntityIdentifier::SpriteBit() | EntityIdentifier::TransformBit();
		ECS::SetUpIdentifier(entity2, bitHolder2, "Sky Background 2");

		m_background = entity;
		m_background2 = entity2;
	}
#pragma endregion 

#pragma region PLAYER ENTITIES
	//Blueberry
	{
		auto entity = ECS::CreateEntity();

		ECS::SetIsMainPlayer(entity, true);
		EntityIdentifier::MainPlayer(entity);

		ECS::AttachComponent<Sprite>(entity);
		ECS::AttachComponent<Transform>(entity);
		ECS::AttachComponent<PhysicsBody>(entity);

		std::string fileName = "Blueberry.png";
		ECS::GetComponent<Sprite>(entity).LoadSprite(fileName, 30.2597402598f, 20);
		ECS::GetComponent<Transform>(entity).SetPosition(vec3(-100.f, 50.f, 99.f));

		auto& tempSpr = ECS::GetComponent<Sprite>(entity);
		auto& tempPhsBody = ECS::GetComponent<PhysicsBody>(entity);

		float shrinkX = tempSpr.GetWidth() / 30.2597402598f + 17;
		float shrinkY = tempSpr.GetWidth() / 20.f;

		b2Body* tempBody;
		b2BodyDef tempDef;
		tempDef.type = b2_dynamicBody;
		tempDef.position.Set(float32(-118.f), float32(-93.f));

		tempBody = m_physicsWorld->CreateBody(&tempDef);
		tempBody->SetFixedRotation(true);
		tempBody->SetUserData((void*)entity);

		tempPhsBody = PhysicsBody(tempBody, float(tempSpr.GetWidth() - shrinkX), float(tempSpr.GetHeight() - shrinkY),
			vec2(0.f, 0.f), false);

		tempPhsBody.SetFriction(0.15f);
		tempPhsBody.SetMaxVelo(60.f);
		tempPhsBody.SetGravity(true);

		unsigned int bitHolder = EntityIdentifier::SpriteBit() | EntityIdentifier::TransformBit() | EntityIdentifier::BlueberryBit();
		ECS::SetUpIdentifier(entity, bitHolder, "Blueberry");
	}

	//Watermelon
	{
		auto waterAnim = File::LoadJSON("Watermelon.json");

		auto entity = ECS::CreateEntity();

		ECS::SetIsMainPlayer2(entity, true);
		EntityIdentifier::MainPlayer2(entity);

		ECS::AttachComponent<Sprite>(entity);
		ECS::AttachComponent<Transform>(entity);
		ECS::AttachComponent<PhysicsBody>(entity);
		ECS::AttachComponent<AnimationController>(entity);

		std::string fileName = "WatermelonSS.png";

		auto& animController = ECS::GetComponent<AnimationController>(entity);
		animController.InitUVs(fileName);

		animController.AddAnimation(waterAnim["WalkLeft"]);
		animController.GetAnimation(0);
		animController.AddAnimation(waterAnim["WalkRight"]);
		animController.GetAnimation(1);
		animController.SetActiveAnim(1);

		ECS::GetComponent<Sprite>(entity).LoadSprite(fileName, 45.f, 30.f, true, &animController);
		ECS::GetComponent<Transform>(entity).SetPosition(vec3(-160.f, 60.f, 99.f));

		auto& tempSpr = ECS::GetComponent<Sprite>(entity);
		auto& tempPhsBody = ECS::GetComponent<PhysicsBody>(entity);

		float shrinkX = tempSpr.GetWidth() / 45.f + 20;
		float shrinkY = tempSpr.GetWidth() / 30.f + 11;

		b2Body* tempBody;
		b2BodyDef tempDef;
		tempDef.type = b2_dynamicBody;
		tempDef.position.Set(float32(-150.f), float32(-85.f));

		tempBody = m_physicsWorld->CreateBody(&tempDef);
		tempBody->SetFixedRotation(true);
		tempBody->SetUserData((void*)entity);

		tempPhsBody = PhysicsBody(tempBody, float(tempSpr.GetWidth() - shrinkX), float(tempSpr.GetHeight() - shrinkY),
			vec2(0.f, -6.f), false);

		tempPhsBody.SetFriction(0.15f);
		tempPhsBody.SetMaxVelo(60.f);
		tempPhsBody.SetGravity(true);

		unsigned int bitHolder = EntityIdentifier::SpriteBit() | EntityIdentifier::TransformBit() | EntityIdentifier::WatermelonBit() |
			EntityIdentifier::AnimationBit();
		ECS::SetUpIdentifier(entity, bitHolder, "Watermelon");
	}
#pragma endregion

#pragma region Physics Bodies
	//Ground Bodies
	{
		auto box1 = ECS::CreateEntity();

		ECS::AttachComponent<Transform>(box1);
		ECS::AttachComponent<PhysicsBody>(box1);

		ECS::GetComponent<Transform>(box1).SetPosition(vec3(0.f, 0.f, 50.f));

		auto& tempPhsBody = ECS::GetComponent<PhysicsBody>(box1);

		b2Body* tempBody;
		b2BodyDef tempDef;
		tempDef.type = b2_staticBody;
		tempDef.position.Set(float32(0.f), float32(-94));

		tempBody = m_physicsWorld->CreateBody(&tempDef);

		tempBody->SetUserData((void*)box1);

		tempPhsBody = PhysicsBody(tempBody, 360, 12, vec2(0.f, 0.f), false);

		unsigned int bitHolder = EntityIdentifier::TransformBit() | EntityIdentifier::GroundBit();
		ECS::SetUpIdentifier(box1, bitHolder, "Lower Ground Box");
	}

	{
		auto box1 = ECS::CreateEntity();
	
		ECS::AttachComponent<Transform>(box1);
		ECS::AttachComponent<PhysicsBody>(box1);
	
		ECS::GetComponent<Transform>(box1).SetPosition(vec3(0.f, 0.f, 50.f));
	
		auto& tempPhsBody = ECS::GetComponent<PhysicsBody>(box1);
	
		b2Body* tempBody;
		b2BodyDef tempDef;
		tempDef.type = b2_staticBody;
		tempDef.position.Set(float32(-60.f), float32(-77.f));
	
		tempBody = m_physicsWorld->CreateBody(&tempDef);
	
		tempBody->SetUserData((void*)box1);
	
		tempPhsBody = PhysicsBody(tempBody, 46.25, 1, vec2(0.f, 0.f), false);
	
		unsigned int bitHolder = EntityIdentifier::TransformBit() | EntityIdentifier::GroundBit();
		ECS::SetUpIdentifier(box1, bitHolder, "Hump Box");
	}

	{
		auto box = ECS::CreateEntity();

		ECS::AttachComponent<Transform>(box);
		ECS::AttachComponent<PhysicsBody>(box);

		ECS::GetComponent<Transform>(box).SetPosition(vec3(0.f, 0.f, 50.f));

		auto& tempPhsBody = ECS::GetComponent<PhysicsBody>(box);

		b2Body* tempBody;
		b2BodyDef tempDef;
		tempDef.type = b2_staticBody;
		tempDef.position.Set(float32(-83.f), float32(-83.f));
		
		tempBody = m_physicsWorld->CreateBody(&tempDef);
		
		tempBody->SetUserData((void*)box);
		
		tempPhsBody = PhysicsBody(tempBody, 1, 12, vec2(0.f, 0.f), false);
		
		unsigned int bitHolder = EntityIdentifier::TransformBit();
		ECS::SetUpIdentifier(box, bitHolder, "Left Side of Hump Box");
	}

	{
		auto box = ECS::CreateEntity();

		ECS::AttachComponent<Transform>(box);
		ECS::AttachComponent<PhysicsBody>(box);

		ECS::GetComponent<Transform>(box).SetPosition(vec3(0.f, 0.f, 50.f));

		auto& tempPhsBody = ECS::GetComponent<PhysicsBody>(box);

		b2Body* tempBody;
		b2BodyDef tempDef;
		tempDef.type = b2_staticBody;
		tempDef.position.Set(float32(-37.f), float32(-83.f));

		tempBody = m_physicsWorld->CreateBody(&tempDef);

		tempBody->SetUserData((void*)box);

		tempPhsBody = PhysicsBody(tempBody, 1, 12, vec2(0.f, 0.f), false);

		unsigned int bitHolder = EntityIdentifier::TransformBit();
		ECS::SetUpIdentifier(box, bitHolder, "Right Side of Hump Box");
	}

	{
		auto box1 = ECS::CreateEntity();
	
		ECS::AttachComponent<Transform>(box1);
		ECS::AttachComponent<PhysicsBody>(box1);
	
		ECS::GetComponent<Transform>(box1).SetPosition(vec3(0.f, 0.f, 50.f));
	
		auto& tempPhsBody = ECS::GetComponent<PhysicsBody>(box1);
	
		b2Body* tempBody;
		b2BodyDef tempDef;
		tempDef.type = b2_staticBody;
		tempDef.position.Set(float32(122.f), float32(-12.f));
	
		tempBody = m_physicsWorld->CreateBody(&tempDef);
	
		tempBody->SetUserData((void*)box1);
	
		tempPhsBody = PhysicsBody(tempBody, 120, 1, vec2(0.f, 0.f), false);
	
		unsigned int bitHolder = EntityIdentifier::TransformBit() | EntityIdentifier::GroundBit();
		ECS::SetUpIdentifier(box1, bitHolder, "Middle Ground Box");
	}

	{
		auto box1 = ECS::CreateEntity();
	
		ECS::AttachComponent<Transform>(box1);
		ECS::AttachComponent<PhysicsBody>(box1);
	
		ECS::GetComponent<Transform>(box1).SetPosition(vec3(0.f, 0.f, 50.f));
	
		auto& tempPhsBody = ECS::GetComponent<PhysicsBody>(box1);
	
		b2Body* tempBody;
		b2BodyDef tempDef;
		tempDef.type = b2_staticBody;
		tempDef.position.Set(float32(60.5f), float32(-51.75f));
	
		tempBody = m_physicsWorld->CreateBody(&tempDef);
	
		tempBody->SetUserData((void*)box1);
	
		tempPhsBody = PhysicsBody(tempBody, 1, 80.5, vec2(0.f, 0.f), false);
	
		unsigned int bitHolder = EntityIdentifier::TransformBit();
		ECS::SetUpIdentifier(box1, bitHolder, "Middle Facing Box");
	}

	{
		auto box1 = ECS::CreateEntity();
	
		ECS::AttachComponent<Transform>(box1);
		ECS::AttachComponent<PhysicsBody>(box1);
	
		ECS::GetComponent<Transform>(box1).SetPosition(vec3(0.f, 0.f, 50.f));
	
		auto& tempPhsBody = ECS::GetComponent<PhysicsBody>(box1);
	
		b2Body* tempBody;
		b2BodyDef tempDef;
		tempDef.type = b2_staticBody;
		tempDef.position.Set(float32(155.f), float32(13.f));
	
		tempBody = m_physicsWorld->CreateBody(&tempDef);
	
		tempBody->SetUserData((void*)box1);
	
		tempPhsBody = PhysicsBody(tempBody, 1, 50, vec2(0.f, 0.f), false);
	
		unsigned int bitHolder = EntityIdentifier::TransformBit();
		ECS::SetUpIdentifier(box1, bitHolder, "Right Facing Box");
	}

	{
		auto box1 = ECS::CreateEntity();
	
		ECS::AttachComponent<Transform>(box1);
		ECS::AttachComponent<PhysicsBody>(box1);
	
		ECS::GetComponent<Transform>(box1).SetPosition(vec3(0.f, 0.f, 50.f));
	
		auto& tempPhsBody = ECS::GetComponent<PhysicsBody>(box1);
	
		b2Body* tempBody;
		b2BodyDef tempDef;
		tempDef.type = b2_staticBody;
		tempDef.position.Set(float32(133.5f), float32(38.f));
	
		tempBody = m_physicsWorld->CreateBody(&tempDef);
	
		tempBody->SetUserData((void*)box1);
	
		tempPhsBody = PhysicsBody(tempBody, 100, 1, vec2(0.f, 0.f), false);
	
		unsigned int bitHolder = EntityIdentifier::TransformBit();
		ECS::SetUpIdentifier(box1, bitHolder, "Top Bottom Right Box");
	}

	{
		auto box1 = ECS::CreateEntity();
	
		ECS::AttachComponent<Transform>(box1);
		ECS::AttachComponent<PhysicsBody>(box1);
	
		ECS::GetComponent<Transform>(box1).SetPosition(vec3(0.f, 0.f, 50.f));
	
		auto& tempPhsBody = ECS::GetComponent<PhysicsBody>(box1);
	
		b2Body* tempBody;
		b2BodyDef tempDef;
		tempDef.type = b2_staticBody;
		tempDef.position.Set(float32(83.5f), float32(50.5f));
	
		tempBody = m_physicsWorld->CreateBody(&tempDef);
	
		tempBody->SetUserData((void*)box1);
	
		tempPhsBody = PhysicsBody(tempBody, 1, 26, vec2(0.f, 0.f), false);
	
		unsigned int bitHolder = EntityIdentifier::TransformBit();
		ECS::SetUpIdentifier(box1, bitHolder, "Top Right Facing Box");
	}

	{
		auto box1 = ECS::CreateEntity();
	
		ECS::AttachComponent<Transform>(box1);
		ECS::AttachComponent<PhysicsBody>(box1);
	
		ECS::GetComponent<Transform>(box1).SetPosition(vec3(0.f, 0.f, 50.f));
	
		auto& tempPhsBody = ECS::GetComponent<PhysicsBody>(box1);
	
		b2Body* tempBody;
		b2BodyDef tempDef;
		tempDef.type = b2_staticBody;
		tempDef.position.Set(float32(131.f), float32(63.f));
	
		tempBody = m_physicsWorld->CreateBody(&tempDef);
	
		tempBody->SetUserData((void*)box1);
	
		tempPhsBody = PhysicsBody(tempBody, 93, 1, vec2(0.f, 0.f), false);
	
		unsigned int bitHolder = EntityIdentifier::TransformBit() | EntityIdentifier::GroundBit();
		ECS::SetUpIdentifier(box1, bitHolder, "Top Right Box");
	}

	{
		auto box1 = ECS::CreateEntity();

		ECS::AttachComponent<Transform>(box1);
		ECS::AttachComponent<PhysicsBody>(box1);

		ECS::GetComponent<Transform>(box1).SetPosition(vec3(0.f, 0.f, 50.f));

		auto& tempPhsBody = ECS::GetComponent<PhysicsBody>(box1);

		b2Body* tempBody;
		b2BodyDef tempDef;
		tempDef.type = b2_staticBody;
		tempDef.position.Set(float32(-143.f), float32(38.f));

		tempBody = m_physicsWorld->CreateBody(&tempDef);

		tempBody->SetUserData((void*)box1);

		tempPhsBody = PhysicsBody(tempBody, 23, 129, vec2(0.f, 0.f), false);

		unsigned int bitHolder = EntityIdentifier::TransformBit();
		ECS::SetUpIdentifier(box1, bitHolder, "Top Left Box");
	}
	{
		auto box1 = ECS::CreateEntity();

		ECS::AttachComponent<Transform>(box1);
		ECS::AttachComponent<PhysicsBody>(box1);

		ECS::GetComponent<Transform>(box1).SetPosition(vec3(0.f, 0.f, 50.f));

		auto& tempPhsBody = ECS::GetComponent<PhysicsBody>(box1);

		b2Body* tempBody;
		b2BodyDef tempDef;
		tempDef.type = b2_staticBody;
		tempDef.position.Set(float32(-154.f), float32(-14.f));

		tempBody = m_physicsWorld->CreateBody(&tempDef);

		tempBody->SetUserData((void*)box1);

		tempPhsBody = PhysicsBody(tempBody, 1, 25, vec2(0.f, 0.f), false);

		unsigned int bitHolder = EntityIdentifier::TransformBit();
		ECS::SetUpIdentifier(box1, bitHolder, "Top Bottom Left Facing Box");
	}
	{
		auto box1 = ECS::CreateEntity();

		ECS::AttachComponent<Transform>(box1);
		ECS::AttachComponent<PhysicsBody>(box1);

		ECS::GetComponent<Transform>(box1).SetPosition(vec3(0.f, 0.f, 50.f));

		auto& tempPhsBody = ECS::GetComponent<PhysicsBody>(box1);

		b2Body* tempBody;
		b2BodyDef tempDef;
		tempDef.type = b2_staticBody;
		tempDef.position.Set(float32(-84.f), float32(-14.f));

		tempBody = m_physicsWorld->CreateBody(&tempDef);

		tempBody->SetUserData((void*)box1);

		tempPhsBody = PhysicsBody(tempBody, 1, 25, vec2(0.f, 0.f), false);

		unsigned int bitHolder = EntityIdentifier::TransformBit();
		ECS::SetUpIdentifier(box1, bitHolder, "Top Bottom Right Facing Box");
	}
	{
		auto box1 = ECS::CreateEntity();

		ECS::AttachComponent<Transform>(box1);
		ECS::AttachComponent<PhysicsBody>(box1);

		ECS::GetComponent<Transform>(box1).SetPosition(vec3(0.f, 0.f, 50.f));

		auto& tempPhsBody = ECS::GetComponent<PhysicsBody>(box1);

		b2Body* tempBody;
		b2BodyDef tempDef;
		tempDef.type = b2_staticBody;
		tempDef.position.Set(float32(-119.f), float32(-1.5f));

		tempBody = m_physicsWorld->CreateBody(&tempDef);

		tempBody->SetUserData((void*)box1);

		tempPhsBody = PhysicsBody(tempBody, 70, 1, vec2(0.f, 0.f), false);

		unsigned int bitHolder = EntityIdentifier::TransformBit() | EntityIdentifier::GroundBit();
		ECS::SetUpIdentifier(box1, bitHolder, "Top Bottom Top Ground Box");
	}
	{
		auto box1 = ECS::CreateEntity();

		ECS::AttachComponent<Transform>(box1);
		ECS::AttachComponent<PhysicsBody>(box1);

		ECS::GetComponent<Transform>(box1).SetPosition(vec3(0.f, 0.f, 50.f));

		auto& tempPhsBody = ECS::GetComponent<PhysicsBody>(box1);

		b2Body* tempBody;
		b2BodyDef tempDef;
		tempDef.type = b2_staticBody;
		tempDef.position.Set(float32(-119.f), float32(-26.5f));

		tempBody = m_physicsWorld->CreateBody(&tempDef);

		tempBody->SetUserData((void*)box1);

		tempPhsBody = PhysicsBody(tempBody, 70, 1, vec2(0.f, 0.f), false);

		unsigned int bitHolder = EntityIdentifier::TransformBit();
		ECS::SetUpIdentifier(box1, bitHolder, "Top Bottom Left Facing Box");
	}


#pragma endregion

#pragma region Map Layout
	//ELEVATORS
	{
		auto bluePlatform = File::LoadJSON("BluePlatform.json");

		auto entity = ECS::CreateEntity();

		ECS::AttachComponent<Sprite>(entity);
		ECS::AttachComponent<Transform>(entity);
		ECS::AttachComponent<AnimationController>(entity);
		ECS::AttachComponent<PhysicsBody>(entity);

		std::string fileName = "BluePlatformSS.png";

		auto& animController = ECS::GetComponent<AnimationController>(entity);
		animController.InitUVs(fileName);

		animController.AddAnimation(bluePlatform["PowerOff"]);
		animController.GetAnimation(0);
		animController.AddAnimation(bluePlatform["PowerOn"]);
		animController.GetAnimation(1);

		animController.SetActiveAnim(0);

		ECS::GetComponent<Sprite>(entity).LoadSprite(fileName, 42, 5, true, &animController);
		ECS::GetComponent<Transform>(entity).SetPosition(vec3(0.f, 0.f, 98.f));

		auto& tempSpr = ECS::GetComponent<Sprite>(entity);
		auto& tempPhsBody = ECS::GetComponent<PhysicsBody>(entity);

		float shrinkX = tempSpr.GetWidth() / 400.f;
		float shrinkY = tempSpr.GetWidth() / 400.f;

		b2Body* tempBody;
		b2BodyDef tempDef;
		tempDef.type = b2_kinematicBody;
		tempDef.position.Set(float32(-59.5f), float32(-74.f));

		tempBody = m_physicsWorld->CreateBody(&tempDef);

		tempBody->SetUserData((void*)entity);

		tempPhsBody = PhysicsBody(tempBody, float(tempSpr.GetWidth() - shrinkX), float(tempSpr.GetHeight() - shrinkY),
			vec2(0.f, 0.f), false);

		unsigned int bitHolder = EntityIdentifier::SpriteBit() | EntityIdentifier::TransformBit() | EntityIdentifier::AnimationBit() | EntityIdentifier::ElevatorBit();
		ECS::SetUpIdentifier(entity, bitHolder, "Elevator 1");

		m_elevator = entity;
	}

	{
		auto bluePlatform = File::LoadJSON("BluePlatform.json");

		auto entity = ECS::CreateEntity();

		ECS::AttachComponent<Sprite>(entity);
		ECS::AttachComponent<Transform>(entity);
		ECS::AttachComponent<AnimationController>(entity);
		ECS::AttachComponent<PhysicsBody>(entity);

		std::string fileName = "BluePlatformSS.png";

		auto& animController = ECS::GetComponent<AnimationController>(entity);
		animController.InitUVs(fileName);

		animController.AddAnimation(bluePlatform["PowerOff"]);
		animController.GetAnimation(0);
		animController.AddAnimation(bluePlatform["PowerOn"]);
		animController.GetAnimation(1);

		animController.SetActiveAnim(0);

		ECS::GetComponent<Sprite>(entity).LoadSprite(fileName, 42, 5, true, &animController);
		ECS::GetComponent<Transform>(entity).SetPosition(vec3(-107.5f, 1.f, 98.f));

		auto& tempSpr = ECS::GetComponent<Sprite>(entity);
		auto& tempPhsBody = ECS::GetComponent<PhysicsBody>(entity);

		float shrinkX = tempSpr.GetWidth() / 400.f;
		float shrinkY = tempSpr.GetWidth() / 400.f;

		b2Body* tempBody;
		b2BodyDef tempDef;
		tempDef.type = b2_kinematicBody;
		tempDef.position.Set(float32(-107.5f), float32(1.f));

		tempBody = m_physicsWorld->CreateBody(&tempDef);

		tempBody->SetUserData((void*)entity);

		tempPhsBody = PhysicsBody(tempBody, float(tempSpr.GetWidth() - shrinkX), float(tempSpr.GetHeight() - shrinkY),
			vec2(0.f, 0.f), false);

		unsigned int bitHolder = EntityIdentifier::SpriteBit() | EntityIdentifier::TransformBit() | EntityIdentifier::AnimationBit() | EntityIdentifier::ElevatorBit();
		ECS::SetUpIdentifier(entity, bitHolder, "Elevator 2");

		m_elevator2 = entity;
	}

	//BUTTONS
	{
		auto blueButton = File::LoadJSON("BlueButton.json");

		auto entity = ECS::CreateEntity();

		ECS::AttachComponent<Sprite>(entity);
		ECS::AttachComponent<Transform>(entity);
		ECS::AttachComponent<AnimationController>(entity);

		std::string fileName = "BlueButtonSS.png";

		auto& animController = ECS::GetComponent<AnimationController>(entity);
		animController.InitUVs(fileName);

		animController.AddAnimation(blueButton["ButtonPressFinal"]);
		animController.GetAnimation(0);
		animController.AddAnimation(blueButton["ButtonReleaseFinal"]);
		animController.GetAnimation(1);
		animController.SetActiveAnim(1);

		ECS::GetComponent<Sprite>(entity).LoadSprite(fileName, 26, 5, true, &animController);
		ECS::GetComponent<Transform>(entity).SetPosition(vec3(137.f, -9.5f, 100.f));

		unsigned int bitHolder = EntityIdentifier::SpriteBit() | EntityIdentifier::TransformBit() | EntityIdentifier::AnimationBit();
		ECS::SetUpIdentifier(entity, bitHolder, "Bottom Button Anim");

		m_button = entity;
	}
	{
		auto blueButton = File::LoadJSON("BlueButton.json");

		auto entity = ECS::CreateEntity();

		ECS::AttachComponent<Sprite>(entity);
		ECS::AttachComponent<Transform>(entity);
		ECS::AttachComponent<AnimationController>(entity);

		std::string fileName = "BlueButtonSS.png";

		auto& animController = ECS::GetComponent<AnimationController>(entity);
		animController.InitUVs(fileName);

		animController.AddAnimation(blueButton["ButtonPressFinal"]);
		animController.GetAnimation(0);
		animController.AddAnimation(blueButton["ButtonReleaseFinal"]);
		animController.GetAnimation(1);
		animController.SetActiveAnim(1);

		ECS::GetComponent<Sprite>(entity).LoadSprite(fileName, 26, 5, true, &animController);
		ECS::GetComponent<Transform>(entity).SetPosition(vec3(116.f, 66.f, 100.f));

		unsigned int bitHolder = EntityIdentifier::SpriteBit() | EntityIdentifier::TransformBit() | EntityIdentifier::AnimationBit();
		ECS::SetUpIdentifier(entity, bitHolder, "Top Button Anim");

		m_button2 = entity;
	}

	//Button Bodies
	{
		auto entity = ECS::CreateEntity();

		ECS::AttachComponent<Transform>(entity);
		ECS::AttachComponent<PhysicsBody>(entity);

		ECS::GetComponent<Transform>(entity).SetPosition(vec3(0.f, 0.f, 100.f));

		auto& tempPhsBody = ECS::GetComponent<PhysicsBody>(entity);

		b2Body* tempBody;
		b2BodyDef tempDef;
		tempDef.type = b2_staticBody;
		tempDef.position.Set(float32(128.f), float32(-9.5f));

		tempBody = m_physicsWorld->CreateBody(&tempDef);
		tempBody->SetUserData((void*)entity);

		tempPhsBody = PhysicsBody(tempBody, 1, 5, vec2(0.f, 0.f), false);

		unsigned int bitHolder = EntityIdentifier::TransformBit();
		ECS::SetUpIdentifier(entity, bitHolder, "Left Side of Button1");
	}
	{
		auto entity = ECS::CreateEntity();

		ECS::AttachComponent<Transform>(entity);
		ECS::AttachComponent<PhysicsBody>(entity);

		ECS::GetComponent<Transform>(entity).SetPosition(vec3(0.f, 0.f, 100.f));

		auto& tempPhsBody = ECS::GetComponent<PhysicsBody>(entity);

		b2Body* tempBody;
		b2BodyDef tempDef;
		tempDef.type = b2_staticBody;
		tempDef.position.Set(float32(146.f), float32(-9.5f));

		tempBody = m_physicsWorld->CreateBody(&tempDef);
		tempBody->SetUserData((void*)entity);

		tempPhsBody = PhysicsBody(tempBody, 1, 5, vec2(0.f, 0.f), false);

		unsigned int bitHolder = EntityIdentifier::TransformBit();
		ECS::SetUpIdentifier(entity, bitHolder, "Right Side of Button1");
	}
	{
		auto entity = ECS::CreateEntity();

		ECS::AttachComponent<Transform>(entity);
		ECS::AttachComponent<PhysicsBody>(entity);

		ECS::GetComponent<Transform>(entity).SetPosition(vec3(0.f, 0.f, 100.f));

		auto& tempPhsBody = ECS::GetComponent<PhysicsBody>(entity);

		b2Body* tempBody;
		b2BodyDef tempDef;
		tempDef.type = b2_staticBody;
		tempDef.position.Set(float32(137.f), float32(-7.f));

		tempBody = m_physicsWorld->CreateBody(&tempDef);
		tempBody->SetUserData((void*)entity);

		tempPhsBody = PhysicsBody(tempBody, 18, 1, vec2(0.f, 0.f), false);

		unsigned int bitHolder = EntityIdentifier::TransformBit() | EntityIdentifier::BlueButtonBit();
		ECS::SetUpIdentifier(entity, bitHolder, "Top of Button1");
	}
	{
		auto entity = ECS::CreateEntity();

		ECS::AttachComponent<Transform>(entity);
		ECS::AttachComponent<PhysicsBody>(entity);

		ECS::GetComponent<Transform>(entity).SetPosition(vec3(0.f, 0.f, 100.f));

		auto& tempPhsBody = ECS::GetComponent<PhysicsBody>(entity);

		b2Body* tempBody;
		b2BodyDef tempDef;
		tempDef.type = b2_staticBody;
		tempDef.position.Set(float32(107.f), float32(66.f));

		tempBody = m_physicsWorld->CreateBody(&tempDef);
		tempBody->SetUserData((void*)entity);

		tempPhsBody = PhysicsBody(tempBody, 1, 5, vec2(0.f, 0.f), false);

		unsigned int bitHolder = EntityIdentifier::TransformBit();
		ECS::SetUpIdentifier(entity, bitHolder, "Left Side of Button 2");
	}
	{
		auto entity = ECS::CreateEntity();

		ECS::AttachComponent<Transform>(entity);
		ECS::AttachComponent<PhysicsBody>(entity);

		ECS::GetComponent<Transform>(entity).SetPosition(vec3(0.f, 0.f, 100.f));

		auto& tempPhsBody = ECS::GetComponent<PhysicsBody>(entity);

		b2Body* tempBody;
		b2BodyDef tempDef;
		tempDef.type = b2_staticBody;
		tempDef.position.Set(float32(125.f), float32(66.f));

		tempBody = m_physicsWorld->CreateBody(&tempDef);
		tempBody->SetUserData((void*)entity);

		tempPhsBody = PhysicsBody(tempBody, 1, 5, vec2(0.f, 0.f), false);

		unsigned int bitHolder = EntityIdentifier::TransformBit();
		ECS::SetUpIdentifier(entity, bitHolder, "Right Side of Button 2");
	}
	{
		auto entity = ECS::CreateEntity();

		ECS::AttachComponent<Transform>(entity);
		ECS::AttachComponent<PhysicsBody>(entity);

		ECS::GetComponent<Transform>(entity).SetPosition(vec3(0.f, 0.f, 100.f));

		auto& tempPhsBody = ECS::GetComponent<PhysicsBody>(entity);

		b2Body* tempBody;
		b2BodyDef tempDef;
		tempDef.type = b2_staticBody;
		tempDef.position.Set(float32(116.f), float32(68.5f));

		tempBody = m_physicsWorld->CreateBody(&tempDef);
		tempBody->SetUserData((void*)entity);

		tempPhsBody = PhysicsBody(tempBody, 18, 1, vec2(0.f, 0.f), false);

		unsigned int bitHolder = EntityIdentifier::TransformBit() | EntityIdentifier::BlueButton2Bit();
		ECS::SetUpIdentifier(entity, bitHolder, "Top of Button 2");
	}

	//JELLO
	{
		auto jelloAnim = File::LoadJSON("Jello.json");

		auto entity = ECS::CreateEntity();

		ECS::AttachComponent<Sprite>(entity);
		ECS::AttachComponent<Transform>(entity);
		ECS::AttachComponent<AnimationController>(entity);

		std::string fileName = "JelloSS.png";

		auto& animController = ECS::GetComponent<AnimationController>(entity);
		animController.InitUVs(fileName);

		animController.AddAnimation(jelloAnim["Bounce"]);
		animController.GetAnimation(0);
		animController.SetActiveAnim(0);

		ECS::GetComponent<Sprite>(entity).LoadSprite(fileName, 73, 16, true, &animController);
		ECS::GetComponent<Transform>(entity).SetPosition(vec3(24.f, -92.5f, 98.f));

		unsigned int bitHolder = EntityIdentifier::SpriteBit() | EntityIdentifier::TransformBit() | EntityIdentifier::AnimationBit();
		ECS::SetUpIdentifier(entity, bitHolder, "Jello Anim");

		m_jello = entity;
	}

	//Jello Bodies
	{
		auto entity = ECS::CreateEntity();

		ECS::AttachComponent<Transform>(entity);
		ECS::AttachComponent<PhysicsBody>(entity);

		ECS::GetComponent<Transform>(entity).SetPosition(vec3(0.f, 0.f, 100.f));

		auto& tempPhsBody = ECS::GetComponent<PhysicsBody>(entity);

		b2Body* tempBody;
		b2BodyDef tempDef;
		tempDef.type = b2_kinematicBody;
		tempDef.position.Set(float32(24.f), float32(-86.f));

		tempBody = m_physicsWorld->CreateBody(&tempDef);
		tempBody->SetUserData((void*)entity);

		tempPhsBody = PhysicsBody(tempBody, 70, 1, vec2(0.f, 0.f), false);

		unsigned int bitHolder = EntityIdentifier::TransformBit() | EntityIdentifier::JelloBit();
		ECS::SetUpIdentifier(entity, bitHolder, "Top of Jello");
	}
	{
		auto entity = ECS::CreateEntity();

		ECS::AttachComponent<Transform>(entity);
		ECS::AttachComponent<PhysicsBody>(entity);

		ECS::GetComponent<Transform>(entity).SetPosition(vec3(0.f, 0.f, 100.f));

		auto& tempPhsBody = ECS::GetComponent<PhysicsBody>(entity);

		b2Body* tempBody;
		b2BodyDef tempDef;
		tempDef.type = b2_staticBody;
		tempDef.position.Set(float32(-11.f), float32(-94.f));

		tempBody = m_physicsWorld->CreateBody(&tempDef);
		tempBody->SetUserData((void*)entity);

		tempPhsBody = PhysicsBody(tempBody, 1, 15, vec2(0.f, 0.f), false);

		unsigned int bitHolder = EntityIdentifier::TransformBit();
		ECS::SetUpIdentifier(entity, bitHolder, "Left of Jello");
	}

	//Fruit Bowl
	{
		auto entity = ECS::CreateEntity();

		ECS::AttachComponent<Sprite>(entity);
		ECS::AttachComponent<Transform>(entity);
		ECS::AttachComponent<PhysicsBody>(entity);

		std::string fileName = "FruitBowl.png";

		ECS::GetComponent<Sprite>(entity).LoadSprite(fileName, 50.7692307694, 36.6666666667);
		ECS::GetComponent<Transform>(entity).SetPosition(vec3(0.f, 0.f, 100.f));

		auto& tempSpr = ECS::GetComponent<Sprite>(entity);
		auto& tempPhsBody = ECS::GetComponent<PhysicsBody>(entity);

		float shrinkX = tempSpr.GetWidth() / 100.f;
		float shrinkY = tempSpr.GetWidth() / 100.f;

		b2Body* tempBody;
		b2BodyDef tempDef;
		tempDef.type = b2_staticBody;
		tempDef.position.Set(float32(155.f), float32(81.f));

		tempBody = m_physicsWorld->CreateBody(&tempDef);

		tempBody->SetUserData((void*)entity);


		tempPhsBody = PhysicsBody(tempBody, float(tempSpr.GetWidth() - 15), float(tempSpr.GetHeight() / 4),
			vec2(0.f, -15.f), false);

		unsigned int bitHolder = EntityIdentifier::SpriteBit() | EntityIdentifier::TransformBit() | EntityIdentifier::FruitBowlBit();
		ECS::SetUpIdentifier(entity, bitHolder, "Bowl");
	}
#pragma endregion
}

//GETTERS
int LevelThree::GetCam()
{
	return m_cam;
}
int LevelThree::GetButton()
{
	return m_button;
}
int LevelThree::GetButton2()
{
	return m_button2;
}
int LevelThree::GetElevator()
{
	return m_elevator;
}
int LevelThree::GetElevator2()
{
	return m_elevator2;
}
int LevelThree::GetBackground()
{
	return m_background;
}
int LevelThree::GetBackground2()
{
	return m_background2;
}
bool LevelThree::GetButtonOn1()
{
	return turnOn1;
}
bool LevelThree::GetButtonOn2()
{
	return turnOn2;
}

int LevelThree::GetJello()
{
	return m_jello;
}

bool LevelThree::GetJelloBounce()
{
	return turnJello;
}