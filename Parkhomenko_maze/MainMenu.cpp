#include "MainMenu.h"
#include "Game.h"

MainMenu::MainMenu()
{

}

void MainMenu::Initialize(RenderWindow* window)
{
	this->font.loadFromFile("HennyPenny-Regular.ttf");
	this->text = Text("Je Suis Benny", font, 100U);
	this->text.setFillColor(Color::Black);
	this->text.setOrigin(Vector2f(this->text.getGlobalBounds().width / 2, 0));
	this->text.setPosition(window->getSize().x / 2, window->getSize().y / 3);

	this->play = Text("Play Benny", font, 64U);
	this->play.setFillColor(Color::Black);
	this->play.setOrigin(Vector2f(this->play.getGlobalBounds().width / 2, 0));
	this->play.setPosition(window->getSize().x / 2, window->getSize().y / 3 + text.getGlobalBounds().height + 50);

	this->quit = Text("Quit Benny:(", font, 64U);
	this->quit.setFillColor(Color::Black);
	this->quit.setOrigin(Vector2f(this->quit.getGlobalBounds().width / 2, 0));
	this->quit.setPosition(window->getSize().x / 2, window->getSize().y / 3 + text.getGlobalBounds().height + play.getGlobalBounds().height + 100);

	this->selected = 0;
}
void MainMenu::Update(RenderWindow* window)
{
	if (Keyboard::isKeyPressed(Keyboard::Key::Up) && !up)
	{
		this->selected -= 1;
	}
	if (Keyboard::isKeyPressed(Keyboard::Key::Down) && !down)
	{
		this->selected -= 1;
	}

	if (this->selected < 0)
	{
		this->selected = 1;
	}
	if (this->selected > 1)
	{
		this->selected = 0;
	}

	up = Keyboard::isKeyPressed(Keyboard::Key::Up);
	down = Keyboard::isKeyPressed(Keyboard::Key::Down);
	if (Keyboard::isKeyPressed(Keyboard::Key::Return))
	{
		switch (this->selected)
		{
		case 0:
			coreState.setState(new GameState());
			break;
		case 1:
			quitGame = true;
			break;
		}
	}
}

void MainMenu::Render(RenderWindow* window)
{
	this->play.setFillColor(Color::Black);
	this->quit.setFillColor(Color::Black);
	switch (this->selected)
	{
	case 0:
		this->play.setFillColor(Color::Yellow);
		break;
	case 1:
		this->quit.setFillColor(Color::Yellow);
		break;
	}

	window->draw(this->text);
	window->draw(this->play);
	window->draw(this->quit);
}
void MainMenu::Destroy(RenderWindow* window)
{

}