#ifndef __ENTITYIDENTIFIER_H__
#define __ENTITYIDENTIFIER_H__

#include "JSON.h"

class EntityIdentifier
{
public:
	//Adds the bit identifier to the whole identifier
	void AddComponent(unsigned int component);

	//Getters
	//Gets main player entity
	static unsigned int MainPlayer();
	bool GetIsMainPlayer() const;

	static unsigned int MainPlayer2();
	bool GetIsMainPlayer2() const;

	//Gets main camera entity
	static unsigned int MainCamera();
	bool GetIsMainCamera() const;
	//Get entity number
	unsigned int GetEntity() const;
	//Get identifier bitfield
	unsigned int GetIdentifier() const;
	//Get Name
	std::string GetName() const;
	//Get if this entity is selected
	bool& GetSelected();
	//Gets the actual bit for the specified type
	static unsigned int CameraBit();
	static unsigned int SpriteBit();
	static unsigned int TransformBit();
	static unsigned int AnimationBit();
	static unsigned int PhysicsBit();
	static unsigned int HoriScrollCameraBit();
	static unsigned int VertScrollCameraBit();
	static unsigned int BlueberryBit();
	static unsigned int WatermelonBit();
	static unsigned int GroundBit();
	static unsigned int BlueButtonBit();
	static unsigned int BlueElevatorBit();
	static unsigned int JelloBit();
	static unsigned int BlueButton2Bit();
	static unsigned int FruitBowlBit();
	static unsigned int RedButtonBit();
	static unsigned int RedElevatorBit();

	//Setters
	//Sets main player entity
	static void MainPlayer(unsigned int entity);
	void SetIsMainPlayer(bool main);

	static void MainPlayer2(unsigned int entity);
	void SetIsMainPlayer2(bool main);

	//Sets main camera entity
	static void MainCamera(unsigned int entity);
	void SetIsMainCamera(bool main);
	//Set entity number
	void SetEntity(unsigned int entity);
	//Set identifier bitfield
	void SetIdentifier(unsigned int identity);
	//Set the name
	void SetName(std::string name);
	//Set whether this entity is selected
	void SetSelected(bool selected);

private:
	//Main player
	static unsigned int m_mainPlayer;
	bool m_isMainPlayer = false;

	static unsigned int m_mainPlayer2;
	bool m_isMainPlayer2 = false;

	//Main camera
	static unsigned int m_mainCamera;
	bool m_isMainCamera = false;


	//Stores the entity number
	unsigned int m_entity = 0;
	//Stores the bit(s) of the types attached to this entity
	unsigned int m_identifier = 0;

	//Stores the name
	std::string m_name = "";
	//Stores if this entity is selected
	bool m_selected = false;

	//Stores the bit for the specified type
	static unsigned int m_cameraBit;
	static unsigned int m_spriteBit;
	static unsigned int m_transformBit;
	static unsigned int m_animationBit;
	static unsigned int m_physicsBit;
	static unsigned int m_horiScrollCameraBit;
	static unsigned int m_vertScrollCameraBit;
	static unsigned int m_blueberryBit;
	static unsigned int m_watermelonBit;
	static unsigned int m_groundBit;
	static unsigned int m_buttonBit;
	static unsigned int m_blueElevatorBit;
	static unsigned int m_jelloBit;
	static unsigned int m_blueButton2Bit;
	static unsigned int m_fruitBowlBit;
	static unsigned int m_redButtonBit;
	static unsigned int m_redElevatorBit;
};

#ifndef __ENTITYIDENTIFIERJSON_H__
#define __ENTITYIDENTIFIERJSON_H__

//Sends animation TO json file
inline void to_json(nlohmann::json& j, const EntityIdentifier& id)
{
	//Stores the identifier so that later I can know exactly what components are attached to each entity
	j["Identifier"] = id.GetIdentifier();

	//Stores whether or not this is the main camera
	j["MainCamera"] = id.GetIsMainCamera();

	//Stores whether or not this is the main player
	j["MainPlayer"] = id.GetIsMainPlayer();

	//Stores whether or not this is the main player 2
	j["MainPlayer2"] = id.GetIsMainPlayer2();

	//Stores the name of this entity
	j["Name"] = id.GetName();
}

//Reads animation in FROM json file
inline void from_json(const nlohmann::json& j, EntityIdentifier& id)
{
	//Grab the identifier
	id.SetIdentifier(j["Identifier"]);

	//Grabs whether or not this is the main camera
	id.SetIsMainCamera(j["MainCamera"]);

	//Grabs whether or not this is the main player
	id.SetIsMainPlayer(j["MainPlayer"]);

	//Grabs whether or not this is the main player 2
	id.SetIsMainPlayer2(j["MainPlayer2"]);

	//Grabs the name of this entity
	id.SetName(j["Name"]);
}

#endif // !__ENTITYIDENTIFIERJSON_H__


#endif // !__ENTITYIDENTIFIER_H__
