#ifndef TEXTURE_CLASS_H
#define TEXTURE_CLASS_H

#include<glad/glad.h>
#include <string>

class Shader;

class Texture2D {
public:
	// Reference ID to the Texture Object
	GLuint ID;
	// Type of texture (i.e. GL_TEXTURE_2D)
	GLenum type;
	// Sizes in pixels of the loaded image
	GLuint width, height;
	// Format data
	GLenum internalFormat; // default: GL_RGBA
	GLenum imageFormat; // default: GL_RGBA
	GLenum pixelType; // data type of pixel data, default: GL_UNSIGNED_BYTE
	// Config data
	GLenum wrapS; // wrapping mode on S axis, default: 
	GLenum wrapT; // wrapping mode on T axis
	GLenum filterMin; // filtering mode if texture pixels < screen pixels, default: GL_NEAREST
	GLenum filterMax; // filtering mode if texture pixels > screen pixels, default: GL_NEAREST

	// --------------------------------------------------------------------

	// -- Constructor --
	//	Calls for Generate( )
	//
	//	'imagePath': String path to image to be stored into texture
	//  'slot'     : Specifies which texture unit to make active. Starts in GL_TEXTURE0
	// Texture2D(const char* imagePath, GLenum slot = GL_TEXTURE0);

	// -- Empty Constructor --
	Texture2D();

	// Uses STB lib to load an image file
	//unsigned char* LoadImageSTB(const char* imagePath);

	//	'imagePath': String path to image to be stored into texture
	//  'slot'     : Specifies which texture unit to make active. Starts in GL_TEXTURE0
	// 
	// Imports an image, creates one Texture Object, which it's reference
	//	is stored on class's variable, and assigns the image to given slot
	void Generate(unsigned char* imageBytes, GLenum slot= GL_TEXTURE0);

	// Binds the Texture Object
	void Bind(int slot = 0);
	// Unbinds the Texture Object
	void Unbind();
	// Deletes the Texture Object
	void Delete();
};

#endif