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
		std::string fileName = "Flowers.png";

		auto entity = ECS::CreateEntity();
		ECS::AttachComponent<Sprite>(entity);
		ECS::AttachComponent<Transform>(entity);
		ECS::GetComponent<Sprite>(entity).LoadSprite(fileName, 20, 10);
		ECS::GetComponent<Transform>(entity).SetPosition(vec3(46.f, 11.f, 70.f));
		unsigned int bitHolder = EntityIdentifier::SpriteBit() | EntityIdentifier::TransformBit();
		ECS::SetUpIdentifier(entity, bitHolder, "Flower 1");

		auto entity2 = ECS::CreateEntity();
		ECS::AttachComponent<Sprite>(entity2);
		ECS::AttachComponent<Transform>(entity2);
		ECS::GetComponent<Sprite>(entity2).LoadSprite(fileName, 20, 10);
		ECS::GetComponent<Transform>(entity2).SetPosition(vec3(-40.f, -60.f, 70.f));
		unsigned int bitHolder2 = EntityIdentifier::SpriteBit() | EntityIdentifier::TransformBit();
		ECS::SetUpIdentifier(entity2, bitHolder2, "Flower 2");

		auto entity3 = ECS::CreateEntity();
		ECS::AttachComponent<Sprite>(entity3);
		ECS::AttachComponent<Transform>(entity3);
		ECS::GetComponent<Sprite>(entity3).LoadSprite(fileName, 20, 10);
		ECS::GetComponent<Transform>(entity3).SetPosition(vec3(-70.f, -84.f, 70.f));
		unsigned int bitHolder3 = EntityIdentifier::SpriteBit() | EntityIdentifier::TransformBit();
		ECS::SetUpIdentifier(entity3, bitHolder3, "Flower 3");

		auto entity4 = ECS::CreateEntity();
		ECS::AttachComponent<Sprite>(entity4);
		ECS::AttachComponent<Transform>(entity4);
		ECS::GetComponent<Sprite>(entity4).LoadSprite(fileName, 20, 10);
		ECS::GetComponent<Transform>(entity4).SetPosition(vec3(-155.f, -84.f, 70.f));
		unsigned int bitHolder4 = EntityIdentifier::SpriteBit() | EntityIdentifier::TransformBit();
		ECS::SetUpIdentifier(entity4, bitHolder4, "Flower 4");
	}

	//Grass
	{
		std::string fileName = "Grass.png";

		auto entity = ECS::CreateEntity();
		ECS::AttachComponent<Sprite>(entity);
		ECS::AttachComponent<Transform>(entity);
		ECS::GetComponent<Sprite>(entity).LoadSprite(fileName, 20, 6.171875);
		ECS::GetComponent<Transform>(entity).SetPosition(vec3(-91.f, -86.f, 70.f));
		unsigned int bitHolder = EntityIdentifier::SpriteBit() | EntityIdentifier::TransformBit();
		ECS::SetUpIdentifier(entity, bitHolder, "Grass 1");

		auto entity2 = ECS::CreateEntity();
		ECS::AttachComponent<Sprite>(entity2);
		ECS::AttachComponent<Transform>(entity2);
		ECS::GetComponent<Sprite>(entity2).LoadSprite(fileName, 20, 6.171875);
		ECS::GetComponent<Transform>(entity2).SetPosition(vec3(95.f, 9.f, 70.f));
		unsigned int bitHolder2 = EntityIdentifier::SpriteBit() | EntityIdentifier::TransformBit();
		ECS::SetUpIdentifier(entity2, bitHolder2, "Grass 2");

		auto entity3 = ECS::CreateEntity();
		ECS::AttachComponent<Sprite>(entity3);
		ECS::AttachComponent<Transform>(entity3);
		ECS::GetComponent<Sprite>(entity3).LoadSprite(fileName, 20, 6.171875);
		ECS::GetComponent<Transform>(entity3).SetPosition(vec3(-21.f, -62.f, 70.f));
		unsigned int bitHolder3 = EntityIdentifier::SpriteBit() | EntityIdentifier::TransformBit();
		ECS::SetUpIdentifier(entity3, bitHolder3, "Grass 3");

		auto entity4 = ECS::CreateEntity();
		ECS::AttachComponent<Sprite>(entity4);
		ECS::AttachComponent<Transform>(entity4);
		ECS::GetComponent<Sprite>(entity4).LoadSprite(fileName, 20, 6.171875);
		ECS::GetComponent<Transform>(entity4).SetPosition(vec3(172.f, 9.f, 70.f));
		unsigned int bitHolder4 = EntityIdentifier::SpriteBit() | EntityIdentifier::TransformBit();
		ECS::SetUpIdentifier(entity4, bitHolder4, "Grass 4");
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
		tempDef.position.Set(float32(-125.f), float32(0.f));

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
		auto entity = ECS::CreateEntity();

		ECS::SetIsMainPlayer2(entity, true);
		EntityIdentifier::MainPlayer2(entity);

		ECS::AttachComponent<Sprite>(entity);
		ECS::AttachComponent<Transform>(entity);
		ECS::AttachComponent<PhysicsBody>(entity);

		std::string fileName = "Watermelon.png";
		ECS::GetComponent<Sprite>(entity).LoadSprite(fileName, 40.3463203464f, 26.6666666667f);
		ECS::GetComponent<Transform>(entity).SetPosition(vec3(-160.f, 60.f, 99.f));

		auto& tempSpr = ECS::GetComponent<Sprite>(entity);
		auto& tempPhsBody = ECS::GetComponent<PhysicsBody>(entity);

		float shrinkX = tempSpr.GetWidth() / 40.3463203464f + 10;
		float shrinkY = tempSpr.GetWidth() / 26.6666666667f + 5;

		b2Body* tempBody;
		b2BodyDef tempDef;
		tempDef.type = b2_dynamicBody;
		tempDef.position.Set(float32(-150.f), float32(0.f));

		tempBody = m_physicsWorld->CreateBody(&tempDef);
		tempBody->SetFixedRotation(true);
		tempBody->SetUserData((void*)entity);

		tempPhsBody = PhysicsBody(tempBody, float(tempSpr.GetWidth() - shrinkX), float(tempSpr.GetHeight() - shrinkY),
			vec2(0.f, -2.f), false);

		tempPhsBody.SetFriction(0.15f);
		tempPhsBody.SetMaxVelo(60.f);
		tempPhsBody.SetGravity(true);

		unsigned int bitHolder = EntityIdentifier::SpriteBit() | EntityIdentifier::TransformBit() | EntityIdentifier::WatermelonBit();
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
		tempDef.position.Set(float32(0.f), float32(-95));

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

		unsigned int bitHolder = EntityIdentifier::TransformBit() | EntityIdentifier::GroundBit();
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

		unsigned int bitHolder = EntityIdentifier::TransformBit() | EntityIdentifier::GroundBit();
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

		unsigned int bitHolder = EntityIdentifier::TransformBit() | EntityIdentifier::GroundBit();
		ECS::SetUpIdentifier(entity, bitHolder, "Right Wall");
	}
