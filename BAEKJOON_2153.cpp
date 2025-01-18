#include <iostream>
#include <cmath>
#include <string>
using namespace std;


int main() {
	char a[20];
	int b = 0;
	int y = 0;
	cin >> a;
	for (int i = 0; i < strlen(a); i++) {
		if (a[i] == 'a') {
			b += 1;
		}
		else if (a[i] == 'b') {
			b += 2;
		}
		else if (a[i] == 'c') {
			b += 3;
		}
		else if (a[i] == 'd') {
			b += 4;
		}
		else if (a[i] == 'e') {
			b += 5;
		}
		else if (a[i] == 'f') {
			b += 6;
		}
		else if (a[i] == 'g') {
			b += 7;
		}
		else if (a[i] == 'h') {
			b += 8;
		}
		else if (a[i] == 'i') {
			b += 9;
		}
		else if (a[i] == 'j') {
			b += 10;
		}
		else if (a[i] == 'k') {
			b += 11;
		}
		else if (a[i] == 'l') {
			b += 12;
		}
		else if (a[i] == 'm') {
			b += 13;
		}
		else if (a[i] == 'n') {
			b += 14;
		}
		else if (a[i] == 'o') {
			b += 15;
		}
		else if (a[i] == 'p') {
			b += 16;
		}
		else if (a[i] == 'q') {
			b += 17;
		}
		else if (a[i] == 'r') {
			b += 18;
		}
		else if (a[i] == 's') {
			b += 19;
		}
		else if (a[i] == 't') {
			b += 20;
		}
		else if (a[i] == 'u') {
			b += 21;
		}
		else if (a[i] == 'v') {
			b += 22;
		}
		else if (a[i] == 'w') {
			b += 23;
		}
		else if (a[i] == 'x') {
			b += 24;
		}
		else if (a[i] == 'y') {
			b += 25;
		}
		else if (a[i] == 'z') {
			b += 26;
		}
		else if (a[i] == 'A') {
			b += 27;
		}
		else if (a[i] == 'B') {
			b += 28;
		}
		else if (a[i] == 'C') {
			b += 29;
		}
		else if (a[i] == 'D') {
			b += 30;
		}
		else if (a[i] == 'E') {
			b += 31;
		}
		else if (a[i] == 'F') {
			b += 32;
		}
		else if (a[i] == 'G') {
			b += 33;
		}
		else if (a[i] == 'H') {
			b += 34;
		}
		else if (a[i] == 'I') {
			b += 35;
		}
		else if (a[i] == 'J') {
			b += 36;
		}
		else if (a[i] == 'K') {
			b += 37;
		}
		else if (a[i] == 'L') {
			b += 38;
		}
		else if (a[i] == 'M') {
			b += 39;
		}
		else if (a[i] == 'N') {
			b += 40;
		}
		else if (a[i] == 'O') {
			b += 41;
		}
		else if (a[i] == 'P') {
			b += 42;
		}
		else if (a[i] == 'Q') {
			b += 43;
		}
		else if (a[i] == 'R') {
			b += 44;
		}
		else if (a[i] == 'S') {
			b += 45;
		}
		else if (a[i] == 'T') {
			b += 46;
		}
		else if (a[i] == 'U') {
			b += 47;
		}
		else if (a[i] == 'V') {
			b += 48;
		}
		else if (a[i] == 'W') {
			b += 49;
		}
		else if (a[i] == 'X') {
			b += 50;
		}
		else if (a[i] == 'Y') {
			b += 51;
		}
		else if (a[i] == 'Z') {
			b += 52;
		}
	}
	for (int i = 1; i <= b; i++) {
		if (b % i == 0) {
			y += 1;
		}

	}
	if (y < 3) {
		cout << "It is a prime word.";
	}
	else if (y > 2) {
		cout << "It is not a prime word.";
	}
	return 0;
}