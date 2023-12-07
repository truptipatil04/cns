#include <bits/stdc++.h>
using namespace std;

int prime_checker(int p) {
    if (p < 1) {
        return -1;
    } else if (p > 1) {
        if (p == 2) {
            return 1;
        }
        for (int i = 2; i < p; i++) {
            if (p % i == 0) {
                return -1;
            }
        }
        return 1;
    }
}

int primitive_check(int g, int p, vector<int>& L) {
    // Checks if the entered number is a Primitive Root or not
    for (int i = 1; i < p; i++) {
        int x=pow(g,i);
        L.push_back( x % p);
    }
    for (int i = 1; i < p; i++) {
        if (count(L.begin(), L.end(), i) > 1) {
            L.clear();
            return -1;
        }
    }
    return 1;
}

int main() {
    vector<int> L;
    int P, q, x1, x2, y1, y2, k1, k2;

    while (true) {
        cout << "Enter P : ";
        cin >> P;
        if (prime_checker(P) == -1) {
            cout << "Number Is Not Prime, Please Enter Again!" << endl;
            continue;
        }
        break;
    }

    while (true) {
        cout << "Enter The Primitive Root Of " << P << " : ";
        cin >> q;
        if (primitive_check(q, P, L) == -1) {
            cout << "Number Is Not A Primitive Root Of " << P << ", Please Try Again!" << std::endl;
            continue;
        }
        break;
    }

    // Private Keys
    cout << "Enter The Private Key Of User 1 : ";
    cin >> x1;
    cout << "Enter The Private Key Of User 2 : ";
    cin >> x2;

    while (true) {
        if (x1 >= P || x2 >= P) {
            cout << "Private Key Of Both The Users Should Be Less Than " << P << "!" << std::endl;
            continue;
        }
        break;
    }

    // Calculate Public Keys
    y1 = static_cast<int>(pow(q, x1)) % P;
    y2 = static_cast<int>(pow(q, x2)) % P;

    // Generate Secret Keys
    k1 = static_cast<int>(pow(y2, x1)) % P;
    k2 = static_cast<int>(pow(y1, x2)) % P;

    cout << "\nSecret Key For User 1 Is " << k1 << endl;
    cout << "Secret Key For User 2 Is " << k2 << endl;

    if (k1 == k2) {
        cout << "Keys Have Been Exchanged Successfully" << endl;
    } else {
        cout << "Keys Have Not Been Exchanged Successfully" <<endl;
    }

    return 0;
}
