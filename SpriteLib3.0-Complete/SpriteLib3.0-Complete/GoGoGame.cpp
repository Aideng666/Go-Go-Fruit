#include "GoGoGame.h"
#include <iostream>

//LEVEL 1

GoGoGame::GoGoGame(std::string name)
	: Scene(name)
{
	m_gravity = b2Vec2(float32(0.f), float32(-9.f));
	m_physicsWorld->SetGravity(m_gravity);
}

void GoGoGame::InitScene(float windowWidth, float windowHeight)
{
	m_sceneReg = new entt::registry;

	ECS::AttachRegister(m_sceneReg);

	float aspectRatio = windowWidth / windowHeight;

	//sndPlaySound("BGM.wav", SND_FILENAME | SND_ASYNC | SND_LOOP);
	
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

#pragma region Aesthetics + Environment
	//Aesthetics
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

		m_background = entity;

		auto entity2 = ECS::CreateEntity();
		ECS::AttachComponent<Sprite>(entity2);
		ECS::AttachComponent<Transform>(entity2);
		ECS::GetComponent<Sprite>(entity2).LoadSprite(fileName, 360, 360);
		ECS::GetComponent<Transform>(entity2).SetPosition(vec3(360.f, -80.f, 10.f));
		unsigned int bitHolder2 = EntityIdentifier::SpriteBit() | EntityIdentifier::TransformBit();
		ECS::SetUpIdentifier(entity2, bitHolder2, "Sky Background 2");

		m_background2 = entity2;
	}

	//Ground Layout
	{
		auto entity = ECS::CreateEntity();

		ECS::AttachComponent<Sprite>(entity);
		ECS::AttachComponent<Transform>(entity);

		std::string fileName = "Level1.png";

		ECS::GetComponent<Sprite>(entity).LoadSprite(fileName, 357, 212.7125);
		ECS::GetComponent<Transform>(entity).SetPosition(vec3(0.f, 6.f, 20.f));

		unsigned int bitHolder = EntityIdentifier::SpriteBit() | EntityIdentifier::TransformBit();
		ECS::SetUpIdentifier(entity, bitHolder, "Level 1");
	}

	//Flowers
	{
		auto flowerAnim = File::LoadJSON("Flowers.json");
		std::string fileName = "Flowers.png";

		auto entity = ECS::CreateEntity();
		ECS::AttachComponent<Sprite>(entity);
		ECS::AttachComponent<Transform>(entity);
		ECS::AttachComponent<AnimationController>(entity);
		auto& animController = ECS::GetComponent<AnimationController>(entity);
		animController.InitUVs(fileName);
		animController.AddAnimation(flowerAnim["FlowerSway"]);
		animController.GetAnimation(0);
		animController.SetActiveAnim(0);
		ECS::GetComponent<Sprite>(entity).LoadSprite(fileName, 30, 14, true, &animController);
		ECS::GetComponent<Transform>(entity).SetPosition(vec3(-74.f, -82.f, 70.f));
		unsigned int bitHolder = EntityIdentifier::SpriteBit() | EntityIdentifier::TransformBit() | EntityIdentifier::AnimationBit();
		ECS::SetUpIdentifier(entity, bitHolder, "Flower Anim 1");

		auto entity2 = ECS::CreateEntity();
		ECS::AttachComponent<Sprite>(entity2);
		ECS::AttachComponent<Transform>(entity2);
		ECS::AttachComponent<AnimationController>(entity2);
		auto& animController2 = ECS::GetComponent<AnimationController>(entity2);
		animController2.InitUVs(fileName);
		animController2.AddAnimation(flowerAnim["FlowerSway"]);
		animController2.GetAnimation(0);
		animController2.SetActiveAnim(0);
		ECS::GetComponent<Sprite>(entity2).LoadSprite(fileName, 30, 14, true, &animController2);
		ECS::GetComponent<Transform>(entity2).SetPosition(vec3(100.f, 13.f, 70.f));
		unsigned int bitHolder2 = EntityIdentifier::SpriteBit() | EntityIdentifier::TransformBit() | EntityIdentifier::AnimationBit();
		ECS::SetUpIdentifier(entity2, bitHolder2, "Flower Anim 2");

		auto entity3 = ECS::CreateEntity();
		ECS::AttachComponent<Sprite>(entity3);
		ECS::AttachComponent<Transform>(entity3);
		ECS::AttachComponent<AnimationController>(entity3);
		auto& animController3 = ECS::GetComponent<AnimationController>(entity3);
		animController3.InitUVs(fileName);
		animController3.AddAnimation(flowerAnim["FlowerSway"]);
		animController3.GetAnimation(0);
		animController3.SetActiveAnim(0);
		ECS::GetComponent<Sprite>(entity3).LoadSprite(fileName, 30, 14, true, &animController3);
		ECS::GetComponent<Transform>(entity3).SetPosition(vec3(50.5f, 13.f, 70.f));
		unsigned int bitHolder3 = EntityIdentifier::SpriteBit() | EntityIdentifier::TransformBit() | EntityIdentifier::AnimationBit();
		ECS::SetUpIdentifier(entity3, bitHolder3, "Flower Anim 3");
	}

	//Grass
	{
		auto grassAnim = File::LoadJSON("Grass.json");
		std::string fileName = "GrassV2.png";

		auto entity2 = ECS::CreateEntity();
		ECS::AttachComponent<Sprite>(entity2);
		ECS::AttachComponent<Transform>(entity2);
		ECS::AttachComponent<AnimationController>(entity2);
		auto& animController2 = ECS::GetComponent<AnimationController>(entity2);
		animController2.InitUVs(fileName);
		animController2.AddAnimation(grassAnim["GrassSway"]);
		animController2.GetAnimation(0);
		animController2.SetActiveAnim(0);
		ECS::GetComponent<Sprite>(entity2).LoadSprite(fileName, 50, 7, true, &animController2);
		ECS::GetComponent<Transform>(entity2).SetPosition(vec3(-166.f, -85.f, 70.f));
		unsigned int bitHolder2 = EntityIdentifier::SpriteBit() | EntityIdentifier::TransformBit() | EntityIdentifier::AnimationBit();
		ECS::SetUpIdentifier(entity2, bitHolder2, "Grass Anim 1");

		auto entity3 = ECS::CreateEntity();
		ECS::AttachComponent<Sprite>(entity3);
		ECS::AttachComponent<Transform>(entity3);
		ECS::AttachComponent<AnimationController>(entity3);
		auto& animController3 = ECS::GetComponent<AnimationController>(entity3);
		animController3.InitUVs(fileName);
		animController3.AddAnimation(grassAnim["GrassSway"]);
		animController3.GetAnimation(0);
		animController3.SetActiveAnim(0);
		ECS::GetComponent<Sprite>(entity3).LoadSprite(fileName, 50, 7, true, &animController3);
		ECS::GetComponent<Transform>(entity3).SetPosition(vec3(-34.f, -61.f, 70.f));
		unsigned int bitHolder3 = EntityIdentifier::SpriteBit() | EntityIdentifier::TransformBit() | EntityIdentifier::AnimationBit();
		ECS::SetUpIdentifier(entity3, bitHolder3, "Grass Anim 2");

		auto entity4 = ECS::CreateEntity();
		ECS::AttachComponent<Sprite>(entity4);
		ECS::AttachComponent<Transform>(entity4);
		ECS::AttachComponent<AnimationController>(entity4);
		auto& animController4 = ECS::GetComponent<AnimationController>(entity4);
		animController4.InitUVs(fileName);
		animController4.AddAnimation(grassAnim["GrassSway"]);
		animController4.GetAnimation(0);
		animController4.SetActiveAnim(0);
		ECS::GetComponent<Sprite>(entity4).LoadSprite(fileName, 50, 7, true, &animController4);
		ECS::GetComponent<Transform>(entity4).SetPosition(vec3(-114.f, -85.f, 70.f));
		unsigned int bitHolder4 = EntityIdentifier::SpriteBit() | EntityIdentifier::TransformBit() | EntityIdentifier::AnimationBit();
		ECS::SetUpIdentifier(entity4, bitHolder4, "Grass Anim 3");

		auto entity5 = ECS::CreateEntity();
		ECS::AttachComponent<Sprite>(entity5);
		ECS::AttachComponent<Transform>(entity5);
		ECS::AttachComponent<AnimationController>(entity5);
		auto& animController5 = ECS::GetComponent<AnimationController>(entity5);
		animController5.InitUVs(fileName);
		animController5.AddAnimation(grassAnim["GrassSway"]);
		animController5.GetAnimation(0);
		animController5.SetActiveAnim(0);
		ECS::GetComponent<Sprite>(entity5).LoadSprite(fileName, 50, 7, true, &animController5);
		ECS::GetComponent<Transform>(entity5).SetPosition(vec3(153.f, 9.f, 70.f));
		unsigned int bitHolder5 = EntityIdentifier::SpriteBit() | EntityIdentifier::TransformBit() | EntityIdentifier::AnimationBit();
		ECS::SetUpIdentifier(entity5, bitHolder5, "Grass Anim 4");
	}
