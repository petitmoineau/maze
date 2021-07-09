#pragma once

#include <SFML/Graphics.hpp>
#include "ObjectManager.h"

using namespace sf;

class GameState
{
public:
	GameState();
	void LoadLevel(int levelData[]);
	
	virtual void Initialize(RenderWindow* window);
	virtual void Update(RenderWindow* window);
	virtual void Render(RenderWindow* window);
	virtual void Destroy(RenderWindow* window);
private:
	Font font;
	Text treasures, lives;
	ObjectManager* manager;
};

class State
{
public:
	State()
	{
	}
	void setWindow(RenderWindow* window)
	{
		this->window = window;
	}

	void setState(GameState* state)
	{
		if (this->state != NULL)
		{
			this->state->Destroy(this->window);
			delete this->state;
		}
		this->state = state;
		if (this->state != NULL)
		{
			this->state->Initialize(this->window);
		}
	}

	void Update()
	{
		if (this->state != NULL)
		{
			this->state->Update(this->window);
			this->state->Render(this->window);
		}
	}

	~State()
	{
		if (state != NULL)
		{
			delete this->state;
		}
	}
private:
	RenderWindow* window;
	GameState* state;
};

extern State coreState;
extern bool quitGame;