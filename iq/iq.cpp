#include <bits/stdc++.h>
using namespace std;
#define rep(i, n) for(int i = 0; i < (int)(n); i++)
#define all(v) v.begin(), v.end()

int main() {
    random_device seed_gen;
    default_random_engine engine(seed_gen());
    normal_distribution<> dist(100, 15);

    vector<int> iqs(200);
    rep(i, 100000000){
        int iq = dist(engine);
        if(iq >= 200) continue;
        iqs.at(iq)++;
    }

    rep(i, 200) cout << i << " " << iqs.at(i) << endl;
}