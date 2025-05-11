#include <iostream>
#include <cmath>
#include <string>
#include <queue>
#include <vector>
#include <algorithm>
#include <fstream>
#include <iomanip>
using namespace std;

int main()
{	
	int n, m, a, b, c, d, e;
	int p;



	cin >> n >> m;
	cin >> a >> b >> c >> d >> e;
	p = n * m;

	a = a - p;
	b = b - p;
	c = c - p;
	d = d - p;
	e = e - p;

	cout << a << " " << b << " " << c << " " << d << " " << e;

	return 0;


}
