#include "GameContext.h"

std::map<std::string, std::unique_ptr<GameObject>> GameContext::CurrentObjects;
std::map<std::string, std::unique_ptr<Attribute>> GameContext::CurrentAttributes;
std::queue<std::pair<std::string, float>> GameContext::SoundQueue;

bool GameContext::gameOver = false;
bool GameContext::win = false;