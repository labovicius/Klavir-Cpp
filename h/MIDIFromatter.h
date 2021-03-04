#pragma once
#include "Formatter.h"
#include "makeMidi.h"
class MIDIFromatter :
	public Formatter
{
public:
	MIDIFromatter(Composition c, map<pair <int, string>, string> mapa) {
		com = c;
		makeMidi(mapa);
	};
	
	~MIDIFromatter() {};
};

