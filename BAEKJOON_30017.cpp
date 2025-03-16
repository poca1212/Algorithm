#include <iostream>
#include <cmath>
#include <string>
using namespace std;

int main()
{
	int A, B;
	int c;
	cin >> A >> B;
	c = A - B;

	if (A > B) {
		cout << B + B + 1;
	}
	else if (A < B) {
		cout << A + A -1;
	}
	
	else {
		cout << A + B - 1;
	}
}
