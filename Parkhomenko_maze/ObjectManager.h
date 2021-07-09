#pragma once

#include "Object.h"
#include <unordered_map>
#include <vector>

using namespace std;
using namespace sf;

typedef void CollisionUpdateEvent(Object* objectA, Object* objectB);

class ObjectManager
{
public:
	ObjectManager()
	{

	}

	void SetCollisionMethod(CollisionUpdateEvent* collisionsEvent)
	{
		this->collisionsEvent = collisionsEvent;
	}

	void AddEntity(string& name, Object* object)
	{
		unordered_map<string, Object*>::const_iterator found = this->objects.find(name);
		while (found != this->objects.end())
		{
			name += "0";
			found = this->objects.find(name);
		}
		this->objects.insert(make_pair(name, object));
	}

	Object* Get(string name)
	{
		unordered_map<string, Object*>::const_iterator found = this->objects.find(name);
		if (found != this->objects.end())
		{
			return found->second;
		}
		return NULL;
	}

	void Update()
	{
		vector<string> toRemove;

		for (auto& iterator : this->objects)
		{
			if (iterator.second != NULL)
			{
				if (this->collisionsEvent != NULL)
				{
					for (auto& iterator2 : this->objects)
					{
						if (iterator != iterator2)
						{
							if (iterator.second->Collision(iterator2.second))
							{
								this->collisionsEvent(iterator.second, iterator2.second);
							}
						}
					}
				}
				
				if (iterator.second->Active())
				{
					iterator.second->Update();
				}
				else
				{
					toRemove.push_back(iterator.first);
				}
			}
		}
		
		while (toRemove.size() > 0)
		{
			this->objects.erase(toRemove[toRemove.size() - 1]);
			toRemove.pop_back();
		}
		toRemove.clear();
	}

	void Render(RenderWindow* window)
	{
		for (auto& iterator : this->objects)
		{
			if (iterator.second != NULL)
			{
				if (iterator.second->Active())
				{
					window->draw(*iterator.second);
				}
			}
		}
	}

	~ObjectManager()
	{
		for (auto& iterator : this->objects)
		{
			//delete iterator.second;
		}
		this->objects.clear();
	}
private:
	unordered_map<string, Object*> objects;
	vector<string> toRemove;
	CollisionUpdateEvent* collisionsEvent;
};
