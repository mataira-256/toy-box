#include <bits/stdc++.h>
using namespace std;
#define rep(i, n) for(int i = 0; i < (int)(n); i++)
#define all(v) v.begin(), v.end()

const int target_num = 100000000;

const int init_sens = 300;

const double range = 2.5;

int main() {
    const double mean = 1; // 固定

    double sigma = (range - mean) / 3; // 3sigmaがrangeになるようにしたい
    // おまじない
    random_device seed_gen;
    default_random_engine engine(seed_gen());
    normal_distribution<> dist(mean, sigma);

    /*
    1.1倍の逆は0.9倍ではなく、1.1で割った数字にしたい
      生成された値が1より小さかった場合は捨てる
      大きかった場合には、その数字でかけると割るの2回行う
    これでいい感じ
    */
    int t_senses_range = init_sens * (mean + sigma * 4) + 1;
    vector<int> t_senses(t_senses_range);
    rep(i, target_num){
        double nd = dist(engine);
        if(nd < mean) continue;
        if(init_sens * nd > t_senses_range) continue;
        t_senses.at(init_sens * nd)++;
        t_senses.at(init_sens / nd)++;

        if(i % 1000000 == 0) printf("%4.1f%%\n", i*100.0/target_num);
    }

    rep(i, t_senses_range) cout << i << " " << t_senses.at(i) << endl;
}