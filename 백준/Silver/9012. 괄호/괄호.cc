#include <iostream>
#include <cmath>
#include <string>
#include <queue>
#include <vector>
#include <algorithm>
using namespace std;


int main()
{	
	int num;
	char a[51] = {};
	int b=0, c = 0, n=0;
	cin >> num;
	for (int i = 0; i < num; i++) {
		cin >> a;
		n = 0;
		b = 0;
		for (int j = 0; a[j] != '\0'; j++) {
			if (a[j] == '(') {
				b += 1;
			
			}
			else if(a[j]==')'){
				b-= 1;
			}
			if (b < 0) {
				n = 1;
			}
		}

		if (n == 1 || b != 0) {
			cout << "NO"<< endl;
		}
		else {
			cout << "YES"<< endl;
		}

	}
	return 0;


}
