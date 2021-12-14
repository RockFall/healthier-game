#ifndef TRANSFORM_H
#define TRANSFORM_H

#include <glm/glm.hpp>

// Position, scale and rotation data
struct Transform {
	glm::vec2 position, size, velocity;
	float rotation;
};

#endif