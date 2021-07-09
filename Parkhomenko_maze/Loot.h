#pragma once

#include "Object.h"

using namespace sf;

class Loot : public Object
{
public:
	Loot(std::string filename) : Object(filename)
	{
		this->group_id = 3;
	}

	Loot(std::string filename, IntRect rect) : Object(filename, rect)
	{
		this->group_id = 3;
	}

	void Update()
	{
	}

	~Loot()
	{
		delete this->getTexture();
	}
};
