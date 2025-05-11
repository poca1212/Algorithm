#include <iostream>
#include <cmath>
#include <string>
#include <queue>
#include <vector>
#include <algorithm>
#include <fstream>
#include <iomanip>
using namespace std;

int main()
{	
	char word[9] = { 'C', 'A', 'M', 'B', 'R', 'I', 'D', 'G', 'E' };
	char m[101] = { };
	char op[101] = { };
	int a = 0, b = 0;;
	cin >> m;

	for (int i = 0; m[i] != '\0'; i++) {
		a = 0;
		for (int j = 0; j < 9; j++) {
			if (m[i] == word[j]) {
				a = 1;
			}
		}
		if (a == 0) {
			op[b] = m[i];
			b += 1;
		}
	}
	for (int i = 0; op[i] != '\0'; i++) {
		cout << op[i];
	}
	return 0;


}
