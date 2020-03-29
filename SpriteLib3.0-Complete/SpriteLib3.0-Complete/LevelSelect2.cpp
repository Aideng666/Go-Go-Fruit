#include "LevelSelect2.h"
#include "Utilities.h"

LevelSelect2::LevelSelect2(std::string name)
	: Scene(name)
{
}

void LevelSelect2::InitScene(float windowWidth, float windowHeight)
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
		ECS::SetUpIdentifier(entity, bitHolder, "Level Select 2 Camera");
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
		ECS::GetComponent<Sprite>(entity).SetTransparency(0.7f);
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
		ECS::GetComponent<Transform>(entity).SetPosition(vec3(0.f, 42.f, -97.f));

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

		ECS::GetComponent<Sprite>(entity).LoadSprite(fileName, 100, 30, true, &animController);
		ECS::GetComponent<Transform>(entity).SetPosition(vec3(0.f, -35.f, -97.f));

		unsigned int bitHolder = EntityIdentifier::SpriteBit() | EntityIdentifier::TransformBit() | EntityIdentifier::AnimationBit();
		ECS::SetUpIdentifier(entity, bitHolder, "Blink Play Text");

		m_play = entity;
	}

	//{
	//	auto entity = ECS::CreateEntity();

	//	ECS::AttachComponent<Sprite>(entity);
	//	ECS::AttachComponent<Transform>(entity);

	//	std::string fileName = "LevelSelect2.png";

	//	ECS::GetComponent<Sprite>(entity).LoadSprite(fileName, 360, 202);
	//	ECS::GetComponent<Transform>(entity).SetPosition(vec3(0.f, 0.f, -99.f));

	//	unsigned int bitHolder = EntityIdentifier::SpriteBit() | EntityIdentifier::TransformBit();
	//	ECS::SetUpIdentifier(entity, bitHolder, "Level Select 2");

	//	m_menu = entity;
	//}

	//{
	//	auto entity = ECS::CreateEntity();

	//	ECS::AttachComponent<Sprite>(entity);
	//	ECS::AttachComponent<Transform>(entity);

	//	std::string fileName = "LevelPic2.png";

	//	ECS::GetComponent<Sprite>(entity).LoadSprite(fileName, 166, 94);
	//	ECS::GetComponent<Sprite>(entity).SetTransparency(0.7f);
	//	ECS::GetComponent<Transform>(entity).SetPosition(vec3(0.f, 0.f, -98.f));

	//	unsigned int bitHolder = EntityIdentifier::SpriteBit() | EntityIdentifier::TransformBit();
	//	ECS::SetUpIdentifier(entity, bitHolder, "Level 2 Template");

	//	level2Template = entity;
	//}

	//{
	//	auto entity = ECS::CreateEntity();

	//	ECS::AttachComponent<Sprite>(entity);
	//	ECS::AttachComponent<Transform>(entity);

	//	std::string fileName = "LevelPic1.png";

	//	ECS::GetComponent<Sprite>(entity).LoadSprite(fileName, 166, 94);
	//	ECS::GetComponent<Transform>(entity).SetPosition(vec3(-220.f, 0.f, -98.f));

	//	unsigned int bitHolder = EntityIdentifier::SpriteBit() | EntityIdentifier::TransformBit();
	//	ECS::SetUpIdentifier(entity, bitHolder, "Level 1 Template");

	//	level1Template = entity;
	//}

	//{
	//	auto entity = ECS::CreateEntity();

	//	ECS::AttachComponent<Sprite>(entity);
	//	ECS::AttachComponent<Transform>(entity);

	//	std::string fileName = "LevelPic3.png";

	//	ECS::GetComponent<Sprite>(entity).LoadSprite(fileName, 166, 94);
	//	ECS::GetComponent<Sprite>(entity).SetTransparency(0.7f);
	//	ECS::GetComponent<Transform>(entity).SetPosition(vec3(220.f, 0.f, -98.f));

	//	unsigned int bitHolder = EntityIdentifier::SpriteBit() | EntityIdentifier::TransformBit();
	//	ECS::SetUpIdentifier(entity, bitHolder, "Level 3 Template");

	//	level3Template = entity;
	//}

	////Arrows
	//{
	//	auto arrowAnim = File::LoadJSON("RightArrow.json");

	//	auto entity = ECS::CreateEntity();

	//	ECS::AttachComponent<Sprite>(entity);
	//	ECS::AttachComponent<Transform>(entity);
	//	ECS::AttachComponent<AnimationController>(entity);

	//	std::string fileName = "RightArrow.png";

	//	auto& animController = ECS::GetComponent<AnimationController>(entity);
	//	animController.InitUVs(fileName);

	//	animController.AddAnimation(arrowAnim["ArrowBlink"]);
	//	animController.GetAnimation(0);
	//	animController.SetActiveAnim(0);

	//	ECS::GetComponent<Sprite>(entity).LoadSprite(fileName, 50, 27, true, &animController);
	//	ECS::GetComponent<Transform>(entity).SetPosition(vec3(111.f, -4.f, -98.f));

	//	unsigned int bitHolder = EntityIdentifier::SpriteBit() | EntityIdentifier::TransformBit() | EntityIdentifier::AnimationBit();
	//	ECS::SetUpIdentifier(entity, bitHolder, "Right Arrow");

	//	m_right = entity;
	//}

	//{
	//	auto arrowAnim = File::LoadJSON("LeftArrow.json");

	//	auto entity = ECS::CreateEntity();

	//	ECS::AttachComponent<Sprite>(entity);
	//	ECS::AttachComponent<Transform>(entity);
	//	ECS::AttachComponent<AnimationController>(entity);

	//	std::string fileName = "LeftArrow.png";

	//	auto& animController = ECS::GetComponent<AnimationController>(entity);
	//	animController.InitUVs(fileName);

	//	animController.AddAnimation(arrowAnim["ArrowBlink"]);
	//	animController.GetAnimation(0);
	//	animController.SetActiveAnim(0);

	//	ECS::GetComponent<Sprite>(entity).LoadSprite(fileName, 50, 27, true, &animController);
	//	ECS::GetComponent<Transform>(entity).SetPosition(vec3(-111.f, -4.f, -98.f));

	//	unsigned int bitHolder = EntityIdentifier::SpriteBit() | EntityIdentifier::TransformBit() | EntityIdentifier::AnimationBit();
	//	ECS::SetUpIdentifier(entity, bitHolder, "Left Arrow");

	//	m_left = entity;
	//}

	//{
	//	auto medalAnim = File::LoadJSON("Medal.json");

	//	auto entity = ECS::CreateEntity();

	//	ECS::AttachComponent<Sprite>(entity);
	//	ECS::AttachComponent<Transform>(entity);
	//	ECS::AttachComponent<AnimationController>(entity);

	//	std::string fileName = "MedalSS.png";

	//	auto& animController = ECS::GetComponent<AnimationController>(entity);
	//	animController.InitUVs(fileName);

	//	animController.AddAnimation(medalAnim["Shine"]);
	//	animController.GetAnimation(0);
	//	animController.SetActiveAnim(0);

	//	ECS::GetComponent<Sprite>(entity).LoadSprite(fileName, 20, 20, true, &animController);
	//	ECS::GetComponent<Sprite>(entity).SetTransparency(0.f);
	//	ECS::GetComponent<Transform>(entity).SetPosition(vec3(70.f, 34.f, 100.f));

	//	unsigned int bitHolder = EntityIdentifier::SpriteBit() | EntityIdentifier::TransformBit() | EntityIdentifier::AnimationBit();
	//	ECS::SetUpIdentifier(entity, bitHolder, "Medal");

	//	m_medal = entity;
	//}

	//{
	//	auto textAnim = File::LoadJSON("BlinkText.json");
	//
	//	auto entity = ECS::CreateEntity();
	//
	//	ECS::AttachComponent<Sprite>(entity);
	//	ECS::AttachComponent<Transform>(entity);
	//	ECS::AttachComponent<AnimationController>(entity);
	//
	//	std::string fileName = "BlinkPlay.png";
	//
	//	auto& animController = ECS::GetComponent<AnimationController>(entity);
	//	animController.InitUVs(fileName);
	//
	//	animController.AddAnimation(textAnim["DrawText"]);
	//	animController.GetAnimation(0);
	//	animController.SetActiveAnim(0);
	//
	//	ECS::GetComponent<Sprite>(entity).LoadSprite(fileName, 110, 33, true, &animController);
	//	ECS::GetComponent<Transform>(entity).SetPosition(vec3(0.f, -85.f, -97.f));
	//
	//	unsigned int bitHolder = EntityIdentifier::SpriteBit() | EntityIdentifier::TransformBit() | EntityIdentifier::AnimationBit();
	//	ECS::SetUpIdentifier(entity, bitHolder, "Blink Play Text");
	//
	//	m_play = entity;
	//}
}

