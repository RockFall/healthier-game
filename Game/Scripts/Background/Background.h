#ifndef BACKGROUND_H
#define BACKGROUND_H

#include "../BaseBehaviour.h"

class Background : BaseBehaviour
{
public:
	// ------ CONSTRUCTOR ------
	Background() : speed(0), gameObject(nullptr) { }
	Background(GameObject* go);
	~Background();

	// Called first and once
	void Start();
	// Called every frame
	void Update(float dt, bool keys[], glm::vec2 mousePos);

	void setSpeed(float speed);
	void increaseSpeedBy(float speed);

	float getSpeed();

private:
	GameObject* gameObject;

	float speed;
};

#endif


