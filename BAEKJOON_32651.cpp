#include <iostream>
#include <cmath>
#include <string>
using namespace std;

int main()
{
	long long int year;

	cin >> year;

	if (year % 2024 == 0 && year <= 100000) {
		cout << "Yes";

	}
	else {
		cout << "No";
	}
	return 0;

}