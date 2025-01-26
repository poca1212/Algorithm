#include  <iostream>
#include <cstring>
#include <string>
using namespace std;

int main()
{
	char qq;
	string b;
	int num = 0;

	for (int i = 0; i < 1000; i++) {
		cin >> qq;
		getline(cin, b);
		if (qq == '#') {
			break;
		}
		for (int j = 0; j < b.size(); j++) {
			if (b[j] == char(qq) || b[j] == char(qq-32) ) {
				num += 1;
			}
		}
		cout << qq << " " << num << endl;
		num = 0;
	}



	return 0;
}
