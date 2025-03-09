#include <iostream>
#include <cmath>
#include <string>
#include <algorithm>
using namespace std;

int hol(int m);

int summ(int n[]);

int small(int v[]);
int main()
{	
	int	num[7] = {};
	int hol1[7] = {};
	int ans=0;
	int check;
	int p=0;
	int re1, re2;

	for (int i = 0; i < 7; i++) {
		cin >> num[i];
	}
	for (int i = 0; i < 7; i++) {
		ans = hol(num[i]);
		if (ans == 1) {
			hol1[i] = num[i];

		}
	}
	for (int i = 0; i < 7; i++) {
		if (hol1[i] == 0) {
			check = 0;
		}
		else {
			check = 1;
			break;
		}
	}
	if (check == 1) {
		re1 = summ(hol1);

		re2 = small(hol1);
	}

	if (check == 0) {
		cout << "-1";
	}
	else {
		cout << re1 << endl;
		cout << re2;
	}
	return 0;
}
int hol(int m)
{
	if (m % 2 != 0) {
		return 1;
	}
	else {
		return 0;
	}
}
int summ(int n[])
{
	int sum = 0;
	for (int i = 0; i < 7; i++) {
		sum += n[i];
	}
	return sum;
}
int small(int v[])
{
	int c = 2000000000;
	for (int i = 0; i < 7; i++) {
		if (v[i] != 0) {
			if (c >= v[i]) {
				c = v[i];
			}
		}
	}
	return c;
}



