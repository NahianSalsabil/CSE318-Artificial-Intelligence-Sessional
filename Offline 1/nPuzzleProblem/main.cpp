#include <bits/stdc++.h>
using namespace std;
#define N 3

struct Node
{
    Node* parent;
    int** current_board;
    int k;
    int x, y;
    int cost;
    int move;
};

Node* makeNode(int k, int x, int y, int move, Node* parent, int** current_board){
    Node* node = new Node;
    node->k = k;
    node->x = x;
    node->y = y;
    node->move = move;
    node->parent = parent;
    // new node board memory allocation
    node->current_board = new int*[k];
    for (int i = 0; i < k; i++) {
        node->current_board[i] = new int[k];
    }

    // new node board creation
    for(int i = 0; i < k; i++){
        for (int j = 0; j < k; j++){
            node->current_board[i][j] = current_board[i][j];
        }
    }
    if(node->parent != nullptr){
        swap(node->current_board[parent->x][parent->y], node->current_board[x][y]);
    }
    return node;
}


int Hamming_Distance(int k, int** max, int** goal){
    int hamming_distance = 0;
    for(int i = 0; i < k; i++){
        for(int j = 0; j < k; j++){
            if(max[i][j] !=0 && max[i][j] != goal[i][j])
                hamming_distance++;
        }
    }
    return hamming_distance;
}

int Manhattan_Distance(int k, int** mat){
    int manhattan_distance = 0;
    vector <pair<int,int>> goal_position;
    for(int i = 0; i < k; i++){
        for(int j = 0; j < k; j++){
            goal_position.push_back(make_pair(i,j));
        }
    }

    for(int i = 0; i < k; i++){
        for(int j = 0; j < k; j++){
            if(mat[i][j] != 0){
                manhattan_distance += abs(i - goal_position[mat[i][j]-1].first);
                manhattan_distance += abs(j - goal_position[mat[i][j]-1].second);
            }
        }
    }
    return manhattan_distance;
}

int Linear_Conflict(int k, int** mat){
    vector <pair<int,int>> row_num;
    int num = 1, linear_conlict = 0;
    for(int i = 0; i < k; i++){
        for(int j = 0; j < k; j++){
            row_num.push_back(make_pair(num,i));
            num++;
        }
    }

    for(int i = 0; i < k; i++){
        for(int j = 0; j < k; j++){
            if(mat[i][j] != 0 && row_num[mat[i][j]-1].second == i){
                for(int m = j+1; m < k; m++){
                    if(row_num[mat[i][m]-1].second == i && mat[i][j] > mat[i][m]){
                        linear_conlict++;
                    }
                }
            }
        }
    }
    return 2*linear_conlict;
}

int CalculateCost(int func, int k, int** initial, int** goal, int move_cost){
    int heu_cost_ham = Hamming_Distance(k, initial, goal);
    int heu_cost_man = Manhattan_Distance(k,initial);
    int lin_cost = Linear_Conflict(k,initial);

    if(func == 1) {
        //cout << "ham cost " << heu_cost_ham << " move cost " << move_cost << endl;
        return move_cost + heu_cost_ham;
    }
    if(func == 2) {
        //cout << "man cost " << heu_cost_man << " move cost " << move_cost << endl;
        return move_cost + heu_cost_man;
    }
    if(func == 3) {
        //cout << "lin cost " << lin_cost << " move cost " << move_cost << endl;
        return move_cost +  heu_cost_man + lin_cost;
    }
}


int count_inversion(int k, int** initial){
    int num_arr[k*k], count = 0, inversion = 0;
    // copy the matrix in an array
    for(int i = 0; i < k; i++){
        for(int j = 0; j < k; j++){
            num_arr[count] = initial[i][j];
            count++;
        }
    }
    //count inversion
    for(int i = 0; i < count; i++){
        if(num_arr[i] != 0){
            for(int j = i+1; j < count; j++){
                if(num_arr[j] != 0 && num_arr[j] < num_arr[i])
                    inversion++;
            }
        }
    }
    return inversion;
}

bool check_solvability(int k, int** initial){
    int inversion = count_inversion(k, initial);
    int blank;
    // blank position find
    for(int i = 0; i < k; i++){
        for(int j = 0; j < k; j++){
            if(initial[i][j] == 0)
                blank = i;
        }
    }
    // solvability check
    if(k%2==1 && inversion%2==1)   // k odd, inversion odd
        return false;
    if(k%2==1 && inversion%2==0) // k odd, inversion even
        return true;
    if(k%2==0 && ((blank%2==0 && inversion%2==1) || (blank%2==1 && inversion%2==0)))  //k even, blank even + inversion odd or blank odd + inversion even
        return true;
    return false;
}

bool isValid(int k, int x, int y){
    if(x >= 0 && x < k && y >= 0 && y < k)
        return true;
    return false;
}