#pragma endregion
	
#pragma region PLAYER ENTITIES
	//Blueberry
	{
		auto blueberryAnim = File::LoadJSON("Blueberry.json");

		auto entity = ECS::CreateEntity();

		ECS::SetIsMainPlayer(entity, true);
		EntityIdentifier::MainPlayer(entity);

		ECS::AttachComponent<Sprite>(entity);
		ECS::AttachComponent<Transform>(entity);
		ECS::AttachComponent<PhysicsBody>(entity);
		ECS::AttachComponent<AnimationController>(entity);

		std::string fileName = "BlueberrySS.png";

		auto& animController = ECS::GetComponent<AnimationController>(entity);
		animController.InitUVs(fileName);

		animController.AddAnimation(blueberryAnim["WalkLeft"]);
		animController.GetAnimation(0);
		animController.AddAnimation(blueberryAnim["WalkRight"]);
		animController.GetAnimation(1);
		animController.SetActiveAnim(1);

		ECS::GetComponent<Sprite>(entity).LoadSprite(fileName, 40.f, 34.f, true, &animController);
		ECS::GetComponent<Transform>(entity).SetPosition(vec3(-100.f, 50.f, 99.f));

		auto& tempSpr = ECS::GetComponent<Sprite>(entity);
		auto& tempPhsBody = ECS::GetComponent<PhysicsBody>(entity);

		float shrinkX = tempSpr.GetWidth() / 40.f + 26;
		float shrinkY = tempSpr.GetWidth() / 34.f + 18;

		b2Body* tempBody;
		b2BodyDef tempDef;
		tempDef.type = b2_dynamicBody;
		tempDef.position.Set(float32(-120.f), float32(-85.f));

		tempBody = m_physicsWorld->CreateBody(&tempDef);
		tempBody->SetFixedRotation(true);
		tempBody->SetUserData((void*)entity);

		tempPhsBody = PhysicsBody(tempBody, float(tempSpr.GetWidth() - shrinkX), float(tempSpr.GetHeight() - shrinkY),
			vec2(1.f, -9.f), false);

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

		ECS::GetComponent<Sprite>(entity).LoadSprite(fileName, 35.f, 35.f, true, &animController);
		ECS::GetComponent<Transform>(entity).SetPosition(vec3(-160.f, 60.f, 99.f));

		auto& tempSpr = ECS::GetComponent<Sprite>(entity);
		auto& tempPhsBody = ECS::GetComponent<PhysicsBody>(entity);

		float shrinkX = tempSpr.GetWidth() / 35.f + 20;
		float shrinkY = tempSpr.GetWidth() / 35.f + 14;

		b2Body* tempBody;
		b2BodyDef tempDef;
		tempDef.type = b2_dynamicBody;
		tempDef.position.Set(float32(-150.f), float32(-85.f));

		tempBody = m_physicsWorld->CreateBody(&tempDef);
		tempBody->SetFixedRotation(true);
		tempBody->SetUserData((void*)entity);

		tempPhsBody = PhysicsBody(tempBody, float(tempSpr.GetWidth() - shrinkX), float(tempSpr.GetHeight() - shrinkY),
			vec2(0.f, -7.f), false);

		tempPhsBody.SetFriction(0.15f);
		tempPhsBody.SetMaxVelo(60.f);
		tempPhsBody.SetGravity(true);

		unsigned int bitHolder = EntityIdentifier::SpriteBit() | EntityIdentifier::TransformBit() | EntityIdentifier::WatermelonBit() | 
			EntityIdentifier::AnimationBit();
		ECS::SetUpIdentifier(entity, bitHolder, "Watermelon");
	}
