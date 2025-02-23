#include <iostream>
#include <cmath>
#include <string>
using namespace std;

int main()
{

	int N, M, a = 0, ans = 0;
	int k[100000] = { 0 };
	cin >> N >> M;

	for (int i = 0; i < N; i++) {
		cin >> k[i];
	}


	for (int i = N-1; i >= 0; i--) {
		a += k[i];
		if (a < M) {
			
		}
		else if (a >= M) {
			ans = i+1;
			break;
		}
	}

	if (ans == 0) {
		ans = -1;
	}

	cout << ans;
}