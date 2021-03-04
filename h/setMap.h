#pragma once
#include <iostream>
#include <cstdlib>
#include <fstream>
#include <string>
#include <set>
#include <map>
#include <regex>

using namespace std;

void setMap(map<pair <int, string>, string>& map_csv,string map) {
	ifstream shema(map.c_str());
	string s;
	regex reg("([^,]*),([^,]*),([0-9]*)");
	while (getline(shema, s)) {
		smatch result;
		if (regex_match(s, result, reg)) {
			string sign = result.str(1);
			string note = result.str(2);
			int broj = atoi(result.str(3).c_str());
			pair<int, string> p = make_pair(broj, note);
			map_csv.insert(make_pair(p, sign));
		}
	}
};