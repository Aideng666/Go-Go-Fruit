#include "LevelTwo.h"
#include <iostream>

LevelTwo::LevelTwo(std::string name)
	: Scene(name)
{
	m_gravity = b2Vec2(float32(0.f), float32(-9.f));
	m_physicsWorld->SetGravity(m_gravity);
}

void LevelTwo::InitScene(float windowWidth, float windowHeight)
{
	m_sceneReg = new entt::registry;

	ECS::AttachRegister(m_sceneReg);

	float aspectRatio = windowWidth / windowHeight;

	sndPlaySound("Level 4.wav", SND_FILENAME | SND_ASYNC | SND_LOOP);

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
	//Background Level Image
	{
		auto entity = ECS::CreateEntity();

		ECS::AttachComponent<Sprite>(entity);
		ECS::AttachComponent<Transform>(entity);

		std::string fileName = "Level2.png";

		ECS::GetComponent<Sprite>(entity).LoadSprite(fileName, 357, 212.7125);
		ECS::GetComponent<Transform>(entity).SetPosition(vec3(0.f, 6.f, 20.f));

		unsigned int bitHolder = EntityIdentifier::SpriteBit() | EntityIdentifier::TransformBit();
		ECS::SetUpIdentifier(entity, bitHolder, "Level 2");
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

		m_bg = entity;
		m_bg2 = entity2;
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
		ECS::GetComponent<Transform>(entity).SetPosition(vec3(-60.f, -82.f, 70.f));
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
		ECS::GetComponent<Transform>(entity2).SetPosition(vec3(-75.f, -10.6f, 70.f));
		unsigned int bitHolder2 = EntityIdentifier::SpriteBit() | EntityIdentifier::TransformBit() | EntityIdentifier::AnimationBit();
		ECS::SetUpIdentifier(entity2, bitHolder2, "Flower Anim 2");
	}

	//Grass
	{
		auto grassAnim = File::LoadJSON("Grass.json");
		std::string fileName = "GrassV2.png";

		auto entity = ECS::CreateEntity();
		ECS::AttachComponent<Sprite>(entity);
		ECS::AttachComponent<Transform>(entity);
		ECS::AttachComponent<AnimationController>(entity);
		auto& animController = ECS::GetComponent<AnimationController>(entity);
		animController.InitUVs(fileName);
		animController.AddAnimation(grassAnim["GrassSway"]);
		animController.GetAnimation(0);
		animController.SetActiveAnim(0);
		ECS::GetComponent<Sprite>(entity).LoadSprite(fileName, 50, 7, true, &animController);
		ECS::GetComponent<Transform>(entity).SetPosition(vec3(-16.f, -86.f, 70.f));
		unsigned int bitHolder = EntityIdentifier::SpriteBit() | EntityIdentifier::TransformBit() | EntityIdentifier::AnimationBit();
		ECS::SetUpIdentifier(entity, bitHolder, "Grass Anim 1");

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
		ECS::GetComponent<Transform>(entity2).SetPosition(vec3(-104.f, -86.f, 70.f));
		unsigned int bitHolder2 = EntityIdentifier::SpriteBit() | EntityIdentifier::TransformBit() | EntityIdentifier::AnimationBit();
		ECS::SetUpIdentifier(entity2, bitHolder2, "Grass Anim 2");

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
		ECS::GetComponent<Transform>(entity3).SetPosition(vec3(122.f, 57.f, 70.f));
		unsigned int bitHolder3 = EntityIdentifier::SpriteBit() | EntityIdentifier::TransformBit() | EntityIdentifier::AnimationBit();
		ECS::SetUpIdentifier(entity3, bitHolder3, "Grass Anim 3");
	}
#pragma endregion

#pragma region PLAYER ENTITIES
	//Blueberry
	{
		auto blueberryAnim = File::LoadJSON("BlueberryFinal.json");

		auto entity = ECS::CreateEntity();

		ECS::SetIsMainPlayer(entity, true);
		EntityIdentifier::MainPlayer(entity);

		ECS::AttachComponent<Sprite>(entity);
		ECS::AttachComponent<Transform>(entity);
		ECS::AttachComponent<PhysicsBody>(entity);
		ECS::AttachComponent<AnimationController>(entity);

		std::string fileName = "BlueberryFull.png";

		auto& animController = ECS::GetComponent<AnimationController>(entity);
		animController.InitUVs(fileName);

		animController.AddAnimation(blueberryAnim["LeftWalk"]);
		animController.GetAnimation(0);
		animController.AddAnimation(blueberryAnim["RightWalk"]);
		animController.GetAnimation(1);
		animController.AddAnimation(blueberryAnim["LeftIdle"]);
		animController.GetAnimation(2);
		animController.AddAnimation(blueberryAnim["RightIdle"]);
		animController.GetAnimation(3);
		animController.SetActiveAnim(3);

		ECS::GetComponent<Sprite>(entity).LoadSprite(fileName, 40.f, 40.f, true, &animController);
		ECS::GetComponent<Transform>(entity).SetPosition(vec3(-100.f, 50.f, 99.f));

		auto& tempSpr = ECS::GetComponent<Sprite>(entity);
		auto& tempPhsBody = ECS::GetComponent<PhysicsBody>(entity);

		b2Body* tempBody;
		b2BodyDef tempDef;
		tempDef.type = b2_dynamicBody;
		tempDef.position.Set(float32(-65.f), float32(-79.f));

		tempBody = m_physicsWorld->CreateBody(&tempDef);
		tempBody->SetFixedRotation(true);
		tempBody->SetUserData((void*)entity);

		tempPhsBody = PhysicsBody(tempBody, float(13), float(19), vec2(1.f, -10.f), false);

		tempPhsBody.SetFriction(0.15f);
		tempPhsBody.SetMaxVelo(60.f);
		tempPhsBody.SetGravity(true);

		unsigned int bitHolder = EntityIdentifier::SpriteBit() | EntityIdentifier::TransformBit() | EntityIdentifier::BlueberryBit();
		ECS::SetUpIdentifier(entity, bitHolder, "Blueberry");
	}

	//Watermelon
	{
		auto waterAnim = File::LoadJSON("WatermelonFinal.json");

		auto entity = ECS::CreateEntity();

		ECS::SetIsMainPlayer2(entity, true);
		EntityIdentifier::MainPlayer2(entity);

		ECS::AttachComponent<Sprite>(entity);
		ECS::AttachComponent<Transform>(entity);
		ECS::AttachComponent<PhysicsBody>(entity);
		ECS::AttachComponent<AnimationController>(entity);

		std::string fileName = "WatermelonFull.png";

		auto& animController = ECS::GetComponent<AnimationController>(entity);
		animController.InitUVs(fileName);

		animController.AddAnimation(Animation());
		auto& anim = animController.GetAnimation(0);
		anim.AddFrame(vec2(1301.f, 2599.f), vec2(1949.f, 1951.f));
		anim.AddFrame(vec2(1951.f, 2599.f), vec2(2599.f, 1951.f));
		anim.AddFrame(vec2(1.f, 3899.f), vec2(649.f, 3251.f));
		anim.AddFrame(vec2(1.f, 3899.f), vec2(649.f, 3251.f));
		anim.AddFrame(vec2(3901.f, 3899.f), vec2(4549.f, 3251.f));
		anim.AddFrame(vec2(1.f, 4549.f), vec2(649.f, 3901.f));
		anim.AddFrame(vec2(651.f, 4549.f), vec2(1299.f, 3901.f));
		anim.AddFrame(vec2(651.f, 4549.f), vec2(1299.f, 3901.f));
		anim.AddFrame(vec2(1301.f, 4549.f), vec2(1949.f, 3901.f));
		anim.AddFrame(vec2(1951.f, 4549.f), vec2(2599.f, 3901.f));
		anim.AddFrame(vec2(2601.f, 2599.f), vec2(3249.f, 1951.f));
		anim.AddFrame(vec2(2601.f, 2599.f), vec2(3249.f, 1951.f));
		anim.AddFrame(vec2(2601.f, 2599.f), vec2(3249.f, 1951.f));
		anim.AddFrame(vec2(3251.f, 2599.f), vec2(3899.f, 1951.f));
		anim.AddFrame(vec2(3901.f, 2599.f), vec2(4549.f, 1951.f));
		anim.AddFrame(vec2(3901.f, 2599.f), vec2(4549.f, 1951.f));
		anim.AddFrame(vec2(4551.f, 2599.f), vec2(5199.f, 1951.f));
		anim.AddFrame(vec2(5201.f, 2599.f), vec2(5849.f, 1951.f));
		anim.AddFrame(vec2(1.f, 3249.f), vec2(649.f, 2601.f));
		anim.AddFrame(vec2(1.f, 3249.f), vec2(649.f, 2601.f));
		anim.AddFrame(vec2(651.f, 3249.f), vec2(1299.f, 2601.f));
		anim.AddFrame(vec2(1301.f, 3249.f), vec2(1949.f, 2601.f));
		anim.AddFrame(vec2(1951.f, 3249.f), vec2(2599.f, 2601.f));
		anim.AddFrame(vec2(1951.f, 3249.f), vec2(2599.f, 2601.f));
		anim.AddFrame(vec2(2601.f, 3249.f), vec2(3249.f, 2601.f));
		anim.AddFrame(vec2(3251.f, 3249.f), vec2(3899.f, 2601.f));
		anim.AddFrame(vec2(3901.f, 3249.f), vec2(4549.f, 2601.f));
		anim.AddFrame(vec2(3901.f, 3249.f), vec2(4549.f, 2601.f));
		anim.AddFrame(vec2(4551.f, 3249.f), vec2(5199.f, 2601.f));
		anim.AddFrame(vec2(5201.f, 3249.f), vec2(5849.f, 2601.f));
		anim.AddFrame(vec2(651.f, 3899.f), vec2(1299.f, 3251.f));
		anim.AddFrame(vec2(651.f, 3899.f), vec2(1299.f, 3251.f));
		anim.AddFrame(vec2(1301.f, 3899.f), vec2(1949.f, 3251.f));
		anim.AddFrame(vec2(1951.f, 3899.f), vec2(2599.f, 3251.f));
		anim.AddFrame(vec2(1951.f, 3899.f), vec2(2599.f, 3251.f));
		anim.AddFrame(vec2(1951.f, 3899.f), vec2(2599.f, 3251.f));
		anim.AddFrame(vec2(2601.f, 3899.f), vec2(3249.f, 3251.f));
		anim.AddFrame(vec2(3251.f, 3899.f), vec2(3899.f, 3251.f));
		anim.AddFrame(vec2(3251.f, 3899.f), vec2(3899.f, 3251.f));
		anim.AddFrame(vec2(2601.f, 3899.f), vec2(3249.f, 3251.f));
		anim.AddFrame(vec2(1301.f, 3899.f), vec2(1949.f, 3251.f));
		anim.AddFrame(vec2(651.f, 3899.f), vec2(1299.f, 3251.f));
		anim.AddFrame(vec2(651.f, 3899.f), vec2(1299.f, 3251.f));
		anim.AddFrame(vec2(5201.f, 3249.f), vec2(5849.f, 2601.f));
		anim.AddFrame(vec2(1951.f, 3899.f), vec2(2599.f, 3251.f));
		anim.AddFrame(vec2(1951.f, 3899.f), vec2(2599.f, 3251.f));
		anim.AddFrame(vec2(1951.f, 3899.f), vec2(2599.f, 3251.f));
		anim.AddFrame(vec2(4551.f, 3899.f), vec2(5199.f, 3251.f));
		anim.AddFrame(vec2(5201.f, 3899.f), vec2(5849.f, 3251.f));
		anim.AddFrame(vec2(3251.f, 3899.f), vec2(3899.f, 3251.f));
		anim.AddFrame(vec2(2601.f, 3899.f), vec2(3249.f, 3251.f));
		anim.AddFrame(vec2(1301.f, 3899.f), vec2(1949.f, 3251.f));
		anim.AddFrame(vec2(651.f, 3899.f), vec2(1299.f, 3251.f));
		anim.AddFrame(vec2(651.f, 3899.f), vec2(1299.f, 3251.f));
		anim.AddFrame(vec2(5201.f, 3249.f), vec2(5849.f, 2601.f));
		anim.AddFrame(vec2(2601.f, 3249.f), vec2(3249.f, 2601.f));
		anim.AddFrame(vec2(2601.f, 3249.f), vec2(3249.f, 2601.f));
		anim.AddFrame(vec2(3251.f, 3249.f), vec2(3899.f, 2601.f));
		anim.AddFrame(vec2(5201.f, 3249.f), vec2(5849.f, 2601.f));
		anim.AddFrame(vec2(651.f, 3899.f), vec2(1299.f, 3251.f));
		anim.AddFrame(vec2(651.f, 3899.f), vec2(1299.f, 3251.f));
		anim.SetRepeating(true);
		anim.SetSecPerFrame(0.04f);

		animController.AddAnimation(waterAnim["LeftIdle"]);
		animController.GetAnimation(1);
		animController.AddAnimation(waterAnim["LeftWalk"]);
		animController.GetAnimation(2);
		animController.AddAnimation(waterAnim["RightWalk"]);
		animController.GetAnimation(3);
		animController.SetActiveAnim(0);

		ECS::GetComponent<Sprite>(entity).LoadSprite(fileName, 48.f, 48.f, true, &animController);
		ECS::GetComponent<Transform>(entity).SetPosition(vec3(-160.f, 60.f, 99.f));

		auto& tempSpr = ECS::GetComponent<Sprite>(entity);
		auto& tempPhsBody = ECS::GetComponent<PhysicsBody>(entity);

		b2Body* tempBody;
		b2BodyDef tempDef;
		tempDef.type = b2_dynamicBody;
		tempDef.position.Set(float32(-100.f), float32(-85.f));

		tempBody = m_physicsWorld->CreateBody(&tempDef);
		tempBody->SetFixedRotation(true);
		tempBody->SetUserData((void*)entity);

		tempPhsBody = PhysicsBody(tempBody, float(20), float(20), vec2(-1.f, -2.5f), false);

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
		tempDef.position.Set(float32(0.f), float32(-94.5f));

		tempBody = m_physicsWorld->CreateBody(&tempDef);

		tempBody->SetUserData((void*)box1);

		tempPhsBody = PhysicsBody(tempBody, 360, 12, vec2(0.f, 0.f), false);

		unsigned int bitHolder = EntityIdentifier::TransformBit() | EntityIdentifier::GroundBit();
		ECS::SetUpIdentifier(box1, bitHolder, "Lower Ground Box");
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
		tempDef.position.Set(float32(60.f), float32(-24.f));

		tempBody = m_physicsWorld->CreateBody(&tempDef);

		tempBody->SetUserData((void*)box);

		tempPhsBody = PhysicsBody(tempBody, 1, 156, vec2(0.f, 0.f), false);

		unsigned int bitHolder = EntityIdentifier::TransformBit();
		ECS::SetUpIdentifier(box, bitHolder, "Right Facing Box");
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
		tempDef.position.Set(float32(120.5f), float32(53.5f));

		tempBody = m_physicsWorld->CreateBody(&tempDef);

		tempBody->SetUserData((void*)box);

		tempPhsBody = PhysicsBody(tempBody, 120, 1, vec2(0.f, 0.f), false);

		unsigned int bitHolder = EntityIdentifier::TransformBit() | EntityIdentifier::GroundBit();
		ECS::SetUpIdentifier(box, bitHolder, "Right Ground");
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
		tempDef.position.Set(float32(-130.5f), float32(6.5f));

		tempBody = m_physicsWorld->CreateBody(&tempDef);

		tempBody->SetUserData((void*)box);

		tempPhsBody = PhysicsBody(tempBody, 1, 95, vec2(0.f, 0.f), false);

		unsigned int bitHolder = EntityIdentifier::TransformBit();
		ECS::SetUpIdentifier(box, bitHolder, "Top Left Facing Box");
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
		tempDef.position.Set(float32(-107.5f), float32(17.5f));

		tempBody = m_physicsWorld->CreateBody(&tempDef);

		tempBody->SetUserData((void*)box);

		tempPhsBody = PhysicsBody(tempBody, 1, 73, vec2(0.f, 0.f), false);

		unsigned int bitHolder = EntityIdentifier::TransformBit();
		ECS::SetUpIdentifier(box, bitHolder, "Top Left Facing Box 2");
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
		tempDef.position.Set(float32(-119.f), float32(53.5f));

		tempBody = m_physicsWorld->CreateBody(&tempDef);

		tempBody->SetUserData((void*)box);

		tempPhsBody = PhysicsBody(tempBody, 21, 1, vec2(0.f, 0.f), false);

		unsigned int bitHolder = EntityIdentifier::TransformBit() | EntityIdentifier::GroundBit();
		ECS::SetUpIdentifier(box, bitHolder, "Top Top Left Ground Box");
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
		tempDef.position.Set(float32(-84.f), float32(-17.5f));

		tempBody = m_physicsWorld->CreateBody(&tempDef);

		tempBody->SetUserData((void*)box);

		tempPhsBody = PhysicsBody(tempBody, 48, 1, vec2(0.f, 0.f), false);

		unsigned int bitHolder = EntityIdentifier::TransformBit() | EntityIdentifier::GroundBit();
		ECS::SetUpIdentifier(box, bitHolder, "Top Left Ground Box");
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
		tempDef.position.Set(float32(-60.f), float32(-40.5f));

		tempBody = m_physicsWorld->CreateBody(&tempDef);

		tempBody->SetUserData((void*)box);

		tempPhsBody = PhysicsBody(tempBody, 140, 1, vec2(0.f, 0.f), false);

		unsigned int bitHolder = EntityIdentifier::TransformBit();
		ECS::SetUpIdentifier(box, bitHolder, "Top Left Bottom Facing Box");
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

		ECS::GetComponent<Sprite>(entity).LoadSprite(fileName, 48, 5, true, &animController);
		ECS::GetComponent<Transform>(entity).SetPosition(vec3(0.f, 0.f, 98.f));

		auto& tempSpr = ECS::GetComponent<Sprite>(entity);
		auto& tempPhsBody = ECS::GetComponent<PhysicsBody>(entity);

		float shrinkX = tempSpr.GetWidth() / 400.f;
		float shrinkY = tempSpr.GetWidth() / 400.f;

		b2Body* tempBody;
		b2BodyDef tempDef;
		tempDef.type = b2_kinematicBody;
		tempDef.position.Set(float32(-155.f), float32(-86.f));

		tempBody = m_physicsWorld->CreateBody(&tempDef);

		tempBody->SetUserData((void*)entity);

		tempPhsBody = PhysicsBody(tempBody, float(tempSpr.GetWidth()), float(tempSpr.GetHeight()),
			vec2(0.f, 0.f), false);

		unsigned int bitHolder = EntityIdentifier::SpriteBit() | EntityIdentifier::TransformBit() | EntityIdentifier::AnimationBit() | EntityIdentifier::BlueElevatorBit();
		ECS::SetUpIdentifier(entity, bitHolder, "Blue Elevator");

		m_elevator1 = entity;
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
		ECS::GetComponent<Transform>(entity).SetPosition(vec3(-94.f, -15.f, 100.f));

		unsigned int bitHolder = EntityIdentifier::SpriteBit() | EntityIdentifier::TransformBit() | EntityIdentifier::AnimationBit();
		ECS::SetUpIdentifier(entity, bitHolder, "Blue Button Anim");

		m_button1 = entity;
	}

	//Blue Button Bodies
	{
		auto entity = ECS::CreateEntity();

		ECS::AttachComponent<Transform>(entity);
		ECS::AttachComponent<PhysicsBody>(entity);

		ECS::GetComponent<Transform>(entity).SetPosition(vec3(0.f, 0.f, 100.f));

		auto& tempPhsBody = ECS::GetComponent<PhysicsBody>(entity);

		b2Body* tempBody;
		b2BodyDef tempDef;
		tempDef.type = b2_staticBody;
		tempDef.position.Set(float32(-102.5f), float32(-15.f));

		tempBody = m_physicsWorld->CreateBody(&tempDef);
		tempBody->SetUserData((void*)entity);

		tempPhsBody = PhysicsBody(tempBody, 1, 5, vec2(0.f, 0.f), false);

		unsigned int bitHolder = EntityIdentifier::TransformBit();
		ECS::SetUpIdentifier(entity, bitHolder, "Left Side of Blue Button");
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
		tempDef.position.Set(float32(-84.f), float32(-15.f));

		tempBody = m_physicsWorld->CreateBody(&tempDef);
		tempBody->SetUserData((void*)entity);

		tempPhsBody = PhysicsBody(tempBody, 1, 5, vec2(0.f, 0.f), false);

		unsigned int bitHolder = EntityIdentifier::TransformBit();
		ECS::SetUpIdentifier(entity, bitHolder, "Right Side of Blue Button");
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
		tempDef.position.Set(float32(-93.5f), float32(-13.f));

		tempBody = m_physicsWorld->CreateBody(&tempDef);
		tempBody->SetUserData((void*)entity);

		tempPhsBody = PhysicsBody(tempBody, 18, 1, vec2(0.f, 0.f), false);

		unsigned int bitHolder = EntityIdentifier::TransformBit() | EntityIdentifier::BlueButtonBit();
		ECS::SetUpIdentifier(entity, bitHolder, "Top of Blue Button");
	}

	{
		auto blueButton = File::LoadJSON("RedButton.json");

		auto entity = ECS::CreateEntity();

		ECS::AttachComponent<Sprite>(entity);
		ECS::AttachComponent<Transform>(entity);
		ECS::AttachComponent<AnimationController>(entity);

		std::string fileName = "RedButtonSS.png";

		auto& animController = ECS::GetComponent<AnimationController>(entity);
		animController.InitUVs(fileName);

		animController.AddAnimation(blueButton["PowerOff"]);
		animController.GetAnimation(0);
		animController.AddAnimation(blueButton["PowerOn"]);
		animController.GetAnimation(0);

		animController.SetActiveAnim(0);

		ECS::GetComponent<Sprite>(entity).LoadSprite(fileName, 26, 5, true, &animController);
		ECS::GetComponent<Transform>(entity).SetPosition(vec3(80.f, 56.f, 99.f));

		unsigned int bitHolder = EntityIdentifier::SpriteBit() | EntityIdentifier::TransformBit() | EntityIdentifier::AnimationBit();
		ECS::SetUpIdentifier(entity, bitHolder, "Red Button Anim");

		m_redButton = entity;
	}

	//Red Button Bodies
	{
		auto entity = ECS::CreateEntity();

		ECS::AttachComponent<Transform>(entity);
		ECS::AttachComponent<PhysicsBody>(entity);

		ECS::GetComponent<Transform>(entity).SetPosition(vec3(0.f, 0.f, 100.f));

		auto& tempPhsBody = ECS::GetComponent<PhysicsBody>(entity);

		b2Body* tempBody;
		b2BodyDef tempDef;
		tempDef.type = b2_staticBody;
		tempDef.position.Set(float32(80.f), float32(58.5f));

		tempBody = m_physicsWorld->CreateBody(&tempDef);
		tempBody->SetUserData((void*)entity);

		tempPhsBody = PhysicsBody(tempBody, 18, 1, vec2(0.f, 0.f), false);

		unsigned int bitHolder = EntityIdentifier::TransformBit() | EntityIdentifier::RedButtonBit();
		ECS::SetUpIdentifier(entity, bitHolder, "Top of Red Button");
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
		tempDef.position.Set(float32(71.f), float32(56.f));

		tempBody = m_physicsWorld->CreateBody(&tempDef);
		tempBody->SetUserData((void*)entity);

		tempPhsBody = PhysicsBody(tempBody, 1, 5, vec2(0.f, 0.f), false);

		unsigned int bitHolder = EntityIdentifier::TransformBit();
		ECS::SetUpIdentifier(entity, bitHolder, "Left Side of Red Button");
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
		tempDef.position.Set(float32(89.f), float32(56.f));

		tempBody = m_physicsWorld->CreateBody(&tempDef);
		tempBody->SetUserData((void*)entity);

		tempPhsBody = PhysicsBody(tempBody, 1, 5, vec2(0.f, 0.f), false);

		unsigned int bitHolder = EntityIdentifier::TransformBit();
		ECS::SetUpIdentifier(entity, bitHolder, "Right Side of Red Button");
	}

	//Red Platform
	{
		auto redPlatform = File::LoadJSON("RedPlatform.json");
	
		auto entity = ECS::CreateEntity();
	
		ECS::AttachComponent<Sprite>(entity);
		ECS::AttachComponent<Transform>(entity);
		ECS::AttachComponent<AnimationController>(entity);
		ECS::AttachComponent<PhysicsBody>(entity);

		std::string fileName = "RedPlatformSS.png";

		auto& animController = ECS::GetComponent<AnimationController>(entity);
		animController.InitUVs(fileName);

		animController.AddAnimation(redPlatform["PowerOff"]);
		animController.GetAnimation(0);
		animController.AddAnimation(redPlatform["PowerOn"]);
		animController.GetAnimation(1);

		animController.SetActiveAnim(0);

		ECS::GetComponent<Sprite>(entity).LoadSprite(fileName, 48, 5, true, &animController);
		ECS::GetComponent<Transform>(entity).SetPosition(vec3(0.f, 0.f, 98.f));

		auto& tempSpr = ECS::GetComponent<Sprite>(entity);
		auto& tempPhsBody = ECS::GetComponent<PhysicsBody>(entity);

		float shrinkX = tempSpr.GetWidth() / 400.f;
		float shrinkY = tempSpr.GetWidth() / 400.f;

		b2Body* tempBody;
		b2BodyDef tempDef;
		tempDef.type = b2_kinematicBody;
		tempDef.position.Set(float32(35.5f), float32(-86.f));

		tempBody = m_physicsWorld->CreateBody(&tempDef);

		tempBody->SetUserData((void*)entity);

		tempPhsBody = PhysicsBody(tempBody, float(tempSpr.GetWidth()), float(tempSpr.GetHeight()),
			vec2(0.f, 0.f), false);

		unsigned int bitHolder = EntityIdentifier::SpriteBit() | EntityIdentifier::TransformBit() | EntityIdentifier::AnimationBit() | EntityIdentifier::RedElevatorBit();
		ECS::SetUpIdentifier(entity, bitHolder, "Red Elevator");

		m_elevator2 = entity;
	}

	//JELLO
	{
		auto jelloAnim = File::LoadJSON("Jello2.json");

		auto entity = ECS::CreateEntity();

		ECS::AttachComponent<Sprite>(entity);
		ECS::AttachComponent<Transform>(entity);
		ECS::AttachComponent<AnimationController>(entity);

		std::string fileName = "JelloSS2.png";

		auto& animController = ECS::GetComponent<AnimationController>(entity);
		animController.InitUVs(fileName);

		animController.AddAnimation(jelloAnim["Bounce"]);
		animController.GetAnimation(0);
		animController.AddAnimation(jelloAnim["Blink"]);
		animController.GetAnimation(1);
		animController.SetActiveAnim(1);

		ECS::GetComponent<Sprite>(entity).LoadSprite(fileName, 72, 18, true, &animController);
		ECS::GetComponent<Transform>(entity).SetPosition(vec3(-24.5f, -23.f, 98.f));

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
		tempDef.position.Set(float32(-24.5f), float32(-17.5f));

		tempBody = m_physicsWorld->CreateBody(&tempDef);
		tempBody->SetUserData((void*)entity);

		tempPhsBody = PhysicsBody(tempBody, 68, 1, vec2(0.f, 0.f), false);

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
		tempDef.position.Set(float32(10.f), float32(-24.f));

		tempBody = m_physicsWorld->CreateBody(&tempDef);
		tempBody->SetUserData((void*)entity);

		tempPhsBody = PhysicsBody(tempBody, 1, 14, vec2(0.f, 0.f), false);

		unsigned int bitHolder = EntityIdentifier::TransformBit();
		ECS::SetUpIdentifier(entity, bitHolder, "Right of Jello");
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
		ECS::GetComponent<Transform>(entity).SetPosition(vec3(150.f, 69.f, 100.f));

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
		tempDef.position.Set(float32(149.f), float32(64.f));

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
		tempDef.position.Set(float32(125.f), float32(57.f));

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
		tempDef.position.Set(float32(173.f), float32(57.f));

		tempBody = m_physicsWorld->CreateBody(&tempDef);
		tempBody->SetUserData((void*)entity);

		tempPhsBody = PhysicsBody(tempBody, 1, 14, vec2(0.f, 0.f), false);

		unsigned int bitHolder = EntityIdentifier::TransformBit();
		ECS::SetUpIdentifier(entity, bitHolder, "Right of Fruit Bowl");
	}
#pragma endregion
}

int LevelTwo::GetBg1()
{
	return m_bg;
}

int LevelTwo::GetBg2()
{
	return m_bg2;
}

int LevelTwo::GetElevator()
{
	return m_elevator1;
}

int LevelTwo::GetElevator2()
{
	return m_elevator2;
}

int LevelTwo::GetButton()
{
	return m_button1;
}

int LevelTwo::GetRedButton()
{
	return m_redButton;
}

bool LevelTwo::GetButtonOn1()
{
	return turnOn1;
}

bool LevelTwo::GetButtonOn2()
{
	return turnOn2;
}

int LevelTwo::GetJello()
{
	return m_jello;
}

int LevelTwo::GetFruitBowl()
{
	return m_fruitBowl;
}

int LevelTwo::GetCam()
{
	return m_cam;
}