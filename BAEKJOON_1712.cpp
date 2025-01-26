#include  <iostream>
#include <cstring>
#include <string>
using namespace std;

int main()
{
	int in = 0;
	int ma = 0;
	int se = 0; 
	int a = 0;
	int num = 0;
	cin >> in >> ma >> se;
	a = se - ma;
	if(a<=0){
		cout << "-1";
	}
	else if (a != -1) {
		num = in / a;
		num += 1;
		cout << num;
	}

	return 0;
}

