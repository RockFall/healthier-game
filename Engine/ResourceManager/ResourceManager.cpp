#include "ResourceManager.h"

#include <iostream>
#include <sstream>
#include <fstream>

#include <stb/stb_image.h>


// Instantiate static variables
std::map<std::string, std::shared_ptr<Texture2D>>   ResourceManager::Textures;
std::map<std::string, Shader>                       ResourceManager::Shaders;
std::map<std::string, std::string>                  ResourceManager::SoundPaths;


void ResourceManager::LoadShader(const char* vertexFile, const char* fragmentFile, const char* geometryFile, std::string name)
{
    // Creates and add shader to global map
    //Shaders[name] = LoadShaderFromFile(vertexFile, fragmentFile, geometryFile);
    Shaders[name] = AlternativeLoadShaderFromFile(vertexFile, fragmentFile, geometryFile);
}

Shader ResourceManager::GetShader(std::string name)
{
    return Shaders[name];
}

void ResourceManager::LoadTexture(const char* file, bool alpha, std::string name)
{
    Textures[name] = std::make_shared<Texture2D>(LoadTextureFromFile(file, alpha));
}

std::shared_ptr<Texture2D> ResourceManager::GetTexture(std::string name)
{
    if (Textures.find(name) == Textures.end()) {
        std::cout << "RESOURCE MANAGER: Texture \""<< name << "\" not found on internal std::map.\n" <<
            "Have you added it to Game::LoadAllTextures ?\n-----------------------------------------" << std::endl;
        return nullptr;
    }

    return Textures[name];
}

std::string ResourceManager::LoadSound(std::string filePath, std::string soundName)
{
    SoundPaths[soundName] = filePath;
    return SoundPaths[soundName];
}

std::string ResourceManager::GetSoundPath(std::string name)
{
    if (SoundPaths.find(name) == SoundPaths.end()) {
        std::cout << "RESOURCE MANAGER: Sound \"" << name << "\" not found on internal std::map.\n" <<
            "Have you added it to Game::LoadAllSounds ?\n-----------------------------------------" << std::endl;
        return "";
    }

    return SoundPaths[name];
}

void ResourceManager::Clear()
{
    // Delete all shaders	
    for (auto iter : Shaders)
        glDeleteProgram(iter.second.ID);
    // Delete all Textures
    for (auto iter : Textures)
        glDeleteTextures(1, &iter.second->ID);
}

Shader ResourceManager::LoadShaderFromFile(const char* vertexFile, const char* fragmentFile, const char* geometryFile)
{
    // CURRENTLY NOT USED
    // TO DO: COMPARE EFFICIENCY
    // TO DO: CHECK FILE EXISTANCE AND OTHER ERRORS

    // 1. retrieve the vertex/fragment source code from filePath
    std::string vertexCode;
    std::string fragmentCode;
    std::string geometryCode;
    try
    {
        // open files
        std::ifstream vertexShaderFile(vertexFile);
        std::ifstream fragmentShaderFile(fragmentFile);
        std::stringstream vertexStream, fragmentStream;
        // read file's buffer contents into streams
        vertexStream << vertexShaderFile.rdbuf();
        fragmentStream << fragmentShaderFile.rdbuf();
        // close file handlers
        vertexShaderFile.close();
        fragmentShaderFile.close();
        // convert stream into string
        vertexCode = vertexStream.str();
        fragmentCode = fragmentStream.str();
        // if geometry shader path is present, also load a geometry shader
        if (geometryFile != nullptr)
        {
            std::ifstream geometryShaderFile(geometryFile);
            std::stringstream geometryStream;
            geometryStream << geometryShaderFile.rdbuf();
            geometryShaderFile.close();
            geometryCode = geometryStream.str();
        }
    }
    catch (std::exception e)
    {
        std::cout << "ERROR::SHADER: Failed to read shader files" << std::endl;
    }
    const char* vertexSource = vertexCode.c_str();
    const char* fragmentSource = fragmentCode.c_str();
    const char* geometrySource = geometryCode.c_str();
    // 2. now create shader object from source code
    Shader shader;
    shader.CompileNLink(vertexSource, fragmentSource, geometryFile != nullptr ? geometrySource : nullptr);
    return shader;
}

Shader ResourceManager::AlternativeLoadShaderFromFile(const char* vertexFile, const char* fragmentFile, const char* geometryFile) {
    // Getting shader codes from files
    std::string vertexCode = get_file_contents(vertexFile);
    std::string fragmentCode = get_file_contents(fragmentFile);
    // String -> char
    const char* vertexSource = vertexCode.c_str();
    const char* fragmentSource = fragmentCode.c_str();

    // Deals with geometry shader, if given
    std::string geometryCode;
    const char* geometrySource = nullptr;
    if (geometryFile != nullptr) {
        geometryCode = get_file_contents(geometryFile);
        geometrySource = geometryCode.c_str();
    }

    Shader shader;
    shader.CompileNLink(vertexSource, fragmentSource, geometryFile != nullptr ? geometrySource : nullptr);
    return shader;
}

std::string get_file_contents(const char* filename) {

    std::ifstream in(filename, std::ios::binary);
    if (in) {
        std::string contents;
        in.seekg(0, std::ios::end);
        contents.resize(in.tellg());
        in.seekg(0, std::ios::beg);
        in.read(&contents[0], contents.size());
        in.close();
        return (contents);
    }
    std::cout << "ERROR:shaderClass::get_file_contents: Given file not found?\n"
        << "filename:" << filename << "\n -- --------------------------------- --\n" << std::endl;
    throw(errno);
}

Texture2D ResourceManager::LoadTextureFromFile(const char* filePath, bool alpha)
{
    //stbi_set_flip_vertically_on_load(false);

    // create texture object
    Texture2D texture;
    if (alpha)
    {
        texture.internalFormat = GL_RGBA;
        texture.imageFormat = GL_RGBA;
    }
    // load image
    int width, height, nrChannels;
    unsigned char* data = stbi_load(filePath, &width, &height, &nrChannels, 0);

    // Error Handle
    if (data == NULL) {
        std::cout << "ERROR:Texture(): image not fount\n" <<
            "imagePath: " << filePath << "\n-- -------------------------- --\n" << std::endl;
    }

    texture.width = width;
    texture.height = height;

    // now generate texture
    texture.Generate(data, 0);
    // and finally free image data
    stbi_image_free(data);


    return texture;
}

/* OLD Image Loader
unsigned char* Texture2D::LoadImageSTB(const char* imagePath) {
    int widthImg, heightImg, numColorChannels;
    stbi_set_flip_vertically_on_load(true);
    unsigned char* bytes = stbi_load(imagePath, &widthImg, &heightImg, &numColorChannels, 0);
    if (bytes == NULL) {
        std::cout << "ERROR:Texture(): image not fount\n" <<
            "imagePath: " << imagePath << "\n-- -------------------------- --\n" << std::endl;
        return nullptr;
    }

    this->width = widthImg;
    this->height = heightImg;

    return bytes;
}
*/