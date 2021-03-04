#pragma once
#include <iostream>
using namespace std;

class Duration {
protected:
	int b, i;
public:

	Duration(int br, int im) : b(br) , i (im) {}
	Duration() {};

	int dohvBrojilac() {
		return b;
	}
	int dohvImenilac() {
		return i;
	}
	Duration sredi(const Duration &r) {
		return Duration();
	}
	friend Duration operator+(const Duration &r1, const Duration &r2) {
		if (r1.b == 0 && r1.i == 0) return Duration(r2.b, r2.i);
		if (r2.b == 0 && r2.i == 0) return Duration(r1.b, r1.i);
		return Duration(r1.b*r2.i + r2.b*r1.i, r1.i*r2.i);
	}
	friend Duration operator-(const Duration &r1, const Duration &r2) {
		   return Duration(r1.b*r2.i - r2.b*r1.i, r1.i*r2.i);
	}
	friend bool operator>(const Duration &r1, const Duration &r2) {
		   return r1.b*r2.i > r2.b*r1.i;
	}
	friend bool operator==(const Duration &r1, const Duration &r2) {
		return (r1.b*r2.i == r2.b*r1.i);
	}
	friend ostream& operator<<(ostream &it,const Duration &r) {
		   return it << r.b << "/" << r.i;
	}
};
