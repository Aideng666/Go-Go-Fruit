#include "ContactListener.h"
#include "Game.h"
#include "ECS.h"
#include "Box2D/Box2D.h"
#include "entt/entity/registry.hpp"
#include <iostream>

using namespace std;

void ContactListener::BeginContact(b2Contact* contact)
{
    auto fixtureA = contact->GetFixtureA();
    auto bodyA = fixtureA->GetBody();
    unsigned int entityA = (unsigned int)bodyA->GetUserData();

    auto identifierA = ECS::GetComponent<EntityIdentifier>(entityA).GetIdentifier();

    auto fixtureB = contact->GetFixtureB();
    auto bodyB = fixtureB->GetBody();
    unsigned int entityB = (unsigned int)bodyB->GetUserData();

    auto identifierB = ECS::GetComponent<EntityIdentifier>(entityB).GetIdentifier();

    if (fixtureA == NULL || fixtureB == NULL)
        return;

    if (fixtureA->GetUserData() == NULL || fixtureB->GetUserData() == NULL)
        return;

#pragma region Blueberry Collision
if (identifierA & EntityIdentifier::BlueberryBit())
{
    if (identifierB & EntityIdentifier::GroundBit())
    {
        bJump = true;
        bGrounded = true;
    }

    if (identifierB & EntityIdentifier::WatermelonBit())
    {
        bJump = true;
        wJump = true;
    }

    if (identifierB & EntityIdentifier::BlueButtonBit())
    {
        bJump = true;
        buttonPressed = true;
    }
}
#pragma endregion

#pragma region Watermelon Collision
if (identifierA & EntityIdentifier::WatermelonBit())
{
    if (identifierB & EntityIdentifier::GroundBit())
    {
        wJump = true;
        wGrounded = true;
    }

    if (identifierB & EntityIdentifier::BlueberryBit())
    {
        wJump = true;
    }

    if (identifierB & EntityIdentifier::BlueButtonBit())
    {
        wJump = true;
    }
}
#pragma endregion

}

void ContactListener::EndContact(b2Contact* contact)
{
    auto fixtureA = contact->GetFixtureA();
    auto bodyA = fixtureA->GetBody();
    unsigned int entityA = (unsigned int)bodyA->GetUserData();

    auto identifierA = ECS::GetComponent<EntityIdentifier>(entityA).GetIdentifier();

    auto fixtureB = contact->GetFixtureB();
    auto bodyB = fixtureB->GetBody();
    unsigned int entityB = (unsigned int)bodyB->GetUserData();

    auto identifierB = ECS::GetComponent<EntityIdentifier>(entityB).GetIdentifier();

    if (fixtureA == NULL || fixtureB == NULL)
        return;

    if (fixtureA->GetUserData() == NULL || fixtureB->GetUserData() == NULL)
        return;

#pragma region Blueberry Fallout
if (identifierA & EntityIdentifier::BlueberryBit())
{
    if (identifierB & EntityIdentifier::GroundBit())
    {
        bJump = false;
    }

    if (identifierB & EntityIdentifier::WatermelonBit())
    {
        bJump = false;
        wJump = false;
    }

    //Check if the blue button was pressed by the blueberry
    if (identifierB & EntityIdentifier::BlueButtonBit())
    {
        bJump = false;
        buttonPressed = false;
    }
}
#pragma endregion
    
#pragma region Watermelon Fallout
if (identifierA & EntityIdentifier::WatermelonBit())
{
    if (identifierB & EntityIdentifier::GroundBit())
    {
        wJump = false;
    }

    if (identifierB & EntityIdentifier::BlueberryBit())
    {
        wJump = false;
    }

    if (identifierB & EntityIdentifier::BlueButtonBit())
    {
        wJump = false;
    }
}
#pragma endregion

}

bool ContactListener::GetBJump() {
    return bJump;
}

bool ContactListener::GetWJump() {
    return wJump;
}

bool ContactListener::GetWGrounded() {
    return wGrounded;
}

bool ContactListener::GetBGrounded() {
    return bGrounded;
}

bool ContactListener::GetPressed()
{
    return buttonPressed;
}

void ContactListener::SetBGrounded(bool grounded) {
    bGrounded = grounded;
}

void ContactListener::SetWGrounded(bool grounded) {
    wGrounded = grounded;
}