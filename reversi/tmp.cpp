#include <bits/stdc++.h>
using namespace std;
#define rep(i, n) for(int i = 0; i < (int)(n); i++)
#define all(v) v.begin(), v.end()

int main() {
    rep(i, 3){
        rep(j, 3){
            rep(k, 3){
                printf("{%d, %d, %d},\n", i-1, j-1, k-1);
            }
        }
    }
}