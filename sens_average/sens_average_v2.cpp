#include <bits/stdc++.h>
using namespace std;
#define rep(i, n) for(int i = 0; i < (int)(n); i++)
#define all(v) v.begin(), v.end()

const int DATA_SIZE = 25;

const double TUKEY_K = 1.5;
const double SIGMA_K = 2.5;

double calc_ave(vector<double>& a){
    double sum = 0;

    rep(i, a.size()) sum += a.at(i);

    return sum / a.size();
}

double calc_std(vector<double>& a, double ave){
    double sum = 0;

    rep(i, a.size()) {
        double dev = a.at(i) - ave;
        sum += dev * dev;
    }

    return sqrt(sum / a.size());
}

double calc_median(vector<double> & a, int left, int right){
    int n = right - left;
    int mid = left + n / 2;

    if(n % 2 == 0){
        return (a.at(mid-1) + a.at(mid)) / 2;
    }else{
        return a.at(mid);
    }
}

double calc_Q1(vector<double> a) {
    sort(a.begin(), a.end());
    
    return calc_median(a, 0, a.size() / 2);
}

double calc_Q3(vector<double> a) {
    sort(a.begin(), a.end());
    int n = a.size();

    if(n % 2 == 0){
        return calc_median(a, n / 2, n);
    }else{
        return calc_median(a, n / 2 + 1, n);
    }
}

int main() {
    /* input */
    vector<double> values;
    string line;

    while (getline(cin, line)) {
        if (line.empty()) continue;

        stringstream ss(line);
        string a, b, c;

        // a b c の形式でない行は無視
        if (!(ss >> a >> b >> c)) continue;

        // b が "-" の場合は無視
        if (b == "-") continue;

        try {
            double num = stod(b);

            if (num > 0.0) {
                values.push_back(num);
            }
        } catch (...) {
            continue;
        }
    }

    /* solve */
    // 乗数として扱いたいので指数を取る
    vector<double> log_values(values.size());
    rep(i, values.size()) log_values.at(i) = log(values.at(i));

    // 参考にするデータを決める
    vector<double> selected_values;

    // 「外れ値を省いてもDATA_SIZEが確保できる数」を探す。
    // 外れ値判定は、tukey法のあとに標準偏差
    // 探索量的に全探索で大丈夫だろうけど、せっかくなら二分探索
    int left = DATA_SIZE, right = log_values.size();
    while(left <= right){
        int mid = (left + right) / 2;
        
        // tukey法で使う値を用意して行って
        vector<double> tukey_filtered_values;
        vector<double> search_array(log_values.begin(), log_values.begin() + mid);
        double Q1 = calc_Q1(search_array);
        double Q3 = calc_Q3(search_array);
        double IQR = Q3 - Q1;

        // tukey法で外れ値でない値の配列を作る
        rep(i, search_array.size()){
            if(Q1 - IQR * TUKEY_K <= search_array.at(i) && search_array.at(i) <= Q3 + IQR * TUKEY_K){
                tukey_filtered_values.push_back(search_array.at(i));
            }
        }

        // 標準偏差+-3で使う値を用意して行って
        vector<double> sigma_filtered_values;
        double ave = calc_ave(tukey_filtered_values);
        double std = calc_std(tukey_filtered_values, ave);

        // 標準偏差+-3で外れ値でない値の数を数えて
        rep(i, tukey_filtered_values.size()){
            if(ave - std * SIGMA_K <= tukey_filtered_values.at(i) && tukey_filtered_values.at(i) <= ave + std * SIGMA_K){
                sigma_filtered_values.push_back(tukey_filtered_values.at(i));
            }
        }

        // cout << "debug right: " << right << " mid: " << mid << " left: " << left << " size: " << sigma_filtered_values.size() << endl;
        // DATA_SIZE以上ならとか色々考える
        if(DATA_SIZE <= sigma_filtered_values.size()){
            selected_values = sigma_filtered_values;
            right = mid - 1;
        }else{
            left = mid + 1;
        }
    }

    // 必要個数ない場合
    if(selected_values.size() < DATA_SIZE){
        cout << "small data size" << endl;
        return 1;
    }

    // 表示
    double ave = calc_ave(selected_values);
    double std = calc_std(selected_values, ave);

    printf("Very Fast: %.1f\n", exp(ave - std * 2));
    printf("Fast:      %.1f\n", exp(ave - std * 1));
    printf("Normal:    %.1f\n", exp(ave));
    printf("Slow:      %.1f\n", exp(ave + std * 1));
    printf("Very Slow: %.1f", exp(ave + std * 2));
}
