#include "Attribute.h"

Attribute::Attribute(GameObject* go, std::string type) : gameObject(go)
{
	this->type = type;

	if (type == "Player") {
		this->playerScript = Player(gameObject);
	}
	else if (type == "Enemy") {
		this->enemyScript = Enemy(gameObject);
	}
	else if (type == "Bullet") {
		this->bulletScript = Bullet(gameObject);
	}
	else if (type == "GameLevel") {
		this->gameLevelScript = GameLevel(gameObject);
	}
	else if (type == "Background") {
		this->backgroundScript = Background(gameObject);
	}
	else if (type == "AnimatedSprite") {
		this->animationScript = AnimatedSprite(gameObject);
	}
}

Attribute::~Attribute()
{
	/*
	std::cout << "Destructing ATTRIBUTE; player=" << player << std::endl;
	if (player != nullptr) {
		std::cout << "Before delete" << std::endl;
		delete player;
		std::cout << "After delete" << std::endl;
	}*/
}

void Attribute::Update(float dt, bool keys[], glm::vec2 mousePos)
{
	if (type == "Player") {
		this->playerScript.Update(dt, keys, mousePos);
	}
	else if (type == "Enemy") {
		this->enemyScript.Update(dt, keys, mousePos);
	}
	else if (type == "Bullet") {
		this->bulletScript.Update(dt, keys, mousePos);
	}
	else if (type == "GameLevel") {
		this->gameLevelScript.Update(dt, keys, mousePos);
	}
	else if (type == "Background") {
		this->backgroundScript.Update(dt, keys, mousePos);
	}
	else if (type == "AnimatedSprite") {
		this->animationScript.Update(dt, keys, mousePos);
	}
}

void Attribute::Start()
{
}