#pragma endregion

#pragma region Physics Bodies
	//Ground Boxes
	{
		auto box1 = ECS::CreateEntity();
		
		ECS::AttachComponent<Transform>(box1);
		ECS::AttachComponent<PhysicsBody>(box1);

		ECS::GetComponent<Transform>(box1).SetPosition(vec3(0.f, 0.f, 50.f));

		auto& tempPhsBody = ECS::GetComponent<PhysicsBody>(box1);

		b2Body* tempBody;
		b2BodyDef tempDef;
		tempDef.type = b2_staticBody;
		tempDef.position.Set(float32(0.f), float32(-95.f));

		tempBody = m_physicsWorld->CreateBody(&tempDef);

		tempBody->SetUserData((void*)box1);

		tempPhsBody = PhysicsBody(tempBody, 360, 12, vec2(0.f, 0.f), false);

		unsigned int bitHolder = EntityIdentifier::TransformBit() | EntityIdentifier::GroundBit();
		ECS::SetUpIdentifier(box1, bitHolder, "Lower Ground Box");	
	}

	{
		auto box2 = ECS::CreateEntity();

		ECS::AttachComponent<Transform>(box2);
		ECS::AttachComponent<PhysicsBody>(box2);

		ECS::GetComponent<Transform>(box2).SetPosition(vec3(0.f, 0.f, 50.f));

		auto& tempPhsBody = ECS::GetComponent<PhysicsBody>(box2);

		b2Body* tempBody;
		b2BodyDef tempDef;
		tempDef.type = b2_staticBody;
		tempDef.position.Set(float32(-59.f), float32(-80.f));

		tempBody = m_physicsWorld->CreateBody(&tempDef);

		tempBody->SetUserData((void*)box2);

		tempPhsBody = PhysicsBody(tempBody, 1, 30, vec2(0.f, 0.f), false);

		unsigned int bitHolder = EntityIdentifier::TransformBit();
		ECS::SetUpIdentifier(box2, bitHolder, "Lower Facing Box");
	}

	{
		auto box2 = ECS::CreateEntity();

		ECS::AttachComponent<Transform>(box2);
		ECS::AttachComponent<PhysicsBody>(box2);

		ECS::GetComponent<Transform>(box2).SetPosition(vec3(0.f, 0.f, 50.f));

		auto& tempPhsBody = ECS::GetComponent<PhysicsBody>(box2);

		b2Body* tempBody;
		b2BodyDef tempDef;
		tempDef.type = b2_staticBody;
		tempDef.position.Set(float32(62.f), float32(-75.f));

		tempBody = m_physicsWorld->CreateBody(&tempDef);

		tempBody->SetUserData((void*)box2);

		tempPhsBody = PhysicsBody(tempBody, 240, 20, vec2(0.f, 0.f), false);

		unsigned int bitHolder = EntityIdentifier::TransformBit() | EntityIdentifier::GroundBit();
		ECS::SetUpIdentifier(box2, bitHolder, "Middle Ground Box");
	}

	{
		auto box2 = ECS::CreateEntity();

		ECS::AttachComponent<Transform>(box2);
		ECS::AttachComponent<PhysicsBody>(box2);

		ECS::GetComponent<Transform>(box2).SetPosition(vec3(0.f, 0.f, 50.f));

		auto& tempPhsBody = ECS::GetComponent<PhysicsBody>(box2);

		b2Body* tempBody;
		b2BodyDef tempDef;
		tempDef.type = b2_staticBody;
		tempDef.position.Set(float32(36.f), float32(-33.f));

		tempBody = m_physicsWorld->CreateBody(&tempDef);

		tempBody->SetUserData((void*)box2);

		tempPhsBody = PhysicsBody(tempBody, 1, 79, vec2(0.f, 0.f), false);

		unsigned int bitHolder = EntityIdentifier::TransformBit();
		ECS::SetUpIdentifier(box2, bitHolder, "Middle Facing Box");
	}

	{
		auto box4 = ECS::CreateEntity();

		ECS::AttachComponent<Transform>(box4);
		ECS::AttachComponent<PhysicsBody>(box4);
		ECS::GetComponent<Transform>(box4).SetPosition(vec3(0.f, 0.f, 50.f));

		auto& tempPhsBody = ECS::GetComponent<PhysicsBody>(box4);

		b2Body* tempBody;
		b2BodyDef tempDef;
		tempDef.type = b2_staticBody;
		tempDef.position.Set(float32(111.f), float32(6.f));

		tempBody = m_physicsWorld->CreateBody(&tempDef);

		tempBody->SetUserData((void*)box4);

		tempPhsBody = PhysicsBody(tempBody, 150, 1, vec2(0.f, 0.f), false);

		unsigned int bitHolder = EntityIdentifier::TransformBit() | EntityIdentifier::GroundBit();
		ECS::SetUpIdentifier(box4, bitHolder, "Top Ground Box");
	}
