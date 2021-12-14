#include "Background.h"
#include "../../Editor/GameEditor.h"

Background::Background(GameObject* go) : speed(), gameObject(go)
{
	Start();
}

Background::~Background()
{
}

void Background::Start()
{
	this->speed = 200.0f;
}

void Background::Update(float dt, bool keys[], glm::vec2 mousePos)
{
	if (gameObject->transform.position.y >= GameEditor::GAME_HEIGHT) {
		gameObject->transform.position.y -= 2100*2;
	}

	gameObject->transform.position.y += speed * dt;
}

void Background::setSpeed(float speed) {
	this->speed = speed;
}

void Background::increaseSpeedBy(float speed)
{
	this->speed += speed;
}

float Background::getSpeed()
{
	return this->speed;
}
