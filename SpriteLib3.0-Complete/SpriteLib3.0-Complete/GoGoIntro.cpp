#include "GoGoIntro.h"
#include "Utilities.h"

GoGoIntro::GoGoIntro(std::string name)
	: Scene(name)
{
}

void GoGoIntro::InitScene(float windowWidth, float windowHeight)
{
	m_sceneReg = new entt::registry;

	ECS::AttachRegister(m_sceneReg);

	float aspectRatio = windowWidth / windowHeight;

	{
		auto entity = ECS::CreateEntity();

		ECS::AttachComponent<Camera>(entity);
		vec4 temp = ECS::GetComponent<Camera>(entity).GetOrthoSize();
		ECS::GetComponent<Camera>(entity).SetWindowSize(vec2(float(windowWidth), float(windowHeight)));
		ECS::GetComponent<Camera>(entity).Orthographic(aspectRatio, temp.x, temp.y, temp.z, temp.w, -100.f, 100.f);

		unsigned int bitHolder = EntityIdentifier::CameraBit();
		ECS::SetUpIdentifier(entity, bitHolder, "Title Camera");
	}

	//Background Level Image
	{
		auto entity = ECS::CreateEntity();

		ECS::AttachComponent<Sprite>(entity);
		ECS::AttachComponent<Transform>(entity);

		std::string fileName = "GameIntro.png";

		ECS::GetComponent<Sprite>(entity).LoadSprite(fileName, 357, 212.7125);
		ECS::GetComponent<Transform>(entity).SetPosition(vec3(0.f, 6.f, 20.f));

		unsigned int bitHolder = EntityIdentifier::SpriteBit() | EntityIdentifier::TransformBit();
		ECS::SetUpIdentifier(entity, bitHolder, "Game Intro");
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

	//Fruit Bowl
	{
		auto fruitBowlAnim = File::LoadJSON("SaladBowl.json");

		auto entity = ECS::CreateEntity();

		ECS::AttachComponent<Sprite>(entity);
		ECS::AttachComponent<Transform>(entity);
		ECS::AttachComponent<AnimationController>(entity);
		ECS::AttachComponent<PhysicsBody>(entity);

		std::string fileName = "FruitBowlSS.png";

		auto& animController = ECS::GetComponent<AnimationController>(entity);
		animController.InitUVs(fileName);

		animController.AddAnimation(fruitBowlAnim["Smile"]);
		animController.GetAnimation(0);
		animController.AddAnimation(fruitBowlAnim["Shine"]);
		animController.GetAnimation(1);
		animController.SetActiveAnim(1);

		auto& tempSpr = ECS::GetComponent<Sprite>(entity);
		auto& tempPhsBody = ECS::GetComponent<PhysicsBody>(entity);

		b2Body* tempBody;
		b2BodyDef tempDef;
		tempDef.type = b2_kinematicBody;
		tempDef.position.Set(float32(0.f), float32(-74.f));

		tempBody = m_physicsWorld->CreateBody(&tempDef);
		tempBody->SetUserData((void*)entity);

		tempPhsBody = PhysicsBody(tempBody, float(tempSpr.GetWidth()), float(tempSpr.GetHeight()),
			vec2(0.f, 0.f), false);

		ECS::GetComponent<Sprite>(entity).LoadSprite(fileName, 52, 30, true, &animController);
		ECS::GetComponent<Transform>(entity).SetPosition(vec3(0.f, -74.f, 99.f));

		unsigned int bitHolder = EntityIdentifier::SpriteBit() | EntityIdentifier::TransformBit() | EntityIdentifier::AnimationBit();
		ECS::SetUpIdentifier(entity, bitHolder, "Fruit Bowl Anim");

		bowl = entity;
	}

	//Blink Text
	{
		auto textAnim = File::LoadJSON("BlinkText.json");

		auto entity = ECS::CreateEntity();

		ECS::AttachComponent<Sprite>(entity);
		ECS::AttachComponent<Transform>(entity);
		ECS::AttachComponent<AnimationController>(entity);

		std::string fileName = "BlinkText.png";

		auto& animController = ECS::GetComponent<AnimationController>(entity);
		animController.InitUVs(fileName);

		animController.AddAnimation(textAnim["DrawText"]);
		animController.GetAnimation(0);
		animController.SetActiveAnim(0);

		ECS::GetComponent<Sprite>(entity).LoadSprite(fileName, 150, 35, true, &animController);
		ECS::GetComponent<Transform>(entity).SetPosition(vec3(0.f, 0.f, 99.f));

		unsigned int bitHolder = EntityIdentifier::SpriteBit() | EntityIdentifier::TransformBit() | EntityIdentifier::AnimationBit();
		ECS::SetUpIdentifier(entity, bitHolder, "Text");

		text = entity;
	}
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
		tempDef.position.Set(float32(-200.f), float32(-70.f));

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

		berry = entity;
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
		tempDef.position.Set(float32(-240.f), float32(-72.f));

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

		melon = entity;

	}
	//Intro Texts
	{
		auto entity = ECS::CreateEntity();

		ECS::AttachComponent<Sprite>(entity);
		ECS::AttachComponent<Transform>(entity);

		std::string fileName = "IntroText1.png";

		ECS::GetComponent<Sprite>(entity).LoadSprite(fileName, 375, 200);
		ECS::GetComponent<Transform>(entity).SetPosition(vec3(0.f, 0.f, -99.f));

		unsigned int bitHolder = EntityIdentifier::SpriteBit() | EntityIdentifier::TransformBit();
		ECS::SetUpIdentifier(entity, bitHolder, "Text 1");

		text1 = entity;
	}
	{
		auto entity = ECS::CreateEntity();

		ECS::AttachComponent<Sprite>(entity);
		ECS::AttachComponent<Transform>(entity);

		std::string fileName = "IntroText2.png";

		ECS::GetComponent<Sprite>(entity).LoadSprite(fileName, 375, 200);
		ECS::GetComponent<Transform>(entity).SetPosition(vec3(0.f, 0.f, -99.f));

		unsigned int bitHolder = EntityIdentifier::SpriteBit() | EntityIdentifier::TransformBit();
		ECS::SetUpIdentifier(entity, bitHolder, "Text 2");

		text2 = entity;
	}
	{
		auto entity = ECS::CreateEntity();

		ECS::AttachComponent<Sprite>(entity);
		ECS::AttachComponent<Transform>(entity);

		std::string fileName = "IntroText3.png";

		ECS::GetComponent<Sprite>(entity).LoadSprite(fileName, 375, 200);
		ECS::GetComponent<Transform>(entity).SetPosition(vec3(0.f, 0.f, -99.f));

		unsigned int bitHolder = EntityIdentifier::SpriteBit() | EntityIdentifier::TransformBit();
		ECS::SetUpIdentifier(entity, bitHolder, "Text 3");

		text3 = entity;
	}
#pragma endregion

}

