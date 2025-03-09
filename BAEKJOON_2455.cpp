#include <iostream>
#include <cmath>
#include <string>
#include <algorithm>
using namespace std;

int main()
{	
	
	int big[5] = {};
	big[0] = 0;
	int a, b;

	for (int i = 1; i <= 4; i++) {
		cin >> a >> b;
		big[i] = big[i-1] + (a - b) * -1;
	}

	int c = 0;

	for (int i = 1; i <= 4; i++) {
		if (c < big[i]) {
			c = big[i];
		}
	}
	cout << c;
	return 0;

}

