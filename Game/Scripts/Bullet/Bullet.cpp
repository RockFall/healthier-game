#include "Bullet.h"
#include "../../Editor/GameEditor.h"
#include "../GameLevel/GameLevel.h"
#include "../../../Engine/GameObject/Attribute.h"

Bullet::Bullet(GameObject* go) :  gameObject(go), speed(0.0f), targetName(), damage(0)
{
	Start();
}

Bullet::~Bullet()
{
}

void Bullet::Start()
{
	targetName = "Enemy";
	damage = 1;
}

void Bullet::Update(float dt, bool keys[], glm::vec2 mousePos)
{
	DoMovement(dt);
	
	CheckOutScreen();

	DoCollisions(dt);
}

void Bullet::DoMovement(float dt)
{
	gameObject->transform.position += speed * dt;
}

void Bullet::setSpeed(glm::vec2 speed)
{
	this->speed = speed;
}

void Bullet::setTarget(std::string name)
{
	this->targetName = name;
}

glm::vec2 Bullet::getSpeed()
{
	return this->speed;
}

void Bullet::CheckOutScreen() {
	if (gameObject->transform.position.y < -gameObject->transform.size.y ||
		gameObject->transform.position.y > GameEditor::GAME_HEIGHT)
	{
		GameEditor::DestroyGameObject(gameObject->GetFormattedName());
	}
}

void Bullet::DoCollisions(float dt)
{
	for (auto& targetIt : GameContext::CurrentObjects) {
		if (targetIt.second->hasBeenDestroyed == false 
			&& targetIt.second->GetTag() == targetName
			&& targetIt.second->isSolid) {
			if (CheckCollision(targetIt.second.get(), this->gameObject)) {
				if (targetIt.second->GetTag() == "Enemy") {
					GameContext::CurrentAttributes[targetIt.second->GetFormattedName()]->enemyScript.Hit(damage);
					GameEditor::DestroyGameObject(this->gameObject->GetFormattedName());
				}
				else if (targetIt.second->GetTag() == "Player") {

					GameContext::CurrentAttributes[targetIt.second->GetFormattedName()]->playerScript.Hit(damage, dt);
					GameEditor::DestroyGameObject(this->gameObject->GetFormattedName());
				}
				return;
			}
		}
	}
}

bool Bullet::CheckCollision(GameObject* one, GameObject* thisObj)
{
	// collision x-axis?
	bool collisionX = one->transform.position.x + (one->transform.size.x) >= thisObj->transform.position.x &&
		thisObj->transform.position.x + thisObj->transform.size.x >= one->transform.position.x;
	// collision y-axis?
	bool collisionY = one->transform.position.y + one->transform.size.y >= thisObj->transform.position.y &&
		thisObj->transform.position.y + thisObj->transform.size.y >= one->transform.position.y;
	// collision only if on both axes
	return collisionX && collisionY;
}
