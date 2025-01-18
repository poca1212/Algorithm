#include <iostream>
#include <cmath>
#include <string>
using namespace std;


int main() {
    char a[15][15];
    int b;
    for (int i = 0; i < 15; i++) {
        for (int j = 0; j < 15; j++) {
            cin >> a[i][j];
        }
    }
    
    for (int i = 0; i < 15; i++){
        for (int j = 0; j < 15; j++) {
            if (a[i][j] == 'w') {
                b = 0;
            }

            else if (a[i][j] == 'b') {
                b = 1;
            }

            else if (a[i][j] == 'g') {
                b = 2;
            }
        }
    }
    if (b == 0) {
        cout << "chunbae";
    }
    else if(b == 1) {
        cout << "nabi";
    }
    else if (b == 2) {
        cout << "yeongcheol";
    }
    return 0;
}
