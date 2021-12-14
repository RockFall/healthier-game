#ifndef PLAYER_BULLET_H
#define PLAYER_BULLET_H

#include "../BaseBehaviour.h"

#include<glad/glad.h>
#include<glfw/glfw3.h>

class Bullet : BaseBehaviour
{
public:
	// ------ CONSTRUCTOR ------
	Bullet() : speed(0), targetName(), damage(0), gameObject(nullptr) { }
	Bullet(GameObject* go);
	~Bullet();

	// Called first and once
	void Start();
	// Called every frame
	void Update(float dt, bool keys[], glm::vec2 mousePos);

	// Makes the bullet GameObject move in the Y-axis
	void DoMovement(float dt);

	void setSpeed(glm::vec2 speed);
	void setTarget(std::string name);
	glm::vec2 getSpeed();

	// Checks if the bullet is out of the screen, is so, destroys it
	void CheckOutScreen();

	void DoCollisions(float dt);

	bool CheckCollision(GameObject* one, GameObject* two);

private:
	// Player GameObject
	GameObject* gameObject;

	glm::vec2 speed;

	int damage;

	std::string targetName;
};

#endif

