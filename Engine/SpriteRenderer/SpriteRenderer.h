#ifndef SPRITE_RENDERER_H
#define SPRITE_RENDERER_H

#include "../Shaders/Shader.h"
#include "../Texture/Texture2D.h"

#include "../Buffers/VAO.h"
#include "../Buffers/VBO.h"

class SpriteRenderer
{
public:
	// ---- Constructor and destructor ----
	// Stores given shader instance for future uses
	SpriteRenderer(Shader &shader);
	~SpriteRenderer();

	// 'texture' : Texture2D object
	// 'position': Position (x,y) of the object in World Space
	// 'size'	 : Desired size of the sprite. DEFAULT: (10f, 10f)
	// 'rotate'  : Rotation (angles) applied to sprite. DEFAULT: 0.0f
	// 'color'	 : Color changes to sprite. DEFAULT: (1.0f, 1.0f, 1.0f)
	// 
	// Creates the model matrix for sprite transformations
	// and inserts it into the shader
	void DrawSprite(Texture2D &texture, 
		glm::vec2 position, 
		glm::vec2 size = glm::vec2(10.0f, 10.0f), 
		GLfloat rotate = 0.0f,
		glm::vec4 color = glm::vec4(1.0f)
	);

private:
	// Stores the shader
	Shader shader;
	// Stores a VAO with vertex(vec2) and texture data(vec2)
	VAO quadVAO;

	// Creates the vertices of a square on a VBO and
	// also creating a VAO with the VBO data, being stored on
	// class's internal 'quadVAO' variable
	void initRenderData();
};

#endif
