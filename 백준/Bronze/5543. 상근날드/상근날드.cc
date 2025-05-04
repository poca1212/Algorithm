#include <iostream>
#include <cmath>
#include <string>
#include <queue>
using namespace std;
int main()
{
	int b[3], n, m, k;
	cin >> b[0] >> b[1] >> b[2] >> n >> m;
	k = b[0];
	for (int i = 1; i <= 2; i++) {
		if (k > b[i]) {
			k = b[i];
		}
	}
	
	if (n >= m) {
		cout << m + k - 50;
	}
	else {
		cout << n + k - 50;
	}
	return 0;

}