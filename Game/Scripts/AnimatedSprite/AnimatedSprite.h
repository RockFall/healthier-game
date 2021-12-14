#ifndef ANIMATED_SPRITE_H
#define ANIMATED_SPRITE_H

#include "../BaseBehaviour.h"

#include <vector>

class AnimatedSprite : BaseBehaviour {
public:
	AnimatedSprite() : animationRate(0), timeSinceLastFrame(0), shouldLoop(false), textures(), nextTextureIndex(0), gameObject(nullptr) {}
	AnimatedSprite(GameObject* go);
	~AnimatedSprite();

	// Called first and once
	void Start();
	// Called every frame
	void Update(float dt, bool keys[], glm::vec2 mousePos);

	void NextFrame();
	void EndAnimation();

	void AddTexture(std::string texName);

private:
	// Player GameObject
	GameObject* gameObject;

	// Animation timing
	int animationRate;
	float timeSinceLastFrame;
	// Behaviour variables
	bool shouldLoop;
	// Texture variables
	std::vector<std::string> textures;
	int nextTextureIndex;
};

#endif