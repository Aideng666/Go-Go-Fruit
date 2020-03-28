#include "LevelSelect4.h"
#include "Utilities.h"

LevelSelect4::LevelSelect4(std::string name)
	: Scene(name)
{
}

void LevelSelect4::InitScene(float windowWidth, float windowHeight)
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
		ECS::SetUpIdentifier(entity, bitHolder, "Level Select 4 Camera");
	}

	{
		auto entity = ECS::CreateEntity();

		ECS::AttachComponent<Sprite>(entity);
		ECS::AttachComponent<Transform>(entity);

		std::string fileName = "LevelSelectText.png";

		ECS::GetComponent<Sprite>(entity).LoadSprite(fileName, 100, 19);
		ECS::GetComponent<Transform>(entity).SetPosition(vec3(0.f, 84.f, -99.f));

		unsigned int bitHolder = EntityIdentifier::SpriteBit() | EntityIdentifier::TransformBit();
		ECS::SetUpIdentifier(entity, bitHolder, "Level Select Text");
	}

#pragma region Level Images
	{
		auto entity = ECS::CreateEntity();

		ECS::AttachComponent<Sprite>(entity);
		ECS::AttachComponent<Transform>(entity);

		std::string fileName = "LevelSelect1Temp.png";

		ECS::GetComponent<Sprite>(entity).LoadSprite(fileName, 100, 56);
		ECS::GetComponent<Sprite>(entity).SetTransparency(0.7f);
		ECS::GetComponent<Transform>(entity).SetPosition(vec3(-118.f, 42.f, -98.f));

		unsigned int bitHolder = EntityIdentifier::SpriteBit() | EntityIdentifier::TransformBit();
		ECS::SetUpIdentifier(entity, bitHolder, "Level Select 1");
	}

	{
		auto entity = ECS::CreateEntity();

		ECS::AttachComponent<Sprite>(entity);
		ECS::AttachComponent<Transform>(entity);

		std::string fileName = "LevelSelect2Temp.png";

		ECS::GetComponent<Sprite>(entity).LoadSprite(fileName, 100, 56);
		ECS::GetComponent<Sprite>(entity).SetTransparency(0.7f);
		ECS::GetComponent<Transform>(entity).SetPosition(vec3(0.f, 42.f, -98.f));

		unsigned int bitHolder = EntityIdentifier::SpriteBit() | EntityIdentifier::TransformBit();
		ECS::SetUpIdentifier(entity, bitHolder, "Level Select 2");
	}

	{
		auto entity = ECS::CreateEntity();

		ECS::AttachComponent<Sprite>(entity);
		ECS::AttachComponent<Transform>(entity);

		std::string fileName = "LevelSelect3Temp.png";

		ECS::GetComponent<Sprite>(entity).LoadSprite(fileName, 100, 56);
		ECS::GetComponent<Sprite>(entity).SetTransparency(0.7f);
		ECS::GetComponent<Transform>(entity).SetPosition(vec3(118.f, 42.f, -98.f));

		unsigned int bitHolder = EntityIdentifier::SpriteBit() | EntityIdentifier::TransformBit();
		ECS::SetUpIdentifier(entity, bitHolder, "Level Select 3");
	}

	{
		auto entity = ECS::CreateEntity();

		ECS::AttachComponent<Sprite>(entity);
		ECS::AttachComponent<Transform>(entity);

		std::string fileName = "LevelSelect4Temp.png";

		ECS::GetComponent<Sprite>(entity).LoadSprite(fileName, 100, 56);
		ECS::GetComponent<Transform>(entity).SetPosition(vec3(-118.f, -42.f, -98.f));

		unsigned int bitHolder = EntityIdentifier::SpriteBit() | EntityIdentifier::TransformBit();
		ECS::SetUpIdentifier(entity, bitHolder, "Level Select 4");
	}

	{
		auto entity = ECS::CreateEntity();

		ECS::AttachComponent<Sprite>(entity);
		ECS::AttachComponent<Transform>(entity);

		std::string fileName = "LevelSelect5Temp.png";

		ECS::GetComponent<Sprite>(entity).LoadSprite(fileName, 100, 56);
		ECS::GetComponent<Sprite>(entity).SetTransparency(0.7f);
		ECS::GetComponent<Transform>(entity).SetPosition(vec3(118.f, -42.f, -98.f));

		unsigned int bitHolder = EntityIdentifier::SpriteBit() | EntityIdentifier::TransformBit();
		ECS::SetUpIdentifier(entity, bitHolder, "Level Select 5");
	}
#pragma endregion

