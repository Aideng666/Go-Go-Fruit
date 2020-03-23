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

		std::string fileName = "LevelSelect1.png";

		ECS::GetComponent<Sprite>(entity).LoadSprite(fileName, 360, 202);
		ECS::GetComponent<Transform>(entity).SetPosition(vec3(0.f, 0.f, -99.f));

		unsigned int bitHolder = EntityIdentifier::SpriteBit() | EntityIdentifier::TransformBit();
		ECS::SetUpIdentifier(entity, bitHolder, "Level Select 1");

		m_menu = entity;
	}

	{
		auto entity = ECS::CreateEntity();
	
		ECS::AttachComponent<Sprite>(entity);
		ECS::AttachComponent<Transform>(entity);
	
		std::string fileName = "LevelPic1.png";
	
		ECS::GetComponent<Sprite>(entity).LoadSprite(fileName, 166, 94);
		ECS::GetComponent<Transform>(entity).SetPosition(vec3(0.f, 0.f, -98.f));
	
		unsigned int bitHolder = EntityIdentifier::SpriteBit() | EntityIdentifier::TransformBit();
		ECS::SetUpIdentifier(entity, bitHolder, "Level 1 Template");
	
		level1Template = entity;
	}
	
	{
		auto entity = ECS::CreateEntity();
	
		ECS::AttachComponent<Sprite>(entity);
		ECS::AttachComponent<Transform>(entity);
	
		std::string fileName = "LevelPic2.png";
	
		ECS::GetComponent<Sprite>(entity).LoadSprite(fileName, 166, 94);
		ECS::GetComponent<Sprite>(entity).SetTransparency(0.7f);
		ECS::GetComponent<Transform>(entity).SetPosition(vec3(220.f, 0.f, -98.f));
	
		unsigned int bitHolder = EntityIdentifier::SpriteBit() | EntityIdentifier::TransformBit();
		ECS::SetUpIdentifier(entity, bitHolder, "Level 2 Template");
	
		level2Template = entity;
	}
	
	{
		auto entity = ECS::CreateEntity();
	
		ECS::AttachComponent<Sprite>(entity);
		ECS::AttachComponent<Transform>(entity);
	
		std::string fileName = "LevelPic3.png";
	
		ECS::GetComponent<Sprite>(entity).LoadSprite(fileName, 166, 94);
		ECS::GetComponent<Sprite>(entity).SetTransparency(0.7f);
		ECS::GetComponent<Transform>(entity).SetPosition(vec3(-220.f, 0.f, -98.f));
	
		unsigned int bitHolder = EntityIdentifier::SpriteBit() | EntityIdentifier::TransformBit();
		ECS::SetUpIdentifier(entity, bitHolder, "Level 3 Template");
	
		level3Template = entity;
	}

	//Arrows
	{
		auto arrowAnim = File::LoadJSON("RightArrow.json");

		auto entity = ECS::CreateEntity();

		ECS::AttachComponent<Sprite>(entity);
		ECS::AttachComponent<Transform>(entity);
		ECS::AttachComponent<AnimationController>(entity);

		std::string fileName = "RightArrow.png";

		auto& animController = ECS::GetComponent<AnimationController>(entity);
		animController.InitUVs(fileName);

		animController.AddAnimation(arrowAnim["ArrowBlink"]);
		animController.GetAnimation(0);
		animController.SetActiveAnim(0);

		ECS::GetComponent<Sprite>(entity).LoadSprite(fileName, 50, 27, true, &animController);
		ECS::GetComponent<Transform>(entity).SetPosition(vec3(111.f, -4.f, -98.f));

		unsigned int bitHolder = EntityIdentifier::SpriteBit() | EntityIdentifier::TransformBit() | EntityIdentifier::AnimationBit();
		ECS::SetUpIdentifier(entity, bitHolder, "Right Arrow");

		m_right = entity;
	}

	{
		auto arrowAnim = File::LoadJSON("LeftArrow.json");

		auto entity = ECS::CreateEntity();

		ECS::AttachComponent<Sprite>(entity);
		ECS::AttachComponent<Transform>(entity);
		ECS::AttachComponent<AnimationController>(entity);

		std::string fileName = "LeftArrow.png";

		auto& animController = ECS::GetComponent<AnimationController>(entity);
		animController.InitUVs(fileName);

		animController.AddAnimation(arrowAnim["ArrowBlink"]);
		animController.GetAnimation(0);
		animController.SetActiveAnim(0);

		ECS::GetComponent<Sprite>(entity).LoadSprite(fileName, 50, 27, true, &animController);
		ECS::GetComponent<Transform>(entity).SetPosition(vec3(-111.f, -4.f, -98.f));

		unsigned int bitHolder = EntityIdentifier::SpriteBit() | EntityIdentifier::TransformBit() | EntityIdentifier::AnimationBit();
		ECS::SetUpIdentifier(entity, bitHolder, "Left Arrow");

		m_left = entity;
	}

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

void LevelSelectMain::Update()
{
	if (fade)
	{
		FadeBackground();
		timer += Timer::deltaTime;
		if (timer >= (m_repeatTime))
		{
			fade = false;
			timer = 0.f;

			vec4 temp = m_clearColor2;
			m_clearColor2 = m_clearColor1;
			m_clearColor1 = temp;

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

int LevelSelectMain::GetRight()
{
	return m_right;
}

int LevelSelectMain::GetLeft()
{
	return m_left;
}

int LevelSelectMain::GetPlay()
{
	return m_play;
}

int LevelSelectMain::GetLevel1Template()
{
	return level1Template;
}

int LevelSelectMain::GetLevel2Template()
{
	return level2Template;
}

int LevelSelectMain::GetLevel3Template()
{
	return level3Template;
}