#pragma endregion

#pragma region BARRIERS
	//BARRIERS
	//Top Wall
	{
		auto entity = ECS::CreateEntity();

		ECS::AttachComponent<Transform>(entity);
		ECS::AttachComponent<PhysicsBody>(entity);

		ECS::GetComponent<Transform>(entity).SetPosition(vec3(0.f, 0.f, 100.f));

		auto& tempPhsBody = ECS::GetComponent<PhysicsBody>(entity);

		b2Body* tempBody;
		b2BodyDef tempDef;
		tempDef.type = b2_staticBody;
		tempDef.position.Set(float32(0.f), float32(102));

		tempBody = m_physicsWorld->CreateBody(&tempDef);
		tempBody->SetUserData((void*)entity);

		tempPhsBody = PhysicsBody(tempBody, 400, 5, vec2(0.f, 0.f), false);

		unsigned int bitHolder = EntityIdentifier::TransformBit();
		ECS::SetUpIdentifier(entity, bitHolder, "Top Wall");
	}
	//Left Wall
	{
		auto entity = ECS::CreateEntity();

		ECS::AttachComponent<Transform>(entity);
		ECS::AttachComponent<PhysicsBody>(entity);

		ECS::GetComponent<Transform>(entity).SetPosition(vec3(0.f, 0.f, 100.f));

		auto& tempPhsBody = ECS::GetComponent<PhysicsBody>(entity);

		b2Body* tempBody;
		b2BodyDef tempDef;
		tempDef.type = b2_staticBody;
		tempDef.position.Set(float32(-180.f), float32(0));

		tempBody = m_physicsWorld->CreateBody(&tempDef);
		tempBody->SetUserData((void*)entity);

		tempPhsBody = PhysicsBody(tempBody, 5, 400, vec2(0.f, 0.f), false);

		unsigned int bitHolder = EntityIdentifier::TransformBit();
		ECS::SetUpIdentifier(entity, bitHolder, "Left Wall");
	}
	//Right Wall
	{
		auto entity = ECS::CreateEntity();

		ECS::AttachComponent<Transform>(entity);
		ECS::AttachComponent<PhysicsBody>(entity);

		ECS::GetComponent<Transform>(entity).SetPosition(vec3(0.f, -0.f, 100.f));

		auto& tempPhsBody = ECS::GetComponent<PhysicsBody>(entity);

		b2Body* tempBody;
		b2BodyDef tempDef;
		tempDef.type = b2_staticBody;
		tempDef.position.Set(float32(180.f), float32(0));

		tempBody = m_physicsWorld->CreateBody(&tempDef);
		tempBody->SetUserData((void*)entity);

		tempPhsBody = PhysicsBody(tempBody, 5, 400, vec2(0.f, 0.f), false);

		unsigned int bitHolder = EntityIdentifier::TransformBit();
		ECS::SetUpIdentifier(entity, bitHolder, "Right Wall");
	}