#pragma endregion

#pragma region MAP LAYOUT
	//PLATFORMS
	{
		auto entity = ECS::CreateEntity();

		ECS::AttachComponent<Sprite>(entity);
		ECS::AttachComponent<Transform>(entity);
		ECS::AttachComponent<PhysicsBody>(entity);

		std::string fileName = "BluePlat.png";

		ECS::GetComponent<Sprite>(entity).LoadSprite(fileName, 44.1333333334, 5);
		ECS::GetComponent<Transform>(entity).SetPosition(vec3(0.f, -100.f, 98.f));

		auto& tempSpr = ECS::GetComponent<Sprite>(entity);
		auto& tempPhsBody = ECS::GetComponent<PhysicsBody>(entity);

		float shrinkX = tempSpr.GetWidth() / 400.f;
		float shrinkY = tempSpr.GetWidth() / 400.f;

		b2Body* tempBody;
		b2BodyDef tempDef;
		tempDef.type = b2_kinematicBody;
		tempDef.position.Set(float32(13.5f), float32(-62));

		tempBody = m_physicsWorld->CreateBody(&tempDef);

		tempBody->SetUserData((void*)entity);

		tempPhsBody = PhysicsBody(tempBody, float(tempSpr.GetWidth() - shrinkX), float(tempSpr.GetHeight() - shrinkY),
			vec2(0.f, 0.f), false);

		unsigned int bitHolder = EntityIdentifier::SpriteBit() | EntityIdentifier::TransformBit() | EntityIdentifier::GroundBit();
		ECS::SetUpIdentifier(entity, bitHolder, "Elevator");

		m_elevator = entity;
	}

	//Button
	{
		auto entity = ECS::CreateEntity();

		ECS::AttachComponent<Sprite>(entity);
		ECS::AttachComponent<Transform>(entity);
		ECS::AttachComponent<PhysicsBody>(entity);

		std::string fileName = "BlueButton.png";

		ECS::GetComponent<Sprite>(entity).LoadSprite(fileName, 25, 5);
		ECS::GetComponent<Transform>(entity).SetPosition(vec3(100.f, -95.f, 98.f));

		auto& tempSpr = ECS::GetComponent<Sprite>(entity);
		auto& tempPhsBody = ECS::GetComponent<PhysicsBody>(entity);

		float shrinkX = tempSpr.GetWidth() / 400.f;
		float shrinkY = tempSpr.GetWidth() / 400.f;

		b2Body* tempBody;
		b2BodyDef tempDef;
		tempDef.type = b2_staticBody;
		tempDef.position.Set(float32(75.f), float32(9.f));

		tempBody = m_physicsWorld->CreateBody(&tempDef);

		tempBody->SetUserData((void*)entity);


		tempPhsBody = PhysicsBody(tempBody, float(tempSpr.GetWidth() - 8), float(tempSpr.GetHeight()),
			vec2(0.f, 0.f), false);
		

		unsigned int bitHolder = EntityIdentifier::SpriteBit() | EntityIdentifier::TransformBit() | EntityIdentifier::BlueButtonBit();
		ECS::SetUpIdentifier(entity, bitHolder, "Button");

		m_button = entity;
	}
	
	//Fruit Bowl
	{
		auto entity = ECS::CreateEntity();

		ECS::AttachComponent<Sprite>(entity);
		ECS::AttachComponent<Transform>(entity);
		ECS::AttachComponent<PhysicsBody>(entity);

		std::string fileName = "FruitBowl.png";

		ECS::GetComponent<Sprite>(entity).LoadSprite(fileName, 76.1538461541, 55);
		ECS::GetComponent<Transform>(entity).SetPosition(vec3(0.f, 0.f, 100.f));

		auto& tempSpr = ECS::GetComponent<Sprite>(entity);
		auto& tempPhsBody = ECS::GetComponent<PhysicsBody>(entity);

		float shrinkX = tempSpr.GetWidth() / 100.f;
		float shrinkY = tempSpr.GetWidth() / 100.f;

		b2Body* tempBody;
		b2BodyDef tempDef;
		tempDef.type = b2_staticBody;
		tempDef.position.Set(float32(140.f), float32(33.f));

		tempBody = m_physicsWorld->CreateBody(&tempDef);

		tempBody->SetUserData((void*)entity);


		tempPhsBody = PhysicsBody(tempBody, float(tempSpr.GetWidth() - 22), float(tempSpr.GetHeight() / 4),
			vec2(0.f, -22.f), false);

		unsigned int bitHolder = EntityIdentifier::SpriteBit() | EntityIdentifier::TransformBit();
		ECS::SetUpIdentifier(entity, bitHolder, "Bowl");
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