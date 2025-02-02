#include <iostream>
#include <string.h>

using namespace std;

int main(void)
{
    int card[4] = {};
    int a, b, c = 0;
    string str;
    cin >> a;

    for (int i = 0; i < a; i++) {
        cin >> str >> b;

        if (str == "STRAWBERRY") {
            card[0] += b;
        }
        else if (str == "BANANA") {
            card[1] += b;
        }
        else if (str == "LIME") {
            card[2] += b;
        }
        else if (str == "PLUM") {
            card[3] += b;
        }
    }
    if (card[0] == 5 || card[1] == 5 || card[2] == 5 || card[3] == 5) {
        cout << "YES";
        c = 1;
    }
    else if (c == 0) {
        cout << "NO";
    }
}