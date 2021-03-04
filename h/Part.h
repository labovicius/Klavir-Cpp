#pragma once
#include "Measure.h"
#include "iterate.h"
class Part
{
protected:
	list<Measure> taktovi;
	Measure m;
	Duration main;
public:
	Part(Duration d) {
		main = d;
		taktovi.push_back(m);
		taktovi.back().setAvailable();
	}
	Part() {};
	void addSymbol(MusicSymbol *ms) {
		if (!(taktovi.back().haveSpace(*ms))) {
			taktovi.push_back(m);
			taktovi.back().changeDuration(main);
			taktovi.back().setAvailable();
		}
		taktovi.back().changeDuration(main);
		taktovi.back().addSymbol(ms);
		if (ms->getHalf()) {
		taktovi.push_back(m);
		taktovi.back().changeDuration(main);
		taktovi.back().setAvailable();
		taktovi.back().addSymbol(ms);
		}
	}
	list<Measure> getList() {
		return taktovi;
	}
	void changeOctave(int i) {
		list <Measure> ::iterator it;
		for (it = taktovi.begin(); it != taktovi.end(); ++it) {
			it->changeOctave(i);
		}
	}
	int writePart(int i) {
		list <Measure> ::iterator it;
		for (auto it = next(taktovi.begin(), i); it != taktovi.end(); ++it) {
			it->writeMeasure();
			if (i % 5 == 4) break;
			i++;
		}
		i++;
		cout << "\n";
		return i;
	}
	int iterateMeasure(int i) {
		list <Measure> ::iterator it;
		for (auto it = next(taktovi.begin(), i); it != taktovi.end(); ++it) {
			it->writeMeasure();
			i++;
			return i;
		}
	}
	iterateS iterateSymbol(iterateS iter) {
		iterateS iterateSym;
		list <Measure> ::iterator it;
		for (auto it = next(taktovi.begin(), iter.t); it != taktovi.end(); ++it) {
			iter.i = it->iterateSymbol(iter.i);
			
			iterateSym.i = iter.i;
			iterateSym.t = iter.t;
			
			return iterateSym;
		}
	}
	void addTogether() {
		taktovi.back().addTogether();
	}
	int size() {
		int i;
		return i = taktovi.size();
	}
	Duration getMainDuration() {
		return main;
	}
	void setMainDuration(Duration d) {
		main = d;
		for (auto it = taktovi.begin(); it != taktovi.end(); ++it) {
			it->changeDuration(d);
		}
	}