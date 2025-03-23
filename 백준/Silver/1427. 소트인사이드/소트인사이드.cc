#define _CRT_SECURE_NO_WARNINGS
#define NUM 5
#include <stdio.h>
#include <string.h>
#include <ctype.h>

int main(void){
	char test[10];
	int i, j, s, t, tmp;
	scanf("%s", &test);
	
	for (s = 0; s < strlen(test)-1; s++) {
		for (t = s + 1; t < strlen(test); t++) {
			if (test[t] > test[s]) {
				tmp = test[t];
				test[t] = test[s];
				test[s] = tmp;
			}
		}
	}

	for (int i = 0; i < strlen(test); i++) {
		printf("%c", test[i]);
	}
	return 0;
}