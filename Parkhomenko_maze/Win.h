#pragma once

#include "ObjectManager.h"
#include "Game.h"

using namespace sf;

class Win : public GameState
{
public:
	Win();
	virtual void Initialize(RenderWindow* window);
	virtual void Update(RenderWindow* window);
	virtual void Render(RenderWindow* window);
	virtual void Destroy(RenderWindow* window);
private:
	Font font;
	Text win;
};