#include "ContactListener.h"
#include "Game.h"
#include "ECS.h"
#include "Box2D/Box2D.h"
#include "entt/entity/registry.hpp"
#include <iostream>

using namespace std;

void ContactListener::BeginContact(b2Contact* contact)
{
    //Identifies the first player
    auto fixtureA = contact->GetFixtureA();
    auto bodyA = fixtureA->GetBody();
    unsigned int entityA = (unsigned int)bodyA->GetUserData();
    auto identifierA = ECS::GetComponent<EntityIdentifier>(entityA).GetIdentifier();

    //Identifies the second player
    auto fixtureB = contact->GetFixtureB();
    auto bodyB = fixtureB->GetBody();
    unsigned int entityB = (unsigned int)bodyB->GetUserData();
    auto identifierB = ECS::GetComponent<EntityIdentifier>(entityB).GetIdentifier();

    //Checks to make sure the players are valid
    if (fixtureA == NULL || fixtureB == NULL)
        return;
    if (fixtureA->GetUserData() == NULL || fixtureB->GetUserData() == NULL)
        return;

#pragma region Blueberry Collision
if (identifierA & EntityIdentifier::BlueberryBit())
{
    //Collides with ground bit
    if (identifierB & EntityIdentifier::GroundBit())
    {
        bJump = true;
        bGrounded = true;
    }
    //Collides with watermelon
    if (identifierB & EntityIdentifier::WatermelonBit())
    {
        bJump = true;
        wJump = true;
    }
    //Collides with blue buttons
    if (identifierB & EntityIdentifier::BlueButtonBit())
    {
        bJump = true;
        buttonPressed = true;
    }
    if (identifierB & EntityIdentifier::BlueButton2Bit())
    {
        bJump = true;
        button2Pressed = true;
    }
    //Collides with jello
    if (identifierB & EntityIdentifier::JelloBit())
    {
        float impulse = bodyA->GetMass() * -bodyA->GetLinearVelocity().y * 2;
        bodyA->ApplyLinearImpulse(b2Vec2(0, impulse), bodyA->GetWorldCenter(), true);
    }
}
#pragma endregion

#pragma region Watermelon Collision
if (identifierA & EntityIdentifier::WatermelonBit())
{
    //Collides with ground
    if (identifierB & EntityIdentifier::GroundBit())
    {
        wJump = true;
        wGrounded = true;
    }
    //Collides with blueberry
    if (identifierB & EntityIdentifier::BlueberryBit())
    {
        wJump = true;
    }
    //Collides with blue buttons
    if (identifierB & EntityIdentifier::BlueButtonBit())
    {
        wJump = true;
    }
    if (identifierB & EntityIdentifier::BlueButton2Bit())
    {
        wJump = true;
    }
    //Collides with jello
    if (identifierB & EntityIdentifier::JelloBit())
    {
        float impulse = bodyA->GetMass() * -bodyA->GetLinearVelocity().y * 2;
        bodyA->ApplyLinearImpulse(b2Vec2(0, impulse), bodyA->GetWorldCenter(), true);
    }
}
#pragma endregion
}

void ContactListener::EndContact(b2Contact* contact)
{
    //Identifies first player
    auto fixtureA = contact->GetFixtureA();
    auto bodyA = fixtureA->GetBody();
    unsigned int entityA = (unsigned int)bodyA->GetUserData();
    auto identifierA = ECS::GetComponent<EntityIdentifier>(entityA).GetIdentifier();

    //Identifies second player
    auto fixtureB = contact->GetFixtureB();
    auto bodyB = fixtureB->GetBody();
    unsigned int entityB = (unsigned int)bodyB->GetUserData();
    auto identifierB = ECS::GetComponent<EntityIdentifier>(entityB).GetIdentifier();

    //Checks to make sure the players are valid
    if (fixtureA == NULL || fixtureB == NULL)
        return;
    if (fixtureA->GetUserData() == NULL || fixtureB->GetUserData() == NULL)
        return;

#pragma region Blueberry Fallout
if (identifierA & EntityIdentifier::BlueberryBit())
{
    //End of collision with ground
    if (identifierB & EntityIdentifier::GroundBit())
    {
        bJump = false;
    }
    //End of collision with watermelon
    if (identifierB & EntityIdentifier::WatermelonBit())
    {
        bJump = false;
        wJump = false;
    }
    //End of collision with blue buttons
    if (identifierB & EntityIdentifier::BlueButtonBit())
    {
        bJump = false;
        buttonPressed = false;
    }
    if (identifierB & EntityIdentifier::BlueButton2Bit())
    {
        bJump = false;
        button2Pressed = false;
    }

}
#pragma endregion
    
#pragma region Watermelon Fallout
if (identifierA & EntityIdentifier::WatermelonBit())
{
    //End of collision with ground
    if (identifierB & EntityIdentifier::GroundBit())
    {
        wJump = false;
    }
    //End of collision with blueberry
    if (identifierB & EntityIdentifier::BlueberryBit())
    {
        wJump = false;
    }
    //End of collision with blue buttons
    if (identifierB & EntityIdentifier::BlueButtonBit())
    {
        wJump = false;
    }
    if (identifierB & EntityIdentifier::BlueButton2Bit())
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
bool ContactListener::Get2Pressed()
{
    return button2Pressed;
}
void ContactListener::SetBGrounded(bool grounded) {
    bGrounded = grounded;
}
void ContactListener::SetWGrounded(bool grounded) {
    wGrounded = grounded;
}