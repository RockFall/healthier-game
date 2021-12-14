#include "Game.h"
#include <cstdlib>

// Deals with sprite rendering
SpriteRenderer* Renderer;
// Deals with Sounds
SoundPlayer* Sounds;
// Creates Particles
ParticleGenerator* Particles;
// Handles Text
//TextRenderer* Text;

Game::Game()
	: state(GameState::GAME_ACTIVE), keys(), mousePos(0.0f, 0.0f), 
	gameWidth(0), gameHeight(0), screenWidth(0), screenHeight(0),
	canUpdate(true), dt(0)
{

}

Game::~Game()
{
	delete Renderer;
	delete Sounds;
	delete Particles;
	//delete Text;
}

// Called once before everything
void Game::Init(unsigned int width, unsigned int height)
{

	this->screenWidth = width;
	this->screenHeight = height;

	// Sets Game Editor screen size variables
	GameEditor::GAME_WIDTH = 600;
	GameEditor::GAME_HEIGHT = this->screenHeight;
	GameEditor::GAME_OFFSET = (this->screenWidth - 600) / 2.0f;
	

	// Loading Shaders
	ResourceManager::LoadShader("./Engine/Shaders/sprite.vs", "./Engine/Shaders/sprite.frag", nullptr, "sprite");
	ResourceManager::LoadShader("./Engine/Shaders/particle.vs", "./Engine/Shaders/particle.frag", nullptr, "particle");

	// Configuring Shaders
	// Applying orthigraphic projection over World Space (as we don't have a needed camera)
	glm::mat4 projection = glm::mat4(1.0f);
	projection = glm::ortho(
		0.0f, // Left
		(GLfloat)this->screenWidth, // Right
		(GLfloat)this->screenHeight, // Bottom
		0.0f, // Top
		-1.0f, // Near
		1.0f // Far
	);

	// Set texture slot to default 0
	ResourceManager::GetShader("sprite").SetInteger("image", 0, true);
	// Set projection matrix to the created one
	ResourceManager::GetShader("sprite").SetMatrix4("projection", projection, true);

	// Creates the SpriteRenderer with the just created shader
	Shader spriteShader = ResourceManager::GetShader("sprite");
	
	Renderer = new SpriteRenderer(spriteShader);
	Sounds = new SoundPlayer();

	// Loading tetures
	LoadAllTextures();

	// Creating particles generator and setting projection to shader
	Particles = new ParticleGenerator(
		ResourceManager::GetShader("particle"),
		ResourceManager::GetTexture("Player"),
		500
	);

	ResourceManager::GetShader("particle").Activate().SetMatrix4("projection", projection);

	// Set up Text
	//Text = new TextRenderer(this->screenWidth, this->screenHeight);
	//Text->Load("Resources/Fonts/ocraext.TTF", 24);

	// Loading sounds
	LoadAllSounds();

	Sounds->Play(ResourceManager::GetSoundPath("Background Music"), true);
	GameEditor::LoadInitialScene();
}

void Game::LoadAllTextures()
{
	ResourceManager::LoadTexture("Resources/Linfocito_B.png", true, "Player");
	ResourceManager::LoadTexture("Resources/Anticorpo.png", true, "Anticorpo");

	ResourceManager::LoadTexture("Resources/VirusEsfera.png", true, "VirusEsfera");
	ResourceManager::LoadTexture("Resources/VirusPoliedro.png", true, "VirusPoliedro");
	ResourceManager::LoadTexture("Resources/VirusComplexo.png", true, "VirusComplexo");
	ResourceManager::LoadTexture("Resources/Bacteria.png", true, "Bacteria");
	ResourceManager::LoadTexture("Resources/RNA.png", true, "RNA");

	ResourceManager::LoadTexture("Resources/None.png", true, "None");
	ResourceManager::LoadTexture("Resources/BackgroundBig.png", true, "Background");
	ResourceManager::LoadTexture("Resources/BackgroundHemacias.png", true, "BackgroundHemacias");
	ResourceManager::LoadTexture("Resources/Fights01.png", true, "Fights01");
	ResourceManager::LoadTexture("Resources/Fights02.png", true, "Fights02");

	ResourceManager::LoadTexture("Resources/Animations/Linfocito_B_anim1.png", true, "PlayerAnim01");
	ResourceManager::LoadTexture("Resources/Animations/Linfocito_B_anim2.png", true, "PlayerAnim02");
	ResourceManager::LoadTexture("Resources/Animations/Linfocito_B_anim3.png", true, "PlayerAnim03");
	ResourceManager::LoadTexture("Resources/Animations/Linfocito_B_anim4.png", true, "PlayerAnim04");
	ResourceManager::LoadTexture("Resources/Animations/Linfocito_B_anim5.png", true, "PlayerAnim05");
	ResourceManager::LoadTexture("Resources/Animations/Linfocito_B_anim6.png", true, "PlayerAnim06");
	ResourceManager::LoadTexture("Resources/Animations/Linfocito_B_anim7.png", true, "PlayerAnim07");
	ResourceManager::LoadTexture("Resources/Animations/Linfocito_B_anim8.png", true, "PlayerAnim08");

	ResourceManager::LoadTexture("Resources/GameOver.png", true, "Game Over");
	ResourceManager::LoadTexture("Resources/YouWin.png", true, "You Win");
}

