#ifndef PARTICLE_GENERATOR_H
#define PARTICLE_GENERATOR_H

#include <vector>

#include <glad/glad.h>
#include <glm/glm.hpp>

#include "Particle.h"
#include "../Texture/Texture2D.h"
#include "../Shaders/Shader.h"
#include "../GameObject/GameObject.h"

// Responsible for generating particles
// This class is based o tutorials rom learnopengl.com
class ParticleGenerator
{
public:
    // ----- Constructor -----
    ParticleGenerator(Shader shader, std::shared_ptr<Texture2D> texture, unsigned int amount);
    // Called every frame
    void Update(float dt, GameObject& object, unsigned int newParticles, glm::vec2 offset = glm::vec2(0.0f, 0.0f));
    // Called at the end of frame, on Rendering
    void Draw(glm::vec2 gameOffset);
private:
    // Current particles
    std::vector<Particle> particles;
    unsigned int amount;

    // Render Data
    Shader shader;
    std::shared_ptr<Texture2D> texture;
    unsigned int VAO;

    // Initializze VBO and VAO
    void init();
    // returns the first Particle index that's currently unused e.g. Life <= 0.0f or 0 if no particle is currently inactive
    unsigned int firstUnusedParticle();
    // respawns particle
    void respawnParticle(Particle& particle, GameObject& object, glm::vec2 offset = glm::vec2(0.0f, 0.0f));

};

#endif
