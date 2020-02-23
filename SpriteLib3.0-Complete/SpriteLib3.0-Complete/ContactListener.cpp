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
        cout << "Blue hit Ground\n";
        bJump = false;
    }

    if (identifierB & EntityIdentifier::WatermelonBit())
    {
        cout << "Blue hit Water\n";
        bJump = false;
    }
}
#pragma endregion
    
#pragma region Watermelon Fallout
if (identifierA & EntityIdentifier::WatermelonBit())
{
    if (identifierB & EntityIdentifier::GroundBit())
    {
        cout << "Water hit Ground\n";
        wJump = false;
    }

    if (identifierB & EntityIdentifier::BlueberryBit())
    {
        cout << "Water hit Blue\n";
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

void ContactListener::SetBGrounded(bool grounded) {
    bGrounded = grounded;
}

void ContactListener::SetWGrounded(bool grounded) {
    wGrounded = grounded;
}