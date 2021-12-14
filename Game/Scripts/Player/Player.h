#ifndef PLAYER_H
#define PLAYER_H

#include "../BaseBehaviour.h"

#include<glad/glad.h>
#include<glfw/glfw3.h>

class Player : BaseBehaviour
{
public:
	// ------ CONSTRUCTOR ------
	Player() : timeSinceLastShot(0.0f), shootingRate(0.0f), bulletSize(0), lives(0), speed(0), gameObject(nullptr) { }
	Player(GameObject* go);
	~Player();

	// Called first and once
	void Start();
	// Called every frame
	virtual void Update(float dt, bool keys[], glm::vec2 mousePos);

	// Makes the player GameObject move in the X-axis following the mouse
	void DoMovement(float dt, bool keys[], glm::vec2 mousePos);
	// Creates a bullet object when Mouse Left Click is pressed
	// Has a cooldown rate
	void Shoot(bool clicking, float dt);

	void Hit(int damage, float dt);
	void Die(float dt);

	glm::vec2 getSpeed();
private:
	// Player GameObject
	GameObject* gameObject;

	int lives;
	float speed;

	// Shooting variables
	float timeSinceLastShot;
	float shootingRate; // in bullets/second
	int bulletSize;
};

#endif

