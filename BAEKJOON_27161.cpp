#include <iostream>
#include <string.h>

using namespace std;

int main(void)
{
	int num;
	string str[15] = {};
	int t[15] = {}; // ����ð�
	int a = 1; // 1�� �ð� ++ 0�� �ð� --
	int c[15] = {};  // YES or NO ����
	int c1[15] = {}; // �� ��� �ð� ����
	int time = 0; // �����ð�
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
