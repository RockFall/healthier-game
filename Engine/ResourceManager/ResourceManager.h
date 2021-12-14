#ifndef RESOURCE_MANAGER_H
#define RESOURCE_MANAGER_H

#include <map>
#include <string>

#include <glad/glad.h>

#include "../Texture/Texture2D.h"
#include "../Shaders/Shader.h"


// Based on tutorials of learnopengl.com
//
// Responsible for the Loading of shaders and textures
// All shaders and textures are stored in a map for future use
// This class can't be instantiated and all functions are static
class ResourceManager
{
public:
    // Resource storage
    static std::map<std::string, Shader>                         Shaders;
    static std::map<std::string, std::shared_ptr<Texture2D>>     Textures;
    static std::map<std::string, std::string>                    SoundPaths;

    // From given vertex, fragment and optionally geometry shaders source codes, 
    // it loads all shaders, creating multiple Shader instances and returning them. 
    // -> 'geometryFile' can be nullptr and will not be loaded
    static void LoadShader(const char* vertexFile, const char* fragmentFile, const char* geometryFile, std::string name);

    // Returns shader with given name from global map
    static Shader GetShader(std::string name);

    // Load and create a Texture from a given file
    static void LoadTexture(const char* filePath, bool alpha, std::string name);

    // Returns texture with given name from global map
    static std::shared_ptr<Texture2D> GetTexture(std::string name);

    static std::string LoadSound(std::string filePath, std::string soundName);

    static std::string GetSoundPath(std::string name);

    // De-allocates all loaded shaders and textures
    static void Clear();
private:
    // Private Constructor so we can keep from creating instances
    ResourceManager() { }
    // Do the Loading of Shaders and Textures
    static Shader LoadShaderFromFile(const char* vertexFile, const char* fragmentFile, const char* geometryFile = nullptr);
    static Texture2D LoadTextureFromFile(const char* file, bool alpha);

    // Alternative version - with this we check for File existance
    static Shader AlternativeLoadShaderFromFile(const char* vertexFile, const char* fragmentFile, const char* geometryFile);
};

#endif