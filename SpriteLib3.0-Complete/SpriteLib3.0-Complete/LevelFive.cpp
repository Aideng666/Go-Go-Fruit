#include "LevelFive.h"

LevelFive::LevelFive(std::string name)
	: Scene(name)
{
	m_gravity = b2Vec2(float32(0.f), float32(-9.f));
	m_physicsWorld->SetGravity(m_gravity);
}

void LevelFive::InitScene(float windowWidth, float windowHeight)
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
	}

#pragma region Aesthetics + Environment
	//Background Level Image
	{
		auto entity = ECS::CreateEntity();

		ECS::AttachComponent<Sprite>(entity);
		ECS::AttachComponent<Transform>(entity);

		std::string fileName = "Level5.png";

		ECS::GetComponent<Sprite>(entity).LoadSprite(fileName, 357, 212.7125);
		ECS::GetComponent<Transform>(entity).SetPosition(vec3(0.f, 6.f, 20.f));

		unsigned int bitHolder = EntityIdentifier::SpriteBit() | EntityIdentifier::TransformBit();
		ECS::SetUpIdentifier(entity, bitHolder, "Level 5");
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
		tempDef.position.Set(float32(-110.f), float32(-94));

		tempBody = m_physicsWorld->CreateBody(&tempDef);

		tempBody->SetUserData((void*)box1);

		tempPhsBody = PhysicsBody(tempBody, 148, 12, vec2(0.f, 0.f), false);

		unsigned int bitHolder = EntityIdentifier::TransformBit() | EntityIdentifier::GroundBit();
		ECS::SetUpIdentifier(box1, bitHolder, "Left Ground Box");
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
		tempDef.position.Set(float32(108.f), float32(-94));

		tempBody = m_physicsWorld->CreateBody(&tempDef);

		tempBody->SetUserData((void*)box1);

		tempPhsBody = PhysicsBody(tempBody, 145, 12, vec2(0.f, 0.f), false);

		unsigned int bitHolder = EntityIdentifier::TransformBit() | EntityIdentifier::GroundBit();
		ECS::SetUpIdentifier(box1, bitHolder, "Right Ground Box");
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
		tempDef.position.Set(float32(-132.f), float32(36.f));

		tempBody = m_physicsWorld->CreateBody(&tempDef);

		tempBody->SetUserData((void*)box1);

		tempPhsBody = PhysicsBody(tempBody, 97, 1, vec2(0.f, 0.f), false);

		unsigned int bitHolder = EntityIdentifier::TransformBit() | EntityIdentifier::GroundBit();
		ECS::SetUpIdentifier(box1, bitHolder, "Left Top Ground Box");
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
		tempDef.position.Set(float32(-84.f), float32(24.f));

		tempBody = m_physicsWorld->CreateBody(&tempDef);

		tempBody->SetUserData((void*)box1);

		tempPhsBody = PhysicsBody(tempBody, 1, 23, vec2(0.f, 0.f), false);

		unsigned int bitHolder = EntityIdentifier::TransformBit();
		ECS::SetUpIdentifier(box1, bitHolder, "Left Top Facing Box");
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
		tempDef.position.Set(float32(-132.f), float32(13.f));

		tempBody = m_physicsWorld->CreateBody(&tempDef);

		tempBody->SetUserData((void*)box1);

		tempPhsBody = PhysicsBody(tempBody, 97, 1, vec2(0.f, 0.f), false);

		unsigned int bitHolder = EntityIdentifier::TransformBit();
		ECS::SetUpIdentifier(box1, bitHolder, "Bottom Top Facing Box");
	}

#pragma endregion

#pragma region Barriers
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
}

int LevelFive::GetBg1()
{
	return m_background;
}

int LevelFive::GetBg2()
{
	return m_background2;
}
