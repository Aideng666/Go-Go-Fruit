#include "LevelSelect2.h"

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

		std::string fileName = "LevelSelect2.png";

		ECS::GetComponent<Sprite>(entity).LoadSprite(fileName, 360, 202);
		ECS::GetComponent<Transform>(entity).SetPosition(vec3(0.f, 0.f, -99.f));

		unsigned int bitHolder = EntityIdentifier::SpriteBit() | EntityIdentifier::TransformBit();
		ECS::SetUpIdentifier(entity, bitHolder, "Level Select 2");
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
	}

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

		ECS::GetComponent<Sprite>(entity).LoadSprite(fileName, 150, 20, true, &animController);
		ECS::GetComponent<Transform>(entity).SetPosition(vec3(0.f, -85.f, -97.f));

		unsigned int bitHolder = EntityIdentifier::SpriteBit() | EntityIdentifier::TransformBit() | EntityIdentifier::AnimationBit();
		ECS::SetUpIdentifier(entity, bitHolder, "Blink Play Text");
	}
}