#include <iostream>
#include <cmath>
#include <string>
using namespace std;

int main()
{
	int A, B, K, X;
	int s, b, a, h=0;
	cin >> A >> B;
	cin >> K >> X;
	s = K - X;
	b = K + X;
	a = b - s + 1;

	for (int i = s; i <=b; i++) {
		if (i >= A && i <= B) {
			h += 1;
		}
	}


	if (h==0) {
		cout << "IMPOSSIBLE";
	}
	else {
		cout << h;
	}
}
