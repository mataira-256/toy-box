#include <bits/stdc++.h>
using namespace std;
#define rep(i, n) for(int i = 0; i < (int)(n); i++)
#define all(v) v.begin(), v.end()

int main() {

    vector<vector<int64_t>> num(10, vector<int64_t>(10));

    for(int i = 1; i <= 10; i++){
        for(int j = 1; j <= 10; j++){
            num.at(i-1).at(j-1) = pow(i, j);
        }
    }

    rep(i, 10){
        rep(j, 10) cout << num.at(i).at(j) << " ";
        cout << endl;
    }

}