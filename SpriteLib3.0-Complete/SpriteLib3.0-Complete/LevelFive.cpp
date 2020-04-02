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

	sndPlaySound("BGM.wav", SND_FILENAME | SND_ASYNC | SND_LOOP);

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
		ECS::GetComponent<Transform>(entity).SetPosition(vec3(96.f, -81.8f, 70.f));
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
		ECS::GetComponent<Transform>(entity2).SetPosition(vec3(139.f, -81.8f, 70.f));
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
		ECS::GetComponent<Transform>(entity3).SetPosition(vec3(-110.f, -82.f, 70.f));
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
		ECS::GetComponent<Transform>(entity2).SetPosition(vec3(-143.f, 30.f, 70.f));
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
		ECS::GetComponent<Transform>(entity3).SetPosition(vec3(121.f, -13.f, 70.f));
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
		ECS::GetComponent<Transform>(entity4).SetPosition(vec3(-151.f, -85.f, 70.f));
		unsigned int bitHolder4 = EntityIdentifier::SpriteBit() | EntityIdentifier::TransformBit() | EntityIdentifier::AnimationBit();
		ECS::SetUpIdentifier(entity4, bitHolder4, "Grass Anim 3");
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

		float shrinkX = tempSpr.GetWidth() / 40.f + 26;
		float shrinkY = tempSpr.GetWidth() / 40.f + 21;

		b2Body* tempBody;
		b2BodyDef tempDef;
		tempDef.type = b2_dynamicBody;
		tempDef.position.Set(float32(-118.f), float32(-74.f));

		tempBody = m_physicsWorld->CreateBody(&tempDef);
		tempBody->SetFixedRotation(true);
		tempBody->SetUserData((void*)entity);

		tempPhsBody = PhysicsBody(tempBody, float(tempSpr.GetWidth() - shrinkX), float(tempSpr.GetHeight() - shrinkY),
			vec2(1.f, -10.f), false);

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

		float shrinkX = tempSpr.GetWidth() / 48.f + 22;
		float shrinkY = tempSpr.GetWidth() / 48.f + 26;

		b2Body* tempBody;
		b2BodyDef tempDef;
		tempDef.type = b2_dynamicBody;
		tempDef.position.Set(float32(-150.f), float32(-80.f));

		tempBody = m_physicsWorld->CreateBody(&tempDef);
		tempBody->SetFixedRotation(true);
		tempBody->SetUserData((void*)entity);

		tempPhsBody = PhysicsBody(tempBody, float(tempSpr.GetWidth() - shrinkX), float(tempSpr.GetHeight() - shrinkY),
			vec2(-1.f, -3.f), false);

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
		tempDef.position.Set(float32(-132.f), float32(27.f));

		tempBody = m_physicsWorld->CreateBody(&tempDef);

		tempBody->SetUserData((void*)box1);

		tempPhsBody = PhysicsBody(tempBody, 97, 1, vec2(0.f, 0.f), false);

		unsigned int bitHolder = EntityIdentifier::TransformBit() | EntityIdentifier::GroundBit();
		ECS::SetUpIdentifier(box1, bitHolder, "Left Plat Ground Box");
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
		tempDef.position.Set(float32(-84.f), float32(15.f));

		tempBody = m_physicsWorld->CreateBody(&tempDef);

		tempBody->SetUserData((void*)box1);

		tempPhsBody = PhysicsBody(tempBody, 1, 23, vec2(0.f, 0.f), false);

		unsigned int bitHolder = EntityIdentifier::TransformBit();
		ECS::SetUpIdentifier(box1, bitHolder, "Left Side Plat Facing Box");
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
		tempDef.position.Set(float32(-132.f), float32(4.f));

		tempBody = m_physicsWorld->CreateBody(&tempDef);

		tempBody->SetUserData((void*)box1);

		tempPhsBody = PhysicsBody(tempBody, 97, 1, vec2(0.f, 0.f), false);

		unsigned int bitHolder = EntityIdentifier::TransformBit();
		ECS::SetUpIdentifier(box1, bitHolder, "Left Bot Plat Facing Box");
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
		tempDef.position.Set(float32(131.f), float32(-16.f));

		tempBody = m_physicsWorld->CreateBody(&tempDef);

		tempBody->SetUserData((void*)box1);

		tempPhsBody = PhysicsBody(tempBody, 95, 1, vec2(0.f, 0.f), false);

		unsigned int bitHolder = EntityIdentifier::TransformBit() | EntityIdentifier::GroundBit();
		ECS::SetUpIdentifier(box1, bitHolder, "Right Plat Ground Box");
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
		tempDef.position.Set(float32(131.f), float32(-40.f));

		tempBody = m_physicsWorld->CreateBody(&tempDef);

		tempBody->SetUserData((void*)box1);

		tempPhsBody = PhysicsBody(tempBody, 95, 1, vec2(0.f, 0.f), false);

		unsigned int bitHolder = EntityIdentifier::TransformBit();
		ECS::SetUpIdentifier(box1, bitHolder, "Right Bot Plat Facing Box");
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
		tempDef.position.Set(float32(84.f), float32(-28.f));

		tempBody = m_physicsWorld->CreateBody(&tempDef);

		tempBody->SetUserData((void*)box1);

		tempPhsBody = PhysicsBody(tempBody, 1, 23, vec2(0.f, 0.f), false);

		unsigned int bitHolder = EntityIdentifier::TransformBit();
		ECS::SetUpIdentifier(box1, bitHolder, "Right Plat Facing Box");
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
		ECS::GetComponent<Transform>(entity).SetPosition(vec3(-104.f, 29.5f, 100.f));

		unsigned int bitHolder = EntityIdentifier::SpriteBit() | EntityIdentifier::TransformBit() | EntityIdentifier::AnimationBit();
		ECS::SetUpIdentifier(entity, bitHolder, "Top Blue Button Anim");

		m_button1 = entity;
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
		ECS::GetComponent<Transform>(entity).SetPosition(vec3(66.f, -86.f, 100.f));

		unsigned int bitHolder = EntityIdentifier::SpriteBit() | EntityIdentifier::TransformBit() | EntityIdentifier::AnimationBit();
		ECS::SetUpIdentifier(entity, bitHolder, "Bottom Blue Button Anim");

		m_button2 = entity;
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
		animController.GetAnimation(1);
		animController.SetActiveAnim(0);

		ECS::GetComponent<Sprite>(entity).LoadSprite(fileName, 26, 5, true, &animController);
		ECS::GetComponent<Transform>(entity).SetPosition(vec3(163.f, -13.5f, 100.f));

		unsigned int bitHolder = EntityIdentifier::SpriteBit() | EntityIdentifier::TransformBit() | EntityIdentifier::AnimationBit();
		ECS::SetUpIdentifier(entity, bitHolder, "Red Button Anim");

		m_button3 = entity;
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
		tempDef.position.Set(float32(-113.f), float32(30.f));

		tempBody = m_physicsWorld->CreateBody(&tempDef);
		tempBody->SetUserData((void*)entity);

		tempPhsBody = PhysicsBody(tempBody, 1, 4, vec2(0.f, 0.f), false);

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
		tempDef.position.Set(float32(-95.f), float32(30.f));

		tempBody = m_physicsWorld->CreateBody(&tempDef);
		tempBody->SetUserData((void*)entity);

		tempPhsBody = PhysicsBody(tempBody, 1, 4, vec2(0.f, 0.f), false);

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
		tempDef.position.Set(float32(-104.f), float32(32.f));

		tempBody = m_physicsWorld->CreateBody(&tempDef);
		tempBody->SetUserData((void*)entity);

		tempPhsBody = PhysicsBody(tempBody, 18, 1, vec2(0.f, 0.f), false);

		unsigned int bitHolder = EntityIdentifier::TransformBit() | EntityIdentifier::BlueButton2Bit();
		ECS::SetUpIdentifier(entity, bitHolder, "Top of Blue Button");
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
		tempDef.position.Set(float32(57.f), float32(-85.f));

		tempBody = m_physicsWorld->CreateBody(&tempDef);
		tempBody->SetUserData((void*)entity);

		tempPhsBody = PhysicsBody(tempBody, 1, 4, vec2(0.f, 0.f), false);

		unsigned int bitHolder = EntityIdentifier::TransformBit();
		ECS::SetUpIdentifier(entity, bitHolder, "Left Side of Blue Button 2");
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
		tempDef.position.Set(float32(75.f), float32(-85.f));

		tempBody = m_physicsWorld->CreateBody(&tempDef);
		tempBody->SetUserData((void*)entity);

		tempPhsBody = PhysicsBody(tempBody, 1, 4, vec2(0.f, 0.f), false);

		unsigned int bitHolder = EntityIdentifier::TransformBit();
		ECS::SetUpIdentifier(entity, bitHolder, "Right Side of Blue Button 2");
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
		tempDef.position.Set(float32(66.f), float32(-83.5f));

		tempBody = m_physicsWorld->CreateBody(&tempDef);
		tempBody->SetUserData((void*)entity);

		tempPhsBody = PhysicsBody(tempBody, 18, 1, vec2(0.f, 0.f), false);

		unsigned int bitHolder = EntityIdentifier::TransformBit() | EntityIdentifier::BlueButtonBit();
		ECS::SetUpIdentifier(entity, bitHolder, "Top of Blue Button 2");
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
		tempDef.position.Set(float32(154.f), float32(-13.f));

		tempBody = m_physicsWorld->CreateBody(&tempDef);
		tempBody->SetUserData((void*)entity);

		tempPhsBody = PhysicsBody(tempBody, 1, 4, vec2(0.f, 0.f), false);

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
		tempDef.position.Set(float32(172.f), float32(-13.f));

		tempBody = m_physicsWorld->CreateBody(&tempDef);
		tempBody->SetUserData((void*)entity);

		tempPhsBody = PhysicsBody(tempBody, 1, 4, vec2(0.f, 0.f), false);

		unsigned int bitHolder = EntityIdentifier::TransformBit();
		ECS::SetUpIdentifier(entity, bitHolder, "Right Side of Red Button");
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
		tempDef.position.Set(float32(163.f), float32(-10.5f));

		tempBody = m_physicsWorld->CreateBody(&tempDef);
		tempBody->SetUserData((void*)entity);

		tempPhsBody = PhysicsBody(tempBody, 18, 1, vec2(0.f, 0.f), false);

		unsigned int bitHolder = EntityIdentifier::TransformBit() | EntityIdentifier::RedButtonBit();
		ECS::SetUpIdentifier(entity, bitHolder, "Top of Red Button");
	}
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
		tempDef.position.Set(float32(-69.f), float32(-86.f));

		tempBody = m_physicsWorld->CreateBody(&tempDef);

		tempBody->SetUserData((void*)entity);

		tempPhsBody = PhysicsBody(tempBody, float(tempSpr.GetWidth()), float(tempSpr.GetHeight()),
			vec2(0.f, 0.f), false);

		unsigned int bitHolder = EntityIdentifier::SpriteBit() | EntityIdentifier::TransformBit() | EntityIdentifier::AnimationBit() | EntityIdentifier::BlueElevatorBit();
		ECS::SetUpIdentifier(entity, bitHolder, "Blue Elevator 1");

		m_elevator1 = entity;
	}
	{
		auto bluePlatform = File::LoadJSON("RedPlatform.json");

		auto entity = ECS::CreateEntity();

		ECS::AttachComponent<Sprite>(entity);
		ECS::AttachComponent<Transform>(entity);
		ECS::AttachComponent<AnimationController>(entity);
		ECS::AttachComponent<PhysicsBody>(entity);

		std::string fileName = "RedPlatformSS.png";

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
		tempDef.position.Set(float32(107.5f), float32(-42.f));

		tempBody = m_physicsWorld->CreateBody(&tempDef);

		tempBody->SetUserData((void*)entity);

		tempPhsBody = PhysicsBody(tempBody, float(tempSpr.GetWidth()), float(tempSpr.GetHeight()),
			vec2(0.f, 0.f), false);

		unsigned int bitHolder = EntityIdentifier::SpriteBit() | EntityIdentifier::TransformBit() | EntityIdentifier::AnimationBit() | EntityIdentifier::RedElevatorBit();
		ECS::SetUpIdentifier(entity, bitHolder, "Red Elevator");

		m_elevator2 = entity;
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

		ECS::GetComponent<Sprite>(entity).LoadSprite(fileName, 48, 5, true, &animController);
		ECS::GetComponent<Transform>(entity).SetPosition(vec3(0.f, 0.f, 98.f));

		auto& tempSpr = ECS::GetComponent<Sprite>(entity);
		auto& tempPhsBody = ECS::GetComponent<PhysicsBody>(entity);

		float shrinkX = tempSpr.GetWidth() / 400.f;
		float shrinkY = tempSpr.GetWidth() / 400.f;

		b2Body* tempBody;
		b2BodyDef tempDef;
		tempDef.type = b2_kinematicBody;
		tempDef.position.Set(float32(-108.f), float32(1.f));

		tempBody = m_physicsWorld->CreateBody(&tempDef);

		tempBody->SetUserData((void*)entity);

		tempPhsBody = PhysicsBody(tempBody, float(tempSpr.GetWidth()), float(tempSpr.GetHeight()),
			vec2(0.f, 0.f), false);

		unsigned int bitHolder = EntityIdentifier::SpriteBit() | EntityIdentifier::TransformBit() | EntityIdentifier::AnimationBit() | EntityIdentifier::BlueElevatorBit();
		ECS::SetUpIdentifier(entity, bitHolder, "Blue Elevator 2");

		m_elevator3 = entity;
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

		ECS::GetComponent<Sprite>(entity).LoadSprite(fileName, 73, 18.25, true, &animController);
		ECS::GetComponent<Transform>(entity).SetPosition(vec3(0.f, -91.f, 98.f));

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
		tempDef.position.Set(float32(0.f), float32(-85.f));

		tempBody = m_physicsWorld->CreateBody(&tempDef);
		tempBody->SetUserData((void*)entity);

		tempPhsBody = PhysicsBody(tempBody, 69, 1, vec2(0.f, 0.f), false);

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
		tempDef.position.Set(float32(35.f), float32(-92.f));

		tempBody = m_physicsWorld->CreateBody(&tempDef);
		tempBody->SetUserData((void*)entity);

		tempPhsBody = PhysicsBody(tempBody, 1, 14, vec2(0.f, 0.f), false);

		unsigned int bitHolder = EntityIdentifier::TransformBit();
		ECS::SetUpIdentifier(entity, bitHolder, "Right of Jello");
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
		tempDef.position.Set(float32(-34.5f), float32(-92.f));

		tempBody = m_physicsWorld->CreateBody(&tempDef);
		tempBody->SetUserData((void*)entity);

		tempPhsBody = PhysicsBody(tempBody, 1, 14, vec2(0.f, 0.f), false);

		unsigned int bitHolder = EntityIdentifier::TransformBit();
		ECS::SetUpIdentifier(entity, bitHolder, "Left of Jello");
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
		ECS::GetComponent<Transform>(entity).SetPosition(vec3(-151.f, 42.f, 100.f));

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
		tempDef.position.Set(float32(-153.f), float32(38.f));

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
		tempDef.position.Set(float32(-128.f), float32(31.5f));

		tempBody = m_physicsWorld->CreateBody(&tempDef);
		tempBody->SetUserData((void*)entity);

		tempPhsBody = PhysicsBody(tempBody, 1, 14, vec2(0.f, 0.f), false);

		unsigned int bitHolder = EntityIdentifier::TransformBit();
		ECS::SetUpIdentifier(entity, bitHolder, "Right of Fruit Bowl");
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

int LevelFive::GetCam()
{
	return m_cam;
}

int LevelFive::GetBlueButton2()
{
	return m_button1;
}

int LevelFive::GetBlueButton1()
{
	return m_button2;
}

int LevelFive::GetRedButton()
{
	return m_button3;
}

int LevelFive::GetJello()
{
	return m_jello;
}

int LevelFive::GetFruitBowl()
{
	return m_fruitBowl;
}

int LevelFive::GetElevator1()
{
	return m_elevator1;
}

int LevelFive::GetElevator2()
{
	return m_elevator2;
}

int LevelFive::GetElevator3()
{
	return m_elevator3;
}

bool LevelFive::GetButtonOn1()
{
	return turnOn1;
}

bool LevelFive::GetButtonOn2()
{
	return turnOn2;
}

bool LevelFive::GetButtonOn3()
{
	return turnOn3;
}
