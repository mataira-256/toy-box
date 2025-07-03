#include <bits/stdc++.h>
using namespace std;
#define rep(i, n) for(int i = 0; i < (int)(n); i++)
#define all(v) v.begin(), v.end()

const int TEST_COUNT = 100000;
const int LENGTH_MIN = 3;
const int LENGTH_MAX = 3;

int main() {

    random_device rd;
    mt19937 gen(rd());

    for(int length = LENGTH_MIN; length <= LENGTH_MAX; length++){

        uniform_int_distribution<> dist(0, pow(10, length)-1);

        vector<int> count(pow(10, length));

        rep(i, TEST_COUNT){
            count.at(dist(gen))++;
        }

        rep(i, pow(10, length)){
            printf("%8d %5d\n", i, count.at(i));
        }

    }

}
