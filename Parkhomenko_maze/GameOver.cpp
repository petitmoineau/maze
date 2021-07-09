#include "MainMenu.h"
#include "Game.h"
#include "GameOver.h"

GameOver::GameOver()
{

}

void GameOver::Initialize(RenderWindow* window)
{
	this->font.loadFromFile("HennyPenny-Regular.ttf");
	this->gameOver = Text("Game Over:(", font, 100U);
	this->gameOver.setFillColor(Color::Black);
	this->gameOver.setOrigin(Vector2f(this->gameOver.getGlobalBounds().width / 2, this->gameOver.getGlobalBounds().height / 2));
	this->gameOver.setPosition(window->getSize().x / 2, window->getSize().y / 2);
}
void GameOver::Update(RenderWindow* window)
{
	if (Keyboard::isKeyPressed(Keyboard::Key::Return))
	{
		coreState.setState(new MainMenu());
	}
}

void GameOver::Render(RenderWindow* window)
{
	window->draw(this->gameOver);
}
void GameOver::Destroy(RenderWindow* window)
{

}