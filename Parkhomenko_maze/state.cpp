#include "Game.h"
#include "Object.h"
#include "Benny.h"
#include "Dummy.h"
#include "Border.h"
#include "Loot.h"
#include "MainMenu.h"
#include "GameOver.h"
#include "Win.h"
#include <fstream>
#include <sstream>

using namespace std;

string in_file_name = "firstLevel.txt";
int firstLevel[400];
bool won = false;
int lootAmount = 4;
bool nextLevel = false;

void UpdateCollisions(Object* objectA, Object* objectB)
{
	((Benny*)objectA)->setNextLevel(false);//
	if (objectA->Group() == 1 && objectB->Group() == 2)
	{
		objectA->move(Vector2f(-objectA->velocity.x, -objectA->velocity.y));
	}
	if (objectA->Group() == 1 && objectB->Group() == 3)
	{
		objectA->move(Vector2f(-objectA->velocity.x, -objectA->velocity.y));
		objectB->Load("Loot.png", IntRect(300, 30, 82, 70));
		if(!objectB->getState()) ((Benny*)objectA)->AddLoot();
		objectB->setOpened();
	}
	if (objectA->Group() == 1 && objectB->Group() == 4)
	{
		objectB->setActive(0);
		((Benny*)objectA)->RemoveLife();
	}
	if (objectA->Group() == 1 && objectB->Group() == 5)
	{
		if (((Benny*)objectA)->LootCount() == 4)
		{
			objectB->Load("Door.png", IntRect(4, 67, 330, 721));
			objectB->setOpened();
		}
		if (!objectB->getState()) objectA->move(Vector2f(-objectA->velocity.x, -objectA->velocity.y));
		
	}
	if (objectA->Group() == 1 && ((Benny*)objectA)->LootCount() == lootAmount)
	{
		((Benny*)objectA)->NewLevel();
		((Benny*)objectA)->setNextLevel(true);
		nextLevel = ((Benny*)objectA)->nextLevel;
		lootAmount++;
		if (lootAmount == 8)
		{
			won = true;
			lootAmount = 0;
			((Benny*)objectA)->NewGame();
		}
	}
}

GameState::GameState()
{
	this->manager = new ObjectManager();
}

void GameState::LoadLevel(int levelData[])
{
	nextLevel = false;
	switch (lootAmount)
	{
	case 5:
		in_file_name = "secondLevel.txt";
		break;
	case 6:
		in_file_name = "thirdLevel.txt";
		break;
	case 7:
		in_file_name = "fourthLevel.txt";
		break; 
	case 8:
		in_file_name = "fifthLevel.txt";
		break;
	}
	if (!in_file_name.empty())
	{
		std::ifstream file(in_file_name);

		if (file.is_open())
		{
			int number;
			for (int i = 0; file >> number; i++)
			{
				firstLevel[i] = number;
			}
			file.close();
		}
	}

	for (int y = 0; y < 15; y += 1)
	{
		for (int x = 0; x < 17; x += 1)
		{
			string name = "";
			switch (levelData[x + y * 17])
			{
			case 1:
				name = "Benny";
				this->manager->AddEntity(name, new Benny("Benny.png", IntRect(50, 13, 100, 86)));
				this->manager->Get(name)->setScale(0.8, 0.8);
				break;
			case 2:
				name = "Border";
				this->manager->AddEntity(name, new Border("Border.png"));
				//this->manager->Get(name)->setPosition(x * 70, y * 80);
				break;
			case 3:
				name = "Loot";
				this->manager->AddEntity(name, new Loot("Loot.png", IntRect(60, 38, 75, 52)));
				break;
			case 4:
				name = "Dummy";
				this->manager->AddEntity(name, new Dummy("Dummy.png", IntRect(60, 38, 74, 52)));
				break;
			default:
				continue;
			}
			this->manager->Get(name)->setPosition(x * 70, y * 80);
		}
	}
}

void GameState::Initialize(RenderWindow* window)
{
	this->manager->SetCollisionMethod(UpdateCollisions);

	this->font.loadFromFile("HennyPenny-Regular.ttf");

	this->treasures = Text("Treasures: ", font, 32U);
	this->treasures.setFillColor(Color::Black);
	this->treasures.setOrigin(Vector2f(0, 0));
	this->treasures.setPosition(window->getSize().x / 5, 0);

	this->lives = Text("Lives: ", font, 32U);
	this->lives.setFillColor(Color::Black);
	this->lives.setOrigin(Vector2f(this->lives.getGlobalBounds().width / 2, 0));
	this->lives.setPosition(window->getSize().x / 5 * 4, 0);

	this->LoadLevel(firstLevel);
}
void GameState::Update(RenderWindow* window)
{
	manager->Update();
	if (((Benny*)this->manager->Get("Benny"))->Lives() < 1)
	{
		coreState.setState(new GameOver());
	}
	if (Keyboard::isKeyPressed(Keyboard::Key::Escape))
	{
		coreState.setState(new MainMenu());
	}
	if (won)
	{
		won = false;
		nextLevel = false;
		coreState.setState(new Win());
	}
	else if (!won && nextLevel) coreState.setState(new GameState());
}
void GameState::Render(RenderWindow* window)
{
	this->treasures.setString("Treasures: " + to_string(((Benny*)this->manager->Get("Benny"))->LootCount()));
	this->lives.setString("Lives: " + to_string(((Benny*)this->manager->Get("Benny"))->Lives()));
	manager->Render(window);
	window->draw(treasures);
	window->draw(lives);
}
void GameState::Destroy(RenderWindow* window)
{
	delete manager;
}