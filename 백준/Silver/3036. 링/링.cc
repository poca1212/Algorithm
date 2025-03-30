#include <iostream>
#include <cmath>
#include <string>
using namespace std;

int main()
{
	int N;
	int t[101];
	int s = 0;
	int G=1;
	cin >> N;

	for (int i = 0; i < N; i++) {
		cin >> t[i];
	}

	for (int i = 1; i < N; i++) {
		if (t[0] >= t[i]) {
			for (int j = 1; j <= t[i]; j++) {
				if (t[0] % j == 0 && t[i] % j == 0) {
					G = j;
				}
			}
		}
		else {
			for (int j = 1; j <= t[0]; j++) {
				if (t[0] % j == 0 && t[i] % j == 0) {
					G = j;
				}
			}
		}
		cout << t[0] / G << "/" << t[i] / G << endl;
	}
	return 0;

}