void Game::LoadAllSounds() {
	ResourceManager::LoadSound("Resources/Sounds/music.mp3", "Background Music");
	ResourceManager::LoadSound("Resources/Sounds/gameover_music.mp3", "GameOver Music");
	ResourceManager::LoadSound("Resources/Sounds/PlayerShoot.mp3", "Player Shoot");
	ResourceManager::LoadSound("Resources/Sounds/EnemyShoot.mp3", "Enemy Shoot");
	ResourceManager::LoadSound("Resources/Sounds/Hit01.mp3", "Hit little");
	ResourceManager::LoadSound("Resources/Sounds/Hit02.mp3", "Hit big");
	ResourceManager::LoadSound("Resources/Sounds/Dive.mp3", "Dive");
	ResourceManager::LoadSound("Resources/Sounds/BossShoot.mp3", "Boss Shoot");
	ResourceManager::LoadSound("Resources/Sounds/PlayerDeath.mp3", "Player Death");
	ResourceManager::LoadSound("Resources/Sounds/EnemyDeath.mp3", "Enemy Death");
	ResourceManager::LoadSound("Resources/Sounds/BossDeath.mp3", "Boss Death");
	ResourceManager::LoadSound("Resources/Sounds/FinalBossDeath.mp3", "Final Boss Death");
}

// Called every frame first
void Game::ProcessGameState(float dt)
{
	// ESC to quit game
	if (keys[GLFW_KEY_ESCAPE] == true) {
		state = GameState::GAME_CLOSE;
		return;
	}
	// Pressing R resets the Game
	if (keys[GLFW_KEY_R] == true) {
		RestartGame();
		return;
	}

	// If on debug mode, can do one iteration by pressing MIDDLE MOUSE BUTTON
	if (this->state == GameState::GAME_DEBUG) {
		if (keys[GLFW_MOUSE_BUTTON_MIDDLE] == true) {
			keys[GLFW_MOUSE_BUTTON_MIDDLE] = false;
			canUpdate = true;
			return;
		}
	}

	// If the game is going on
	if (this->state == GameState::GAME_ACTIVE) {
		// Check RIGHT MOUSE BUTTON for pausing
		if (keys[GLFW_MOUSE_BUTTON_RIGHT] == true) {
			keys[GLFW_MOUSE_BUTTON_RIGHT] = false;
			std::cout << "GAME PAUSED" << std::endl;
			state = GameState::GAME_PAUSE;
			return;
		}
		// Check MIDDLE MOUSE BUTTON for entering debug mode
		if (keys[GLFW_MOUSE_BUTTON_MIDDLE] == true) {
			keys[GLFW_MOUSE_BUTTON_MIDDLE] = false;
			std::cout << "GAME IN DEBUG MODE" << std::endl;
			state = GameState::GAME_DEBUG;
			return;
		}

		if (GameContext::gameOver == true) {
			//state = GameState::GAME_LOSE;
		}
	}

	// Check RIGHT MOUSE BUTTON for unpausing or getting out of debug mode
	if (this->state == GameState::GAME_PAUSE || this->state == GameState::GAME_DEBUG) {
		if (keys[GLFW_MOUSE_BUTTON_RIGHT] == true) {
			keys[GLFW_MOUSE_BUTTON_RIGHT] = false;
			std::cout << "GAME RESUMED" << std::endl;
			state = GameState::GAME_ACTIVE;
			return;
		}
	}
}

