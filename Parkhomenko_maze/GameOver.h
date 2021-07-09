#pragma once

#include "Game.h"
#include "ObjectManager.h"

using namespace sf;

class GameOver : public GameState
{
public:
	GameOver();

	virtual void Initialize(RenderWindow* window);
	virtual void Update(RenderWindow* window);
	virtual void Render(RenderWindow* window);
	virtual void Destroy(RenderWindow* window);
private:
	Font font;
	Text gameOver;
};
