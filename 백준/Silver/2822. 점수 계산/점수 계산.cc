#include <iostream>
#include <cmath>
#include <string>
using namespace std;

int main()
{
	int arr[8];
	int size = 8;
	int temp = 0;
	int sum = 0;
	int Arr[8];

	for (int i = 0; i < 8; i++) {
		cin >> arr[i];
	}
	for (int i = 0; i < 8; i++) {
		Arr[i] = arr[i];
	}
	
	for (int i = 0; i < size - 1; i++) {
		for (int j = 0; j < size - i - 1; j++) {
			if (arr[j] < arr[j + 1]) {
				temp = arr[j];
				arr[j] = arr[j + 1];
				arr[j + 1] = temp;
			}
		}
	}

	for (int i = 0; i < 5; i++) {
		sum += arr[i];
	}
	cout << sum<< endl;

	for (int i = 0; i < 8; i++) {

		if (Arr[i] == arr[0] || Arr[i] == arr[1] || Arr[i] == arr[2] || Arr[i] == arr[3] || Arr[i] == arr[4]) {
			cout << i+1 << " ";
		}
	}
	return 0;

}
