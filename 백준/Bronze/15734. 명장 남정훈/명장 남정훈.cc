#include <iostream>
#include <cmath>
#include <string>
using namespace std;

int main()
{
    int A, B, n, k = 0, l=0, an=0, cup;
    cin >> A >> B;
    cin >> n;

    if (A > B) {
        cup = B;
        B = A;
        A = cup;
    }

    if (A == B) {
        k += A + B;
        n = n - (n % 2);
        k += n;
    }

    else if (A < B) {
        if (A + n < B) {
            k = A + B + n;
            an = A + n;
            k = k - (B - an);
        }
        else if (A + n > B) {
            l = B - A;
            A += l;
            n -= l;
            n = n - (n % 2);
            k += A + B + n;
        }
        else if (A + n == B) {
            k = A + B + n;
        }
    }
 
    cout << k;
}