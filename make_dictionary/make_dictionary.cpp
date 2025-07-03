#include <bits/stdc++.h>
using namespace std;
#define rep(i, n) for(int i = 0; i < (int)(n); i++)
#define all(v) v.begin(), v.end()

struct word{
    string display_text;
    string reading;
    string last_kana;
    string first_kana;
};


int main() {
    /* input */
    int n;
    cin >> n;
    vector<word> words(n);
    rep(i, n) cin >> words.at(i).display_text >> words.at(i).reading >> words.at(i).last_kana >> words.at(i).first_kana;

    /* solve */
    map<string, vector<word>> dictionary;
    for(word& e : words){
        if(dictionary.count(e.first_kana)){
            dictionary.at(e.first_kana).push_back(e);
        }else{
            dictionary[e.first_kana] = {e};
        }
    }

    int i = 0;
    cout << "{" << endl;
    for (auto& [kana, vec] : dictionary) {
        cout << "  \"" << kana << "\": [" << endl;

        int j = 0;
        for (auto& w : vec) {
            cout << "    {\"displayText\": \"" << w.display_text << "\", \"reading\": \"" << w.reading << "\", \"lastKana\": \"" << w.last_kana << "\"}";
            cout << (j == vec.size() - 1 ? "" : ",") << endl;
            j++;
        }
        
        cout << "  ]" << (i == dictionary.size()-  1 ? "" : ",") << endl;
        i++;
    }
    cout << "}" << endl;


}