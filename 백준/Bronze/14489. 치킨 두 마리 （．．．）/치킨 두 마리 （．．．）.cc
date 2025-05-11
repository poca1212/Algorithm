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
	int A, B, C;
	
	cin >> A >> B;
	cin >> C;

	C = C * 2;

	if (A + B >= C) {
		cout << A + B - C;
	}
	else {
		cout << A + B;
	}
	return 0;


}
