#pragma once
#include "Composition.h"

class Formatter
{
protected:
	Composition com;
public:
	Formatter(Composition c) {
		com = c;
	};
	Formatter() {};
	~Formatter() {}
};

