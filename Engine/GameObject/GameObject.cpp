#include "GameObject.h"

GameObject::GameObject()
	: isSolid(false), hasBeenDestroyed(false) {
	this->name = "";
	this->tag = "";
	this->id = 0;
	this->transform.position = glm::vec2(0.0f, 0.0f);
	this->transform.size = glm::vec2(1.0f, 1.0f);
	this->transform.velocity = glm::vec2(0.0f, 0.0f);
	this->transform.rotation = 0.0f;

	this->sprite.color = glm::vec4(1.0f);
	this->sprite.texture = nullptr;
}
GameObject::~GameObject()
{
}


GameObject::GameObject(std::string name, int id, glm::vec2 pos, glm::vec2 size, std::shared_ptr<Texture2D> texture, glm::vec4 color, glm::vec2 velocity)
	: isSolid(false), hasBeenDestroyed(false), tag() {
	this->name = name;
	this->id = id;
	this->transform.position = pos;
	this->transform.size = size;
	this->transform.velocity = velocity;
	this->transform.rotation = 0.0f;
	this->sprite.color = color;
	this->sprite.texture = texture;
}

std::string GameObject::GetName()
{
	return this->name;
}

int GameObject::GetID()
{
	return this->id;
}

std::string GameObject::GetFormattedName() {
	return (this->name + "_" + std::to_string(this->id));
}

std::string GameObject::GetTag()
{
	return this->tag;
}

void GameObject::SetTag(std::string tagName)
{
	this->tag = tagName;
}

void GameObject::setTexture(std::string texName)
{
	this->sprite.texture = ResourceManager::GetTexture(texName);
}

std::string GameObject::FormattedName(std::string name, int id)
{
	return (name + "_" + std::to_string(id));
}
