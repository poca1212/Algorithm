#include <iostream>
#include <cmath>
#include <string>
#include <queue>
using namespace std;

int main()
{	
	int N, num[50] = {};
	cin >> N;
	if (N % 2 == 0) {
		int a = N;
		int b = 1;
		cout << a << " ";
		cout << b << " ";
		for (int i = 0; i < N/2-1; i++) {
			a = a - 1;
			cout << a << " ";
			b = b + 1;
			cout << b << " ";
		}
	}
	else {
		int a = N;
		int b = 1;
		cout << a << " ";
		cout << b << " ";
		N - 1;
		for (int i = 0; i < N / 2-1; i++) {
			a = a - 1;
			cout << a << " ";
			b = b + 1;
			cout << b << " ";
		}
		cout << b + 1;

	}
	return 0;

}