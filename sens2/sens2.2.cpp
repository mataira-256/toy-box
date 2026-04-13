#include <bits/stdc++.h>
using namespace std;
#define rep(i, n) for(int i = 0; i < (int)(n); i++)
#define all(v) v.begin(), v.end()

/*
母集団から、m個の標本を取り出す際に
「j個目の要素は、j-1個目までの標本における平均から、標準偏差いくつ分離れているか」をn回試行し、
それらの標準偏差を、j毎に求める
*/

const int NUM_TRIAL = 40000000;   // 上の説明における n
const int NUM_SUB_TRIAL = 5;   // 上の説明における m

// 母集団の定数
const double MEAN = 0.0;    // 平均
const double SIGMA = 1.0;   // 標準偏差


/*
渡された配列に対応する平均の配列を返す
i番目には、渡された配列の0~i番目までの平均が入る
*/
vector<double> calc_ave(vector<double>& a){
    int size = a.size();
    vector<double> ave(size);

    // 累積和
    vector<double> sum(size+1);
    rep(i, size) sum.at(i+1) = sum.at(i) + a.at(i);

    rep(i, size) ave.at(i) = sum.at(i+1) / (i+1);

    return ave;
}


/*
渡された配列に対応する標準偏差の配列を返す
i番目には、渡された配列の0~i番目までの標準偏差が入る
*/
vector<double> calc_std(vector<double>& a){
    int size = a.size();
    vector<double> std(size);

    // 普通のと2乗の累積和
    vector<double> sum(size+1), sum_pow(size+1);
    rep(i, size){
        sum.at(i+1) = sum.at(i) + a.at(i);
        sum_pow.at(i+1) = sum_pow.at(i) + pow(a.at(i), 2);
    }

    for(int i = 1; i < size; i++){  // 1つ目は飛ばす
        std.at(i) = (i+1) * sum_pow.at(i+1) - pow(sum.at(i+1), 2);
        std.at(i) = sqrt(std.at(i) / ((i+1) * i)); // データの数を表すnを用いるとn(n-1)になる式を、添え字のiでやるとこうなる
    }

    return std;
}


/*
渡された配列の j毎の標準偏差を表示する
*/
void show_ave_std(vector<vector<double>>& a){
    // calc_aveと、calc_stdで帰ってくる数字はここで使いづらい & OFが起こるので、関数呼び出しじゃなくて普通に計算する
    // 平均の変数化
    vector<double> ave(NUM_SUB_TRIAL);
    rep(i, NUM_SUB_TRIAL){
        rep(j, NUM_TRIAL) ave.at(i) += a.at(j).at(i);
        ave.at(i) /= NUM_TRIAL;
    }

    // 標準偏差の変数化
    vector<double> std(NUM_SUB_TRIAL);
    rep(i, NUM_SUB_TRIAL){
        rep(j, NUM_TRIAL) std.at(i) += pow(a.at(j).at(i) - ave.at(i), 2);   // 偏差の二乗の合計
        std.at(i) = sqrt(std.at(i) / (NUM_TRIAL -1)); // 分散求めてそのままルート取って標準偏差
    }


    cout << "index ";
    rep(i, NUM_SUB_TRIAL) cout << i+1 << " ";
    cout << endl << "std ";
    rep(i, NUM_SUB_TRIAL) printf("%7.4f ", std.at(i));
}

int main() {
    random_device seed_gen;
    default_random_engine engine(seed_gen());
    normal_distribution<> dist(MEAN, SIGMA);

    /* 試行 */
    // diff ... i回目の試行の、j個目の要素は、j-1個目までの標本における平均から、標準偏差いくつ分離れているか
    // ave ... i回目の試行におけるjまでの標本の平均
    // std ... i回目の試行におけるjまでの標本の標準偏差
    vector<vector<double>> diff(NUM_TRIAL, vector<double>(NUM_SUB_TRIAL));
    vector<vector<double>> ave(NUM_TRIAL, vector<double>(NUM_SUB_TRIAL));
    vector<vector<double>> std(NUM_TRIAL, vector<double>(NUM_SUB_TRIAL));

    // 上の3つの配列に、実際にデータを持たせていく
    rep(i, NUM_TRIAL){
        // 今回の標本
        vector<double> sample(NUM_SUB_TRIAL);
        rep(j, NUM_SUB_TRIAL) sample.at(j) = dist(engine);

        // 今回の平均と標準偏差
        ave.at(i) = calc_ave(sample);
        std.at(i) = calc_std(sample);

        // 今回の1つ前までの標本において、平均から標準偏差いくつ分離れているか
        for(int j = 2; j < NUM_SUB_TRIAL; j++){ // 1つ前までの標本をもとにするので、jが0と1の間は飛ばす
            diff.at(i).at(j) = (sample.at(j) - ave.at(i).at(j-1)) / std.at(i).at(j-1);
        }

        if(i % (NUM_TRIAL / 100) == 0) printf("%3d\n", i * 100 / NUM_TRIAL);    // デバッグ
    }


    /* 表示 */
    cout << endl << "j個目の要素は、j-1個目までの標本における平均から、標準偏差いくつ分離れているか" << endl;
    show_ave_std(diff);

}