// Called every frame second
void Game::Update(float dt)
{
	this->dt = dt;

	if (state == GameState::GAME_LOSE) {
		GameEditor::PlayerDeathScene(dt);
		return;
	}
	
	if (GameContext::gameOver) {
		GameEditor::PlayerDeathScene(dt);
		//return;
	}

	// If the game is paused
	if (state == GameState::GAME_PAUSE) {
		return;
	}

	if (state == GameState::GAME_DEBUG) {
		if (canUpdate == false) {
			return;
		}
		// If can update, show info on terminal and do one iteration
		ShowGameInfo();
		canUpdate = false;
	}

	AttributeManager::Update(dt, keys, mousePos);

	// Checks and destroy gameObjects if needed
	for (auto it = GameContext::CurrentObjects.cbegin(), next_it = it; it != GameContext::CurrentObjects.cend(); it = next_it)
	{
		if (it->second->GetName() == "Player") {
			Particles->Update(dt, *it->second, 2, glm::vec2(it->second->transform.size / 2.0f));
		}

		++next_it;
		if (it->second->hasBeenDestroyed) {
			std::string name = it->second->GetFormattedName();
			size_t eA = GameContext::CurrentAttributes.erase(name);
			size_t eO = GameContext::CurrentObjects.erase(name);
		}
	}
}

// Called every frame at last
void Game::Render()
{
	

	// Do the rendering of all GameObjects on Scene 
	// in their current location
	for (auto& iter : GameContext::CurrentObjects)
	{
		GameObject& go = *iter.second;
		if (go.GetName() == "Player") {
			Particles->Draw(glm::vec2(GameEditor::GAME_OFFSET, 0.0f));
		}

		Renderer->DrawSprite(
			*(go.sprite.texture),
			go.transform.position + glm::vec2(GameEditor::GAME_OFFSET, 0.0f),
			go.transform.size,
			go.transform.rotation,
			go.sprite.color);
	}

	

	// Play all queued sounds
	while (!GameContext::SoundQueue.empty())
	{
		if (GameContext::SoundQueue.front().first == "Stop all") {
			Sounds->StopAll();
			GameContext::SoundQueue.pop();
		}
		std::string soundPath = ResourceManager::GetSoundPath(GameContext::SoundQueue.front().first);
		Sounds->Play(soundPath, false, GameContext::SoundQueue.front().second);
		GameContext::SoundQueue.pop();
	}
}

void Game::ShowGameInfo()
{
#ifdef _WIN32
#define CLEAR "cls"
#else
#define CLEAR "clear"
#endif
	// Clears the terminal
	system(CLEAR);

	std::cout << "    GAME IN DEBUG MODE" << std::endl;

	// Prints the Player at the top
	if (GameContext::gameOver != true) {
		GameObject playerGO = *GameContext::CurrentObjects["Player_0"];
		glm::vec2 playerSpeed = GameContext::CurrentAttributes["Player_0"]->playerScript.getSpeed();
		std::cout << "----------------------------\n"
			<< "GameObject: " << playerGO.GetFormattedName() << "\n"
			<< "Position:   (" << playerGO.transform.position.x << ", " << playerGO.transform.position.y << ")\n"
			<< "Velocity:   (" << playerSpeed.x << ", " << playerSpeed.y << ")" << std::endl;
	}
	// Prints anything else
	for (auto& iter : GameContext::CurrentObjects)
	{
		GameObject gameObject = *iter.second;
		
		if (gameObject.GetTag() == "Enemy") {
			glm::vec2 enemySpeed = GameContext::CurrentAttributes[gameObject.GetFormattedName()]->enemyScript.getSpeed();
			std::cout << "----------------------------\n"
				<< "GameObject: " << gameObject.GetFormattedName() << "\n"
				<< "Position:   (" << gameObject.transform.position.x << ", " << gameObject.transform.position.y << ")\n" 
				<< "Velocity:   (" << enemySpeed.x << ", " << enemySpeed.y << ")" << std::endl;
		}
		else if (gameObject.GetName() == "Bullet") {
			glm::vec2 bulletSpeed = GameContext::CurrentAttributes[gameObject.GetFormattedName()]->bulletScript.getSpeed();
			std::cout << "----------------------------\n"
				<< "GameObject: " << gameObject.GetFormattedName() << "\n"
				<< "Position:   (" << gameObject.transform.position.x << ", " << gameObject.transform.position.y << ")\n"
				<< "Velocity:   (" << bulletSpeed.x * dt << ", " << bulletSpeed.y * dt << ")" << std::endl;
		}
	}
}

void Game::RestartGame()
{
	state = GameState::GAME_PAUSE;

	GameContext::CurrentObjects.clear();
	GameContext::CurrentAttributes.clear();

	GameEditor::LoadInitialScene();
}

void Game::SetMousePos(glm::vec2 pos) {
	this->mousePos = pos - glm::vec2(GameEditor::GAME_OFFSET, 0.0f);
}




