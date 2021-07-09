#pragma once

#include "Object.h"

using namespace sf;

class Dummy : public Object
{
public:
	Dummy(std::string filename) : Object(filename)
	{
		this->group_id = 4;
	}

	Dummy(std::string filename, IntRect rect) : Object(filename, rect)
	{
		this->group_id = 4;
	}

	void Update()
	{
	}

	~Dummy() {}
};