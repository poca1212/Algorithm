#include <iostream>
#include <cmath>
#include <string>
using namespace std;

int main()
{
	int days;

	int a;
	int b = 0;
	int ans = 0;

	cin >> a;

	for (int i = 1; i <= a; i++) {
		cin >> days;
		if (days == 0) {
			b -= 1;
		}
		else {
			b += 1;
		}
		ans += b;
	}
	cout << ans ;
	return 0;

}