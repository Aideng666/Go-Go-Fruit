#include "PhysicsSystem.h"
#include "PhysicsBody.h"

using namespace std;

void PhysicsSystem::Init()
{
	physicsDrawShader.Load("./assets/shader/PhysicsDraw.vert", "./assets/shader/PhysicsDraw.frag");
}

void PhysicsSystem::Update(entt::registry * reg)
{
	auto view = reg->view<PhysicsBody, Transform>();

	//Runs the update for the physics bodies
	for (auto entity : view)
	{
		//Grabs references to each component within view
		auto& physBod = view.get<PhysicsBody>(entity);
		auto& trans = view.get<Transform>(entity);

		//Updates physics body
		physBod.Update(&trans, Timer::deltaTime);
	}

	//Runs the various things
	//(currently just checking collisions)
	Run(reg);
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

void PhysicsSystem::Run(entt::registry* reg)
{


	auto view = reg->view<PhysicsBody, Transform>();

	for (auto entity : view)
	{
		auto& trans1 = view.get<Transform>(entity);
		auto& body1 = view.get<PhysicsBody>(entity);

		Box worldPosB;

		switch (body1.GetBodyType())
		{
		case BodyType::BOX:
			worldPosB.m_center = trans1.GetPosition() + vec3(body1.GetCenterOffset().x, body1.GetCenterOffset().y, 0.f);
			worldPosB.m_bottomLeft = trans1.GetPosition() + vec3(body1.GetBottomLeft().x, body1.GetBottomLeft().y, 0.f);
			worldPosB.m_topRight = trans1.GetPosition() + vec3(body1.GetTopRight().x, body1.GetTopRight().y, 0.f);
			worldPosB.m_bottomRight = vec3(worldPosB.m_topRight.x, worldPosB.m_bottomLeft.y, 0.f);
			worldPosB.m_topLeft = vec3(worldPosB.m_bottomLeft.x, worldPosB.m_topRight.y, 0.f);
			break;
		}

		if (body1.GetDynamic())
		{
			for (auto entity2 : view)
			{
				if (entity != entity2)
				{
					auto& trans2 = view.get<Transform>(entity2);
					auto& body2 = view.get<PhysicsBody>(entity2);

					Box worldPosB2;

					switch (body2.GetBodyType())
					{
					case BodyType::BOX:
						worldPosB2.m_center = trans2.GetPosition() + vec3(body2.GetCenterOffset().x, body2.GetCenterOffset().y, 0.f);
						worldPosB2.m_bottomLeft = trans2.GetPosition() + vec3(body2.GetBottomLeft().x, body2.GetBottomLeft().y, 0.f);
						worldPosB2.m_topRight = trans2.GetPosition() + vec3(body2.GetTopRight().x, body2.GetTopRight().y, 0.f);
						worldPosB2.m_bottomRight = vec3(worldPosB2.m_topRight.x, worldPosB2.m_bottomLeft.y, 0.f);
						worldPosB2.m_topLeft = vec3(worldPosB2.m_bottomLeft.x, worldPosB2.m_topRight.y, 0.f);
						break;
					}
					if (body1.GetBodyType() == BodyType::BOX)
					{
						if (body2.GetBodyType() == BodyType::BOX)
						{
							//Perform Box-Box collision
							if (BoxBoxCollision(std::pair<PhysicsBody&, Box>(body1, worldPosB), std::pair<PhysicsBody&, Box>(body2, worldPosB2))) 		
							{

								vec3 position1 = trans1.GetPosition();
								float tempWidth1 = body1.GetWidth() / 2;
								vec3 position2 = trans2.GetPosition();
								float tempWidth2 = body2.GetWidth() / 2;

								float front1 = position1.x + tempWidth1;
								float back1 = position1.x - tempWidth1;
								float front2 = position2.x + tempWidth2;
								float back2 = position2.x - tempWidth2;
								float bottom = trans1.GetPosition().y - (body1.GetHeight() / 2);
								float bottom2 = trans2.GetPosition().y - (body2.GetHeight() / 2);
								float top = trans1.GetPosition().y + (body1.GetHeight() / 2);
								float top2 = trans2.GetPosition().y + (body2.GetHeight() / 2);


								if ((front1 < back2 || back1 > front2) || (bottom > top2 || bottom2 > top))
								{
									body1.SetCanMoveL(true);
									body1.SetCanMoveR(true);
								}
								if (front1 >= back2 && (bottom < top2 && top > bottom2))
								{
									body1.SetCanMoveR(false);
									body1.SetCanMoveL(true);
									if (body2.GetType() == 0 || body2.GetType() == 1)
									{
										body2.SetCanMoveR(true);
										body2.SetCanMoveL(false);
									}
								}
								if (back1 <= front2 && (bottom < top2 && top > bottom2))
								{
									body1.SetCanMoveL(false);
									body1.SetCanMoveR(true);
									if (body2.GetType() == 0 || body2.GetType() == 1)
									{
										body2.SetCanMoveL(true);
										body2.SetCanMoveR(false);
									}
								}
								/*if (front1 <= back2)
								{
									cout << "HI";
									body1.SetCanMoveL(true);
								}
								if (back1 >= front2)
								{
									body1.SetCanMoveR(true);
								}*/
								/*else
								{

									if (front1 >= back2 && (body1.GetType() == 0 || body1.GetType() == 1))
									{

										if (body2.GetType() != 0 && body2.GetType() != 1)
										{
											trans1.SetPosition(vec3(trans1.GetPosition().x - 2.f, trans1.GetPosition().y, trans1.GetPosition().z));
										}
										if (body2.GetType() == 0 || body2.GetType() == 1)
										{
											trans1.SetPosition(vec3(trans1.GetPosition().x - 2.f, trans1.GetPosition().y, trans1.GetPosition().z));
											trans2.SetPosition(vec3(trans2.GetPosition().x + 2.f, trans2.GetPosition().y, trans2.GetPosition().z));
										}
									}
									if (back1 <= front2 && (body1.GetType() == 0 || body1.GetType() == 1))
									{
										if (body2.GetType() != 0 && body2.GetType() != 1)
										{
											trans1.SetPosition(vec3(trans1.GetPosition().x + 2.f, trans1.GetPosition().y, trans1.GetPosition().z));
										}
										else
										{
											trans1.SetPosition(vec3(trans1.GetPosition().x + 2.f, trans1.GetPosition().y, trans1.GetPosition().z));
											trans2.SetPosition(vec3(trans2.GetPosition().x - 2.f, trans2.GetPosition().y, trans2.GetPosition().z));
										}
									}
								}*/
								



								//Allows the players to jump after they have landed on something
								if (body1.GetType() == 0)
								{
									ECS::GetComponent<Transform>(EntityIdentifier::MainPlayer()).SetJump(true);
								}
								if (body1.GetType() == 1)
								{
									ECS::GetComponent<Transform>(EntityIdentifier::MainPlayer2()).SetJump(true);
								}	

								//Checks if a button was pressed
								if (body2.GetType() == 4)
								{
									body2.SetPressed(true);
								}

									trans1.SetPosition(trans1.GetPosition() + (-body1.GetVelocity() * (Timer::deltaTime)));
									body1.SetAcceleration(vec3(0.f, 0.f, 0.f));
									body1.SetVelocity(vec3(0.f, 0.f, 0.f));
								
							}		

						}
					}

				}
			}
		}
	}
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