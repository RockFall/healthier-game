#include "AnimatedSprite.h"

AnimatedSprite::AnimatedSprite(GameObject* go) : animationRate(0), timeSinceLastFrame(0), shouldLoop(false), textures(), nextTextureIndex(0), gameObject(go)
{
	Start();
}

AnimatedSprite::~AnimatedSprite()
{
}

void AnimatedSprite::Start()
{
	animationRate = 100; // ms per frame
}

void AnimatedSprite::Update(float dt, bool keys[], glm::vec2 mousePos)
{
	if (timeSinceLastFrame >= animationRate) {
		timeSinceLastFrame = 0;
		NextFrame();
		return;
	}

	timeSinceLastFrame += dt*1000;
}

void AnimatedSprite::NextFrame() {
	if (nextTextureIndex == textures.size()) {
		if (!shouldLoop) {
			EndAnimation();
			return;
		}

		nextTextureIndex = 0;
	}

	gameObject->setTexture(textures[nextTextureIndex]);
	nextTextureIndex++;
}

void AnimatedSprite::EndAnimation()
{
	this->gameObject->hasBeenDestroyed = true;
}

void AnimatedSprite::AddTexture(std::string texName)
{
	textures.push_back(texName);
}


