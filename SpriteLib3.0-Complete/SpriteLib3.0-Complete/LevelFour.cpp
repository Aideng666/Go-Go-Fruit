#include "LevelFour.h"

LevelFour::LevelFour(std::string name)
	: Scene(name)
{
	m_gravity = b2Vec2(float32(0.f), float32(-9.f));
	m_physicsWorld->SetGravity(m_gravity);
}

void LevelFour::InitScene(float windowWidth, float windowHeight)
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

		std::string fileName = "Level4.png";

		ECS::GetComponent<Sprite>(entity).LoadSprite(fileName, 357, 212.7125);
		ECS::GetComponent<Transform>(entity).SetPosition(vec3(0.f, 6.f, 20.f));

		unsigned int bitHolder = EntityIdentifier::SpriteBit() | EntityIdentifier::TransformBit();
		ECS::SetUpIdentifier(entity, bitHolder, "Level 4");
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
		ECS::GetComponent<Transform>(entity).SetPosition(vec3(83.f, 61.f, 70.f));
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
		ECS::GetComponent<Transform>(entity2).SetPosition(vec3(114.f, -81.8f, 70.f));
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
		ECS::GetComponent<Transform>(entity3).SetPosition(vec3(-97.f, -81.8f, 70.f));
		unsigned int bitHolder3 = EntityIdentifier::SpriteBit() | EntityIdentifier::TransformBit() | EntityIdentifier::AnimationBit();
		ECS::SetUpIdentifier(entity3, bitHolder3, "Flower Anim 3");
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
		ECS::GetComponent<Transform>(entity).SetPosition(vec3(-151.f, -85.f, 70.f));
		unsigned int bitHolder = EntityIdentifier::SpriteBit() | EntityIdentifier::TransformBit() | EntityIdentifier::AnimationBit();
		ECS::SetUpIdentifier(entity, bitHolder, "Grass Anim 1");

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
		ECS::GetComponent<Transform>(entity3).SetPosition(vec3(-133.f, 57.f, 70.f));
		unsigned int bitHolder3 = EntityIdentifier::SpriteBit() | EntityIdentifier::TransformBit() | EntityIdentifier::AnimationBit();
		ECS::SetUpIdentifier(entity3, bitHolder3, "Grass Anim 3");

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
		ECS::GetComponent<Transform>(entity4).SetPosition(vec3(-48.f, -85.f, 70.f));
		unsigned int bitHolder4 = EntityIdentifier::SpriteBit() | EntityIdentifier::TransformBit() | EntityIdentifier::AnimationBit();
		ECS::SetUpIdentifier(entity4, bitHolder4, "Grass Anim 4");

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
		ECS::GetComponent<Transform>(entity5).SetPosition(vec3(65.f, -85.f, 70.f));
		unsigned int bitHolder5 = EntityIdentifier::SpriteBit() | EntityIdentifier::TransformBit() | EntityIdentifier::AnimationBit();
		ECS::SetUpIdentifier(entity5, bitHolder5, "Grass Anim 5");
	}
#pragma endregion

