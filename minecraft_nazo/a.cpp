#include <bits/stdc++.h>
using namespace std;

int main() {
    vector<int> d = {0,1,2,3,4,5,6,7,8,9}; // 0〜9の10個の数字
    int count = 0;

    do {
        int tetu = d[0];
        int eme = d[1];
        int rapisu = d[2];
        int daiya = d[3];
        int me = d[4];
        int amezisuto = d[5];
        int neza = d[6];
        int ennda = d[7];
        int seki = d[8];
        int nezasuta = d[9];

        // 3つの条件を同時に満たすかチェック
        if ((tetu * 10 + eme) * rapisu == daiya * 10 + eme &&
            me * (amezisuto * 10 + neza) == daiya * 10 + ennda &&
            seki * (tetu * 10 + nezasuta) == seki * 10 + nezasuta) {

            cout << "tetu: " << tetu << endl;
            cout << "eme: " << eme << endl;
            cout << "rapisu: " << rapisu << endl;
            cout << "daiya: " << daiya << endl;
            cout << "me: " << me << endl;
            cout << "amezisuto: " << amezisuto << endl;
            cout << "neza: " << neza << endl;
            cout << "ennda: " << ennda << endl;
            cout << "seki: " << seki << endl;
            cout << "nezasuta: " << nezasuta << endl;
            cout << endl;
            count++;
        }

    } while (next_permutation(d.begin(), d.end()));

    cout << "count = " << count << endl;
}
