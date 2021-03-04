#pragma once
#include "Duration.h"
#include <iomanip>
class MusicSymbol
{
protected:
	Duration d;
	int oktava;
	string visina;
	bool increase;
	bool first = false;
	bool together = false;
	bool last = false;
	bool half = false;
public:
	MusicSymbol(int b,int i) {
		d = Duration(b,i);
		oktava = 0;
		visina = "";
		increase = NULL;
	};
	MusicSymbol(int b, int i,int o ,string v ) {
		d = Duration(b, i);
		oktava = o;
		visina = v;
		increase = false;

	}
	MusicSymbol(int b, int i, int o, string v,bool in) {
		d = Duration(b, i);
		oktava = o;
		visina = v;
		increase = true;

	}
	void changingOctave(int i) {
		if (oktava != 0) {
			oktava += i;
		if (oktava > 6) oktava = 6;
		if (oktava < 2) oktava = 2;
		}
	}
	int getOktava() {
		return oktava;
	}
	bool getIncrease() {
		return increase;
	}
	void setHalf() {
		half = true;
	}
	bool getHalf() {
		return half;
	}
	string getVisina() {
		return visina;
	}
	MusicSymbol() {};
	void addTogether() {
		together = true;
	}
	void setDuration(Duration d) {
		this->d = d;
	}
	Duration getDuration() {
		return d;
	}
	void addIncrease() {
		if (!increase) increase = true;
	}
	void deleteIncrease() {
		if (increase) increase = false;
	}
	bool haveIncrease() {
		return increase;
	}
	void changeVis(string v) {
		visina = v;
	}
	void changeOkt(int o) {
		oktava = o;
	}
	void setFirst() {
		first = true;
	}
	bool getFirst() {
		return first;
	}
	bool getTogether() {
		return together;
	}
	void writeSymbol() {
		if (oktava == 0) {
			if (together) {
				if (d.dohvImenilac() == 8) {
					cout << " ü";
				}
				else {
					cout << " ä";
				}
				return;
			}
			else {
				if (d.dohvImenilac() == 8) {
					cout << " ü ";
				}
				else {
					cout << " ä ";
				}
				return;
			}
		}
		else {
			if (together) {
				if (d.dohvImenilac() == 4) {
					cout << visina;
				}
				else {
					char v = tolower(visina[0]);
					cout << v;
				}
				if (increase) cout << "#";
				cout << oktava << "";
				return;
			}
			else {
				if (d.dohvImenilac() == 4) {
					cout << visina;
				}
				else {
					char v = tolower(visina[0]);
					cout << v;
				}
				if (increase) cout << "#";
				cout << oktava << " ";
				return;
			}
		}
	}
};