void LevelSelect2::Update()
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

void LevelSelect2::FadeBackground()
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

void LevelSelect2::RainbowBackground()
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

bool LevelSelect2::GetFade()
{
	return fade;
}

void LevelSelect2::SetFade(bool fade)
{
	this->fade = fade;
}

int LevelSelect2::GetMenu()
{
	return m_menu;
}

int LevelSelect2::GetSelect1()
{
	return select1;
}

int LevelSelect2::GetSelect2()
{
	return select2;
}

int LevelSelect2::GetSelect3()
{
	return select3;
}

int LevelSelect2::GetSelect4()
{
	return select4;
}

int LevelSelect2::GetSelect5()
{
	return select5;
}

int LevelSelect2::GetLabel1()
{
	return label1;
}

int LevelSelect2::GetLabel2()
{
	return label2;
}

int LevelSelect2::GetLabel3()
{
	return label3;
}

int LevelSelect2::GetLabel4()
{
	return label4;
}

int LevelSelect2::GetLabel5()
{
	return label5;
}

int LevelSelect2::GetText()
{
	return m_text;
}

int LevelSelect2::GetBorder()
{
	return m_border;
}

int LevelSelect2::GetPlay()
{
	return m_play;
}

int LevelSelect2::GetMedal()
{
	return m_medal;
}

int LevelSelect2::GetLevel1Template()
{
	return level1Template;
}

int LevelSelect2::GetLevel2Template()
{
	return level2Template;
}

int LevelSelect2::GetLevel3Template()
{
	return level3Template;
}