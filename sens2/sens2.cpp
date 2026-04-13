#include <bits/stdc++.h>
using namespace std;
#define rep(i, n) for(int i = 0; i < (int)(n); i++)
#define all(v) v.begin(), v.end()

/*
母集団から、m個の標本を取り出す際に
「j個目の要素は、j-1個目までの標本における平均から、標準偏差いくつ分離れているか」と
「j個目までの標本において、平均と標準偏差は、母集団とどのくらい違うか」を、n回試行し、
j毎の、それらの平均と標準偏差を求める
*/

const int NUM_TRIAL = 3000000;   // 上の説明における n
const int NUM_SUB_TRIAL = 32;   // 上の説明における m

// 母集団の定数
const double MEAN = 0.0;    // 平均
const double SIGMA = 1.0;   // 標準偏差


/* 渡された配列の平均を求める */
double calc_ave(vector<double>& a){
    double sum = 0.0;
    rep(i, a.size()) sum += a.at(i);
    return sum / a.size();
}


/*
渡された配列の標準偏差を求める
母集団ではなく標本に対して計算するので、分散を求める際の分母は -1 している
また、標準偏差の計算には平均の数値も必要だが、この関数内で計算すると計算量がかなり増えるので、引数としてその配列の平均も与えるようにしている
*/
double calc_std(vector<double>& a, double ave){
    double dev = 0.0;
    rep(i, a.size()) dev += pow(a.at(i) - ave, 2);
    dev /= a.size() - 1; // 標本分散だから -1
    return sqrt(dev);
}


/*
渡された配列の i毎の平均と標準偏差を表示する
元の配列が n*mの形で、このままだと上二つの関数を使えないので、 m*nに変形してから計算する
*/
void show_ave_std(vector<vector<double>>& a){
    // 行列入れ替えを作る
    vector<vector<double>> a_t(NUM_SUB_TRIAL, vector<double>(NUM_TRIAL));
    rep(i, NUM_SUB_TRIAL) rep(j, NUM_TRIAL) a_t.at(i).at(j) = a.at(j).at(i);

    // 平均の変数化
    vector<double> ave(NUM_SUB_TRIAL);
    rep(i, NUM_SUB_TRIAL) ave.at(i) = calc_ave(a_t.at(i));

    // 標準偏差の変数化
    vector<double> std(NUM_SUB_TRIAL);
    rep(i, NUM_SUB_TRIAL) std.at(i) = calc_std(a_t.at(i), ave.at(i));

    cout << "index ";
    rep(i, NUM_SUB_TRIAL) cout << i+1 << " ";
    cout << endl << "ave ";
    rep(i, NUM_SUB_TRIAL) printf("%7.4f ", ave.at(i));
    cout << endl << "std ";
    rep(i, NUM_SUB_TRIAL) printf("%7.4f ", std.at(i));
}

int main() {
    cout << "sens2" << endl;
    // 正規分布から値を得るための準備
    // これ以降 dist(engine) と書くことで、平均をMEAN, 標準偏差をSIGMAとした正規分布から値を得られる
    random_device seed_gen;
    default_random_engine engine(seed_gen());
    normal_distribution<> dist(MEAN, SIGMA);

    /* 試行 */
    // 以下の3つの2次元配列(行列)はn*mであり、 0 <= i < n, 0 <= j < m とした際に、以下のようなデータを保存する
    // diff ... i回目の試行の、j個目の要素は、j-1個目までの標本における平均から、標準偏差いくつ分離れているか
    // ave ... i回目の試行におけるjまでの標本の平均
    // std ... i回目の試行におけるjまでの標本の標準偏差
    vector<vector<double>> diff(NUM_TRIAL, vector<double>(NUM_SUB_TRIAL));
    vector<vector<double>> ave(NUM_TRIAL, vector<double>(NUM_SUB_TRIAL));
    vector<vector<double>> std(NUM_TRIAL, vector<double>(NUM_SUB_TRIAL));

    // 上の3つの配列に、実際にデータを持たせていく
    rep(i, NUM_TRIAL){
        vector<double> num = {dist(engine), dist(engine)};  // 平均や標準偏差を計算するなら、最初から2つ値欲しい
        ave.at(i).at(1) = calc_ave(num);
        std.at(i).at(1) = calc_std(num, ave.at(i).at(1));

        for(int j = 2; j < NUM_SUB_TRIAL; j++){ // 0と1には、すでに値を入れてるから飛ばす
            double rand = dist(engine);

            diff.at(i).at(j) = (rand - ave.at(i).at(j-1)) / std.at(i).at(j-1);

            num.push_back(rand);
            ave.at(i).at(j) = calc_ave(num);
            std.at(i).at(j) = calc_std(num, ave.at(i).at(j));
        }


        if(i % (NUM_TRIAL / 100) == 0) printf("%3d\n", i * 100 / NUM_TRIAL);    // デバッグ
    }


    /* 表示 */
    cout << endl << "j個目の要素は、j-1個目までの標本における平均から、標準偏差いくつ分離れているか" << endl;
    show_ave_std(diff);

    cout << endl << endl << "j個目までの標本において、平均は、母集団とどのくらい違うか" << endl;
    show_ave_std(ave);

    cout << endl << endl << "j個目までの標本において、標準偏差は、母集団とどのくらい違うか" << endl;
    show_ave_std(std);
}