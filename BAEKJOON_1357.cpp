#include <iostream>
#include <cmath>
#include <string>
#include <algorithm>
using namespace std;

int main()
{
	string num, num1;

	int ans;


	cin >> num >> num1;

	reverse(num.begin(), num.end());
	reverse(num1.begin(), num1.end());

	ans = stoi(num) + stoi(num1);
	string a = to_string(ans);
	reverse(a.begin(), a.end());

	cout << stoi(a);


}