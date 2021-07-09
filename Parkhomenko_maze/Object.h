#pragma once 

#include <SFML/Graphics.hpp>
#include <string>

using namespace sf;

class Object : public sf::Sprite
{
public:
	Object()
	{
		this->active = 1;
		this->texture = new Texture();
		this->isOpened = false;
	}
	Object(std::string filename)
	{
		this->active = 1;
		this->texture = new Texture();
		this->Load(filename, IntRect());
		this->isOpened = false;
	}

	Object(std::string filename, IntRect rect)
	{
		this->active = 1;
		this->texture = new Texture();
		this->Load(filename, rect);
		this->isOpened = false;
	}

	void Load(std::string filename)
	{
		this->Load(filename, IntRect());
	}

	void Load(std::string filename, IntRect rect)
	{
		this->texture->loadFromFile(filename, rect);
		this->setTexture(*this->texture);
	}

	bool Collision(Object* object)
	{
		if (object != NULL)
		{
			return this->getGlobalBounds().intersects(object->getGlobalBounds());
		}
		return false;
	}

	void setActive(int active)
	{
		this->active = active;
	}

	int Active()
	{
		return this->active;
	}

	int Group()
	{
		return this->group_id;
	}

	void setOpened()
	{
		this->isOpened = true;
	}

	bool getState()
	{
		return this->isOpened;
	}

	virtual void Update()
	{
		this->move(this->velocity);
	}

	virtual ~Object()
	{
		delete this->texture;
	}

	Vector2f velocity;
protected:
	int active, group_id;
	bool isOpened;
private:
	Texture* texture;
};