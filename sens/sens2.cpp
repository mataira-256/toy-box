#include <bits/stdc++.h>
using namespace std;
#define rep(i, n) for(int i = 0; i < (int)(n); i++)
#define all(v) v.begin(), v.end()

/*
「同じ正規分布から確率変数を取り続けた場合について、
nが、n-1までの平均から標準偏差何個分になるのか求める」
*/

const int NUM_TRIAL = 10000000;
const int NUM_SUB_TRIAL = 13;


double calc_ave(vector<double>& num){
    double sum = 0.0;
    rep(i, num.size()) sum += num.at(i);
    return sum / num.size();
}

double calc_std(vector<double>& num, double ave){
    double dev = 0.0;
    rep(i, num.size()) dev += pow(ave - num.at(i), 2);
    dev /= num.size();
    return sqrt(dev);
}

int main() {
    random_device seed_gen;
    default_random_engine engine(seed_gen());
    normal_distribution<> dist(0, 1);

    vector<vector<double>> diff(NUM_TRIAL, vector<double>(NUM_SUB_TRIAL));
    rep(i, NUM_TRIAL){
        vector<double> num = {dist(engine), dist(engine)};
        double ave = calc_ave(num);
        double std = calc_std(num, ave);

        rep(j, NUM_SUB_TRIAL - 2){
            double rand = dist(engine);

            diff.at(i).at(j + 2) = abs(rand - ave) / std;

            num.push_back(rand);
            ave = calc_ave(num);
            std = calc_std(num, ave);
        }
        // rep(j, NUM_SUB_TRIAL) printf("%6.3f ", num.at(j));
        // cout << endl << endl;
    }



    /* 表示 */
    // diffの行列入れ替え
    vector<vector<double>> diff_transposed(NUM_SUB_TRIAL, vector<double>(NUM_TRIAL));
    rep(i, NUM_SUB_TRIAL) rep(j, NUM_TRIAL) diff_transposed.at(i).at(j) = diff.at(j).at(i);

    // 平均の変数化
    vector<double> diff_ave(NUM_SUB_TRIAL);
    rep(i, NUM_SUB_TRIAL) diff_ave.at(i) = calc_ave(diff_transposed.at(i));

    // 表示
    rep(i, NUM_SUB_TRIAL) printf("%6.3f ", diff_ave.at(i));
    cout << endl;
    rep(i, NUM_SUB_TRIAL) printf("%6.3f ", calc_std(diff_transposed.at(i), diff_ave.at(i)));

}