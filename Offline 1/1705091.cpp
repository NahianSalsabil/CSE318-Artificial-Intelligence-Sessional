#include <bits/stdc++.h>
using namespace std;

int main(){
    int k,n;
    cin >> k;
    int **initial;
    int goal[3][3] = {{1,2,3},{4,5,6},{7,8,0}};

    cout << "done2\n";
    for(int i = 0; i < k; i++){
        for(int j = 0; j < k; j++){
            cin >> initial[i][j];    // zero will be considered as blank
        }
    }
    cout << "done\n";
    for(int i = 0; i < k; i++){
        for(int j = 0; j < k; j++){
            cout << initial[i][j];    // zero will be considered as blank
        }
    }
    //check solvability
//    if(!check_solvability(k, initial)){
//        cout << "not solvable\n";
//    }
//    else{
//        cout << "Solvable\n";
//    }


    return 0;
}

