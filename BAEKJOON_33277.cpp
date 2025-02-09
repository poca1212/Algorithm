#include <iostream>
#include <cmath>
using namespace std;

int main()
{
	float num, num1 = 0, ans = 0, a = 0, b = 0, d = 0;
	cin >> num >> num1;
	ans = num1 / num * 100;

	ans = 14.4 * ans;

	a= int(ans) / 60 ;
	b = int(ans) % 60;


	if (a < 10 && b < 10) {
		cout << "0" << a << ":" << "0" << b;
	}
	else if (a >= 10 && b >= 10) {
		cout << a << ":" << b;
	}
	else if (a >= 10 && b < 10) {
		cout << a <<":" << "0" << b;
	}
	else if (a < 10 && b >= 10) {
		cout << "0" << a << ":" << b;
	}
	return 0;

}