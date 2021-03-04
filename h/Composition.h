#pragma once
 #include "Part.h"

class Composition
{
protected:
	Part left;
	Part right;
	Duration duration;

public:
	Composition(Duration d) {
		duration = d;
		left = Part(duration);
		right = Part(duration);
	}
	void setComposition(map<pair <int, string>, string> mapa,string kompozicija) {
		ifstream melodija(kompozicija.c_str());
		regex reg1(".*");
		string s;

		string incr2 = "#2";
		string incr3 = "#3";
		string incr4 = "#4";
		string incr5 = "#5";
		string incr6 = "#6";
		char st = '[';
		string start(1, st);
		char e = ']';
		string en(1, e);
		char blanko = ' ';
		string space(1, blanko);
		char gore = '|';
		string up(1, gore);

		left.setMainDuration(duration);
		right.setMainDuration(duration);
		
		while (getline(melodija, s)) {
			smatch result;
			if (regex_match(s, result, reg1)) {
				string niz = result.str(0);

				cout << niz << endl;

				string::iterator iter;
				map<pair <int, string >, string> ::iterator it;
				
					int br = niz.length();
					it = mapa.begin();
					string::iterator help = niz.begin();
					bool together = false;
					bool first = false;
					bool last = false;
					bool haveSpace = false;
					for (int i = 0; i < br; i++){ 
					bool added = false;
						for (iter = niz.begin(); iter != niz.end(), help != niz.end(); iter++, help++) {
							if (added) { help = iter; break; }
							if (help != iter) iter = help;
							char c = *iter;
							string str(1, c);
							for (it = mapa.begin(); it != mapa.end(); it++) {
								if (str == start) {
									together = true;
									first = true;
									added = true;
									break;
								}
								if (str == en) {
									together = false;
									last = true;
									break;
								}
								if (it->second == str) {
									added = true;
									string three = "3";
									string::iterator findOct;
									string oct = it->first.second;
									MusicSymbol note;
									findOct = oct.begin();
									char vis = oct.at(0);
									string visina(1, vis);
									note.changeVis(visina);
									findOct++;
									note.deleteIncrease();
				
									if (&*findOct == incr2 || &*findOct == incr3 || &*findOct == incr4
										|| &*findOct == incr5 || &*findOct == incr6) {
										note.addIncrease();
										findOct++;
									}
									int okt = atoi(&*findOct);
									note.changeOkt(okt);
									if (&*findOct > three) {
										if (together) {
											added = true;
											if (haveSpace) {
												Duration durat(1, 8);
												note.setDuration(durat);
												this->right.addSymbol(new MusicSymbol(note));
												this->left.addTogether();
												this->right.addTogether();
												this->left.addSymbol(new MusicSymbol(1, 8));
											}
											else {
												Duration durat(1, 4);
												note.setDuration(durat);
												this->right.addSymbol(new MusicSymbol(note));
												this->left.addTogether();
												this->right.addTogether();
												this->left.addSymbol(new MusicSymbol(1, 4));
											}
										}
										else {
											added = true;
											Duration durat(1, 4);
											note.setDuration(durat);
											this->right.addSymbol(new MusicSymbol(note));
											this->left.addSymbol(new MusicSymbol(1, 4));
										}
									}
									else {
										if (together) {
											added = true;
											if (haveSpace) {
												Duration durat(1, 8);
												note.setDuration(durat);
												this->right.addSymbol(new MusicSymbol(note));
												this->left.addTogether();
												this->right.addTogether();
												this->left.addSymbol(new MusicSymbol(1, 8));
											}
											else {
												Duration durat(1, 4);
												note.setDuration(durat);
												this->right.addSymbol(new MusicSymbol(note));
												this->left.addTogether();
												this->right.addTogether();
												this->left.addSymbol(new MusicSymbol(1, 4));
											}
										}
										else {
											added = true;
											Duration durat(1, 4);
											note.setDuration(durat);
											this->left.addSymbol(new MusicSymbol(note));
											this->right.addSymbol(new MusicSymbol(1, 4));
										}
									}
									break;
								}
								if (str == space) {
									if (!together) {
										//	this->left.addTogether();
										//	this->right.addTogether();


										added = true;
										haveSpace = true;
										this->right.addSymbol(new MusicSymbol(1, 8));
										this->left.addSymbol(new MusicSymbol(1, 8));
										break;
									}
								}
								if (str == up) {
									added = true;
									this->right.addSymbol(new MusicSymbol(1, 4));
									this->left.addSymbol(new MusicSymbol(1, 4));
									break;
								}
							}
						}

				}
			}
		}
	}

	Duration getDuration() {
		return duration;
	}
	Composition() {};
	void writeComposition() {
		int m = left.size();
		int r = 0,l = 0;
		for (; l < m;) {
			r = right.writePart(r);
			l = left.writePart(l);
			cout << endl;
		}
	}
	Part getRight() {
		return right;
	}
	Part getLeft() {
		return left;
	}
	void changeOctave(int i) {
		left.changeOctave(i);
		right.changeOctave(i);
	}
	void changeDuration(Duration d) {
		duration = d;
	}
};
