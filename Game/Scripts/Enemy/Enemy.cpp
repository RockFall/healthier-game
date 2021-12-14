#include "Enemy.h"
#include "../../Editor/GameEditor.h"

#include <random>

Enemy::Enemy(GameObject* go) : gameObject(go), speed(0.0f), movementRange(0.0f), xTargetPos(0.0f), originalPos(0.0f), diving(false), initialMove(false), timeSinceLastShot(0.0f), shootingRate(0), bulletSize(0), isBoss(false)
{
	Start();
}

Enemy::~Enemy()
{
}

void Enemy::Start()
{
	speed = glm::vec2(40.0f, 10.0f);
	movementRange = 40.0f;
	originalPos = gameObject->transform.position;

	shootingRate = 0.75f;
	bulletSize = gameObject->transform.size/2.0f;
	timeSinceLastShot = 1.0f;

	health = ceil(gameObject->transform.size.x / 50.0f);
	if (gameObject->transform.size.x >= (GameEditor::GAME_WIDTH - 100.0f)/3.0f - 20.0f) {
		isBoss = true;
		timeSinceLastShot = 1.0f;
		health = 20;
		if (gameObject->transform.size.x >= 400.0f) {
			isFinalBoss = true;
			health = 40;
		}
	}
}

void Enemy::Update(float dt, bool keys[], glm::vec2 mousePos)
{
	if (GameContext::gameOver)
		return;

	if (diving && GameContext::gameOver == false) {
		// If diving, the enemy WILL shoot, when in a certain area 
		if (gameObject->transform.position.y <= 520 && gameObject->transform.position.y > originalPos.y + 200.0f) {
			Shoot(dt);
		}

		if (gameObject->transform.position.y >= GameEditor::GAME_HEIGHT) {
			gameObject->transform.position.y -= GameEditor::GAME_HEIGHT * 1.3f;
		}
	}
	else {
		// If non-divers get to the bottom of the screen, it is GAME OVER
		if (gameObject->transform.position.y >= GameEditor::GAME_HEIGHT) {
			if (GameContext::gameOver == false)
				GameContext::gameOver = true;
			GameEditor::DestroyGameObject(this->gameObject->GetFormattedName());
		}

		if (isBoss) // If it is a boss, will shoot based on shootSpeed
			Shoot(dt);
		else if (rand() % 30 == 0) // Will call shoot with 10% chance
			Shoot(dt);
	}

	DoMovement(dt);
}

void Enemy::DoMovement(float dt)
{
	if (diving) {
		//return;
	}

	if (gameObject->transform.position.x > originalPos.x + movementRange){
		gameObject->transform.position.x = originalPos.x + movementRange;
		speed.x *= -1;
		return;
	}
	else if (gameObject->transform.position.x < originalPos.x - movementRange) {
		gameObject->transform.position.x = originalPos.x - movementRange;
		speed.x *= -1;
		return;
	}

	gameObject->transform.position.x -= speed.x * dt;
	gameObject->transform.position.y += speed.y * dt;
}

void Enemy::SetYSpeed(float speed)
{
	this->speed.y = speed;
}

void Enemy::SetSpeed(glm::vec2 speed)
{
	this->speed = speed;
}

glm::vec2 Enemy::getSpeed()
{
	return this->speed;
}

void Enemy::Dive()
{
	SetSpeed(glm::vec2(60.0f, 150.0f));
	this->diving = true;
	// random initial shooting time
	timeSinceLastShot = (rand() % 60) / 60.0f;

	GameContext::SoundQueue.push(std::make_pair("Dive", 0.5f));
}

void Enemy::Shoot(float dt)
{
	if (timeSinceLastShot > 0) {
		timeSinceLastShot -= dt;
		return;
	}

	timeSinceLastShot = 1 / shootingRate;
	
	glm::vec2 bulletPos = gameObject->transform.position + (gameObject->transform.size / 2.0f);

	std::string bulletID = GameEditor::CreateGameObject(
		"Bullet",
		bulletPos,
		true,
		bulletSize,
		true,
		"RNA"
	);

	GameContext::CurrentObjects[bulletID]->SetTag("Bullet");

	glm::vec2 playerSize = GameContext::CurrentObjects["Player_0"]->transform.size;
	glm::vec2 playerPos = GameContext::CurrentObjects["Player_0"]->transform.position + (playerSize/2.0f);
	glm::vec2 bulletDirection = glm::normalize(playerPos - bulletPos);

	GameContext::CurrentAttributes[bulletID]->bulletScript.setSpeed(bulletDirection * 400.0f);
	GameContext::CurrentAttributes[bulletID]->bulletScript.setTarget("Player");
	GameEditor::GameObjectSetSolid(bulletID, true);

	// Play sound
	if (isBoss)
		GameContext::SoundQueue.push(std::make_pair("Boss Shoot", 0.5f));
	else
		GameContext::SoundQueue.push(std::make_pair("Enemy Shoot", 0.4f));
	
}

void Enemy::Hit(int damage) {
	if (health == 1) {
		GameContext::SoundQueue.push(std::make_pair("Hit little", 0.5f));
	}
	else {
		GameContext::SoundQueue.push(std::make_pair("Hit big", 0.7f));
	}
	this->health -= damage;
	if (health <= 0) {
		GameContext::CurrentAttributes["GameLevel_0"]->gameLevelScript.EnemyDied(gameObject->GetFormattedName());
		GameEditor::DestroyGameObject(gameObject->GetFormattedName());
		if (isBoss) {
			if (isFinalBoss) {
				GameContext::SoundQueue.push(std::make_pair("Final Boss Death", 0.7f));
				GameContext::win = true;
				GameContext::gameOver = true;
				GameEditor::CreateGameObject(
					"WIN",
					glm::vec2(50.0f, GameEditor::GAME_HEIGHT / 2.0f - 100.0f),
					true,
					glm::vec2(500.0f, 200.0f),
					false,
					"You Win"
				);
				GameContext::CurrentObjects["WIN_0"]->sprite.color.w = 0.0f;
			}
			else
				GameContext::SoundQueue.push(std::make_pair("Boss Death", 0.7f));
		}
		else {
			if (ceil(gameObject->transform.size.x / 50.0f > 1))
				GameContext::SoundQueue.push(std::make_pair("Enemy Death", 0.2f));
		}

	}
}
