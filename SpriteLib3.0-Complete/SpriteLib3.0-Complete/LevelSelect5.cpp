#include "LevelSelect5.h"
#include "Utilities.h"

LevelSelect5::LevelSelect5(std::string name)
	: Scene(name)
{
}

void LevelSelect5::InitScene(float windowWidth, float windowHeight)
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
		ECS::SetUpIdentifier(entity, bitHolder, "Level Select 5 Camera");
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

		m_text = entity;
	}

#pragma region Level Images
	{
		auto entity = ECS::CreateEntity();

		ECS::AttachComponent<Sprite>(entity);
		ECS::AttachComponent<Transform>(entity);

		std::string fileName = "LevelSelect1Temp.png";

		ECS::GetComponent<Sprite>(entity).LoadSprite(fileName, 100, 56);
		ECS::GetComponent<Transform>(entity).SetPosition(vec3(-118.f, 42.f, -98.f));

		unsigned int bitHolder = EntityIdentifier::SpriteBit() | EntityIdentifier::TransformBit();
		ECS::SetUpIdentifier(entity, bitHolder, "Level Select 1");

		select1 = entity;
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

		select2 = entity;
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

		select3 = entity;
	}

	{
		auto entity = ECS::CreateEntity();

		ECS::AttachComponent<Sprite>(entity);
		ECS::AttachComponent<Transform>(entity);

		std::string fileName = "LevelSelect4Temp.png";

		ECS::GetComponent<Sprite>(entity).LoadSprite(fileName, 100, 56);
		ECS::GetComponent<Sprite>(entity).SetTransparency(0.7f);
		ECS::GetComponent<Transform>(entity).SetPosition(vec3(-118.f, -42.f, -98.f));

		unsigned int bitHolder = EntityIdentifier::SpriteBit() | EntityIdentifier::TransformBit();
		ECS::SetUpIdentifier(entity, bitHolder, "Level Select 4");

		select4 = entity;
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

		select5 = entity;
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

		label1 = entity;
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

		label2 = entity;
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

		label3 = entity;
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

		label4 = entity;
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

		label5 = entity;
	}
#pragma endregion

	//Level Border
	{
		auto entity = ECS::CreateEntity();

		ECS::AttachComponent<Sprite>(entity);
		ECS::AttachComponent<Transform>(entity);

		std::string fileName = "Border.png";

		ECS::GetComponent<Sprite>(entity).LoadSprite(fileName, 100, 57);
		ECS::GetComponent<Transform>(entity).SetPosition(vec3(118.f, -42.f, -97.f));

		unsigned int bitHolder = EntityIdentifier::SpriteBit() | EntityIdentifier::TransformBit();
		ECS::SetUpIdentifier(entity, bitHolder, "Border");

		m_border = entity;
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

		ECS::GetComponent<Sprite>(entity).LoadSprite(fileName, 130, 39, true, &animController);
		ECS::GetComponent<Transform>(entity).SetPosition(vec3(0.f, -35.f, -97.f));

		unsigned int bitHolder = EntityIdentifier::SpriteBit() | EntityIdentifier::TransformBit() | EntityIdentifier::AnimationBit();
		ECS::SetUpIdentifier(entity, bitHolder, "Blink Play Text");

		m_play = entity;
	}


	{
		auto medalAnim = File::LoadJSON("Medal.json");

		auto entity = ECS::CreateEntity();

		ECS::AttachComponent<Sprite>(entity);
		ECS::AttachComponent<Transform>(entity);
		ECS::AttachComponent<AnimationController>(entity);

		std::string fileName = "MedalSS.png";

		auto& animController = ECS::GetComponent<AnimationController>(entity);
		animController.InitUVs(fileName);

		animController.AddAnimation(medalAnim["Shine"]);
		animController.GetAnimation(0);
		animController.SetActiveAnim(0);

		ECS::GetComponent<Sprite>(entity).LoadSprite(fileName, 15, 15, true, &animController);
		ECS::GetComponent<Sprite>(entity).SetTransparency(0.f);
		ECS::GetComponent<Transform>(entity).SetPosition(vec3(156.f, -25.f, 100.f));

		unsigned int bitHolder = EntityIdentifier::SpriteBit() | EntityIdentifier::TransformBit() | EntityIdentifier::AnimationBit();
		ECS::SetUpIdentifier(entity, bitHolder, "Medal");

		m_medal = entity;
	}

	{
		auto medalAnim = File::LoadJSON("Medal.json");

		auto entity = ECS::CreateEntity();

		ECS::AttachComponent<Sprite>(entity);
		ECS::AttachComponent<Transform>(entity);
		ECS::AttachComponent<AnimationController>(entity);

		std::string fileName = "MedalSS.png";

		auto& animController = ECS::GetComponent<AnimationController>(entity);
		animController.InitUVs(fileName);

		animController.AddAnimation(medalAnim["Shine"]);
		animController.GetAnimation(0);
		animController.SetActiveAnim(0);

		ECS::GetComponent<Sprite>(entity).LoadSprite(fileName, 15, 15, true, &animController);
		ECS::GetComponent<Sprite>(entity).SetTransparency(0.f);
		ECS::GetComponent<Transform>(entity).SetPosition(vec3(-80.f, -60.f, 100.f));

		unsigned int bitHolder = EntityIdentifier::SpriteBit() | EntityIdentifier::TransformBit() | EntityIdentifier::AnimationBit();
		ECS::SetUpIdentifier(entity, bitHolder, "Lvl 1 Medal");

		m_medal2 = entity;
	}
}

void LevelSelect5::Update()
{
	RainbowBackground();

	if (fade)
	{
		FadeBackground();
		timer += Timer::deltaTime;
		if (timer >= (m_repeatTime * 2))
		{
			fade = false;
			timer = 0.f;
		}
	}
	else
	{
		timer = 0;
	}
}

void LevelSelect5::FadeBackground()
{
	m_clearColor = Util::Lerp<vec4>(m_clearColor1, m_clearColor2, m_lerpVal);

	if (m_lerpVal >= 1.f)
	{
		vec4 temp = m_clearColor2;
		m_clearColor2 = m_clearColor1;
		m_clearColor1 = temp;

		m_lerpVal = 0.f;
	}

	m_lerpVal += Timer::deltaTime / m_repeatTime;
}

void LevelSelect5::RainbowBackground()
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

bool LevelSelect5::GetFade()
{
	return fade;
}

void LevelSelect5::SetFade(bool fade)
{
	this->fade = fade;
}

int LevelSelect5::GetMenu()
{
	return m_menu;
}

int LevelSelect5::GetSelect1()
{
	return select1;
}

int LevelSelect5::GetSelect2()
{
	return select2;
}

int LevelSelect5::GetSelect3()
{
	return select3;
}

int LevelSelect5::GetSelect4()
{
	return select4;
}

int LevelSelect5::GetSelect5()
{
	return select5;
}

int LevelSelect5::GetLabel1()
{
	return label1;
}

int LevelSelect5::GetLabel2()
{
	return label2;
}

int LevelSelect5::GetLabel3()
{
	return label3;
}

int LevelSelect5::GetLabel4()
{
	return label4;
}

int LevelSelect5::GetLabel5()
{
	return label5;
}

int LevelSelect5::GetText()
{
	return m_text;
}

int LevelSelect5::GetBorder()
{
	return m_border;
}

int LevelSelect5::GetPlay()
{
	return m_play;
}

int LevelSelect5::GetMedal()
{
	return m_medal;
}

int LevelSelect5::GetMedal2()
{
	return m_medal2;
}
