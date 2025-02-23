#include <iostream>
#include <cmath>
#include <string>
using namespace std;

int main()
{
	
	int N, M, a=0,ans=0;
	int k[1000];
	cin >> N >> M;

	for (int i = 0; i < N; i++) {
		cin >> k[i];
	}

	for (int i = 1; i <= N; i++) {
		if (a + k[N - i] < M) {
			a += k[N - i];
		}
		else if (a + k[N - i] >= M) {
			ans = i-1;
		}
		else {
			ans = -1;
		}
	}
	cout << ans;
}