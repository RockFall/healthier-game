#include "GameLevel.h"
#include "../../Editor/GameEditor.h"
#include "../../../Engine/GameObject/Attribute.h"

#include <random>
#include <algorithm>

GameLevel::GameLevel(GameObject* go) : gameObject(go), enemies(), level(0), diverCountDown(0.0f), timeBetweenDivers(0.0f), amountOfDivers(0)
{
	Start();
}

GameLevel::~GameLevel()
{

}

void GameLevel::Start()
{
    level = 1;
	Load("Resources/Levels/level01.txt");
}

void GameLevel::Update(float dt, bool keys[], glm::vec2 mousePos)
{  
    if (GameContext::gameOver)
        return;

    // If all enemies dies, go to next level
    if (enemies.size() == 0) {
        LevelUp();
        return;
    }

    if (diverCountDown > 0) {
        diverCountDown -= dt;
    }
    else if (enemies.size() > 1) {
        // It's time for DIVERSS
        amountOfDivers = rand() % 3; // range(0 to 3)
        timeBetweenDivers = rand() % (50 / enemies.size()) + 0.5f; // range(0.5f to 7.5f)

        if (amountOfDivers > enemies.size())
            amountOfDivers = 1;
        if (timeBetweenDivers >= 7.0f)
            timeBetweenDivers = 7.0f;
        std::cout << amountOfDivers << " enemies are diving. Next wave in " << timeBetweenDivers << " seconds." << std::endl;

        for (int i = 0; i < amountOfDivers; i++)
        {
            int randIndex = rand() % enemies.size();
            GameContext::CurrentAttributes[enemies[randIndex]]->enemyScript.Dive();
            enemies.erase(enemies.begin() + randIndex);

            //GameContext::CurrentAttributes[enemies[i]]->enemyScript.SetSpeed(glm::vec2(60.0f, 150.0f));
        }

        diverCountDown = timeBetweenDivers;
    }

}

void GameLevel::LevelUp()
{
    level++;
    std::string fileName = "Resources/Levels/level0" + std::to_string(level) + ".txt";
    Load(fileName);

    // Accelerates all Backgrounds
    for (auto& go : GameContext::CurrentObjects) {
        if (go.second->GetTag() == "Background") {
            GameContext::CurrentAttributes[go.second->GetFormattedName()]->backgroundScript.increaseSpeedBy(200.0f);
        }
    }
}

void GameLevel::Load(std::string file)
{
	// Clear old data
	enemies.clear();

	char enemyCode;
	std::string line;
	std::ifstream fstream(file);
	std::vector<std::vector<char>> enemyData;

    float enemySpeed = 0.0f;

	if (fstream) {
        // First line is enemy speed
        std::getline(fstream, line);
        enemySpeed = std::stof(line);

		while (std::getline(fstream, line)) {
			std::istringstream sstream(line);
			std::vector<char> row;
			while (sstream >> enemyCode)
				row.push_back(enemyCode);
			enemyData.push_back(row);
		}
		if (enemyData.size() > 0) {
			GenerateLevel(enemyData, enemySpeed);
		}
    }
    else {
        std::cout << "GAMELEVEL::Load: Arquivo não encontrado: " << file << std::endl;
        level = 0;
    }
}

void GameLevel::GenerateLevel(std::vector<std::vector<char>> enemyData, float enemySpeed)
{
    // calculate dimensions
    size_t verticalCount = enemyData.size();
    size_t horizontalCount = enemyData[0].size();
    
    size_t distanceBetween = 10; // 10px between each enemy
    size_t topOffset = 20; // 20px on the top
    size_t lateralOffset = 50; // 50px in each side
    size_t lvlWidth = GameEditor::GAME_WIDTH - (2*lateralOffset);

    float unit_size = std::min(((lvlWidth) / static_cast<float>(horizontalCount))-(distanceBetween), 400.0f);

    // initialize level tiles based on tileData		
    for (unsigned int y = 0; y < verticalCount; ++y)
    {
        for (unsigned int x = 0; x < horizontalCount; ++x)
        {
            // check block type from level data (2D level array)
            if (enemyData[y][x] != 'N') // solid
            {
                std::string texName = "default";
                int randTex = 0;

                switch (enemyData[y][x])
                {
                case 'V':
                    randTex = rand() % 3;
                    if (randTex == 0)
                        texName = "VirusEsfera";
                    if (randTex == 1)
                        texName = "VirusPoliedro";
                    if (randTex == 2)
                        texName = "VirusComplexo";
                    break;
                case 'B':
                    texName = "Bacteria";
                    break;
                default:
                    break;
                }

                float yPos = (topOffset + y * (distanceBetween + unit_size));
                float xPos = (lateralOffset + x * (distanceBetween + unit_size));

                glm::vec2 pos(xPos, yPos);
                glm::vec2 size(unit_size, unit_size);
                
                std::string ID = GameEditor::CreateGameObject("Enemy", pos, true, size, true, texName);
                // Turns collision ON
                GameEditor::GameObjectSetSolid(ID, true);
                // Set GameObject's tag
                GameContext::CurrentObjects[ID]->SetTag("Enemy");
                // Set speed to level speed
                GameContext::CurrentAttributes[ID]->enemyScript.SetYSpeed(enemySpeed);
                

                this->enemies.push_back(ID);
            }
            else if (enemyData[y][x] > 1)
            {
                /*
                glm::vec3 color = glm::vec3(1.0f); // original: white
                if (tileData[y][x] == 2)
                    color = glm::vec3(0.2f, 0.6f, 1.0f);
                else if (tileData[y][x] == 3)
                    color = glm::vec3(0.0f, 0.7f, 0.0f);
                else if (tileData[y][x] == 4)
                    color = glm::vec3(0.8f, 0.8f, 0.4f);
                else if (tileData[y][x] == 5)
                    color = glm::vec3(1.0f, 0.5f, 0.0f);
                
                glm::vec2 pos(unit_width * x, unit_height * y);
                glm::vec2 size(unit_width, unit_height);
                this->Bricks.push_back(
                    GameObject(pos, size, ResourceManager::GetTexture("block"), color)
                );
                */
            }
        }
    }
}

void GameLevel::EnemyDied(std::string name) {
    enemies.erase(std::remove(enemies.begin(), enemies.end(), name), enemies.end());
}


