#ifndef COLOR_H
#define COLOR_H

#include<bits/stdc++.h>

#define edgecumuprob 0.9
#define cornercumuprob 0.1
#define sensorcorrectness 0.85

using namespace std;

void printRed(string text) {
    cout << "\033[1;31m" << text << "\033[0m";
}

void ShowGridProbability(double** grid, int n, int m){
    for(int i = 0; i < n; i++){
        for(int j = 0; j < m; j++){
            cout << "\t=======\t";
        }
        cout << endl;
        for(int j = 0; j < m; j++){
            if(grid[i][j] == -1){
                cout << "||\t  ";
                string text = "Obs";
                printRed(text);
                cout << "  \t";
            }

            else
                cout << "||\t" << fixed << setprecision(4)<< grid[i][j] << "\t";
        }
        cout << "||" << endl;
    }
    for(int j = 0; j < m; j++){
        cout << "\t=======\t";
    }
    cout << endl;
}

int CalculateObstacle(double** grid, int n, int m){
    int obstacle = 0;
    for(int i = 0; i < n; i++){
        for(int j = 0; j < m; j++){
            if(grid[i][j] == -1)
                obstacle++;
        }
    }
    return obstacle;
}

double CalculateGridProb(double** grid, int n, int m, int cumulative_prob){
    return cumulative_prob/double((m*n - CalculateObstacle(grid,n,m)));
}

void SetInitialGridPrbability(double** grid, int n, int m, double initial_prob){
    for(int i = 0; i < n; i++){
        for(int j = 0; j < m; j++){
            if(grid[i][j] != -1)
                grid[i][j] = initial_prob;
        }
    }
}

pair<int, int> GetMostProbablePosition(double** grid, int n, int m){
    double max = 0;
    int u, v;
    for(int i = 0; i < n; i++){
        for(int j = 0; j < m; j++){
            if(grid[i][j] > max){
                max = grid[i][j];
                u = i;
                v = j;
            }
        }
    }
    return make_pair(u,v);
}

pair<int,int> Count(double** grid, int n, int m, int i, int j){
    int edgecount = 0, cornercount = 0;
    int starti = i-1, endi = i+1, startj = j-1, endj = j+1;
    if(i == 0)     starti = i;
    if(i == n-1)   endi = i;
    if(j == 0)     startj = j;
    if(j == m-1)   endj = j;

    for(int a = starti; a <= endi; a++){
        for(int b = startj; b <= endj; b++){
            if(grid[a][b] != -1) {
                if (a == i && b == j) cornercount++;
                else if (a == i || b == j) {
                    if (grid[a][b] != -1) edgecount++;
                } else {
                    if (grid[a][b] != -1) cornercount++;
                }
            }
        }
    }
    return make_pair(edgecount,cornercount);
}

vector<pair<pair<int,int>, double>> GetPossibleIndex(double** grid, int n, int m, int i, int j){
    vector<pair<pair<int, int>, double>> indexes;

    int starti = i-1, endi = i+1, startj = j-1, endj = j+1;
    if(i == 0)     starti = i;
    if(i == n-1)   endi = i;
    if(j == 0)     startj = j;
    if(j == m-1)   endj = j;

    for(int a = starti; a <= endi ; a++){
        for(int b = startj; b <= endj; b++){
            if(grid[a][b] != -1){
                if(a == i && b == j){     // same cell
                    pair<int,int> count = Count(grid,n,m,a,b);
                    int edgecount = count.first;
                    int cornercount = count.second;
                    if(cornercount == 0)
                        indexes.push_back(make_pair(make_pair(a,b),0));
                    else if(edgecount == 0)
                        indexes.push_back(make_pair(make_pair(a,b),1/cornercount));
                    else
                        indexes.push_back(make_pair(make_pair(a,b),cornercumuprob/cornercount));
                }
                else if(a == i || b == j) { // edge cell
                    pair<int, int> count = Count(grid, n, m, a, b);
                    int edgecount = count.first;
                    int cornercount = count.second;
                    if (edgecount == 0)
                        indexes.push_back(make_pair(make_pair(a, b), 0));
                    else if (cornercount == 0)
                        indexes.push_back(make_pair(make_pair(a, b), 1 / edgecount));
                    else
                        indexes.push_back(make_pair(make_pair(a, b), edgecumuprob / edgecount));
                }
                else{     // corner cell
                    pair<int, int> count = Count(grid, n, m, a, b);
                    int edgecount = count.first;
                    int cornercount = count.second;
                    if(cornercount == 0)
                        indexes.push_back(make_pair(make_pair(a,b),0));
                    else if(edgecount == 0)
                        indexes.push_back(make_pair(make_pair(a,b),1/cornercount));
                    else
                        indexes.push_back(make_pair(make_pair(a,b),cornercumuprob/cornercount));
                }
            }
        }
    }
    return indexes;
}

