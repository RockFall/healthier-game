#include "SpriteRenderer.h"


SpriteRenderer::SpriteRenderer(Shader &shader)
{
	this->shader = shader;
	initRenderData();
}

SpriteRenderer::~SpriteRenderer()
{
	this->quadVAO.Delete();
}

void SpriteRenderer::DrawSprite(Texture2D& texture, glm::vec2 position, glm::vec2 size, GLfloat rotate, glm::vec4 color)
{
	this->shader.Activate();

	// Creating the Model Matrix as Identity Matrix
	glm::mat4 model = glm::mat4(1.0f);

	// The transformations, in the end, will be in the order:
	//    Scale -> Rotate -> Translate

	// ----- TRANSLATION -----
	// We move the sprite to given position
	model = glm::translate(model, glm::vec3(position, 0.0f));
	
	// ----- ROTATION -----
	// We move the sprite so we can rotate based on it's center
	model = glm::translate(model, glm::vec3(0.5f * size.x, 0.5f * size.y, 0.0f));
	// Rotating the sprite if a value is given
	model = glm::rotate(model, glm::radians(rotate), glm::vec3(0.0f, 0.0f, 1.0f));
	// Moving the sprite back to it's original position
	model = glm::translate(model, glm::vec3(-0.5f * size.x, -0.5f * size.y, 0.0f));

	// ----- SCALING -----
	// Scalling the sprite while keeping Z-axis = 1.0f
	model = glm::scale(model, glm::vec3(size, 1.0f));

	// Inserting the model matrix into the shader
	this->shader.SetMatrix4("model", model);
	this->shader.SetVector4f("spriteColor", color);

	glActiveTexture(GL_TEXTURE0);
	texture.Bind();

	this->quadVAO.Bind();
	glDrawArrays(GL_TRIANGLES, 0, 6);
	this->quadVAO.Unbind();

}

void SpriteRenderer::initRenderData()
{
	// Configuring VBO and VAO for a square

	GLfloat vertices[] = {
		// Position --- Texture coords
		0.0f, 1.0f,		0.0f, 1.0f,
		1.0f, 0.0f,		1.0f, 0.0f,
		0.0f, 0.0f,		0.0f, 0.0f,

		0.0f, 1.0f,		0.0f, 1.0f,
		1.0f, 1.0f,		1.0f, 1.0f,
		1.0f, 0.0f,		1.0f, 0.0f
	};

	
	// VAO Object
	VAO VAO;

	// VBO with vertices data
	VBO VBO = VBO::VBO(vertices, sizeof(vertices));

	VAO.Bind();
	// Inserting the VBO into the VAO
	VAO.LinkAttrib(VBO, 0, 4, GL_FLOAT, 4*sizeof(float), (void*)0);

	VAO.Unbind(); // Must be unbided before the VBO
	VBO.Unbind();

	this->quadVAO = VAO;
	VBO.Delete();
}
