#pragma once

#include "Object.h"

using namespace sf;

class Benny : public Object
{
public:
	bool nextLevel = false;

	Benny(std::string filename, IntRect rect) : Object(filename, rect)
	{
		this->group_id = 1;
		this->lives = 3;
		this->lootCount = 0;
	}

	void Update() 
	{

		this->velocity.x = Keyboard::isKeyPressed(Keyboard::Key::Right) - Keyboard::isKeyPressed(Keyboard::Key::Left);
		this->velocity.y = Keyboard::isKeyPressed(Keyboard::Key::Down) - Keyboard::isKeyPressed(Keyboard::Key::Up);

		while (this->getPosition().x + this->getGlobalBounds().width >= 1400)
		{
			this->move(Vector2f(-1, 0));
		}

		while (this->getPosition().x <= 0)
		{
			this->move(Vector2f(1, 0));
		}

		while (this->getPosition().y + this->getGlobalBounds().height >= 1040)
		{
			this->move(Vector2f(0, -1));
		}

		while (this->getPosition().y <= 0)
		{
			this->move(Vector2f(0, 1));
		}

		Object::Update();
	}

	void AddLoot()
	{
		this->lootCount += 1;
	}

	void RemoveLoot()
	{
		this->lootCount -= 1;
	}

	void NewGame()
	{
		this->lootCount = 0;
	}

	void RemoveLife()
	{
		this->lives -= 1;
	}

	void NewLevel()
	{
		this->lootCount = 0;
	}

	void setNextLevel(bool set)
	{
		this->nextLevel = set;
	}

	int LootCount()
	{
		return this->lootCount;
	}

	int Lives()
	{
		return this->lives;
	}

	~Benny()
	{
	}

private:
	int lootCount, lives;
	
};
