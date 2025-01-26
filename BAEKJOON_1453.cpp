#include  <iostream>
#include <cstring>
using namespace std;

int main()
{
	int a;
	int b = 0;
	int c[101] = { 0 };
	int num = 0;
	cin >> a;
	for (int i = 0; i < a; i++) {
		cin >> b;
		if (c[b - 1] == 1) {
			num += 1;
		}
		else {
			c[b - 1] = 1;
		}
	}

	cout << num;
	return 0;
}
