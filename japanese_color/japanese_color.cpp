#include <bits/stdc++.h>
using namespace std;
#define rep(i, n) for(int i = 0; i < (int)(n); i++)
#define all(v) v.begin(), v.end()

struct color{
    string name;
    int red;
    int green;
    int blue;
};

const color emerald_green = {"エメラルドグリーン", 00, 169, 68};


int main() {
    /* input */
    int n;
    string name, name_h, rgb;
    cin >> n;
    vector<color> colors(n);
    rep(i, n){
        cin >> name >> name_h >> rgb;
        colors.at(i).name = name;
        colors.at(i).red = stoi(rgb.substr(1, 2), nullptr, 16);
        colors.at(i).green = stoi(rgb.substr(3, 2), nullptr, 16);
        colors.at(i).blue = stoi(rgb.substr(5, 2), nullptr, 16);
    }
    /* solve */
    rep(i, n){
        if(colors.at(i).red <= 128
        && (emerald_green.green / 2 < colors.at(i).green && colors.at(i).green < emerald_green.green * 2)
        && (emerald_green.blue / 2 < colors.at(i).blue && colors.at(i).blue < emerald_green.blue * 2)){
            cout << i << colors.at(i).name << ": "
            << colors.at(i).red << ", "
            << colors.at(i).green << ", "
            << colors.at(i).blue << endl;
        }
    }

}