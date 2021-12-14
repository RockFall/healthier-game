#ifndef ATTRIBUTE_H
#define ATTRIBUTE_H

#include "../../Game/Scripts/Player/Player.h"
#include "../../Game/Scripts/Bullet/Bullet.h"
#include "../../Game/Scripts/GameLevel/GameLevel.h"
#include "../../Game/Scripts/Enemy/Enemy.h"
#include "../../Game/Scripts/Background/Background.h"
#include "../../Game/Scripts/AnimatedSprite/AnimatedSprite.h"

class GameObject;

class Attribute {
public:
	GameObject* gameObject;

	std::string type;

	Player playerScript;
	Enemy enemyScript;
	Bullet bulletScript;
	GameLevel gameLevelScript;
	Background backgroundScript;
	AnimatedSprite animationScript;

	Attribute() : gameObject(nullptr), playerScript(nullptr), enemyScript(nullptr),
		bulletScript(nullptr), gameLevelScript(nullptr), backgroundScript(nullptr), animationScript(nullptr) { }

	//Attribute(const Attribute& a) : gameObject(a.gameObject), playerScript(a.playerScript) { }

	Attribute(GameObject* go, std::string type);

	~Attribute();

	void Update(float dt, bool keys[], glm::vec2 mousePos);

	void Start();
};

#endif