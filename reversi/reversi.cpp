#include <bits/stdc++.h>
using namespace std;
#define rep(i, n) for(int i = 0; i < (int)(n); i++)
#define all(v) v.begin(), v.end()

const int EDGE_LENGTH = 6; // 偶数(奇数の場合は考えないからバグ出まくる)

// 板の状態を保存
// -1 ... 白
//  0 ... 何もない
//  1 ... 黒
//  2 ... 手番側がおける位置
vector<vector<vector<int>>> grid(EDGE_LENGTH, vector<vector<int>>(EDGE_LENGTH, vector<int>(EDGE_LENGTH)));

// 表の処理を簡単にするためのベクトル
vector<vector<int>> directions = {
    {-1, -1, -1},
    {-1, -1, 0},
    {-1, -1, 1},
    {-1, 0, -1},
    {-1, 0, 0},
    {-1, 0, 1},
    {-1, 1, -1},
    {-1, 1, 0},
    {-1, 1, 1},
    {0, -1, -1},
    {0, -1, 0},
    {0, -1, 1},
    {0, 0, -1},
    {0, 0, 1},
    {0, 1, -1},
    {0, 1, 0},
    {0, 1, 1},
    {1, -1, -1},
    {1, -1, 0},
    {1, -1, 1},
    {1, 0, -1},
    {1, 0, 0},
    {1, 0, 1},
    {1, 1, -1},
    {1, 1, 0},
    {1, 1, 1}
}


/* 版の状態を表示 */
void show_grid(){
    vector<string> cell = {"◯ ", "◽", "● ", "▪"};

    int white_count = 0;
    int black_count = 0;

    rep(i, EDGE_LENGTH){
        cout << "layer" << i+1 << endl;
        rep(j, EDGE_LENGTH){
            rep(k, EDGE_LENGTH){
                cout << cell.at(grid.at(i).at(j).at(k) + 1); // gridとcellの添字調整で+1
                if(grid.at(i).at(j).at(k) == -1) white_count++;
                else if(grid.at(i).at(j).at(k) == 1) black_count++;
            }
            cout << endl;
        }
        cout << endl;
    }

    printf("白の数: %2d 黒の数: %2d", white_count, black_count);
}


/* 手番がおける位置をgridに追加 */
void can_put(int order){
    // 前のターンのおける位置を消す
    rep(i, EDGE_LENGTH){
        rep(j, EDGE_LENGTH){
            rep(k, EDGE_LENGTH){
                if(grid.at(i).at(j).at(k) == 2) grid.at(i).at(j).at(k) = 0;
            }
        }
    }
}


/* 指定された位置において、板の更新 */
void put(int order, int x, int y, int z){
    grid.at(x).at(y).at(z) = order;

    // そのベクトルで、色の変更が起きるか調べる
    // 条件は、「orderと同じものまで、orderと逆のもので繋がっている」
    // もし、orderと同じものが隣接していたとしても、繋がっていると考えて、色の変更は起きるベクトルとして考える。(隣接している自分のコマが、自分のコマになる。だから、実際に変わっているわけでわない。)
    // 変更が起きるなら、そのベクトルで見つけた「orderとの距離」を使いながら変更する
    rep(i, directions){
        bool ok = false;
        int diff = 0;
        // 調べるところ
        while(true){
            diff++;

            // 指定された位置を基準に、今回のベクトル*diffで、判定するcell
            int check_x = x + directions.at(i).at(0) * diff;
            int check_y = y + directions.at(i).at(1) * diff;
            int check_z = z + directions.at(i).at(2) * diff;

            // 範囲外チェック
            if(0 <= check_x && check_x < EDGE_LENGTH
            && 0 <= check_y && check_y < EDGE_LENGTH
            && 0 <= check_z && check_z < EDGE_LENGTH){
                break;
            }

            if(grid.at(check_x).at(check_y).at(check_z) == (order * -1)){ // 逆のものかチェック
                continue;
            }else if(grid.at(check_x).at(check_y).at(check_z) == order){ // orderと同じかチェック
                ok = true;
                break;
            }else{ // それ以外(空きだったり、手番がおける位置を示す値だったり)
                break;
            }
        }

        if(!ok) // 変更が起きないなら、次のベクトルに(ネストを浅くしたいからこんな書き方してる)

        // 変更
        for(int j = 1; j < diff; j++){
            
        }
    }
}


int main() {
    // 初期設定
    for(int i = EDGE_LENGTH / 2 - 1; i <= EDGE_LENGTH / 2; i++){
        for(int j = EDGE_LENGTH / 2 - 1; j <= EDGE_LENGTH / 2; j++){
            for(int k = EDGE_LENGTH / 2 - 1; k <= EDGE_LENGTH / 2; k++){
                grid.at(i).at(j).at(k) = ((i + j + k) % 2) * 2 - 1;
            }
        }
    }


    show_grid(grid);
}