#ifndef GAME_EDITOR_H
#define GAME_EDITOR_H

#include <map>
#include <string>
#include <math.h>

#include "../../Engine/GameObject/GameObject.h"
#include "../GameContext/GameContext.h"
#include "../../Engine/SoundPlayer/SoundPlayer.h"

class AttributeManager;

// Responsible for controlling the creation and destruction of
// GameObjects on the current scene, besides the initial scene
// setup (GameObjects created mannualy i.e. background, player)
class GameEditor
{
public:
	// Hard-coded: Will be replaced in the future with the addition of a Scene
	// that contains all information of the current Game
	static unsigned int GAME_OFFSET;
	static unsigned int GAME_WIDTH;
	static unsigned int GAME_HEIGHT;

	// Creates and loads all GameObjects defined for the begining of the game
	static void LoadInitialScene();

	// Rule: The GameObject must have the same name as it's script (i.e. Enemy)
	// 	   This function is responsible for giving the GO it's ID (i.e. Enemy_3)
	// 	   
	// 'name': Name of the GameObject; must be the same as the Script and (optionally) Texture
	// 'pos': glm::vec2 position where the GameObject will be created on
	// 'hasSprite': Must be false if the GameObject is supposed to be invisible
	// 'size': glm::vec2 of the size of the object, conventionally multiple of 10 (and a square)
	// 'hasScript': Must be false if the GameObject is supposed to not have a script
	// 'texName': Used for cases when the name of the Texture is different from the name
	static std::string CreateGameObject(std::string name, glm::vec2 pos, bool hasSprite = true, glm::vec2 size = glm::vec2(100.0f, 100.0f), bool hasScript = true, std::string texName = "default", std::string scriptName = "default");

	// From a given name (i.e. Enemy_0), marks the GameObject 
	// of given name as to be destroyed at the end of Update()
	static void DestroyGameObject(std::string name);

	// Sets the given GameObject as Solid so it can be collided with
	static void GameObjectSetSolid(std::string name, bool isSolid);

	static void PlayerDeathScene(float dt);
private:
	// Private constructor so this static class cannot be wrongfully instantiated
	GameEditor() { }

};

#endif