#pragma endregion

#pragma region MAP LAYOUT
	//PLATFORMS
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

		ECS::GetComponent<Sprite>(entity).LoadSprite(fileName, 44, 5, true, &animController);
		ECS::GetComponent<Transform>(entity).SetPosition(vec3(0.f, 0.f, 98.f));

		auto& tempSpr = ECS::GetComponent<Sprite>(entity);
		auto& tempPhsBody = ECS::GetComponent<PhysicsBody>(entity);

		float shrinkX = tempSpr.GetWidth() / 400.f;
		float shrinkY = tempSpr.GetWidth() / 400.f;

		b2Body* tempBody;
		b2BodyDef tempDef;
		tempDef.type = b2_kinematicBody;
		tempDef.position.Set(float32(13.5f), float32(-62.f));

		tempBody = m_physicsWorld->CreateBody(&tempDef);

		tempBody->SetUserData((void*)entity);

		tempPhsBody = PhysicsBody(tempBody, float(tempSpr.GetWidth()), float(tempSpr.GetHeight()),
			vec2(0.f, 0.f), false);

		unsigned int bitHolder = EntityIdentifier::SpriteBit() | EntityIdentifier::TransformBit() | EntityIdentifier::AnimationBit() | EntityIdentifier::BlueElevatorBit();
		ECS::SetUpIdentifier(entity, bitHolder, "Platform Anim");

		m_elevator = entity;
	}
	//Button
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
		ECS::GetComponent<Transform>(entity).SetPosition(vec3(75.f, 9.f, 100.f));

		unsigned int bitHolder = EntityIdentifier::SpriteBit() | EntityIdentifier::TransformBit() | EntityIdentifier::AnimationBit();
		ECS::SetUpIdentifier(entity, bitHolder, "Button Anim");

		m_button = entity;
	}
	//Button Hitboxes
	{
		auto entity = ECS::CreateEntity();

		ECS::AttachComponent<Transform>(entity);
		ECS::AttachComponent<PhysicsBody>(entity);

		ECS::GetComponent<Transform>(entity).SetPosition(vec3(0.f, 0.f, 100.f));

		auto& tempPhsBody = ECS::GetComponent<PhysicsBody>(entity);

		b2Body* tempBody;
		b2BodyDef tempDef;
		tempDef.type = b2_staticBody;
		tempDef.position.Set(float32(66.f), float32(9));

		tempBody = m_physicsWorld->CreateBody(&tempDef);
		tempBody->SetUserData((void*)entity);

		tempPhsBody = PhysicsBody(tempBody, 1, 5, vec2(0.f, 0.f), false);

		unsigned int bitHolder = EntityIdentifier::TransformBit();
		ECS::SetUpIdentifier(entity, bitHolder, "Left Side of Button");
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
		tempDef.position.Set(float32(84.f), float32(9));

		tempBody = m_physicsWorld->CreateBody(&tempDef);
		tempBody->SetUserData((void*)entity);

		tempPhsBody = PhysicsBody(tempBody, 1, 5, vec2(0.f, 0.f), false);

		unsigned int bitHolder = EntityIdentifier::TransformBit();
		ECS::SetUpIdentifier(entity, bitHolder, "Right Side of Button");
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
		tempDef.position.Set(float32(75.f), float32(11.5));

		tempBody = m_physicsWorld->CreateBody(&tempDef);
		tempBody->SetUserData((void*)entity);

		tempPhsBody = PhysicsBody(tempBody, 18, 1, vec2(0.f, 0.f), false);

		unsigned int bitHolder = EntityIdentifier::TransformBit() | EntityIdentifier::BlueButtonBit();
		ECS::SetUpIdentifier(entity, bitHolder, "Top of Button");
	}
	
	//Fruit Bowl Anim
	{
		auto fruitBowlAnim = File::LoadJSON("SaladBowl.json");

		auto entity = ECS::CreateEntity();

		ECS::AttachComponent<Sprite>(entity);
		ECS::AttachComponent<Transform>(entity);
		ECS::AttachComponent<AnimationController>(entity);

		std::string fileName = "FruitBowlSS.png";

		auto& animController = ECS::GetComponent<AnimationController>(entity);
		animController.InitUVs(fileName);

		animController.AddAnimation(fruitBowlAnim["Smile"]);
		animController.GetAnimation(0);
		animController.AddAnimation(fruitBowlAnim["Shine"]);
		animController.GetAnimation(1);
		animController.SetActiveAnim(1);

		ECS::GetComponent<Sprite>(entity).LoadSprite(fileName, 52, 30, true, &animController);
		ECS::GetComponent<Transform>(entity).SetPosition(vec3(140.f, 21.f, 100.f));

		unsigned int bitHolder = EntityIdentifier::SpriteBit() | EntityIdentifier::TransformBit() | EntityIdentifier::AnimationBit();
		ECS::SetUpIdentifier(entity, bitHolder, "Fruit Bowl Anim");

		m_fruitBowl = entity;
	}

	//Fruit Bowl Bodies
	{
		auto entity = ECS::CreateEntity();

		ECS::AttachComponent<Transform>(entity);
		ECS::AttachComponent<PhysicsBody>(entity);

		ECS::GetComponent<Transform>(entity).SetPosition(vec3(0.f, 0.f, 100.f));

		auto& tempPhsBody = ECS::GetComponent<PhysicsBody>(entity);

		b2Body* tempBody;
		b2BodyDef tempDef;
		tempDef.type = b2_staticBody;
		tempDef.position.Set(float32(139.f), float32(17.f));

		tempBody = m_physicsWorld->CreateBody(&tempDef);
		tempBody->SetUserData((void*)entity);

		tempPhsBody = PhysicsBody(tempBody, 48, 1, vec2(0.f, 0.f), false);

		unsigned int bitHolder = EntityIdentifier::TransformBit() | EntityIdentifier::FruitBowlBit();
		ECS::SetUpIdentifier(entity, bitHolder, "Top of Fruit Bowl");
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
		tempDef.position.Set(float32(115.f), float32(10.f));

		tempBody = m_physicsWorld->CreateBody(&tempDef);
		tempBody->SetUserData((void*)entity);

		tempPhsBody = PhysicsBody(tempBody, 1, 14, vec2(0.f, 0.f), false);

		unsigned int bitHolder = EntityIdentifier::TransformBit();
		ECS::SetUpIdentifier(entity, bitHolder, "Left of Fruit Bowl");
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
		tempDef.position.Set(float32(163.f), float32(10.f));

		tempBody = m_physicsWorld->CreateBody(&tempDef);
		tempBody->SetUserData((void*)entity);

		tempPhsBody = PhysicsBody(tempBody, 1, 14, vec2(0.f, 0.f), false);

		unsigned int bitHolder = EntityIdentifier::TransformBit();
		ECS::SetUpIdentifier(entity, bitHolder, "Right of Fruit Bowl");
	}
#pragma endregion
}

int GoGoGame::GetBackground()
{
	return m_background;
}
int GoGoGame::GetBackground2()
{
	return m_background2;
}
int GoGoGame::GetButton()
{
	return m_button;
}
int GoGoGame::GetCam()
{
	return m_cam;
}
int GoGoGame::GetElevator()
{
	return m_elevator;
}

int GoGoGame::GetFruitBowl()
{
	return m_fruitBowl;
}

bool GoGoGame::GetButtonOn()
{
	return turnOn;
}