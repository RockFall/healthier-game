#ifndef GAME_LEVEL_H
#define GAME_LEVEL_H

#include "../BaseBehaviour.h"

#include <set>
#include <vector>

// Controls the levels of the game - Reads level data from a .txt file
// and creates all the enemies, making some 'dive' from time to time
// When all enemies are dead, goes to next Level
class GameLevel : BaseBehaviour
{
public:
	// ------ CONSTRUCTORS ------
	GameLevel() : gameObject(nullptr), enemies(), level(0), diverCountDown(0.0f), timeBetweenDivers(0.0f), amountOfDivers(0) { };
	GameLevel(GameObject* go);
	~GameLevel();

	// Called first and once
	void Start();
	// Called every frame
	void Update(float dt, bool keys[], glm::vec2 mousePos);

	// Called when an enemy dies. Removes it from the internal vector
	void EnemyDied(std::string name);

private:
	// The GameObject associated to this attribute
	GameObject* gameObject;
	// Current level
	int level;

	// Holds all enemies of current level, when empty go to next level
	// The enemies are in order, from left to right, top to bottom
	std::vector<std::string> enemies;

	// ----- Divers variables -----
	float diverCountDown;
	float timeBetweenDivers;
	int amountOfDivers;

	// Go to next level
	void LevelUp();

	// Loads a Level Data from a file
	void Load(std::string file);
	// From file data, creates each enemy's GameObject
	void GenerateLevel(std::vector<std::vector<char>> enemyData, float enemySpeed);
};

#endif
