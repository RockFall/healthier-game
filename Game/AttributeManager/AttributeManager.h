#ifndef GAME_MANAGER_H
#define GAME_MANAGER_H

#include <glm/glm.hpp>

#include "../GameContext/GameContext.h"

class Attribute;

// Responsible for creating attributes that unite
// Script and GameObject
// Also responsible for calling all Scripts Updates
class AttributeManager
{
public:
	//static std::map<std::string, Attribute> CurrentAttributes;

	// Creates all attributes Start function
	static void StartAttributes();
	// Calls every Script Update
	static void Update(float dt, bool keys[], glm::vec2 mousePos);
	// Creates and Adds an Attribute on a GameObject
	static void AddGameObjectAttribute(std::string GOName, std::string type);
};

#endif

