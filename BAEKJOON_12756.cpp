#include <iostream>
#include <cmath>
#include <string>
using namespace std;

int main()
{
	int f, F, h, H;

	cin >> f >> h;
	cin >> F >> H;

	while (h > 0 && H > 0) {
		h -= F;
		H -= f;
	}

	
	if (h > 0) {
		cout << "PLAYER A";
	}
	else if (H > 0) {
		cout << "PLAYER B";
	}
	else {
		cout << "DRAW";
	}
}
