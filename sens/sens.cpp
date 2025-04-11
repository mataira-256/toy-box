#include <bits/stdc++.h>
using namespace std;
#define rep(i, n) for(int i = 0; i < (int)(n); i++)
#define all(v) v.begin(), v.end()

const int mult_num = 6;
const int target_num = 100000000;

const int init_sens = 300;

const double range = 2.5;

// 評価関数
int evaluation(int diff){
    return diff <= init_sens * 0.03 ? diff : diff * diff;
}

// ターゲット配列の作成
vector<int> make_t_sens(){
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

        if(i % 1000000 == 0) printf("make_t_sens: %4.1f%%\n", i*100.0/target_num); // 動作確認用
    }

    return t_senses;
}


int main() {
    const vector<double> mult_base = {1.50000, 1.33333, 1.25000, 1.20000, 1.12500, 1.11111, 1.06250, 1.04000, 1.03704, 1.03125, 1.01563, 1.01235, 1.00800, 1.00781, 1.00412};

    vector<int> t_senses = make_t_sens();

    // 感度の全パターンを試す
    int64_t score_min = pow(2, 63)-1;
    vector<double> best_mult;
    bool OF;
    rep(m, pow(mult_base.size(), mult_num)){
        OF = false;
        vector<double> mult(mult_num);

        // multに今回の感度パターンを入れる
        int tmp_m = m;
        rep(i, mult_num){
            mult.at(i) = mult_base.at(tmp_m % mult_base.size());
            tmp_m /= mult_base.size();
        }

        // 0~1999に対して試す
        int64_t score = 0;
        rep(i, t_senses.size()){
            if(!t_senses.at(i)) continue;
            // 毎回正しい方を選んだ場合に、どの程度ズレるか調べる
            int sens = init_sens;
            rep(j, mult_num){
                if(sens < i) sens = sens * mult.at(j) + 0.5;
                else sens = sens / mult.at(j) + 0.5;
            }

            // 評価
            score += evaluation(abs(i - sens)) * t_senses.at(i); // その感度の数かける
            if(score < 0){  // OFしてる || これに引っかからない だけだった場合はもう知らん
                OF = true;
                break;
            }
        }

        // オバフロしてたら飛ばす
        if(OF) continue; 

        // 一番良かったやつを保存
        if(score < score_min){
            score_min = score;
            best_mult = mult;
        }

        if(m%10000==0) printf("main: %5.2f%%\n", m*100.0/pow(mult_base.size(), mult_num)); // 動作確認用
    }

    // 結果表示
    cout << endl << "-------" << endl;
    cout << "score: " << score_min <<endl;
    rep(i, mult_num) printf("%7.5f,\n", best_mult.at(i));
}