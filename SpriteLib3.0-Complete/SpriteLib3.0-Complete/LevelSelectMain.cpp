#include "LevelSelectMain.h"
#include "Utilities.h"
#include "Game.h"

LevelSelectMain::LevelSelectMain(std::string name)
	: Scene(name)
{
}

void LevelSelectMain::InitScene(float windowWidth, float windowHeight)
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
		ECS::SetUpIdentifier(entity, bitHolder, "Level Select Main Camera");
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
		ECS::GetComponent<Transform>(entity).SetPosition(vec3(-118.f, 42.f, -97.f));

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

#pragma region Medals
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
		ECS::GetComponent<Transform>(entity).SetPosition(vec3(-80.f, 60.f, 100.f));

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
		ECS::GetComponent<Transform>(entity).SetPosition(vec3(38.f, 60.f, 100.f));

		unsigned int bitHolder = EntityIdentifier::SpriteBit() | EntityIdentifier::TransformBit() | EntityIdentifier::AnimationBit();
		ECS::SetUpIdentifier(entity, bitHolder, "Lvl 2 Medal");

		m_medal2 = entity;
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
		ECS::GetComponent<Transform>(entity).SetPosition(vec3(156.f, 60.f, 100.f));

		unsigned int bitHolder = EntityIdentifier::SpriteBit() | EntityIdentifier::TransformBit() | EntityIdentifier::AnimationBit();
		ECS::SetUpIdentifier(entity, bitHolder, "Lvl 3 Medal");

		m_medal3 = entity;
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
		ECS::GetComponent<Transform>(entity).SetPosition(vec3(-80.f, -25.f, 100.f));

		unsigned int bitHolder = EntityIdentifier::SpriteBit() | EntityIdentifier::TransformBit() | EntityIdentifier::AnimationBit();
		ECS::SetUpIdentifier(entity, bitHolder, "Lvl 4 Medal");

		m_medal4 = entity;
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
		ECS::SetUpIdentifier(entity, bitHolder, "Lvl 5 Medal");

		m_medal5 = entity;
	}
#pragma endregion

}

void LevelSelectMain::Update()
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
}

void LevelSelectMain::FadeBackground()
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

void LevelSelectMain::RainbowBackground()
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

bool LevelSelectMain::GetFade()
{
	return fade;
}

void LevelSelectMain::SetFade(bool fade)
{
	this->fade = fade;
}

int LevelSelectMain::GetMenu()
{
	return m_menu;
}

int LevelSelectMain::GetSelect1()
{
	return select1;
}

int LevelSelectMain::GetSelect2()
{
	return select2;
}

int LevelSelectMain::GetSelect3()
{
	return select3;
}

int LevelSelectMain::GetSelect4()
{
	return select4;
}

int LevelSelectMain::GetSelect5()
{
	return select5;
}

int LevelSelectMain::GetLabel1()
{
	return label1;
}

int LevelSelectMain::GetLabel2()
{
	return label2;
}

int LevelSelectMain::GetLabel3()
{
	return label3;
}

int LevelSelectMain::GetLabel4()
{
	return label4;
}

int LevelSelectMain::GetLabel5()
{
	return label5;
}

int LevelSelectMain::GetText()
{
	return m_text;
}

int LevelSelectMain::GetBorder()
{
	return m_border;
}

int LevelSelectMain::GetPlay()
{
	return m_play;
}

int LevelSelectMain::GetMedal()
{
	return m_medal;
}

int LevelSelectMain::GetMedal2()
{
	return m_medal2;
}

int LevelSelectMain::GetMedal3()
{
	return m_medal3;
}

int LevelSelectMain::GetMedal4()
{
	return m_medal4;
}

int LevelSelectMain::GetMedal5()
{
	return m_medal5;
}