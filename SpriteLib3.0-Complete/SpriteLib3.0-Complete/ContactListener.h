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
	void SetBJump(bool jump);
	void SetWJump(bool jump);
	bool GetLevelCheck();
	void SetLevelCheck(bool levelCheck);
	bool GetLevelCleared(int spot);
	void SetLevelCleared(bool cleared, int spot);


private:

	bool bJump;
	bool wJump;
	bool bGrounded;
	bool wGrounded;
	bool buttonPressed;
	bool button2Pressed;
	bool bBowl = false;
	bool wBowl = false;
	bool shake;
	bool redButtonPressed;
	bool bounced;

	bool levelCleared[3];
	bool levelCheck;
};