void GoGoIntro::Update()
{
	PlayIntro();
}

int GoGoIntro::GetBg1()
{
	return m_bg;
}

int GoGoIntro::GetBg2()
{
	return m_bg2;
}

bool GoGoIntro::GetEnd()
{
	return end;
}

void GoGoIntro::SetStart(bool start)
{
	this->start = start;
}

void GoGoIntro::PlayIntro()
{

	auto blueBody = ECS::GetComponent<PhysicsBody>(berry).GetBody();
	auto waterBody = ECS::GetComponent<PhysicsBody>(melon).GetBody();
	auto bowlBody = ECS::GetComponent<PhysicsBody>(bowl).GetBody();
	auto bowlTrans = ECS::GetComponent<Transform>(bowl);
	auto blueTrans = ECS::GetComponent<Transform>(berry);
	auto waterTrans = ECS::GetComponent<Transform>(melon);


	if (start)
	{

		step1 = true;
		start = false;

		ECS::DestroyEntity(text);
		sndPlaySound("Intro Music.wav", SND_FILENAME | SND_ASYNC);
	}

	if (step1)
	{
		timer += Timer::deltaTime;
		ECS::GetComponent<Transform>(text1).SetPosition(vec3(0.f, 0.f, 100.f));

		if (timer > 5.f)
		{
			ECS::DestroyEntity(text1);
			timer = 0.f;
			step1 = false;
			step2 = true;
		}
	}

	if (step2)
	{
		timer += Timer::deltaTime;

		blueBody->SetLinearVelocity(b2Vec2(5, 0));
		waterBody->SetLinearVelocity(b2Vec2(5, 0));

		std::cout << timer << std::endl;

		if (timer > 2.f)
		{
			blueBody->SetLinearVelocity(b2Vec2(0, 0));
			waterBody->SetLinearVelocity(b2Vec2(0, 0));
			timer = 0.f;
			step2 = false;
			step3 = true;
		}

	}

	if (step3)
	{
		timer += Timer::deltaTime;

		blueBody->SetLinearVelocity(b2Vec2(0, 2));
		waterBody->SetLinearVelocity(b2Vec2(0, 2));

		if (timer > 0.5f)
		{
			blueBody->SetLinearVelocity(b2Vec2(0, 0));
			waterBody->SetLinearVelocity(b2Vec2(0, 0));
			timer = 0.f;
			step3 = false;
			step4 = true;

		}

	}

	if (step4)
	{
		timer += Timer::deltaTime;

		blueBody->SetLinearVelocity(b2Vec2(0, -2));
		waterBody->SetLinearVelocity(b2Vec2(0, -2));

		if (timer > 0.5f)
		{
			blueBody->SetLinearVelocity(b2Vec2(0, 0));
			waterBody->SetLinearVelocity(b2Vec2(0, 0));
			timer = 0.f;
			step4 = false;
			step5 = true;
		}

	}

	if (step5)
	{
		timer += Timer::deltaTime;
		ECS::GetComponent<Transform>(text2).SetPosition(vec3(0.f, 0.f, 100.f));

		if (timer > 5.f)
		{
			ECS::DestroyEntity(text2);
			timer = 0.f;
			step5 = false;
			step6 = true;
			sndPlaySound("Whoosh.wav", SND_FILENAME | SND_ASYNC);
		}
	}

	if (step6)
	{
		timer += Timer::deltaTime;

		bowlBody->SetAngularVelocity(-0.5);
		bowlBody->SetLinearVelocity(b2Vec2(12, 2));

		if (timer > 2.f)
		{
			timer = 0.f;
			step6 = false;
			step7 = true;
			sndPlaySound("Run.wav", SND_FILENAME | SND_ASYNC);
		}
	}

	if (step7)
	{
		timer += Timer::deltaTime;

		blueBody->SetLinearVelocity(b2Vec2(8, 0));
		waterBody->SetLinearVelocity(b2Vec2(8, 0));

		if (timer > 2.f)
		{
			timer = 0.f;
			step7 = false;
			step8 = true;
		}
	}

	if (step8)
	{
		timer += Timer::deltaTime;
		ECS::GetComponent<Transform>(text3).SetPosition(vec3(0.f, 0.f, 100.f));

		if (timer > 4.f)
		{
			ECS::DestroyEntity(text3);
			timer = 0.f;
			step8 = false;
			end = true;
		}
	}



}
