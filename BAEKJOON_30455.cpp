#include <iostream>
#include <cmath>
#include <string>
using namespace std;


int main() {
    int a;
    cin >> a;

    a -= 2;
    if (a % 2 == 0) {
        cout << "Duck";
    }
    else {
        cout << "Goose";
    }
    return 0;
}
