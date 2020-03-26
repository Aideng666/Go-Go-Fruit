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
	bool SetBlue1Pressed(bool isPressed);
	bool Get2Pressed();
	bool SetBlue2Pressed(bool isPressed);
	bool GetBBowl();
	bool GetWBowl();
	bool GetShake();
	void SetBGrounded(bool grounded);
	void SetWGrounded(bool grounded);
	void SetShake(bool shake);
	bool GetRedPressed();
	bool SetRed1Pressed(bool isPressed);
	bool GetBounced();
	void SetBJump(bool jump);
	void SetWJump(bool jump);
	bool GetLevelCheck();
	void SetLevelCheck(bool levelCheck);
	bool GetLevelCleared(int spot);
	void SetLevelCleared(bool cleared, int spot);
	bool GetWin();
	void SetWin(bool win);

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
	bool win;

	bool levelCleared[3];
	bool levelCheck;
};