#include <iostream>
#include <cmath>
#include <string>
#include <queue>
#include <vector>
#include <algorithm>
using namespace std;


int main()
{	
	int a, b, c, d;
	int way[2];
	int s;
	cin >> a >> b >> c >> d;

	way[0] = a + d;
	way[1] = c + b;
	
	if (way[0] < way[1]) {
		s = way[0];
	}
	else {
		s = way[1];
	}
	cout << s;
	return 0;


}

