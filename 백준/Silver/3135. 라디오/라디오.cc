#include <iostream>
#include <cmath>
#include <string>
using namespace std;

int main()
{
	int A, B, n, N[6] = {}, a,b;

	cin >> A >> B;
	cin >> n;
	for (int i = 0; i < n; i++) {
		cin >> N[i];
	}
	a = A - B;
	if (a < 0) {
		a = a * -1;
	}

	for (int i = 0; i < n; i++) {
		if (N[i] - B < 0) {
			b = (N[i] - B ) * -1  +1;
		}
		else {
			b = N[i] - B + 1;
		}
		if (a > b) {
			a = b;
		}
	}
	cout << a;


}