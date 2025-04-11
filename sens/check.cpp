#include <bits/stdc++.h>
using namespace std;
#define rep(i, n) for(int i = 0; i < (int)(n); i++)
#define all(v) v.begin(), v.end()

const int init_sens = 324;
const vector<int> pro_senses = {150, 150, 175, 180, 185, 185, 190, 195, 200, 200, 200, 200, 200, 210, 210, 220, 220, 220, 220, 225, 225, 225, 231, 235, 240, 240, 240, 250, 250, 250, 250, 250, 250, 250, 250, 250, 250, 250, 250, 260, 265, 270, 270, 270, 270, 280, 280, 280, 285, 285, 285, 290, 300, 300, 300, 300, 300, 313, 314, 316, 318, 320, 320, 320, 320, 326, 340, 350, 350, 350, 350, 360, 360, 360, 370, 388, 400, 400, 400, 400, 400, 400, 400, 400, 413, 413, 420, 420, 420, 425, 450, 450, 450, 461, 470, 490, 500, 500, 500, 500, 500, 500, 500, 500, 500, 500, 510, 580, 600, 625, 650, 700, 712};

// 感度近づけていくやつ
int sens_nearer(int sens, int t_sens, vector<double> mult){
    rep(i, mult.size()){
        if(sens < t_sens) sens = sens * mult.at(i) + 0.5;
        else sens = sens / mult.at(i) + 0.5;
    }

    return sens;
}

int main() {
    vector<double> multL{
        1.50000,
        1.25000,
        1.12500,
        1.06250,
        1.03704,
        1.01563,
    };
    vector<double> multM{
        1.25000,
        1.12500,
        1.06250,
        1.03125,
        1.01563,
    };
    vector<double> multS{
        1.03125,
        1.01563,
        1.00800,
        1.00412,
    };
    vector<double> multValo{
        1.50000,
        1.25000,
        1.11111,
        1.06250,
        1.03125,
        1.01563,
        1.00781,
    };
    // ターゲットと基準の感度を作成する(pro_sensesとinit_sensが基本)
    int b_sens = init_sens;
    vector<int> t_senses = pro_senses;

    // ターゲットの感度全部に対して試す
    int score = 0;
    for(int t_sens : t_senses){
        // 毎回正しい方を選んだ場合に、どの程度ズレるか調べる
        int sens = b_sens;

        sens = sens_nearer(sens, t_sens, multL);
        sens = (sens_nearer(sens, t_sens, multM) + sens_nearer(sens, t_sens, multM) + 1) / 2;
        sens = (sens_nearer(sens, t_sens, multS) + sens_nearer(sens, t_sens, multS) + sens_nearer(sens, t_sens, multS) + sens_nearer(sens, t_sens, multS) + 2) / 4;

        // sens = sens_nearer(sens, t_sens, multValo);

        score += abs(t_sens - sens);
        printf("%4d %4d %d\n", t_sens, sens, abs(t_sens - sens));
    }
    cout << "sum: " << score << endl;
    cout << "ave: " << score*1.0/pro_senses.size() << endl;

}