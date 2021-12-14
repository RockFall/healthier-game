#ifndef GAME_CLASS_H
#define GAME_CLASS_H

#include<glad/glad.h>
#include<GLFW/glfw3.h>

//#include <ft2build.h>
//#include FT_FREETYPE_H

#include "AttributeManager/AttributeManager.h"
#include "../../Engine/ResourceManager/ResourceManager.h"

#include "../Engine/SpriteRenderer/SpriteRenderer.h"
#include "../Engine/SoundPlayer/SoundPlayer.h"
#include "../Engine/ParticleGenerator/ParticleGenerator.h"
#include "../Engine/TextRenderer/TextRenderer.h"

#include "Editor/GameEditor.h"

// Represents the current state of the game
enum class GameState {
    GAME_ACTIVE,
    GAME_PAUSE,
    GAME_DEBUG,
    GAME_WIN,
    GAME_LOSE,
    GAME_CLOSE
};

class Game
{
public:
    // Game State
    GameState    state;
    // Hold input data
    bool         keys[1024];
    glm::vec2 mousePos;
    // Resolution of the game
    unsigned int screenWidth, screenHeight, gameWidth, gameHeight;

    // ---- CONSTRUCTOR/DESTRUCTOR ----
    Game();
    ~Game();

    // Initialize Game State (load all shaders/textures/levels)
    void Init(unsigned int width, unsigned int height);

    // Loads all Textures defined
	static void LoadAllTextures();

    // Load all Sounds defined
    static void LoadAllSounds();

    // Deals with the game state
    void ProcessGameState(float dt);

    // Update is called every frame
    // 'dt': the deltaTime between the last frame and current
    void Update(float dt);
    // Called after Update
    // Do the rendering of current frame
    void Render();

    void SetMousePos(glm::vec2 pos);
private:
    // Data of current deltaTime for debug and print purposes
    float dt;
    // Tells the Update() method that, when in DEBUG MODE, wether
    // we can do one iteration or not
    bool canUpdate;


    // Prints on the terminal info about every GameObject with meaning
    void ShowGameInfo();
    // Resets entirely the game
    void RestartGame();
    
};

#endif