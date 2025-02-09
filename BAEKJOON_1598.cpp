#include <iostream>
using namespace std;

int main()
{
	int num, num1;
	int a = 0, b = 0, c = 0, d = 0, ans = 0;;
	cin >> num >> num1;
	a = num / 4;
	b = num % 4;
	if (b == 0) {
		b = 4;
		a--;
	}
	c = num1 / 4;
	d = num1 % 4;
	if (d == 0) {
		d = 4;
		c--;
	}
	
	if (a > c) {
		ans += a - c;
	}
	else {
		ans += c - a;
	}

	if (b > d) {
		ans += b - d;
	}
	else {
		ans += d - b;
	}
	
	cout << ans;

	return 0;

}