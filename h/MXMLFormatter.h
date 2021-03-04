#pragma once
#include "Formatter.h"
#include <fstream>
class MXMLFormatter :
	public Formatter
{
public:
	MXMLFormatter(Composition c) {
		com = c;
	};
	void makeXML() {
		ofstream outData;
		outData.open("C:\\bozo.musicxml");
		string s;
		string note = "<note>", nnote = "</note>";
		string duration = "<duration>", nduration = "</duration>";
		string pitch = "<pitch>", npitch = "</pitch>";
		string octave = "<octave>", noctave = "</octave>";
		string step = "<step>", nstep = "</step>";
		string alter = "<alter>", nalter = "</alter>";
		string chord = "<chord>", nchord = "</chord>";
		string rest = "<rest>", nrest = "</rest>";

		outData << "<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"no\"?>" << endl;
		outData << "<!DOCTYPE score-partwise PUBLIC" << endl;
		outData << "\"-//Recordare//DTD MusicXML 3.1 Partwise//EN\"" << endl;
		outData << "\"http://www.musicxml.org/dtds/partwise.dtd\">" << endl;
		outData << "<score-partwise version=\"3.1\">" << endl;
		outData << "<part-list>" << endl;
		outData << "<score-part id=\"Right\"></score-part>" << endl;
		outData << "<score-part id=\"Left\"></score-part>" << endl;
		outData << "</part-list>" << endl;
		Part r = com.getRight();
		Part l = com.getLeft();

		//Priprema za desnu
		outData << "<part id=\"Right\">" << endl;
		outData << "<measure>" << endl;
		outData << "<attributes>" << endl;
		outData << "<divisions>2</divisions>" << endl;
		Duration d = l.getMainDuration();
		int b = d.dohvBrojilac();
		Duration dd = r.getMainDuration();
		int i = dd.dohvImenilac();
		outData << "<time>" << endl;;
		outData << "<beats>" << b << "</beats>" << endl;
		outData << "<beat-type>" << i << "</beat-type>" << endl;
		outData << "</time>" << endl;
		outData << "<clef>" << endl;
		outData << "<sign>G</sign>" << endl;
		outData << "<line>2</line>" << endl;
		outData << "</clef>" << endl;
		outData << "</attributes>" << endl << endl;

		//Desna
		int prvi = 0;
		int half = 0;
		for (auto i : r.getList()) {
			if (prvi != 0) outData << "<measure>" << endl;
			for (auto j : i.getList()) {
				prvi = 1;
				string v = j.getVisina();
				int o = j.getOktava();
				Duration du = j.getDuration();
				int durat = du.dohvImenilac();
				int h;
				if (durat == 4) h = 2;
				else h = 1;
				if (o == 0) {
					outData << note << endl;
					outData << "<rest/>" << endl;
					outData << duration << h << nduration << endl;
					outData << nnote << endl;
				}
				else {
					outData << note << endl;
					if (j.getTogether()) {
						if (!j.getFirst()) outData << "<chord/>";
					}
					outData << pitch << endl;
					outData << step << v << nstep << endl;
					outData << octave << o << noctave << endl;
					if (j.haveIncrease()) {
						outData << "<alter>1</alter>";
					}
					outData << npitch << endl;
					outData << duration << h << nduration << endl;
					if (half == 1) {
						outData << "<tie type=\"end\"/>";
						half = 0;
					}
					else {
					if (j.getHalf()) {
						half = 1;
						outData << "<tie type=\"start\"/>";
					}
					}
					outData << nnote << endl;
				}
			}
			outData << "</measure>" << endl;
		}

		outData << "</part>" << endl << endl;
		//Priprema za levu
		outData << "<part id=\"Left\">" << endl;
		outData << "<measure>" << endl;
		outData << "<attributes>" << endl;
		outData << "<divisions>2" << "</divisions>" << endl;
		outData << "<time>" << endl;;
		outData << "<beats>" << b << "</beats>" << endl;
		outData << "<beat-type>" << i << "</beat-type>" << endl;
		outData << "</time>" << endl;
		outData << "<clef>" << endl;
		outData << "<sign>F</sign>" << endl;
		outData << "<line>4</line>" << endl;
		outData << "</clef>" << endl;
		outData << "</attributes>" << endl << endl;
		// Leva
		prvi = 0;
		half = 0;
		for (auto i : l.getList()) {
			if (prvi != 0) outData << "<measure>" << endl;
			for (auto j : i.getList()) {
				prvi = 1;
				string v = j.getVisina();
				int o = j.getOktava();
				Duration du = j.getDuration();
				int durat = du.dohvImenilac();
				int h;
				if (durat == 4) h = 2;
				else h = 1;
				if (o == 0) {
					outData << note << endl;
					outData << "<rest/>" << endl;
					outData << duration << h << nduration << endl;
					outData << nnote << endl;
				}
				else {
					outData << note << endl;
					outData << pitch << endl;
					outData << step << v << nstep << endl;
					outData << octave << o << noctave << endl;
					if (j.haveIncrease()) {
						outData << "<alter>1</alter>";
					}
					outData << npitch << endl;
					outData << duration << h << nduration << endl;
					if (half == 1) {
						half = 0;
						outData << "<tie type=\"end\"/>";
					}
					else {
						if (j.getHalf()) {
							half = 1;
							outData << "<tie type=\"start\"/>";
						}
					}
					outData << nnote << endl;
				}
			}
			outData << "</measure>" << endl;
	
		}
		outData << "</part>" << endl;
		outData << "</score-partwise>";
		outData.close();
	}
	~MXMLFormatter() {}
	
};