void NormalizeGrid(double** grid, int n, int m){
    double cumulative_prob = 0;
    for(int i = 0; i < n; i++){
        for(int j = 0; j < m; j++){
            if(grid[i][j] != -1){
                cumulative_prob += grid[i][j];
            }
        }
    }
    if(cumulative_prob != 1){
        for(int i = 0; i < n; i++){
            for(int j = 0; j < m; j++){
                if(grid[i][j] != -1)
                    grid[i][j] = grid[i][j]/cumulative_prob;
            }
        }
    }
}

void UpdateGridAfterTimeUnit(double** grid, int n, int m){
    vector<pair<pair<int, int>,double>> indexes;

    double** updated_grid;
    updated_grid = new double *[n];
    for(int i = 0; i < m; i++) {
        updated_grid[i] = new double [m];
    }

    for(int i = 0; i < n; i++){
        for(int j = 0; j < m; j++){
            double sum = 0;
            if(grid[i][j] != -1){
                indexes = GetPossibleIndex(grid,n,m,i,j);
                for(int k = 0; k < indexes.size(); k++){
                    sum += grid[indexes.at(k).first.first][indexes.at(k).first.second] * indexes.at(k).second;
                }
                updated_grid[i][j] = sum;
            }
            else updated_grid[i][j] = grid[i][j];
        }
    }

    for(int i = 0; i < n; i++){
        for(int j = 0; j < m; j++){
            grid[i][j] = updated_grid[i][j];
        }
    }
}

void UpdateGridBySensor(double** grid, int n, int m, int u, int v, int b){
    if(b == 1){
        for(int i = 0; i < n; i++){
            for(int j = 0; j < m; j++){
                if(grid[i][j] != -1){
                    if(i >= u-1 && i <= u+1 && j >= v-1 && j <= v+1){
                        grid[i][j] = grid[i][j] * sensorcorrectness;
                    }
                    else
                        grid[i][j] = grid[i][j] * (1-sensorcorrectness);
                }
            }
        }
    }
    if(b == 0){
        for(int i = 0; i < n; i++){
            for(int j = 0; j < m; j++){
                if(grid[i][j] != -1){
                    if(i >= u-1 && i <= u+1 && j >= v-1 && j <= v+1){
                        grid[i][j] = grid[i][j] * (1-sensorcorrectness);
                    }
                    else
                        grid[i][j] = grid[i][j] * sensorcorrectness;
                }
            }
        }
    }
    NormalizeGrid(grid,n,m);
}

int main() {
    int m, n, k, u, v, b;
    double **grid;
    string command;

    while(1){
        cout << "Enter the grid size (n*m) and number of obstacles(k): ";
        cin >> n >> m >> k;
        if(n < 3 || n > 20 || m < 3 || m > 20 || k < 0 || k > n*m)
            cout << "Invalid Input! Try Again.\n";
        else break;
    }


    // grid initialization
    grid = new double *[n];
    for(int i = 0; i < m; i++) {
        grid[i] = new double [m];
    }

    for(int i = 0; i < k; i++){
        while(1){
            cout << "Enter the position of obstacle " << i+1 << ": ";
            cin >> u >> v;
            if(u <= 0 || u >= n || v <= 0 || v >= m)
                cout << "Invalid Input! Try Again.\n";
            else break;
        }
        grid[u][v] = -1;
    }
    double initial_prob = CalculateGridProb(grid,n,m,1);
    SetInitialGridPrbability(grid,n,m,initial_prob);
    ShowGridProbability(grid,n,m);

    while(1){
        cout << "R u v b\t\tSensor reading for position u,v (b = 0 or 1)\n";
        cout << "C\t\tInquery about Casper's Position\n";
        cout << "Q\t\tTeminate Searching\n";
        cout << "Enter your command: ";
        cin >> command;
        if(command == "R"){
            cin >> u >> v >> b;
            UpdateGridAfterTimeUnit(grid,n,m);
            cout << "After 1 time unit:\n";
            ShowGridProbability(grid,n,m);
            UpdateGridBySensor(grid,n,m,u,v,b);
            cout << "After Reading Sensor:\n";
            ShowGridProbability(grid,n,m);
        }
        else if(command == "C"){
            pair<int,int> position = GetMostProbablePosition(grid,n,m);
            cout << "Casper is most probably at (" << position.first << "," << position.second << ")" << endl;
        }
        else if(command == "T"){
            UpdateGridAfterTimeUnit(grid,n,m);
            ShowGridProbability(grid,n,m);
        }
        else if(command == "Q"){
            cout << "Bye Casper!\n";
            break;
        }
    }
    return 0;
}
#endif