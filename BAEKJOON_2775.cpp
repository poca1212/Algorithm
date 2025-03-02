#include <iostream>
#include <cmath>
#include <string>
#include <algorithm>
using namespace std;


int main()
{
	int p[15][15] = {};
	int T, k, n=0;
	cin >> T;

	for (int j = 1; j <= 14; j++) {
		p[0][j] = j;
	}
	for (int i = 1; i <= 14; i++) {
		for (int j = 1; j <= 14; j++) {
			for(int k=1 ; k<=j;k++){
				p[i][j] += p[i - 1][k];
			}
			
		}
	}
	

	for (int i = 0; i < T; i++) {
		cin >> k >> n;
		cout << p[k][n] << endl;
	}
	
	
	
	return 0;

}

