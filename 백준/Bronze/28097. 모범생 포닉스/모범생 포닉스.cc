#include <iostream>
#include <cmath>
#include <string>
#include <queue>
using namespace std;
int main()
{
	int N[122], st = 0, day, time;
	double break1 = 0, num;
	cin >> num;
	for (int i = 0; i < num; i++) {
		cin >> N[i];
	}
	break1 = num - 1;

	for (int i = 0; i < num; i++) {
		st += N[i];
	}
	st += 8 * break1;

	day = st / 24;
	time = st % 24;
	cout << day << " " << time;
	return 0;

}
