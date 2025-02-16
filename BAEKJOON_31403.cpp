#include <iostream>
#include <cmath>
#include <string>
using namespace std;

int main()
{
	int A, B, C;

	cin >> A >> B >> C;

	cout << (A + B) - C << endl;
	string a = to_string(A);
	string b = to_string(B);
	string c = a + b;
	int d = stoi(c);
	
	cout <<d-C;
	return 0;

}