#pragma region Level Labels
	{
		auto entity = ECS::CreateEntity();

		ECS::AttachComponent<Sprite>(entity);
		ECS::AttachComponent<Transform>(entity);

		std::string fileName = "Level1Label.png";

		ECS::GetComponent<Sprite>(entity).LoadSprite(fileName, 50, 19);
		ECS::GetComponent<Transform>(entity).SetPosition(vec3(-117.f, 4.f, -98.f));

		unsigned int bitHolder = EntityIdentifier::SpriteBit() | EntityIdentifier::TransformBit();
		ECS::SetUpIdentifier(entity, bitHolder, "Level 1 Label");
	}

	{
		auto entity = ECS::CreateEntity();

		ECS::AttachComponent<Sprite>(entity);
		ECS::AttachComponent<Transform>(entity);

		std::string fileName = "Level2Label.png";

		ECS::GetComponent<Sprite>(entity).LoadSprite(fileName, 50, 19);
		ECS::GetComponent<Transform>(entity).SetPosition(vec3(0.f, 4.f, -98.f));

		unsigned int bitHolder = EntityIdentifier::SpriteBit() | EntityIdentifier::TransformBit();
		ECS::SetUpIdentifier(entity, bitHolder, "Level 2 Label");
	}

	{
		auto entity = ECS::CreateEntity();

		ECS::AttachComponent<Sprite>(entity);
		ECS::AttachComponent<Transform>(entity);

		std::string fileName = "Level3Label.png";

		ECS::GetComponent<Sprite>(entity).LoadSprite(fileName, 50, 19);
		ECS::GetComponent<Transform>(entity).SetPosition(vec3(117.f, 4.f, -98.f));

		unsigned int bitHolder = EntityIdentifier::SpriteBit() | EntityIdentifier::TransformBit();
		ECS::SetUpIdentifier(entity, bitHolder, "Level 3 Label");
	}

	{
		auto entity = ECS::CreateEntity();

		ECS::AttachComponent<Sprite>(entity);
		ECS::AttachComponent<Transform>(entity);

		std::string fileName = "Level4Label.png";

		ECS::GetComponent<Sprite>(entity).LoadSprite(fileName, 50, 19);
		ECS::GetComponent<Transform>(entity).SetPosition(vec3(-117.f, -80.f, -98.f));

		unsigned int bitHolder = EntityIdentifier::SpriteBit() | EntityIdentifier::TransformBit();
		ECS::SetUpIdentifier(entity, bitHolder, "Level 4 Label");
	}

	{
		auto entity = ECS::CreateEntity();

		ECS::AttachComponent<Sprite>(entity);
		ECS::AttachComponent<Transform>(entity);

		std::string fileName = "Level5Label.png";

		ECS::GetComponent<Sprite>(entity).LoadSprite(fileName, 50, 19);
		ECS::GetComponent<Transform>(entity).SetPosition(vec3(117.f, -80.f, -98.f));

		unsigned int bitHolder = EntityIdentifier::SpriteBit() | EntityIdentifier::TransformBit();
		ECS::SetUpIdentifier(entity, bitHolder, "Level 5 Label");
	}
#pragma endregion

	//Level Border
	{
		auto entity = ECS::CreateEntity();

		ECS::AttachComponent<Sprite>(entity);
		ECS::AttachComponent<Transform>(entity);

		std::string fileName = "Border.png";

		ECS::GetComponent<Sprite>(entity).LoadSprite(fileName, 100, 57);
		ECS::GetComponent<Transform>(entity).SetPosition(vec3(-118.f, -42.f, -97.f));

		unsigned int bitHolder = EntityIdentifier::SpriteBit() | EntityIdentifier::TransformBit();
		ECS::SetUpIdentifier(entity, bitHolder, "Border");
	}

	//Press Play Text
	{
		auto textAnim = File::LoadJSON("BlinkText.json");

		auto entity = ECS::CreateEntity();

		ECS::AttachComponent<Sprite>(entity);
		ECS::AttachComponent<Transform>(entity);
		ECS::AttachComponent<AnimationController>(entity);

		std::string fileName = "BlinkPlay.png";

		auto& animController = ECS::GetComponent<AnimationController>(entity);
		animController.InitUVs(fileName);

		animController.AddAnimation(textAnim["DrawText"]);
		animController.GetAnimation(0);
		animController.SetActiveAnim(0);

		ECS::GetComponent<Sprite>(entity).LoadSprite(fileName, 100, 30, true, &animController);
		ECS::GetComponent<Transform>(entity).SetPosition(vec3(0.f, -35.f, -97.f));

		unsigned int bitHolder = EntityIdentifier::SpriteBit() | EntityIdentifier::TransformBit() | EntityIdentifier::AnimationBit();
		ECS::SetUpIdentifier(entity, bitHolder, "Blink Play Text");

		//m_play = entity;
	}
}

void LevelSelect4::Update()
{
	RainbowBackground();
}

void LevelSelect4::RainbowBackground()
{
	m_clearColor = Util::Lerp<vec4>(m_clearColor3, m_clearColor4, m_lerpVal2);

	if (m_lerpVal2 >= 1.f)
	{
		vec4 temp = m_clearColor4;
		m_clearColor4 = m_clearColor3;
		m_clearColor3 = temp;

		m_lerpVal2 = 0.f;
	}

	m_lerpVal2 += Timer::deltaTime / m_repeatTime2;
}