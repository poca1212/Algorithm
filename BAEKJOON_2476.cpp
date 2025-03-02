#include <iostream>
#include <cmath>
#include <string>
#include <algorithm>
using namespace std;


int main()
{
	int p;
	int num[3][1000] = {};
	int num1[1000] = {};
	int big = 0;
	cin >> p;

	for (int i = 0; i < p; i++) {
		for (int j = 0; j < 3; j++) {
			cin >> num[j][i];
		}
	}
	for (int i = 0; i < p; i++) {
		if (num[0][i] == num[1][i] && num[1][i] == num[2][i] && num[0][i] == num[2][i]) {
			num1[i]=10000 + num[0][i] * 1000;
		}
		else if (num[0][i] != num[1][i] && num[1][i] != num[2][i] && num[0][i] != num[2][i]) {
			for (int j = 0; j < 3; j++) {
				if (big <= num[j][i]) {
					big = num[j][i];
				}
			}
			num1[i] = big * 100;
			big = 0;
		}
		else if (num[0][i] == num[1][i] && num[0][i] != num[3][i] && num[1][i] != num[3][i]) {
			num1[i] = 1000 + num[0][i] * 100;
		}

		else if (num[1][i] == num[2][i] && num[1][i] != num[0][i] && num[2][i] != num[0][i]) {
			num1[i] = 1000 + num[1][i] * 100;
		}

		else if (num[0][i] == num[2][i] && num[0][i] != num[1][i] && num[2][i] != num[1][i]) {
			num1[i] = 1000 + num[0][i] * 100;
		}

	}
	for (int i = 0; i < p; i++) {
		if (big <= num1[i]) {
			big = num1[i];
		}
	}
	cout << big;


	return 0;

}

