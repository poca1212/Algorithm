#include <iostream>
#include <cmath>
#include <string>
using namespace std;

int main()
{
    int a = 0, b = 0, c = 0, d = 0;
    int t[4] = {};
    char time[6][16] = {};

    for (int i = 0; i < 5; i++) {
        cin.getline(time[i], 16); // 한 줄씩 입력 받기
    }
    int j = 1;

    for (int i = 0; i < 4; i++) {
        if (time[1][j] == '.' && time[2][j] == '.' && time[3][j] == '.') {
            t[i] = 0;
        }
        else if (time[0][j - 1] == '.' && time[0][j] == '.' && time[1][j - 1] == '.' && time[1][j] == '.' && time[2][j - 1] == '.' && time[2][j] == '.' && time[3][j - 1] == '.' && time[3][j] == '.' && time[4][j - 1] == '.' && time[4][j] == '.') {
            t[i] = 1;
        }
        else if (time[1][j - 1] == '.' && time[1][1] == '.' && time[3][j] == '.' && time[3][j + 1] == '.') {
            t[i] = 2;
        }
        else if (time[1][j - 1] == '.' && time[1][j] == '.' && time[3][j - 1] == '.' && time[3][j] == '.') {
            t[i] = 3;
        }
        else if (time[0][j] == '.' && time[1][j] == '.' && time[3][j - 1] == '.' && time[3][1] == '.' && time[4][j - 1] == '.' && time[4][j] == '.') {
            t[i] = 4;
        }
        else if (time[1][j] == '.' && time[1][j + 1] == '.' && time[3][j - 1] == '.' && time[3][j] == '.') {
            t[i] = 5;
        }
        else if (time[1][j] == '.' && time[1][j + 1] == '.' && time[3][j]) {
            t[i] = 6;
        }
        else if (time[1][j] == '.' && time[1][j - 1] == '.' && time[2][j] == '.' && time[2][j - 1] == '.' && time[3][j] == '.' && time[3][j - 1] == '.' && time[4][j] == '.' && time[4][j - 1] == '.') {
            t[i] = 7;
        }
        else if (time[1][j] == '.' && time[3][j] == '.') {
            t[i] = 8;
        }
        else if (time[1][j] == '.' && time[3][j - 1] == '.' && time[3][j] == '.') {
            t[i] = 9;
        }
        j += 4;
    }
    
    cout << t[0] << t[1] << ":" << t[2] << t[3];

    return 0;

}
