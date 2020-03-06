#include "GoGoMenu.h"
#include "Utilities.h"
#include "Timer.h"

GoGoMenu::GoGoMenu(std::string name)
	: Scene(name)
{
}

void GoGoMenu::InitScene(float windowWidth, float windowHeight)
{
	m_sceneReg = new entt::registry;

	ECS::AttachRegister(m_sceneReg);

	float aspectRatio = windowWidth / windowHeight;

	//Main Menu Camera
	{
		auto entity = ECS::CreateEntity();

		ECS::AttachComponent<Camera>(entity);
		vec4 temp = ECS::GetComponent<Camera>(entity).GetOrthoSize();
		ECS::GetComponent<Camera>(entity).SetWindowSize(vec2(float(windowWidth), float(windowHeight)));
		ECS::GetComponent<Camera>(entity).Orthographic(aspectRatio, temp.x, temp.y, temp.z, temp.w, -100.f, 100.f);

		unsigned int bitHolder = EntityIdentifier::CameraBit();
		ECS::SetUpIdentifier(entity, bitHolder, "Main Menu Camera");
	}

	//Menu Image
	{
		auto entity = ECS::CreateEntity();


		ECS::AttachComponent<Sprite>(entity);
		ECS::AttachComponent<Transform>(entity);

		std::string fileName = "PlayScreen.png";

		ECS::GetComponent<Sprite>(entity).LoadSprite(fileName, 384, 200);
		ECS::GetComponent<Transform>(entity).SetPosition(vec3(0.f, 0.f, -99.f));

		unsigned int bitHolder = EntityIdentifier::SpriteBit() | EntityIdentifier::TransformBit();
		ECS::SetUpIdentifier(entity, bitHolder, "Go Go Fruit Menu");

		m_menu = entity;
	}

}



void GoGoMenu::Update()
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


void GoGoMenu::FadeBackground()
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

bool GoGoMenu::GetFade()
{
	return this->fade;
}
int GoGoMenu::GetMenu()
{
	return m_menu;
}
void GoGoMenu::SetFade(bool fade)
{
	this->fade = fade;
}

