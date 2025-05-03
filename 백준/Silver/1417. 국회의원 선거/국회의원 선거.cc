#include <iostream>
#include <cmath>
#include <string>
#include <queue>
using namespace std;

int main()
{	
	int N;
	int d;
	cin >> N;
	cin >> d;

	priority_queue<int> pq;

	for (int i = 1; i < N; i++) {
		int g;
		cin >> g;
		pq.push(g);
	}

	int buy = 0;

	while (!pq.empty() && pq.top() >= d) {
		int maxg = pq.top();
		pq.pop();

		maxg -= 1;
		d += 1;
		buy += 1;

		pq.push(maxg);
	}
	cout << buy;
	return 0;

}
