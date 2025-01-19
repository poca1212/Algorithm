#include <iostream>
#include <cmath>
#include <string.h>
using namespace std;
int main() {
	int T;
	int N, C;
	int a[104];
	int b = 0, c = 0;
	cin >> T;
	for (int i = 0; i < T; i++) {
		cin >> N >> C;
		if (N % C == 0) {
			b = 0;
		}
		else {
			b = 1;
		}
		N -= b;
		a[i] = N / C + b;
		b = 0;
		N = 0;
		C = 0;
	}
	for (int i = 0; i < T; i++) {
		cout << a[i] << endl;
	}


	return 0;
}
 