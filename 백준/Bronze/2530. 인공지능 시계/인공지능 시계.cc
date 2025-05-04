#include <iostream>
#include <cmath>
#include <string>
#include <queue>
using namespace std;
int main()
{
	int A, B, C, D, a, b, c;
	cin >> A >> B >> C >> D;

	C += D;
	a = C / 60;
	C = C % 60;

	B += a;
	b = B / 60;
	B = B % 60;

	A += b;

	A = A % 24;

	cout << A << " " << B << " " << C;
	return 0;

}

