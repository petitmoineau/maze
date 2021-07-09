#include "MainMenu.h"
#include "Game.h"
#include "Win.h"

Win::Win()
{

}

void Win::Initialize(RenderWindow* window)
{
	this->font.loadFromFile("HennyPenny-Regular.ttf");
	this->win = Text("You finally win!!", font, 100U);
	this->win.setFillColor(Color::Black);
	this->win.setOrigin(Vector2f(this->win.getGlobalBounds().width / 2, this->win.getGlobalBounds().height / 2));
	this->win.setPosition(window->getSize().x / 2, window->getSize().y / 2);
}
void Win::Update(RenderWindow* window)
{
	if (Keyboard::isKeyPressed(Keyboard::Key::Return))
	{
		coreState.setState(new MainMenu());
	}
}

void Win::Render(RenderWindow* window)
{
	window->draw(this->win);
}
void Win::Destroy(RenderWindow* window)
{

}