bool isSame(vector<Node*> puzzleboardclosed, Node* child, int k) {

    for (int i = 0; i < puzzleboardclosed.size(); i++) {
        int same = 1;

        // compare matrix
        for(int j = 0; j < k; j++){
            for(int m = 0; m < k; m++){
                if(child->current_board[j][m] != puzzleboardclosed.at(i)->current_board[j][m]){
                    same = 0;
                    break;
                }
            }
            if(same == 0){
                break;
            }
        }
        if(same == 1){
            return true;
        }
    }
    return false;
}

void printBoard(int k, Node* current){
    for(int i = 0; i < k; i++){
        for(int j = 0; j < k; j++){
            if(current->current_board[i][j] == 0)
                cout << "*\t";
            else
                cout << current->current_board[i][j] << "\t";
        }
        cout << endl;
    }
}

void printSolve(Node* current, int k){
    if(current == nullptr)
        return;
    printSolve(current->parent,k);
    printBoard(k, current);
    cout << endl;
}


void printChild(int k, Node* child){
    for(int i = 0; i < k; i++){
        for(int j = 0; j < k; j++){
            cout << child->current_board[i][j] << "\t";
        }
        cout << endl;
    }
}

struct Comparator
{
    bool operator()(const Node* lhs, const Node* rhs) const
    {
        return (lhs->cost + lhs->move) > (rhs->cost + rhs->move);
    }
};

void PuzzleSolve(int method, int **initial, int k, int x, int y, int **goal) {
    Node *root = makeNode(k, x, y, 0, nullptr, initial);

    // min hip
    priority_queue<Node *, vector<Node *>, Comparator > puzzleboardopen;
    vector<Node *> puzzleboardclosed;

    root->cost = CalculateCost(method, k, initial, goal, 0);
    cout << root->cost << " cost calculated\n";
    puzzleboardopen.push(root);

    while (!puzzleboardopen.empty()) {
        Node *current = puzzleboardopen.top();
        cout << "current node\n";
        printChild(k,current);
        puzzleboardclosed.push_back(current);  // move to closed list
        puzzleboardopen.pop();

        // check goal
        int flag = 1;
        for (int i = 0; i < k; i++) {
            for (int j = 0; j < k; j++) {
                if (current->current_board[i][j] != goal[i][j]) {
                    flag = 0;
                    break;
                }
            }
            if (flag == 0)
                break;
        }
        if (flag == 1) {
            cout << "goal reached\n";
            cout << "Optimal Cost: " << current->move << endl;
            if(method == 1) cout << "Hamming:\n";
            if(method == 2) cout << "Manhattan:\n";
            if(method == 3) cout << "Linear Conflict:\n";
            printSolve(current,k);
            cout << "expanded node: " << puzzleboardclosed.size() - 1;
            cout << ", explored node: " << puzzleboardclosed.size() + puzzleboardopen.size() << endl;
            return;
        }
        int row[4] = {-1, 1, 0, 0};
        int column[4] = {0, 0, -1, 1};
        // generate children
        for (int i = 0; i < 4; i++) {  // a parent can have at best 4 children
            if (isValid(k, current->x + row[i], current->y + column[i])) {
                Node *child = makeNode(current->k, current->x + row[i], current->y + column[i], current->move + 1, current,
                                       current->current_board);
                child->cost = CalculateCost(method, k, child->current_board, goal, child->move);
                if (!isSame(puzzleboardclosed, child, k)){
                    puzzleboardopen.push(child);
//                    cout << "child:\n";
//                    cout << child->cost << endl;
//                    printChild(k, child);
                }
            }
        }
    }
    cout << "goal not reached\n";
}


int main() {
    int k, n, x, y, method;
    cin >> k;
    int **initial = new int *[k];
    int **goal = new int *[k];
    int count = 0;

    // allocate memory
    for (int i = 0; i < k; i++) {
        initial[i] = new int[k];
        goal[i] = new int[k];
    }
    // goal board initialization
    for (int i = 0; i < k; i++) {
        for (int j = 0; j < k; j++) {
            goal[i][j] = ++count;
        }
    }
    goal[k-1][k-1] = 0;
    // initial board input
    for (int i = 0; i < k; i++) {
        for (int j = 0; j < k; j++) {
            cin >> initial[i][j];    // zero will be considered as blank
        }
    }

    for (int i = 0; i < k; i++) {
        for (int j = 0; j < k; j++) {
            if(initial[i][j] == 0) {    // zero will be considered as blank
                x = i;
                y = j;
            }
        }
    }

    //check solvability
    if (!check_solvability(k, initial)) {
        cout << "not solvable\n";
    } else {
        cout << "Solvable\n";
        for(int i = 0; i < 3; i++){
            cout << "Choose function:\n 1.Hamming  2.Manhattan  3.Linear Conflict\n";
            cin >> method;
            PuzzleSolve(method,initial,k,x,y,goal);
        }

    }

    return 0;
}