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
#include "MIDIFromatter.h"
#include "iterate.h"

using namespace std;
using namespace smf;

int main(int argc, char** argv) {

	
	iterateS iterateSr,iterateSl;
	map<pair <int, string>, string> map_csv;
	string putanjaMape,putanjaKompozicije;
	cout << "Unesi putanju do map.csv " << endl;
	getline(cin, putanjaMape);
	setMap(map_csv,putanjaMape);
	cout << "Unesi putanju do kompozicije " << endl;
	getline(cin, putanjaKompozicije);
	int i, b;
	cout << "Ucitaj duzinu trajanja takta ";
	cin >> b;
	getchar();
	cin >> i;
	getchar();
	while (i != 4 && i != 8) {
		cout << "Nedozvoljen imenilac,pokusajte ponovo sa duzinom taktova ";
		cin >> b;
		getchar();
		cin >> i;
	}
	Duration duration(b, i);
	Composition c(duration);
	c.setComposition(map_csv,putanjaKompozicije);
	while (1) {
		int option;
		cout << endl << "_______________________________________" << endl
			<< "|1. Ispisivanje podataka o kompoziciji |" << endl
			<< "|2. Iteriranje kroz kompoziciju        |" << endl
			<< "|3. Izmena takta kompozicije           |" << endl
			<< "|4. Pomeranje kompozicije              |" << endl;
		cin >> option;
		cout << "|______________________________________|" << endl;

		if (option == 1) {
			c.writeComposition();
		}
		if (option == 2) {
			int option2;
			int numr = 0,numl = 0;

			numr = c.getRight().iterateMeasure(numr);
			cout << endl;
			numl = c.getLeft().iterateMeasure(numl);
			cout << endl << "_______________________________________" << endl
				<< "|1. Prelazak na sledeci takt           |" << endl
				<< "|2. Povratak na prethodni takt         |" << endl
				<< "|3. Iteriranje kroz note               |" << endl;
			cin >> option2;
			cout << "|______________________________________|" << endl;
			while (option2 != 0) {
			switch (option2) {
			case 1: numr = c.getRight().iterateMeasure(numr); 
					cout << endl;
					numl = c.getLeft().iterateMeasure(numl); 
					cout << endl << "_______________________________________" << endl
						<< "|1. Prelazak na sledeci takt           |" << endl
						<< "|2. Povratak na prethodni takt         |" << endl
						<< "|3. Iteriranje kroz note               |" << endl;
					cin >> option2;
					cout << "|______________________________________|" << endl;
				break;
			case 2: numr = c.getRight().iterateMeasure(numr-2);
					cout << endl;
					numl = c.getLeft().iterateMeasure(numl-2); 
					cout << endl << "_______________________________________" << endl
						<< "|1. Prelazak na sledeci takt           |" << endl
						<< "|2. Povratak na prethodni takt         |" << endl
						<< "|3. Iteriranje kroz note               |" << endl;
					cin >> option2;
					cout << "|______________________________________|" << endl;
				break;
			case 3:	
				int option3 = 1;
				while (option3 != 0) {
					iterateSr.i = 0;
					iterateSr.t = 0;
					iterateSl.i = 0;
					iterateSl.t = 0;
					cout << endl << "________________________________________" << endl
						<< "|1. Prelazak na sledecu notu            |" << endl
						<< "|2. Povratak na prethodnu notu          |" << endl
						<< "|3. Menjanje oktave ili visine note     |" << endl
						<< "|4. Dodavanje ili uklanjanje povisilice |" << endl;
					cin >> option3;
					cout << "|_______________________________________|" << endl;
					while (option3 != 0) {
						switch (option3) {
						case 1:
							iterateSr = c.getRight().iterateSymbol(iterateSr);
							cout << endl;
							iterateSl = c.getLeft().iterateSymbol(iterateSl);
							cout << endl << "________________________________________" << endl
								<< "|1. Prelazak na sledecu notu            |" << endl
								<< "|2. Povratak na prethodnu notu          |" << endl
								<< "|3. Menjanje oktave ili visine note     |" << endl
								<< "|4. Dodavanje ili uklanjanje povisilice |" << endl;
							cin >> option3;
							cout << "|_______________________________________|" << endl;
							break;
						case 2:

							cout << endl << "________________________________________" << endl
								<< "|1. Prelazak na sledecu notu            |" << endl
								<< "|2. Povratak na prethodnu notu          |" << endl
								<< "|3. Menjanje oktave ili visine note     |" << endl
								<< "|4. Dodavanje ili uklanjanje povisilice |" << endl;
							cin >> option3;
							cout << "|_______________________________________|" << endl;
							break;
						case 3:
							cout << endl << "________________________________________" << endl
								<< "|1. Prelazak na sledecu notu            |" << endl
								<< "|2. Povratak na prethodnu notu          |" << endl
								<< "|3. Menjanje oktave ili visine note     |" << endl
								<< "|4. Dodavanje ili uklanjanje povisilice |" << endl;
							cin >> option3;
							cout << "|_______________________________________|" << endl;
							break;
						case 4:

							cout << endl << "________________________________________" << endl
								<< "|1. Prelazak na sledecu notu            |" << endl
								<< "|2. Povratak na prethodnu notu          |" << endl
								<< "|3. Menjanje oktave ili visine note     |" << endl
								<< "|4. Dodavanje ili uklanjanje povisilice |" << endl;
							cin >> option3;
							cout << "|_______________________________________|" << endl;
							break;
						}
					}
					cout << endl << "_______________________________________" << endl
						<< "|1. Prelazak na sledeci takt           |" << endl
						<< "|2. Povratak na prethodni takt         |" << endl
						<< "|3. Iteriranje kroz note               |" << endl;
					cin >> option2;
					cout << "|______________________________________|" << endl;
				}
				break;
				}
			}
		}
			if (option == 3) {
				cout << "Unesite novu duzinu trajanja takta";
				int bb, ii;
				cin >> bb;
				getchar();
				cin >> ii;
				getchar();
				while (ii != 4 && ii != 8) {
					cout << "Nedozvoljen imenilac,pokusajte ponovo sa duzinom taktova ";
					cin >> bb;
					getchar();
					cin >> ii;
				}
				Duration change(ii, bb);
				c.changeDuration(change);
				Composition nova(change);
				nova.setComposition(map_csv, putanjaKompozicije);
				c = nova;
			}
			if (option == 4){
				cout << "Unesi za koliko oktava menjamo kompoziciju ";
				int o;
				cin >> o;
				getchar();
				c.changeOctave(o);
			}
			if (option == 0) {
				break;
			}
	}

	cout << "Da li zelite da eksportujete kompoziciju? (1-DA ,0-NE) ";
	int eksport;
	cin >> eksport;
	if (eksport == 1) {
		cout << "Unesite vrstu eksportovanja (1-MXML , 2-MIDI , 3-BMP) ";
		int form;
		cin >> form;
		if (form == 1){
			MXMLFormatter xml(c);
			xml.makeXML();
		}
		if (form == 2) {
			MIDIFromatter midi(c, map_csv);
		}
		if (form == 3);
	}
	else {
		cout << "Dovidjenja! :)";
	}	
	system("pause");
}
