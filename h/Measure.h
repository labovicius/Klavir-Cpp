#pragma once
#include "MusicSymbol.h"
#include <list>

using namespace std;

class Measure {
protected:
	Duration duration, available;
	list <MusicSymbol> symbols;
public:
	Measure(Duration d) {
		duration = d;
	}
	Measure() {};
	void addSymbol(MusicSymbol *ms) {
		if (haveSpace(*ms)) {
			symbols.push_back(*ms);
			Duration sum = sumSymbols();
			available = available - sum;
		}
	}
	list<MusicSymbol> getList() {
		return symbols;
	}
	void changeOctave(int i) {
		list <MusicSymbol> ::iterator it;
		for (it = symbols.begin(); it != symbols.end(); ++it) {
			it->changingOctave(i);
		}
	}
	bool haveSpace(MusicSymbol& ms) {
		if (available.dohvBrojilac() == 0) return false;
		Duration nulti(0, 0);
		Duration osmina(1, 8);
		Duration help = ms.getDuration();
		Duration help2 = help - available;
		if (help2 == osmina) {
			ms.setHalf();
			ms.setDuration(osmina);
			return true;
		}
		Duration help3 = available - help;
		if (nulti > help3) {
			return false;
		}
		if (help3.dohvBrojilac() <  0) {
			return false;
		}
		return true;
	}
	Duration sumSymbols() {
		list <MusicSymbol> ::iterator it;
		Duration sum(0,0);
		for (it = symbols.begin(); it != symbols.end(); ++it) {
			Duration help = it->getDuration();
			sum = sum + help;
		}
		return sum;
	}
	Duration getAvailable() {
		return available;
	}
	void addTogether() {
		symbols.back().addTogether();
	}
	void setAvailable() {
		available = duration;
	}
	void changeDuration(Duration d) {
		duration = d;
		available = d;
	}
	int iterateSymbol(int i) {
		list <MusicSymbol> ::iterator it;
		for (auto it = next(symbols.begin(), i); it != symbols.end(); ++it) {
			it->writeSymbol();
			i++;
			return i;
		}
	}
	void writeMeasure() {
		list <MusicSymbol> ::iterator it;
		for (it = symbols.begin(); it != symbols.end(); ++it)
			it->writeSymbol();
		cout << "| ";
	}
};