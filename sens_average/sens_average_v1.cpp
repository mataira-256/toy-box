#include <bits/stdc++.h>
using namespace std;
#define rep(i, n) for(int i = 0; i < (int)(n); i++)
#define all(v) v.begin(), v.end()

const int DATA_SIZE = 25;

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
    vector<double> log_values(values.size());
    rep(i, values.size()) log_values.at(i) = log(values.at(i));

    // 参考にするデータを決める
    while(true){
        vector<double> changed;

        double ave = calc_ave(log_values);
        double std = calc_std(log_values, ave);

        rep(i, log_values.size()){
            if(ave - std * 2 <= log_values.at(i) && log_values.at(i) <= ave + std * 2){
                changed.push_back(log_values.at(i));
            }
        }

        bool same_size = (changed.size() == log_values.size());
        log_values = changed;
        if(same_size) break;
    }

    if(log_values.size() < DATA_SIZE){
        cout << "small data size" << endl;
        return 1;
    }

    // 順位を元にした加重平均
    double sum = 0;

    rep(i, DATA_SIZE){
        sum += log_values.at(i) * (DATA_SIZE - i);
    }

    double log_value = sum / ((DATA_SIZE + 1) * DATA_SIZE / 2.0);

    // 表示
    cout << exp(log_value) << endl;
}
