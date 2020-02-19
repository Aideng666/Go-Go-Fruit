#include "PhysicsBody.h"

unsigned int CollisionIDs::m_playerID		=0x1;
unsigned int CollisionIDs::m_environmentID	=0x10;
unsigned int CollisionIDs::m_enemyID		=0x100;


unsigned int CollisionIDs::Player()
{
	return m_playerID;
}

unsigned int CollisionIDs::Environment()
{
	return m_environmentID;
}

unsigned int CollisionIDs::Enemy()
{
	return m_enemyID;
}

vec3 PhysicsBody::m_gravityAcceleration = vec3(0.f, -185.f, 0.f);//-35 | -175
bool PhysicsBody::m_drawBodies = false;

PhysicsBody::PhysicsBody(vec2 botLeft, vec2 topRight, vec2 centerOffset, unsigned int objectSpecifier, unsigned int collidesWith, bool isDynamic)
{
	m_bodyType = BodyType::BOX;

	m_bottomLeft = botLeft;
	m_topLeft = vec2(botLeft.x, topRight.y);
	m_topRight = topRight;
	m_bottomRight = vec2(topRight.x, botLeft.y);

	m_width = m_bottomRight.x - m_bottomLeft.x;
	m_height = m_topLeft.y - m_bottomLeft.y;

	m_centerOffset = centerOffset;

	m_bodyID = objectSpecifier;

	m_collideID = collidesWith;

	m_dynamic = isDynamic;

	InitBody();
}

PhysicsBody::PhysicsBody(float width, float height, vec2 centerOffset, unsigned int objectSpecifier, unsigned int collidesWith, int type, bool isDynamic)
{
	m_bodyType = BodyType::BOX;

	m_width = width;
	m_height = height;

	m_centerOffset = centerOffset;
	m_bottomLeft = vec2(centerOffset.x - (width / 2.f), centerOffset.y - (height / 2.f));
	m_bottomRight = vec2(centerOffset.x + (width / 2.f), centerOffset.y - (height / 2.f));
	m_topLeft = vec2(centerOffset.x - (width / 2.f), centerOffset.y + (height / 2.f));
	m_topRight = vec2(centerOffset.x + (width / 2.f), centerOffset.y + (height / 2.f));

	m_collideID = collidesWith;
	m_bodyID = objectSpecifier;

	m_dynamic = isDynamic;
	m_type = type;

	InitBody();
}

void PhysicsBody::InitBody()
{
	m_vao = VertexManager::CreateVAO();
	glBindVertexArray(m_vao);

	//Enable slot 0
	glEnableVertexAttribArray(0);	//Vertices

	//VBO positions
	m_vboPos = VertexManager::GetPlaneVertVBO();

	//Pushes away the warnings
#pragma warning(push)
#pragma warning(disable : 4312)
//Bind position buffer
	glBindBuffer(GL_ARRAY_BUFFER, m_vboPos);
	//Sets the attribute pointer
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, reinterpret_cast<void*>(0));
#pragma warning(pop)

	//Unbinds the buffers
	glBindBuffer(GL_ARRAY_BUFFER, GL_NONE);
	glBindVertexArray(GL_NONE);
}

void PhysicsBody::DrawBody()
{
	//Bind vao
	glBindVertexArray(m_vao);
	//Draw the points
	glDrawArrays(GL_TRIANGLES, 0, 6);
	//Unbind vao
	glBindVertexArray(GL_NONE);
}

void PhysicsBody::Update(Transform * trans, float dt)
{
	vec3 transPosition = trans->GetPosition();
	
	if (m_velocity.GetMagnitude() > 0.f)
	{
		if (m_applyGravity)
		{
			m_frictionForce = vec3(-m_velocity.x, 0.f, 0.f) * m_friction;
		}
		else
		{
			m_frictionForce = -m_velocity * m_friction;
		}
	}

	m_netForce = m_appliedForce + m_frictionForce;
	m_acceleration = (m_netForce / m_mass);

	if (m_applyGravity)
	{
		if (m_dynamic)
		{
			m_acceleration = m_acceleration + (m_gravityAcceleration * m_mass);
		}
	}

	m_frictionForce = vec3(0.f, 0.f, 0.f);
	m_appliedForce = vec3(0.f, 0.f, 0.f);

	float tempX = m_velocity.x;
	float tempY = m_velocity.y;

	m_velocity = m_velocity + (m_acceleration * dt);

	if (abs(m_velocity.x) > abs(m_maxVelo))
	{
		m_velocity.x = tempX;
	}
	if (abs(m_velocity.y) > abs(m_maxVelo))
	{
		m_velocity.y = tempY;
	}

	transPosition = transPosition + (m_velocity * dt);

	trans->SetPosition(transPosition);
}

void PhysicsBody::ApplyForce(vec3 force)
{
	m_appliedForce = m_appliedForce + force;
}

void PhysicsBody::AddCollideID(unsigned int collideID)
{
	//Bitwise OR an ID into the physics body types that this one collides with
	m_collideID |= collideID;
}


vec3 PhysicsBody::GetForce() const
{
	//Returns the applied force
	return m_appliedForce;
}

vec3 PhysicsBody::GetAcceleration() const
{
	//Returns current acceleration
	return m_acceleration;
}

float PhysicsBody::GetMaxVelo() const
{
	//Returns max velocity
	return m_maxVelo;
}

