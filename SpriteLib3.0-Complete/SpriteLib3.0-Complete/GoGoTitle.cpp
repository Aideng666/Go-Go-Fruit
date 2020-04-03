#include "GoGoTitle.h"
#include "Utilities.h"

GoGoTitle::GoGoTitle(std::string name)
	: Scene(name)
{
}

void GoGoTitle::InitScene(float windowWidth, float windowHeight)
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

	//Title Image
	{
		auto entity = ECS::CreateEntity();

		ECS::AttachComponent<Sprite>(entity);
		ECS::AttachComponent<Transform>(entity);

		std::string fileName = "TitleScreen.png";

		ECS::GetComponent<Sprite>(entity).LoadSprite(fileName, 375, 200);
		ECS::GetComponent<Transform>(entity).SetPosition(vec3(0.f, 0.f, -99.f));

		unsigned int bitHolder = EntityIdentifier::SpriteBit() | EntityIdentifier::TransformBit();
		ECS::SetUpIdentifier(entity, bitHolder, "Go Go Fruit Title");

		m_image = entity;
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
		ECS::GetComponent<Transform>(entity).SetPosition(vec3(0.f, -53.f, 99.f));

		unsigned int bitHolder = EntityIdentifier::SpriteBit() | EntityIdentifier::TransformBit() | EntityIdentifier::AnimationBit();
		ECS::SetUpIdentifier(entity, bitHolder, "Text");

		m_text = entity;
	}

	//Red Stripe
	{
		auto entity = ECS::CreateEntity();

		ECS::AttachComponent<Sprite>(entity);
		ECS::AttachComponent<Transform>(entity);

		std::string fileName = "RedStripe.png";

		ECS::GetComponent<Sprite>(entity).LoadSprite(fileName, 375, 200);
		ECS::GetComponent<Transform>(entity).SetPosition(vec3(0.f, 0.f, -98.f));

		unsigned int bitHolder = EntityIdentifier::SpriteBit() | EntityIdentifier::TransformBit();
		ECS::SetUpIdentifier(entity, bitHolder, "Red Stripe");

		m_redStripe = entity;
	}

	//Blue Stripe
	{
		auto entity = ECS::CreateEntity();

		ECS::AttachComponent<Sprite>(entity);
		ECS::AttachComponent<Transform>(entity);

		std::string fileName = "BlueStripe.png";

		ECS::GetComponent<Sprite>(entity).LoadSprite(fileName, 375, 200);
		ECS::GetComponent<Transform>(entity).SetPosition(vec3(0.f, 0.f, -98.f));

		unsigned int bitHolder = EntityIdentifier::SpriteBit() | EntityIdentifier::TransformBit();
		ECS::SetUpIdentifier(entity, bitHolder, "Blue Stripe");

		m_blueStripe = entity;
	}

	{
		auto entity = ECS::CreateEntity();
	
		ECS::AttachComponent<Sprite>(entity);
		ECS::AttachComponent<Transform>(entity);
	
		std::string fileName = "Loading.png";
	
		ECS::GetComponent<Sprite>(entity).LoadSprite(fileName, 375, 200);
		ECS::GetComponent<Sprite>(entity).SetTransparency(0.f);
		ECS::GetComponent<Transform>(entity).SetPosition(vec3(0.f, 0.f, -100.f));
	
		unsigned int bitHolder = EntityIdentifier::SpriteBit() | EntityIdentifier::TransformBit();
		ECS::SetUpIdentifier(entity, bitHolder, "Loading");
	
		m_loading = entity;
	}
}

void GoGoTitle::Update()
{
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

void GoGoTitle::FadeBackground()
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

bool GoGoTitle::GetFade()
{
	return fade;
}

void GoGoTitle::SetFade(bool fade)
{
	this->fade = fade;
}