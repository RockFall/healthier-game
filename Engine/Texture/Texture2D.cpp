#include "Texture2D.h"



/* OLD function from when Texture class loaded image
Texture2D::Texture2D(const char* imagePath, GLenum slot) : type(GL_TEXTURE_2D), width(0), height(0), internalFormat(GL_RGBA), imageFormat(GL_RGBA), pixelType(GL_UNSIGNED_BYTE), wrapS(GL_REPEAT), wrapT(GL_REPEAT), filterMin(GL_NEAREST), filterMax(GL_NEAREST)
{
	Generate(imagePath, slot);
}
*/

Texture2D::Texture2D() : type(GL_TEXTURE_2D), width(0), height(0), internalFormat(GL_RGB), imageFormat(GL_RGB), pixelType(GL_UNSIGNED_BYTE), wrapS(GL_REPEAT), wrapT(GL_REPEAT), filterMin(GL_NEAREST), filterMax(GL_NEAREST)
{
	// Creates an texture object
	glGenTextures(1, &this->ID);
}

void Texture2D::Generate(unsigned char* imageBytes, GLenum slot) {
	// Load image and data with stb
	// ! MUST ! call at the end: 
	//       stbi_image_free(bytes)
	//unsigned char* imageBytes = LoadImageSTB(imagePath); 

	// Creates an texture object
	glGenTextures(1, &ID);

	// Activates and binds the created texture to the first Texture Unit
	glActiveTexture(slot);
	glBindTexture(type, ID);

	// Defines the pixel processing of texture (GL_NEAREST for pixel perfect attempt)
	glTexParameteri(type, GL_TEXTURE_MIN_FILTER, this->filterMin);
	glTexParameteri(type, GL_TEXTURE_MAG_FILTER, this->filterMax);

	// Defines the repetition pattern of texture
	glTexParameteri(type, GL_TEXTURE_WRAP_S, this->wrapS);
	glTexParameteri(type, GL_TEXTURE_WRAP_T, this->wrapT);

	// To use GL_CLAMP_TO_BORDER we must choose the background color
	// float flatColor[] = {1.0f, 1.0f, 1.0f, 1.0f};
	// glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER, flatColor);


	glTexImage2D(type, 0, this->internalFormat, width, height, 0, this->imageFormat, pixelType, imageBytes);
	glGenerateMipmap(type);

	glBindTexture(type, 0);
}

void Texture2D::Bind(int slot)
{
	glActiveTexture(GL_TEXTURE0 + slot);
	glBindTexture(type, this->ID);
}

void Texture2D::Unbind()
{
	glBindTexture(type, 0);
}

void Texture2D::Delete()
{
	glDeleteTextures(1, &this->ID);
}
