#include "ContactListener.h"
#include "Game.h"
#include "ECS.h"
#include "Box2D/Box2D.h"
#include "entt/entity/registry.hpp"
#include <iostream>

using namespace std;

float impulse;
const float jumpForce = 2.f;

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
            bBowl = false;
            bGrounded = true;
        }
        //Collides with watermelon
        if (identifierB & EntityIdentifier::WatermelonBit())
        {
            bBowl = false;
            bJump = true;
            wJump = true;
        }
        //Level 1 Fruit Bowl
        if (identifierB & EntityIdentifier::FruitBowlBit())
        {
            bJump = true;
            bBowl = true;
        }
        //Collides with blue buttons
        if (identifierB & EntityIdentifier::BlueButtonBit())
        {
            bJump = true;
            bBowl = false;
            buttonPressed = true;
            bGrounded = true;
        }
        if (identifierB & EntityIdentifier::BlueButton2Bit())
        {
            bJump = true;
            bBowl = false;
            button2Pressed = true;
            bGrounded = true;
        }
        if (identifierB & EntityIdentifier::BlueElevatorBit())
        {
            bJump = true;
            bBowl = false;
            bGrounded = true;
        }
        //Collides with jello
        if (identifierB & EntityIdentifier::JelloBit())
        {
            bJump = false;
            bBowl = false;
            bounced = true;
            impulse = bodyA->GetMass() * -bodyA->GetLinearVelocity().y * jumpForce;
            bodyA->ApplyLinearImpulse(b2Vec2(0, impulse), bodyA->GetWorldCenter(), true);

            if (bodyA->GetLinearVelocity().y == 0)
            {
                bJump = true;
                bounced = false;
            }
        }
        if (identifierB & EntityIdentifier::RedButtonBit())
        {
            bJump = true;
            bBowl = false;
        }
        if (identifierB & EntityIdentifier::RedElevatorBit())
        {
            bJump = true;
            bBowl = false;
            bGrounded = true;
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
            if (bodyA->GetLinearVelocity().y < -1.f)
            {
                shake = true;
            }
            wBowl = false;
        }
        //Collides with blueberry
        if (identifierB & EntityIdentifier::BlueberryBit())
        {
            wJump = true;
            wBowl = false;
        }
        //Level 1 Fruit Bowl
        if (identifierB & EntityIdentifier::FruitBowlBit())
        {
            wJump = true;
            wBowl = true;
        }
        //Collides with blue buttons
        if (identifierB & EntityIdentifier::BlueButtonBit())
        {
            wJump = true;
            wBowl = false;
        }
        if (identifierB & EntityIdentifier::BlueButton2Bit())
        {
            wJump = true;
            wBowl = false;
        }
        if (identifierB & EntityIdentifier::BlueElevatorBit())
        {
            wJump = true;
            wBowl = false;
            wGrounded = true;
            if (bodyA->GetLinearVelocity().y < -1.f)
            {
                shake = true;
            }
        }
        //Collides with jello
        if (identifierB & EntityIdentifier::JelloBit())
        {
            wJump = false;
            wBowl = false;
            bounced = true;
            impulse = bodyA->GetMass() * -bodyA->GetLinearVelocity().y * jumpForce;
            bodyA->ApplyLinearImpulse(b2Vec2(0, impulse), bodyA->GetWorldCenter(), true);

            if (bodyA->GetLinearVelocity().y == 0)
            {
                wJump = true;
                bounced = false;
            }
        }
        if (identifierB & EntityIdentifier::RedButtonBit())
        {
            wJump = true;
            wBowl = false;
            wGrounded = true;
            redButtonPressed = true;
        }
        if (identifierB & EntityIdentifier::RedElevatorBit())
        {
            wJump = true;
            wBowl = false;
            wGrounded = true;
        }
    }
#pragma endregion

    if (bBowl && wBowl)
    {
        sndPlaySound("YouWin.wav", SND_FILENAME | SND_ASYNC);
        levelCheck = true;
    }
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
        bGrounded = false;
    }
    //Fruit Bowl
    if (identifierB & EntityIdentifier::FruitBowlBit())
    {
        bJump = false;
        bBowl = false;
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
    if (identifierB & EntityIdentifier::JelloBit())
    {
        bJump = false;
        bGrounded = false;
        bounced = false;

        if (bodyA->GetLinearVelocity().y == 0)
        {
            bJump = true;
        }
    }
    if (identifierB & EntityIdentifier::BlueElevatorBit())
    {
        bJump = false;
    }
    if (identifierB & EntityIdentifier::RedButtonBit())
    {
        bJump = false;
    }
    if (identifierB & EntityIdentifier::RedElevatorBit())
    {
        bJump = false;
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
        wGrounded = false;
    }
    //End of collision with blueberry
    if (identifierB & EntityIdentifier::BlueberryBit())
    {
        wJump = false;
        wGrounded = true;
    }
    //Fruit Bowl
    if (identifierB & EntityIdentifier::FruitBowlBit())
    {
        wJump = false;
        wBowl = false;
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
    if (identifierB & EntityIdentifier::JelloBit())
    {
        wJump = false;
        wGrounded = false;
        bounced = false;

        if (bodyA->GetLinearVelocity().y == 0)
        {
            wJump = true;
        }
    }
    if (identifierB & EntityIdentifier::BlueElevatorBit())
    {
        wJump = false;
    }
    if (identifierB & EntityIdentifier::RedButtonBit())
    {
        wJump = false;
        redButtonPressed = false;
    }
    if (identifierB & EntityIdentifier::RedElevatorBit())
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
bool ContactListener::GetBBowl()
{
    return bBowl;
}
bool ContactListener::GetWBowl()
{
    return wBowl;
}
bool ContactListener::GetShake()
{
    return shake;
}
void ContactListener::SetBGrounded(bool grounded) {
    bGrounded = grounded;
}
void ContactListener::SetWGrounded(bool grounded) {
    wGrounded = grounded;
}

void ContactListener::SetShake(bool shake)
{
    this->shake = shake;
}

bool ContactListener::GetRedPressed()
{
    return redButtonPressed;
}

bool ContactListener::GetBounced()
{
    return bounced;
}

void ContactListener::SetBJump(bool jump)
{
    this->bJump = jump;
}

void ContactListener::SetWJump(bool jump)
{
    this->wJump = jump;
}

bool ContactListener::GetLevelCheck()
{
    return levelCheck;
}

void ContactListener::SetLevelCheck(bool levelCheck)
{
    this->levelCheck = levelCheck;
}

bool ContactListener::GetLevelCleared(int spot)
{
    return levelCleared[spot];
}

void ContactListener::SetLevelCleared(bool cleared, int spot)
{
    levelCleared[spot] = cleared;
}