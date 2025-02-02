#include <iostream>
#include <string.h>

using namespace std;

int main(void)
{
	int num;
	string str[15] = {};
	int t[15] = {}; // 가상시간
	int a = 1; // 1은 시간 ++ 0은 시간 --
	int c[15] = {};  // YES or NO 구분
	int c1[15] = {}; // 그 당시 시간 저장
	int time = 0; // 실제시간
	cin >> num;

	for (int i = 0; i < num; i++) {
		cin >> str[i] >> t[i];
	}
	for (int i = 0; i < num; i++) {
		if (a == 1) {
			if (time == 12) {
				time = 1;
			}
			else {
				time += 1;
			}
		}
		else if (a == 0) {
			if (time == 1) {
				time = 12;
			}
			else {
				time -= 1;
			}
		}

	
		if (t[i] == time) {
			c[i] = 1;
		}
		else if (t[i] != time) {
			c[i] = 0;
		}



		if (str[i] == "HOURGLASS") {
			if (a == 0) {
				a = 1;
			}
			else {
				a = 0;
			}
		}

		if(str[i]=="HOURGLASS" && time == t[i]) {
			c[i] = 0;
			if(a == 0) {
				a = 1;
			}
			else {
				a = 0;
			}

		}
		
		c1[i] = time;
	}

	for (int i = 0; i < num; i++) {
		if (c[i] == 1) {
			cout << c1[i] << " " << "YES" << endl;
		}

		if (c[i] == 0) {
			cout << c1[i] << " " << "NO" << endl;
		}
	}




}
