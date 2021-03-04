#pragma once
#include "MidiFile.h"
#include <iostream>
#include <fstream>
#include <set>
#include <string>
#include <map>
#include <regex>
#include <iomanip>
#include "setMap.h"
#include "Measure.h"
#include "Duration.h"
#include "Part.h"
#include "Composition.h"

#include "MXMLFormatter.h"

using namespace std;
using namespace smf;

void makeMidi(map<pair <int, string>, string> mapa) {
			
			MidiFile outputfile;
			outputfile.absoluteTicks();
			vector<uchar> midievent;
			midievent.resize(3);
			int tpq = 48;
			outputfile.setTicksPerQuarterNote(tpq);
			outputfile.addTrack(1);

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

			ifstream melodija("C:\\fur_elise.txt");
			regex reg1(".*");
			string s;
			int mrhythm[150];
			int brhythm[150];
			int melody[150];
			int bass[150];
			while (getline(melodija, s)) {
				smatch result;
				if (regex_match(s, result, reg1)) {
					string niz = result.str(0);

					cout << niz << endl;

					map<pair <int, string >, string> ::iterator it;
					string::iterator iter;
					int br = niz.size();

					it = mapa.begin();
					string::iterator help = niz.begin();
					bool together = false;
					for (int i = 0; i < 60; i++) {
						bool added = false;
						bool haveSpace = false;
						for (iter = niz.begin(); iter != niz.end(), help != niz.end(); iter++, help++) {
							if (added) { help = iter; break; }
							if (help != iter) iter = help;
							char c = *iter;
							string str(1, c);
							for (it = mapa.begin(); it != mapa.end(); it++) {
								if (str == start) {
									together = true;
									added = true;
									mrhythm[i] = 1;
									brhythm[i] = 1;
									melody[i] = 1;
									bass[i] = 1;
									break;
								}
								if (str == en) {
									together = false;
									mrhythm[i] = 1;
									brhythm[i] = 1;
									melody[i] = 1;
									bass[i] = 1;
									break;
								}
								if (it->second == str) {
									added = true;
									string three = "3";
									string::iterator findOct;
									string oct = it->first.second;
									findOct = oct.begin();
									findOct++;
									if (&*findOct == incr2 || &*findOct == incr3 || &*findOct == incr4
										|| &*findOct == incr5 || &*findOct == incr6) findOct++;

									if (&*findOct > three) {
										if (together) {
											bass[i] = it->first.first;
											melody[i] = 1;
											brhythm[i] = 0;
											mrhythm[i] = 0;
											added = true;
										}
										else {
											bass[i] = it->first.first;
											melody[i] = 1;
											brhythm[i] = 2;
											mrhythm[i] = 2;
											added = true;
										}
									}
									else {
										if (together) {
											melody[i] = it->first.first;
											bass[i] = 1;
											mrhythm[i] = 0;
											brhythm[i] = 0;
											added = true;
										}
										else {
											melody[i] = it->first.first;
											bass[i] = 1;
											mrhythm[i] = 2;
											brhythm[i] = 2;
											added = true;
										}
									}
									break;
								}
								if (str == space) {
									if (together) haveSpace = true;
									mrhythm[i] = 0;
									brhythm[i] = 0;
									melody[i] = 1;
									bass[i] = 1;
									added = true;
									break;
								}
								if (str == up) {
									mrhythm[i] = 0;
									brhythm[i] = 0;
									melody[i] = 1;
									bass[i] = 1;
									added = true;
									break;
								}
							}
						}
					}
				}
			}
			melody[60] = -1;
			mrhythm[60] = -1;
			bass[60] = -1;
			brhythm[60] = -1;
			int i = 0;
			int actiontime = 0;
			midievent[2] = 64;
			while (melody[i] >= 0) {
				if (melody[i] == 1 && melody[i - 1] == 1) goto skok;
				midievent[0] = 0x90;
				midievent[1] = melody[i];
				outputfile.addEvent(0, actiontime, midievent);
				actiontime += tpq / 2 * mrhythm[i];
				if (mrhythm[i] == 0) {
					actiontime += tpq / 2 * mrhythm[i];
				}
				midievent[0] = 0x80;
				outputfile.addEvent(0, actiontime, midievent);
			skok: i++;
			}
			i = 0;
			actiontime = 0;
			while (bass[i] >= 0) {
				if (bass[i] == 1 && bass[i - 1] == 1) goto skok1;
				midievent[0] = 0x90;
				midievent[1] = bass[i];
				outputfile.addEvent(1, actiontime, midievent);
				actiontime += tpq / 2 * brhythm[i];
				if (brhythm[i] == 0) {
					actiontime -= tpq / 2 * brhythm[i];
				}
				midievent[0] = 0x80;
				outputfile.addEvent(1, actiontime, midievent);
			skok1: i++;
			}
			outputfile.sortTracks();
			outputfile.write("kompozicija.mid");
		}
