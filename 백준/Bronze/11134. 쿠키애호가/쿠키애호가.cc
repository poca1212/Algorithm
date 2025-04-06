#include <iostream>
#include <cmath>
#include <string>
using namespace std;

int main()
{	
	int T = 0, N[102] = {}, C[102] = {}, d[102] = {};
	cin >> T;

	for (int i = 0; i < T; i++) {
		cin >> N[i] >> C[i];
		d[i] += N[i] / C[i];
		if (N[i] % C[i] != 0) {
			d[i] += 1;
		}
	}

	for (int i = 0; i < T; i++) {
		std::cout << d[i] << endl;
	}

	return 0;

}