#include "GoGoExit.h"

GoGoExit::GoGoExit(std::string name)
	: Scene(name)
{
}

void GoGoExit::InitScene(float windowWidth, float windowHeight)
{
	m_sceneReg = new entt::registry;

	ECS::AttachRegister(m_sceneReg);

	float aspectRatio = windowWidth / windowHeight;

	//Exit Camera
	{
		auto entity = ECS::CreateEntity();

		ECS::AttachComponent<Camera>(entity);
		vec4 temp = ECS::GetComponent<Camera>(entity).GetOrthoSize();
		ECS::GetComponent<Camera>(entity).SetWindowSize(vec2(float(windowWidth), float(windowHeight)));
		ECS::GetComponent<Camera>(entity).Orthographic(aspectRatio, temp.x, temp.y, temp.z, temp.w, -100.f, 100.f);

		unsigned int bitHolder = EntityIdentifier::CameraBit();
		ECS::SetUpIdentifier(entity, bitHolder, "Exit Camera");
	}

	//Exit Image
	{
		auto entity = ECS::CreateEntity();

		ECS::AttachComponent<Sprite>(entity);
		ECS::AttachComponent<Transform>(entity);

		std::string fileName = "Select2.png";

		ECS::GetComponent<Sprite>(entity).LoadSprite(fileName, 360.f, 202.f);
		ECS::GetComponent<Transform>(entity).SetPosition(vec3(0.f, 0.f, -99.f));

		unsigned int bitHolder = EntityIdentifier::SpriteBit() | EntityIdentifier::TransformBit();
		ECS::SetUpIdentifier(entity, bitHolder, "Go Go Fruit Exit");
	}

	//Spikes 1
	{
		auto entity = ECS::CreateEntity();

		ECS::AttachComponent<Sprite>(entity);
		ECS::AttachComponent<Transform>(entity);

		std::string fileName = "MovingSpikes.png";

		ECS::GetComponent<Sprite>(entity).LoadSprite(fileName, 360.f, 400.f);
		ECS::GetComponent<Transform>(entity).SetPosition(vec3(0.f, 0.f, -98.f));

		unsigned int bitHolder = EntityIdentifier::SpriteBit() | EntityIdentifier::TransformBit();
		ECS::SetUpIdentifier(entity, bitHolder, "Moving Spikes 1");

		m_spike1 = entity;
	}
	//Spikes 2
	{
		auto entity = ECS::CreateEntity();

		ECS::AttachComponent<Sprite>(entity);
		ECS::AttachComponent<Transform>(entity);

		std::string fileName = "MovingSpikes.png";

		ECS::GetComponent<Sprite>(entity).LoadSprite(fileName, 360.f, 400.f);
		ECS::GetComponent<Transform>(entity).SetPosition(vec3(0.f, 400.f, -98.f));

		unsigned int bitHolder = EntityIdentifier::SpriteBit() | EntityIdentifier::TransformBit();
		ECS::SetUpIdentifier(entity, bitHolder, "Moving Spikes 2");

		m_spike2 = entity;
	}
}

int GoGoExit::GetSpike1()
{
	return m_spike1;
}

int GoGoExit::GetSpike2()
{
	return m_spike2;
}
