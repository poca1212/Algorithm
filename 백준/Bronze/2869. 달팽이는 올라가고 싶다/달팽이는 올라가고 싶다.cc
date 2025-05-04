#include <iostream>
#include <cmath>
#include <string>
#include <queue>
using namespace std;
int main()
{
	double A, B, V, day=0, m=0, a, b;
	double c;
	cin >> A >> B >> V;
	a = V - A;
	b = A - B;

	c = a / b;
	c = ceil(c);
	c += 1;

	cout << int(c);
	return 0;

}