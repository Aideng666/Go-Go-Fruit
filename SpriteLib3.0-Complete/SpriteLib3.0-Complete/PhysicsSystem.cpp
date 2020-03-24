#include "PhysicsSystem.h"
#include "PhysicsBody.h"

using namespace std;

void PhysicsSystem::Init()
{
	physicsDrawShader.Load("./assets/shader/PhysicsDraw.vert", "./assets/shader/PhysicsDraw.frag");
}

void PhysicsSystem::Update(entt::registry* reg, b2World& world)
{
	auto view = reg->view<PhysicsBody, Transform>();

	for (auto entity : view)
	{
		auto& physBod = view.get<PhysicsBody>(entity);
		auto& trans = view.get<Transform>(entity);

		physBod.Update(&trans);
	}

	Run(world);
}

void PhysicsSystem::Draw(entt::registry * reg)
{
	auto view = reg->view<PhysicsBody, Transform>();
	auto& cam = reg->get<Camera>(EntityIdentifier::MainCamera());

	if (PhysicsBody::GetDraw())
	{
		for (auto entity : view)
		{
			auto& physBody = view.get<PhysicsBody>(entity);
			auto& trans = view.get<Transform>(entity);

			//Temporary transform so we can actually draw the bodies
			Transform temp = trans;
			temp.SetScale(vec3(physBody.GetWidth(), physBody.GetHeight(), 1.f));
			//Sets the position so the center offset is still relevant
			temp.SetPosition(temp.GetPosition() + vec3(physBody.GetCenterOffset().x, physBody.GetCenterOffset().y, 0.f));
			//Puts the temporary transform for the physics body at the top z-layer
			temp.SetPositionZ(100.f);

			//Updates the transform to create model matrix
			temp.Update();

			std::string fileName = "Masks/";

			if (physBody.GetBodyType() == BodyType::BOX)
			{
				fileName += "SquareMask.png";
			}
			else if (physBody.GetBodyType() == BodyType::CIRCLE)
			{
				fileName += "CircleMask.png";
			}

			Texture* mask = TextureManager::FindTexture(fileName);

			//Binds the draw shader
			physicsDrawShader.Bind();

			//Sends the uniforms we need for drawing the bodies
			physicsDrawShader.SendUniform("uView", cam.GetView());
			physicsDrawShader.SendUniform("uProj", cam.GetProjection());
			physicsDrawShader.SendUniform("uModel", temp.GetLocalToWorldMatrix());
			physicsDrawShader.SendUniform("uColor", vec4(1.f, 0.f, 0.f, 0.3f));

			mask->Bind(0);

			//Draws the body
			physBody.DrawBody();

			mask->Unbind(0);

			//Unbinds the shader
			physicsDrawShader.Unbind();
		}
	}
}

void PhysicsSystem::Run(b2World & world)
{
	float32 timeStep = 1 / 60.f;

	int32 velocityIterations = 8;
	int32 positionIterations = 3;

	world.Step(timeStep, velocityIterations, positionIterations);
}

bool PhysicsSystem::BoxBoxCollision(std::pair<PhysicsBody&, Box> group1, std::pair<PhysicsBody&, Box> group2)
{
	//if body 1 actually collides with body 2
		//Perform AABB bounding box checks
	//else
		//There's no collision
	if (group1.first.GetCollideID() & group2.first.GetBodyID())
	{
		//Perform bounding box checks
		//Are the x-axes colliding?
		bool axisXCollide = group1.second.m_bottomRight.x >= group2.second.m_bottomLeft.x &&
			group2.second.m_bottomRight.x >= group1.second.m_bottomLeft.x;

		//Are the y-axes colliding?
		bool axisYCollide = group1.second.m_topLeft.y >= group2.second.m_bottomLeft.y &&
			group2.second.m_topLeft.y >= group1.second.m_bottomLeft.y;
		
		//If both axes are overlapping, it means the bodies are colliding
		//If not, then they're not colliding
		return axisXCollide && axisYCollide;
	}
	else
	{
		return false;
	}
}

bool PhysicsSystem::BoxBoxCollision2(std::pair<PhysicsBody&, Box> group1, std::pair<PhysicsBody&, Box> group2)
{
	//if body 1 actually collides with body 2
		//Perform AABB bounding box checks
	//else
		//There's no collision
	if (group1.first.GetCollideID() & group2.first.GetBodyID())
	{
		//Perform bounding box checks
		//Are the x-axes colliding?
		bool axisXCollide = group1.second.m_bottomRight.x >= group2.second.m_bottomLeft.x &&
			group2.second.m_bottomLeft.x >= group1.second.m_bottomRight.x;

		//Are the y-axes colliding?
		bool axisYCollide = group1.second.m_bottomRight.y >= group2.second.m_topLeft.y &&
			group2.second.m_bottomRight.y <= group1.second.m_topLeft.y;

		//If both axes are overlapping, it means the bodies are colliding
		//If not, then they're not colliding
		return axisXCollide && axisYCollide;
	}
	else
	{
		return false;
	}
}