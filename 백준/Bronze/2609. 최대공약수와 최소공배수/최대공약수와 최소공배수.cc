#include <iostream>
#include <cmath>
#include <string>
#include <queue>
using namespace std;
int gcd(int a, int b) {
	if (b == 0) return a;
	return gcd(b, a % b);
}
int main()
{	
	int n, m, q, w;
	cin >> n >> m;
	
	int z = gcd(n, m);
	q = n / z;
	w = m / z;

	int x= z * q * w;
	
	cout << z << endl << x;
	return 0;

}


