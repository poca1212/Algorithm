#include <iostream>
#include <cmath>
#include <string>
#include <queue>
using namespace std;
int main()
{
	int N, num=0;
	cin >> N;

	for (int i = 1; i <= 500; i++) {
		for (int j = 1; j <= 500; j++) {
			if (i*i == j*j + N) {
				num += 1;
			}
		}
	}
	cout << num;
	return 0;

}

