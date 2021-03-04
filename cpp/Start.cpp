#include <iostream>
#include <map>
using namespace std;

enum Visina {C  , D , E , F , G , A , B};
void main() {
	static int	Oktava[5] = { 2 , 3 , 4 , 5 , 6};
	map<int, string> kompozicija;

	int o = Oktava[2];
	cout << o;

}