vec3 PhysicsBody::GetVelocity() const
{
	//Returns current velocity
	return m_velocity;
}

float PhysicsBody::GetFriction() const
{
	//Returns coefficient of friction
	return m_friction;
}

vec3 PhysicsBody::GetGravityAcceleration()
{
	//Returns the acceleration due to gravity
	return m_gravityAcceleration;
}

bool PhysicsBody::GetGravity() const
{
	//Is gravity being applied?
	return m_applyGravity;
}

float PhysicsBody::GetMass() const
{
	//Return the mass of this body
	return m_mass;
}


BodyType PhysicsBody::GetBodyType() const
{
	//What kinda physics body is this?
	return m_bodyType;
}

vec2 PhysicsBody::GetCenterOffset() const
{
	//return offset from the center of the sprite
	return m_centerOffset;
}

vec2 PhysicsBody::GetBottomLeft() const
{
	//return bottom left corner
	return m_bottomLeft;
}

vec2 PhysicsBody::GetBottomRight() const
{
	//return bottom right corner
	return m_bottomRight;
}

vec2 PhysicsBody::GetTopLeft() const
{
	//return top left corner
	return m_topLeft;
}

vec2 PhysicsBody::GetTopRight() const
{
	//return top right corner
	return m_topRight;
}

float PhysicsBody::GetWidth() const
{
	//return body width
	return m_width;
}

float PhysicsBody::GetHeight() const
{
	//return body height
	return m_height;
}

float PhysicsBody::GetRadius() const
{
	return m_radius;
}

unsigned int PhysicsBody::GetBodyID() const
{
	//Returns this physics body's type
	return m_bodyID;
}

unsigned int PhysicsBody::GetCollideID() const
{
	//Returns the ids (OR'd together) that this physics body collides with
	return m_collideID;
}

bool PhysicsBody::GetDynamic() const
{
	//Does this body move?
	return m_dynamic;
}

bool PhysicsBody::GetDraw()
{
	return m_drawBodies;
}

int PhysicsBody::GetType()
{
	return m_type;
}

void PhysicsBody::SetForce(vec3 force)
{
	//Set the applied force
	m_appliedForce = force;
}

void PhysicsBody::SetAcceleration(vec3 accel)
{
	//Set the acceleration
	m_acceleration = accel;
}

void PhysicsBody::SetMaxVelo(float velo)
{
	//Set the max velocity
	m_maxVelo = velo;
}

void PhysicsBody::SetVelocity(vec3 velo)
{
	//Set the velocitys
	m_velocity = velo;
}

void PhysicsBody::SetFriction(float fric)
{
	//Set the coefficient of friction
	m_friction = fric;
}

void PhysicsBody::SetGravityAcceleration(vec3 grav)
{
	//Set the acceleration due to gravity
	m_gravityAcceleration = grav;
}

void PhysicsBody::SetGravity(bool grav)
{
	//Is gravity applying to this object?
	m_applyGravity = grav;
}

void PhysicsBody::SetMass(float mass)
{
	//Set the mass of the body
	m_mass = mass;
}

void PhysicsBody::SetBodyType(BodyType type)
{
	//Set the type of body this is
	m_bodyType = type;
}

void PhysicsBody::SetCenterOffset(vec2 cent)
{
	//Set the center offset
	m_centerOffset = cent;
}

void PhysicsBody::SetBottomLeft(vec2 BL)
{
	//Set the bottom left corner
	m_bottomLeft = BL;
}

void PhysicsBody::SetBottomRight(vec2 BR)
{
	//Set the bottom right corner
	m_bottomRight = BR;
}

void PhysicsBody::SetTopLeft(vec2 TL)
{
	//Set the top left corner
	m_topLeft = TL;
}

void PhysicsBody::SetTopRight(vec2 TR)
{
	//Set the top right corner
	m_topRight = TR;
}

void PhysicsBody::SetWidth(float width)
{
	//Set the physics body width
	m_width = width;
}

void PhysicsBody::SetHeight(float height)
{
	//Sets the physics body height
	m_height = height;
}

void PhysicsBody::SetRadius(float radius)
{
	m_radius = radius;
}

void PhysicsBody::SetDraw(bool drawBodies)
{
	m_drawBodies = drawBodies;
}

void PhysicsBody::SetBodyID(unsigned int bodyID)
{
	//What type is this body?
	m_bodyID = bodyID;
}

void PhysicsBody::SetCollideID(unsigned int collideID)
{
	//What body types will this body collide with?
	m_collideID = collideID;
}

void PhysicsBody::SetDynamic(bool isDynamic)
{
	//Is this body moving?
	m_dynamic = isDynamic;
}

bool PhysicsBody::GetPressed()
{
	return isPressed;
}

void PhysicsBody::SetPressed(bool isPressed)
{
	this->isPressed = isPressed;
}

bool PhysicsBody::GetCanMove()
{
	return this->canMove;
}

void PhysicsBody::SetCanMove(bool canMove)
{
	this->canMove = canMove;
}

bool PhysicsBody::GetCanMoveL()
{
	return this->canMoveL;
}

void PhysicsBody::SetCanMoveL(bool canMove)
{
	this->canMoveL = canMove;
}

bool PhysicsBody::GetCanMoveR()
{
	return this->canMoveR;
}

void PhysicsBody::SetCanMoveR(bool canMove)
{
	this->canMoveR = canMove;
}