#pragma region Player Entities
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

		tempPhsBody = PhysicsBody(tempBody, float(14), float(19), vec2(1.f, -10.f), false);

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

		tempPhsBody = PhysicsBody(tempBody, float(24), float(22), vec2(-1.f, -3.f), false);

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
		tempDef.position.Set(float32(83.f), float32(-40.f));

		tempBody = m_physicsWorld->CreateBody(&tempDef);

		tempBody->SetUserData((void*)box1);

		tempPhsBody = PhysicsBody(tempBody, 93, 1, vec2(0.f, 0.f), false);

		unsigned int bitHolder = EntityIdentifier::TransformBit();
		ECS::SetUpIdentifier(box1, bitHolder, "Bottom Square Box");
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
		tempDef.position.Set(float32(36.5f), float32(6.5f));

		tempBody = m_physicsWorld->CreateBody(&tempDef);

		tempBody->SetUserData((void*)box1);

		tempPhsBody = PhysicsBody(tempBody, 1, 94, vec2(0.f, 0.f), false);

		unsigned int bitHolder = EntityIdentifier::TransformBit();
		ECS::SetUpIdentifier(box1, bitHolder, "Left Square Box");
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
		tempDef.position.Set(float32(130.f), float32(6.5f));

		tempBody = m_physicsWorld->CreateBody(&tempDef);

		tempBody->SetUserData((void*)box1);

		tempPhsBody = PhysicsBody(tempBody, 1, 94, vec2(0.f, 0.f), false);

		unsigned int bitHolder = EntityIdentifier::TransformBit();
		ECS::SetUpIdentifier(box1, bitHolder, "Right Square Box");
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
		tempDef.position.Set(float32(83.25f), float32(53.f));

		tempBody = m_physicsWorld->CreateBody(&tempDef);

		tempBody->SetUserData((void*)box1);

		tempPhsBody = PhysicsBody(tempBody, 92, 1, vec2(0.f, 0.f), false);

		unsigned int bitHolder = EntityIdentifier::TransformBit() | EntityIdentifier::GroundBit();
		ECS::SetUpIdentifier(box1, bitHolder, "Top Square Box");
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
		tempDef.position.Set(float32(-36.f), float32(-30.f));

		tempBody = m_physicsWorld->CreateBody(&tempDef);

		tempBody->SetUserData((void*)box1);

		tempPhsBody = PhysicsBody(tempBody, 47, 1, vec2(0.f, 0.f), false);

		unsigned int bitHolder = EntityIdentifier::TransformBit() | EntityIdentifier::GroundBit();
		ECS::SetUpIdentifier(box1, bitHolder, "Bottom Plat Ground Box");
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
		tempDef.position.Set(float32(-12.f), float32(-41.f));

		tempBody = m_physicsWorld->CreateBody(&tempDef);

		tempBody->SetUserData((void*)box1);

		tempPhsBody = PhysicsBody(tempBody, 1, 22, vec2(0.f, 0.f), false);

		unsigned int bitHolder = EntityIdentifier::TransformBit();
		ECS::SetUpIdentifier(box1, bitHolder, "Bottom Plat Right Box");
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
		tempDef.position.Set(float32(-60.f), float32(-41.f));

		tempBody = m_physicsWorld->CreateBody(&tempDef);

		tempBody->SetUserData((void*)box1);

		tempPhsBody = PhysicsBody(tempBody, 1, 22, vec2(0.f, 0.f), false);

		unsigned int bitHolder = EntityIdentifier::TransformBit();
		ECS::SetUpIdentifier(box1, bitHolder, "Bottom Plat Left Box");
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
		tempDef.position.Set(float32(-36.f), float32(-52.f));

		tempBody = m_physicsWorld->CreateBody(&tempDef);

		tempBody->SetUserData((void*)box1);

		tempPhsBody = PhysicsBody(tempBody, 47, 1, vec2(0.f, 0.f), false);

		unsigned int bitHolder = EntityIdentifier::TransformBit();
		ECS::SetUpIdentifier(box1, bitHolder, "Bottom Plat Bottom Box");
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
		tempDef.position.Set(float32(-145.f), float32(53.5f));

		tempBody = m_physicsWorld->CreateBody(&tempDef);

		tempBody->SetUserData((void*)box1);

		tempPhsBody = PhysicsBody(tempBody, 76, 1, vec2(0.f, 0.f), false);

		unsigned int bitHolder = EntityIdentifier::TransformBit() | EntityIdentifier::GroundBit();
		ECS::SetUpIdentifier(box1, bitHolder, "Top Plat Ground Box");
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
		tempDef.position.Set(float32(-107.f), float32(42.f));

		tempBody = m_physicsWorld->CreateBody(&tempDef);

		tempBody->SetUserData((void*)box1);

		tempPhsBody = PhysicsBody(tempBody, 1, 24, vec2(0.f, 0.f), false);

		unsigned int bitHolder = EntityIdentifier::TransformBit();
		ECS::SetUpIdentifier(box1, bitHolder, "Top Plat Right Box");
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
		tempDef.position.Set(float32(-145.f), float32(30.f));

		tempBody = m_physicsWorld->CreateBody(&tempDef);

		tempBody->SetUserData((void*)box1);

		tempPhsBody = PhysicsBody(tempBody, 76, 1, vec2(0.f, 0.f), false);

		unsigned int bitHolder = EntityIdentifier::TransformBit();
		ECS::SetUpIdentifier(box1, bitHolder, "Top Plat Bottom Box");
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
		ECS::GetComponent<Transform>(entity).SetPosition(vec3(-36.f, -26.5f, 100.f));

		unsigned int bitHolder = EntityIdentifier::SpriteBit() | EntityIdentifier::TransformBit() | EntityIdentifier::AnimationBit();
		ECS::SetUpIdentifier(entity, bitHolder, "Blue Button Anim");

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
		ECS::GetComponent<Transform>(entity).SetPosition(vec3(49.f, 56.5f, 100.f));

		unsigned int bitHolder = EntityIdentifier::SpriteBit() | EntityIdentifier::TransformBit() | EntityIdentifier::AnimationBit();
		ECS::SetUpIdentifier(entity, bitHolder, "Blue Button 2 Anim");

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
		ECS::GetComponent<Transform>(entity).SetPosition(vec3(118.f, 56.5f, 100.f));

		unsigned int bitHolder = EntityIdentifier::SpriteBit() | EntityIdentifier::TransformBit() | EntityIdentifier::AnimationBit();
		ECS::SetUpIdentifier(entity, bitHolder, "Red Button Anim");

		m_button3 = entity;
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
		tempDef.position.Set(float32(-45.f), float32(-26.5f));

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
		tempDef.position.Set(float32(-27.f), float32(-26.5f));

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
		tempDef.position.Set(float32(-36.f), float32(-24.f));

		tempBody = m_physicsWorld->CreateBody(&tempDef);
		tempBody->SetUserData((void*)entity);

		tempPhsBody = PhysicsBody(tempBody, 18, 1, vec2(0.f, 0.f), false);

		unsigned int bitHolder = EntityIdentifier::TransformBit() | EntityIdentifier::BlueButtonBit();
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
		tempDef.position.Set(float32(40.f), float32(56.5f));

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
		tempDef.position.Set(float32(58.f), float32(56.5f));

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
		tempDef.position.Set(float32(49.f), float32(59.f));

		tempBody = m_physicsWorld->CreateBody(&tempDef);
		tempBody->SetUserData((void*)entity);

		tempPhsBody = PhysicsBody(tempBody, 18, 1, vec2(0.f, 0.f), false);

		unsigned int bitHolder = EntityIdentifier::TransformBit() | EntityIdentifier::BlueButton2Bit();
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
		tempDef.position.Set(float32(109.f), float32(56.5f));

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
		tempDef.position.Set(float32(127.f), float32(56.5f));

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
		tempDef.position.Set(float32(118.f), float32(59.f));

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
		tempDef.position.Set(float32(155.5f), float32(-85.5f));

		tempBody = m_physicsWorld->CreateBody(&tempDef);

		tempBody->SetUserData((void*)entity);

		tempPhsBody = PhysicsBody(tempBody, float(tempSpr.GetWidth()), float(tempSpr.GetHeight()),
			vec2(0.f, 0.f), false);

		unsigned int bitHolder = EntityIdentifier::SpriteBit() | EntityIdentifier::TransformBit() | EntityIdentifier::AnimationBit() | EntityIdentifier::BlueElevatorBit();
		ECS::SetUpIdentifier(entity, bitHolder, "Blue Elevator");

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
		tempDef.position.Set(float32(12.f), float32(-85.5f));

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
		tempDef.position.Set(float32(-83.f), float32(51.5f));

		tempBody = m_physicsWorld->CreateBody(&tempDef);

		tempBody->SetUserData((void*)entity);

		tempPhsBody = PhysicsBody(tempBody, float(tempSpr.GetWidth()), float(tempSpr.GetHeight()),
			vec2(0.f, 0.f), false);

		unsigned int bitHolder = EntityIdentifier::SpriteBit() | EntityIdentifier::TransformBit() | EntityIdentifier::AnimationBit() | EntityIdentifier::BlueElevatorBit();
		ECS::SetUpIdentifier(entity, bitHolder, "Blue Elevator 2");

		m_elevator3 = entity;
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
		ECS::GetComponent<Transform>(entity).SetPosition(vec3(-151.f, 69.f, 100.f));

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
		tempDef.position.Set(float32(-152.f), float32(65.f));

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
		tempDef.position.Set(float32(-128.f), float32(58.f));

		tempBody = m_physicsWorld->CreateBody(&tempDef);
		tempBody->SetUserData((void*)entity);

		tempPhsBody = PhysicsBody(tempBody, 1, 14, vec2(0.f, 0.f), false);

		unsigned int bitHolder = EntityIdentifier::TransformBit();
		ECS::SetUpIdentifier(entity, bitHolder, "Right of Fruit Bowl");
	}
#pragma endregion

}

int LevelFour::GetBg1()
{
	return m_background;
}

int LevelFour::GetBg2()
{
	return m_background2;
}

int LevelFour::GetRedButton()
{
	return m_button3;
}

int LevelFour::GetBlueElevator()
{
	return m_elevator1;
}

int LevelFour::GetBlueElevator2()
{
	return m_elevator3;
}

int LevelFour::GetRedElevator()
{
	return m_elevator2;
}

int LevelFour::GetFruitBowl()
{
	return m_fruitBowl;
}


bool LevelFour::GetButtonOn1()
{
	return turnOn1;
}

bool LevelFour::GetButtonOn2()
{
	return turnOn2;
}

bool LevelFour::GetButtonOn3()
{
	return turnOn3;
}

int LevelFour::GetCam()
{
	return m_cam;
}

int LevelFour::GetBlueButton1()
{
	return m_button1;
}

int LevelFour::GetBlueButton2()
{
	return m_button2;
}
