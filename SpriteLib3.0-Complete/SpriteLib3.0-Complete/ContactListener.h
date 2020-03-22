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
	bool GetShake();
	void SetBGrounded(bool grounded);
	void SetWGrounded(bool grounded);
	void SetShake(bool shake);
	bool GetRedPressed();
	bool GetBounced();
	
	bool GetLevel1Cleared();
	void SetLevel1Cleared(bool isLevel1Cleared);

	bool GetLevel2Cleared();
	void SetLevel2Cleared(bool isLevel2Cleared);

private:

	bool bJump;
	bool wJump;
	bool bGrounded;
	bool wGrounded;
	bool buttonPressed;
	bool button2Pressed;
	bool bBowl;
	bool wBowl;
	bool shake;
	bool redButtonPressed;
	bool bounced;

	bool level1Cleared = false;
	bool level2Cleared = false;
};