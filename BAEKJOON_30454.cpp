#include <iostream>
#include <cmath>
#include <string.h>
using namespace std;
int main() {
	int num, len, p = 0, high = 0, n=0;
	int num1[1004] = { 0 };
	char body[1004]= { 0 };
	cin >> num >> len;

	for(int i=0; i < num; i++){ //num�� �ݺ�
		for (int i = 0; i < len; i++) { //len�� �ݺ�
			cin >> body[i];     //9�� �ޱ�

		}

		for (int i = 0; i < len; i++) {  //len�� �ݺ�
			if (body[i] == '1' && body[i+1]!='1') { //�ٵ��� i�� 1�̰� �ٵ��� i+1�� 1�� �ƴҶ�
				p += 1;   //1 ���ϰ�
			}

		}
		num1[i] = p;  //num1�� i �� p�� �ٲ㼭 ����
		p = 0;  p; //�ʱ�ȭ
		for (int i = 0; i < 1001; i++) { //body �ʱ�ȭ
			body[i] = 0;
		}
	}
	high = num1[0];  
	for (int i = 0; i < num; i++) {//num��ŭ �ݺ�
		if (high < num1[i + 1]) { //���� ���� ���� ���ϱ�
			high = num1[i + 1];
		}
	}
	for (int i = 0; i < num; i++) {
		if (high == num1[i]) {// ���� ���� ���� � �̴��� ���ϱ�
			n += 1;
		}
	}
	cout << high << " " << n; // ���
	
	return 0;
}
 