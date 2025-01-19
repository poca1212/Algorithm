#include <iostream>
#include <cmath>
#include <string.h>
using namespace std;
int main() {
	int num, len, p = 0, high = 0, n=0;
	int num1[1004] = { 0 };
	char body[1004]= { 0 };
	cin >> num >> len;

	for(int i=0; i < num; i++){ //num번 반복
		for (int i = 0; i < len; i++) { //len번 반복
			cin >> body[i];     //9번 받기

		}

		for (int i = 0; i < len; i++) {  //len번 반복
			if (body[i] == '1' && body[i+1]!='1') { //바디의 i가 1이고 바디의 i+1이 1이 아닐때
				p += 1;   //1 더하고
			}

		}
		num1[i] = p;  //num1의 i 를 p로 바꿔서 저장
		p = 0;  p; //초기화
		for (int i = 0; i < 1001; i++) { //body 초기화
			body[i] = 0;
		}
	}
	high = num1[0];  
	for (int i = 0; i < num; i++) {//num만큼 반복
		if (high < num1[i + 1]) { //가장 높은 숫자 구하기
			high = num1[i + 1];
		}
	}
	for (int i = 0; i < num; i++) {
		if (high == num1[i]) {// 가장 높은 숫자 몇개 이는지 더하기
			n += 1;
		}
	}
	cout << high << " " << n; // 출력
	
	return 0;
}
 