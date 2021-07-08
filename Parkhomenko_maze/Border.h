#pragma once

#include "Object.h"

using namespace sf;

class Border : public Object
{
public:
	Border(std::string filename) : Object(filename)
	{
		this->group_id = 2;
		this->setPosition(Vector2f(300, 300));
	}

	void Update()
	{
	}

	~Border() {}
};