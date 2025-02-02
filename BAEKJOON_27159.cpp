#include <iostream>
#include <string.h>

using namespace std;

int main(void)
{
	int N[40] = {};
	int num;
	int  sum = 0;
	int a = 0;
	int c=0;
	cin >> num;
	for (int i = 0; i < num; i++) {
		cin >> N[i];
	}

	for (int j = 0; j < num; j++) {
		if (N[j+1] == N[j]+1) {
			c += 1;
		}
		else if(N[j + 1] != N[j]+1) {
			sum += N[j] - c;
			c = 0;
		}
	}
	cout << sum;
}
