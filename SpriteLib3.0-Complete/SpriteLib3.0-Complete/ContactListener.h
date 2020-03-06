#pragma once
#include "Box2D/Box2D.h"
#include "entt/entity/registry.hpp"

class ContactListener : public b2ContactListener
{
public:
	ContactListener() { };
	void BeginContact(b2Contact* contact);
	void EndContact(b2Contact* contact);

	bool GetBJump();
	bool GetWJump();
	bool GetWGrounded();
	bool GetBGrounded();
	bool GetPressed();
	bool Get2Pressed();
	bool GetBBowl();
	bool GetWBowl();
	void SetBGrounded(bool grounded);
	void SetWGrounded(bool grounded);

private:

	bool bJump;
	bool wJump;
	bool bGrounded;
	bool wGrounded;
	bool buttonPressed;
	bool button2Pressed;
	bool bBowl;
	bool wBowl;
};

