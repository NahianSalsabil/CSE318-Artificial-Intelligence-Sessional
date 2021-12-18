#include<bits/stdc++.h>
using namespace std;
#define N 6
#define W1 10
#define W2 5
#define W3 10
#define W4 10
#define heuristic 3


class Game_Control{
    int storage1, storage2, turn, capture;
    int **game_board;

public:
    Game_Control(){
        storage1 = 0;
        storage2 = 0;
        turn=-1;
        capture = 0;
        game_board = new int *[2];
        for(int i = 0; i < 2; i++) {
            game_board[i] = new int[N];
        }
    }
    void setStorage1(int newstorage){
        storage1 = newstorage;
    }
    void setStorage2(int newstorage){
        storage2 = newstorage;
    }
    void setTurn(int newturn){
        turn = newturn;
    }
    void setCapture(int newcapture){
        capture = newcapture;
    }
    int **getGameBoard(){
        return game_board;
    }
    int getStorage1(){
        return storage1;
    }
    int getStorage2(){
        return storage2;
    }
    int getTurn(){
        return turn;
    }
    int getCapture(){
        return capture;
    }

};

void print_board(Game_Control* gameControl){

    cout << "====player 2 board====\n";
    for(int i = 0; i < N; i++){
        cout << " \\ " << gameControl->getGameBoard()[0][i] << " /";
    }
    cout << "\nStorage: " << gameControl->getStorage2() << "\n\n";

    cout << "====player 1 board====\n";
    for(int i = 0; i < N; i++){
        cout << " \\ " << gameControl->getGameBoard()[1][i] << " /";
    }
    cout << "\nStorage: " << gameControl->getStorage1() << "\n\n";
}

int checkAdditionalMove(Game_Control *dummygameControl){
    int additionalmove = 0;
    for(int i = 0; i < N; i++){
        if(dummygameControl->getTurn()%2==0){   // nicher board
            if(dummygameControl->getGameBoard()[1][i] == N-i){
                additionalmove += 1;
            }
        }
        else if(dummygameControl->getTurn()%2==1){   // uporer board
            if(dummygameControl->getGameBoard()[0][i] == i+1){
                additionalmove += 1;
            }
        }
    }
    return additionalmove;
}

int heuristic1(Game_Control *dummygameControl){
    return dummygameControl->getStorage2() - dummygameControl->getStorage1();
}

int heuristic2(Game_Control *dummygameControl){
    int storagediff = dummygameControl->getStorage2() - dummygameControl->getStorage1();
    int board1 = 0, board2 = 0;
    for(int i = 0; i < N; i++){
        board2 += dummygameControl->getGameBoard()[0][i];
        board1 += dummygameControl->getGameBoard()[1][i];
    }
    int stonediff = board2 - board1;
    return W1*storagediff + W2*stonediff;
}

int heuristic3(Game_Control *dummygameControl){
    int storagediff = dummygameControl->getStorage2() - dummygameControl->getStorage1();
    int board1 = 0, board2 = 0;
    for(int i = 0; i < N; i++){
        board2 += dummygameControl->getGameBoard()[0][i];
        board1 += dummygameControl->getGameBoard()[1][i];
    }
    int stonediff = board2 - board1;
    int additional_move_earned = checkAdditionalMove(dummygameControl);
    return W1*storagediff + W2*stonediff + W3*additional_move_earned;
}

int heuristic4(Game_Control *dummygameControl){
    // add code
    int storagediff = dummygameControl->getStorage2() - dummygameControl->getStorage1();

    int board1 = 0, board2 = 0;
    for(int i = 0; i < N; i++){
        board2 += dummygameControl->getGameBoard()[0][i];
        board1 += dummygameControl->getGameBoard()[1][i];
    }
    int stonediff = board2 - board1;

    int additional_move_earned = checkAdditionalMove(dummygameControl);


    return W1*storagediff + W2*stonediff + W3*additional_move_earned + W4*dummygameControl->getCapture();
}

int heuristic5(Game_Control *dummygameControl){
    // add code
}

int heuristic6(Game_Control *dummygameControl){
    // add code
}

void makeCopy(Game_Control *backupgameControl, Game_Control *dummgameControl){
    backupgameControl->setStorage1(dummgameControl->getStorage1());
    backupgameControl->setStorage2(dummgameControl->getStorage2());
    backupgameControl->setTurn(dummgameControl->getTurn());
    for(int i = 0; i < N; i++){
        backupgameControl->getGameBoard()[0][i] = dummgameControl->getGameBoard()[0][i];
        backupgameControl->getGameBoard()[1][i] = dummgameControl->getGameBoard()[1][i];
    }
}

bool Game_Ending_Condition(Game_Control* gameControl){
    int game_end = 1;

    // player 2 board check if empty
    for(int i = 0; i < N; i++){
        if(gameControl->getGameBoard()[0][i] != 0){
            game_end = 0;
            break;
        }
    }
    // if empty
    if(game_end == 1) {
        for(int i = 0; i < N; i++){
            gameControl->setStorage1(gameControl->getStorage1() + gameControl->getGameBoard()[1][i]);
            gameControl->getGameBoard()[1][i] = 0;
        }
        return true;
    }

    // if not empty player 2 board, check player 1 board
    game_end = 1;
    for(int i = 0; i < N; i++) {
        if (gameControl->getGameBoard()[1][i] != 0) {
            game_end = 0;
            break;
        }
    }
    // player 2 board empty
    if(game_end == 1) {
        for(int i = 0; i < N; i++){
            gameControl->setStorage2(gameControl->getStorage2() + gameControl->getGameBoard()[0][i]);
            gameControl->getGameBoard()[0][i] = 0;
        }
        return true;
    }
    return false;
}

int make_Board(Game_Control *dummygameControl, int bin, int row){
    int free_turn = 0;
    if(row == 0){   // player 2 : Computer
        int storage_flag = 0;
        int index = bin-1;
        int no_of_stones = dummygameControl->getGameBoard()[row][index];
        dummygameControl->getGameBoard()[row][index] = 0;

        for(int i = 1; i <= no_of_stones; i++){
            if(bin == 1){   // shurute storage e porbe
                dummygameControl->setStorage2(dummygameControl->getStorage2() + 1);
                row = 1;
                index = -1;
                if(i == no_of_stones) {  // free turn
                    int endflag = 1;
                    for(int j = 0; j < N; j++){
                        if(dummygameControl->getGameBoard()[1-row][j] != 0){
                            endflag = 0;
                        }
                    }
                    if(endflag == 0){   // khela shesh na
                        free_turn = 1;
                    }
                }
            }
            else if(storage_flag == 1){   // storage e dhukse age, ekhon opponent e jabe
                storage_flag = 0;
                row = 1;
                index = 0;
                dummygameControl->getGameBoard()[row][index] += 1;
            }
            else if(row == 0 && index == 0){   // storage e dhukbe
                dummygameControl->setStorage2(dummygameControl->getStorage2() + 1);
                storage_flag = 1;
                if(i == no_of_stones) {  // free turn
                    int endflag = 1;
                    for(int j = 0; j < N; j++){
                        if(dummygameControl->getGameBoard()[1-row][j] != 0){
                            endflag = 0;
                        }
                    }
                    if(endflag == 0){   // khela shesh na
                        free_turn = 1;
                    }
                }
            }
            else if(row == 1 && index == 5){  // opponent er bin shesh
                row = 0;
                index = 5;
                dummygameControl->getGameBoard()[row][index] += 1;
                // stone capture
                if(i == no_of_stones && dummygameControl->getGameBoard()[row][index] == 1 && dummygameControl->getGameBoard()[1-row][index] != 0) {
                    dummygameControl->setStorage2(dummygameControl->getStorage2() + 1 + dummygameControl->getGameBoard()[1-row][index]);
                    dummygameControl->getGameBoard()[row][index] = 0;
                    dummygameControl->getGameBoard()[1-row][index] = 0;
                    // set capture stone
                    dummygameControl->setCapture(dummygameControl->getCapture() + dummygameControl->getGameBoard()[1-row][index]);
                }
            }

            else{   // porer bin e porbe
                if(row == 1) dummygameControl->getGameBoard()[row][index+1] += 1;
                else {
                    dummygameControl->getGameBoard()[row][index-1] += 1;
                    // stone capture
                    if(i == no_of_stones && dummygameControl->getGameBoard()[row][index-1] == 1 && dummygameControl->getGameBoard()[1-row][index-1] != 0) {
                        dummygameControl->setStorage2(1 + dummygameControl->getGameBoard()[1-row][index-1]);
                        dummygameControl->getGameBoard()[row][index-1] = 0;
                        dummygameControl->getGameBoard()[1-row][index-1] = 0;
                        // set capture stone
                        dummygameControl->setCapture(dummygameControl->getCapture() + dummygameControl->getGameBoard()[1-row][index-1]);
                    }

                }
                if(row == 0) index -= 1;
                else index += 1;
            }
        }
    }
    else{    // Player 1
        int storage_flag = 0;
        int index = bin-1;
        int no_of_stones = dummygameControl->getGameBoard()[row][index];
        dummygameControl->getGameBoard()[row][index] = 0;

        for(int i = 1; i <= no_of_stones; i++){
            if(bin == N){    // shurute storage e porbe
                dummygameControl->setStorage1(dummygameControl->getStorage1() + 1);
                row = 0;
                index = N;
                if(i == no_of_stones) {  // free turn
                    int endflag = 1;
                    for(int j = 0; j < N; j++){
                        if(dummygameControl->getGameBoard()[1-row][j] != 0){
                            endflag = 0;
                        }
                    }
                    if(endflag == 0){   // khela shesh na
                        free_turn = 1;
                    }
                }
            }
            else if(storage_flag == 1){   // storage e dhukse age, ekhon opponent e jabe
                row = 0;
                index = 5;
                dummygameControl->getGameBoard()[row][index] += 1;
                storage_flag = 0;
            }
            else if(row == 1 && index == 5){   // storage e dhukbe
                dummygameControl->setStorage1(dummygameControl->getStorage1() + 1);
                storage_flag = 1;
                if(i == no_of_stones) {  // free turn
                    int endflag = 1;
                    for(int j = 0; j < N; j++){
                        if(dummygameControl->getGameBoard()[1-row][j] != 0){
                            endflag = 0;
                        }
                    }
                    if(endflag == 0){   // khela shesh na
                        free_turn = 1;
                    }
                }
            }
            else if(row == 0 && index == 0){  // opponent er bin shesh
                row = 1;
                index = 0;
                dummygameControl->getGameBoard()[row][index] += 1;
                // stone capture
                if(i == no_of_stones && dummygameControl->getGameBoard()[row][index] == 1 && dummygameControl->getGameBoard()[1-row][index] != 0) {
                    dummygameControl->setStorage1(dummygameControl->getStorage1() + 1 + dummygameControl->getGameBoard()[1-row][index]);
                    dummygameControl->getGameBoard()[row][index] = 0;
                    dummygameControl->getGameBoard()[1-row][index] = 0;
                    // set capture stone
                    dummygameControl->setCapture(dummygameControl->getCapture() + dummygameControl->getGameBoard()[1-row][index]);
                }
            }
            else{   // porer bin e porbe
                if(row == 1) {
                    dummygameControl->getGameBoard()[row][index+1] += 1;
                    // stone capture
                    if(i == no_of_stones && dummygameControl->getGameBoard()[row][index+1] == 1 && dummygameControl->getGameBoard()[1-row][index+1] != 0) {
                        dummygameControl->setStorage1(dummygameControl->getStorage1() + 1 + dummygameControl->getGameBoard()[1-row][index+1]);
                        dummygameControl->getGameBoard()[row][index+1] = 0;
                        dummygameControl->getGameBoard()[1-row][index+1] = 0;
                        // set capture stone
                        dummygameControl->setCapture(dummygameControl->getCapture() + dummygameControl->getGameBoard()[1-row][index+1]);
                    }
                }
                else dummygameControl->getGameBoard()[row][index-1] += 1;
                if(row == 0) index -= 1;
                else index += 1;
            }
        }
    }
    if(free_turn == 0){
        dummygameControl->setTurn(dummygameControl->getTurn() + 1);
    }
    return free_turn;
}

int makechild(Game_Control *dummygameControl, int bin, int row){
    int **child_board = new int *[2];
    for (int i = 0; i < 2; i++) {
        child_board[i] = new int[N];
    }
    // child banaite hobe
    int freeturn = make_Board(dummygameControl,bin,row);
    return freeturn;
}

pair<int, int> minimax(Game_Control *dummygameControl, int depth, bool maxplayer, int alpha, int beta){
    int current_bin;
    if(depth == 0){
        // heuristic calculation
        int value;
        if(heuristic == 1)
            value = heuristic1(dummygameControl);
        else if(heuristic == 2)
            value = heuristic2(dummygameControl);
        else if(heuristic == 3)
            value = heuristic3(dummygameControl);
        else if(heuristic == 4)
            value = heuristic4(dummygameControl);
        else if(heuristic == 5)
            value = heuristic5(dummygameControl);
        else if(heuristic == 6)
            value = heuristic6(dummygameControl);
        return make_pair(value, -1);
    }
    // add game ending condition
    if(Game_Ending_Condition(dummygameControl)){
        int value;
        if(heuristic == 1)
            value = heuristic1(dummygameControl);
        else if(heuristic == 2)
            value = heuristic2(dummygameControl);
        else if(heuristic == 3)
            value = heuristic3(dummygameControl);
        else if(heuristic == 4)
            value = heuristic4(dummygameControl);
        else if(heuristic == 5)
            value = heuristic5(dummygameControl);
        else if(heuristic == 6)
            value = heuristic6(dummygameControl);
        return make_pair(value, -1);
    }
    if(maxplayer){
        int row;
        if(dummygameControl->getTurn()%2==1){
            row = 0;
        }
        else{
            row = 1;
        }
        int maxvalue = -999999;
        for(int bin = 1; bin <= N; bin++){
            Game_Control *backupgameControl = new Game_Control;
            makeCopy(backupgameControl,dummygameControl);
            if(dummygameControl->getGameBoard()[row][bin-1] != 0){
                int flag = makechild(dummygameControl, bin, row);
                int currentvalue;
                if(flag == 0){   // no free turn
                    currentvalue = minimax(dummygameControl, depth-1, false, alpha, beta).first;
                }
                else if(flag == 1){  // free turn
                    currentvalue = minimax(dummygameControl, depth-1, true, alpha, beta).first;
                }
                if(currentvalue > maxvalue){
                    maxvalue = currentvalue;
                    current_bin = bin;
                }
                alpha = max(alpha, currentvalue);   // alpha beta pruning
                if(beta <= alpha){
                    break;
                }
            }
            makeCopy(dummygameControl, backupgameControl);
            delete backupgameControl;
        }
        return make_pair(maxvalue, current_bin);
    }
    else{
        int row;
        if(dummygameControl->getTurn()%2==1){
            row = 0;
        }
        else{
            row = 1;
        }
        int minvalue = 999999;
        for(int bin = 1; bin <= N; bin++){
            Game_Control *backupgameControl = new Game_Control;
            makeCopy(backupgameControl,dummygameControl);
            if(dummygameControl->getGameBoard()[row][bin-1] != 0){
                int flag = makechild(dummygameControl, bin, row);
                int currentvalue;
                if(flag == 0) {    // no free turn
                    currentvalue = minimax(dummygameControl, depth - 1, true, alpha, beta).first;
                }
                else if(flag == 1){  // free turn
                    currentvalue = minimax(dummygameControl, depth - 1, false, alpha, beta).first;
                }
                if(currentvalue < minvalue){
                    minvalue = currentvalue;
                    current_bin = bin;
                }
                beta = min(beta, currentvalue);  // alpha beta pruning
                if(beta <= alpha){
                    break;
                }
            }
            makeCopy(dummygameControl, backupgameControl);
            delete backupgameControl;
        }
        return make_pair(minvalue, current_bin);
    }
}

void distribute_stones(int bin, Game_Control *gameControl){
    // turn even hoile board er 1 no row
    // turn odd hoile board er 0 no row
    int free_turn = 0;
    if(gameControl->getTurn()%2 == 0){    // turn even maane player 1
        int row = 1;
        int storage_flag = 0;
        int index = bin-1;
        int no_of_stones = gameControl->getGameBoard()[row][index];
        if(no_of_stones == 0){
            cout << "Computer 1: The bin is empty\n";
            return;
        }
        gameControl->getGameBoard()[row][index] = 0;

        for(int i = 1; i <= no_of_stones; i++){
            if(bin == N){    // shurute storage e porbe
                gameControl->setStorage1(gameControl->getStorage1() + 1);
                row = 0;
                index = N;
                bin = -1;
                if(i == no_of_stones) {  // free turn
                    int endflag = 1;
                    for(int j = 0; j < N; j++){
                        if(gameControl->getGameBoard()[1-row][j] != 0){
                            endflag = 0;
                        }
                    }
                    if(endflag == 0){   // khela shesh na
                        free_turn = 1;
                        cout << "Free Turn\n";
                    }
                }
            }
            else if(storage_flag == 1){   // storage e dhukse age, ekhon opponent e jabe
                row = 0;
                index = 5;
                gameControl->getGameBoard()[row][index] += 1;
                storage_flag = 0;
            }
            else if(row == 1 && index == 5){   // storage e dhukbe
                gameControl->setStorage1(gameControl->getStorage1() + 1);
                storage_flag = 1;
                if(i == no_of_stones) {   // free turn
                    int endflag = 1;
                    for(int j = 0; j < N; j++){
                        if(gameControl->getGameBoard()[1-row][j] != 0){
                            endflag = 0;
                        }
                    }
                    if(endflag == 0){   // khela shesh na
                        free_turn = 1;
                        cout << "Free Turn\n";
                    }
                }
            }
            else if(row == 0 && index == 0){  // opponent er bin shesh
                row = 1;
                index = 0;
                gameControl->getGameBoard()[row][index] += 1;
                // stone capture
                if(i == no_of_stones && gameControl->getGameBoard()[row][index] == 1 && gameControl->getGameBoard()[1-row][index] != 0) {
                    gameControl->setStorage1(gameControl->getStorage1() + 1 + gameControl->getGameBoard()[1-row][index]);
                    gameControl->getGameBoard()[row][index] = 0;
                    gameControl->getGameBoard()[1-row][index] = 0;
                    cout << "Captured!!!\n";
                }
            }
            else{   // porer bin e porbe
                if(row == 1) {
                    gameControl->getGameBoard()[row][index+1] += 1;
                    // stone capture
                    if(i == no_of_stones && gameControl->getGameBoard()[row][index+1] == 1 && gameControl->getGameBoard()[1-row][index+1] != 0) {
                        gameControl->setStorage1(gameControl->getStorage1() + 1 + gameControl->getGameBoard()[1-row][index+1]);
                        gameControl->getGameBoard()[row][index+1] = 0;
                        gameControl->getGameBoard()[1-row][index+1] = 0;
                        cout << "Captured!!!\n";
                    }
                }
                else gameControl->getGameBoard()[row][index-1] += 1;
                if(row == 0) index -= 1;
                else index += 1;
            }
        }
    }
    else{    // turn odd maane player 2
        int row = 0;
        int storage_flag = 0;
        int index = bin-1;
        int no_of_stones = gameControl->getGameBoard()[row][index];
        if(no_of_stones == 0){
            cout << "Computer 2: The bin is empty\n";
            return;
        }
        gameControl->getGameBoard()[row][index] = 0;

        for(int i = 1; i <= no_of_stones; i++){
            if(bin == 1){   // shurute storage e porbe
                gameControl->setStorage2(gameControl->getStorage2() + 1);
                row = 1;
                index = -1;
                bin = -1;
                if(i == no_of_stones) {  // free turn
                    int endflag = 1;
                    for(int j = 0; j < N; j++){
                        if(gameControl->getGameBoard()[1-row][j] != 0){
                            endflag = 0;
                        }
                    }
                    if(endflag == 0){   // khela shesh na
                        free_turn = 1;
                        cout << "Free Turn\n";
                    }
                }
            }
            else if(storage_flag == 1){   // storage e dhukse age, ekhon opponent e jabe
                storage_flag = 0;
                row = 1;
                index = 0;
                gameControl->getGameBoard()[row][index] += 1;
            }
            else if(row == 0 && index == 0){   // storage e dhukbe
                gameControl->setStorage2(gameControl->getStorage2() + 1);
                storage_flag = 1;
                if(i == no_of_stones) {  // free turn
                    int endflag = 1;
                    for(int j = 0; j < N; j++){
                        if(gameControl->getGameBoard()[1-row][j] != 0){
                            endflag = 0;
                        }
                    }
                    if(endflag == 0){   // khela shesh na
                        free_turn = 1;
                        cout << "Free Turn\n";
                    }
                }
            }
            else if(row == 1 && index == 5){  // opponent er bin shesh
                row = 0;
                index = 5;
                gameControl->getGameBoard()[row][index] += 1;
                if(i == no_of_stones && gameControl->getGameBoard()[row][index] == 1 && gameControl->getGameBoard()[1-row][index] != 0) {
                    gameControl->setStorage2(gameControl->getStorage2() + 1 + gameControl->getGameBoard()[1-row][index]);
                    gameControl->getGameBoard()[row][index] = 0;
                    gameControl->getGameBoard()[1-row][index] = 0;
                    cout << "Captured!!!\n";
                }
            }
            else{   // porer bin e porbe
                if(row == 1) gameControl->getGameBoard()[row][index+1] += 1;
                else {
                    gameControl->getGameBoard()[row][index-1] += 1;
                    if(i == no_of_stones && gameControl->getGameBoard()[row][index-1] == 1 && gameControl->getGameBoard()[1-row][index-1] != 0) {
                        gameControl->setStorage2(gameControl->getStorage2() + 1 + gameControl->getGameBoard()[1-row][index-1]);
                        gameControl->getGameBoard()[row][index-1] = 0;
                        gameControl->getGameBoard()[1-row][index-1] = 0;
                        cout << "Captured!!!\n";
                    }
                }
                if(row == 0) index -= 1;
                else index += 1;
            }
        }
    }
    if(free_turn == 0) {
        gameControl->setTurn(gameControl->getTurn() + 1);
    }
}

void start_playing(int playing_mode, int first_player, Game_Control* gamecontrol){
    print_board(gamecontrol);

    // player vs computer
    if(playing_mode == 1){
        int bin;
        if(first_player == 1){    // player
            gamecontrol->setTurn(0);   // turn even hoile player 1 turn
        }
        else if(first_player == 2){   // computer
            gamecontrol->setTurn(1);   // turn odd hoile player 2 turn
        }
        while(true){
            cout << "TURN: " << gamecontrol->getTurn() << endl;
            if(gamecontrol->getTurn()%2 == 0){
                cout << "Player's Turn:\n";
                cout << "Enter bin (1-6) \n";
                cin >> bin;
                if(bin < 1 || bin > 6) {
                    cout << "Invalid Bin, Try Again!\n";
                    continue;
                }
            }
            else{
                cout << "Computer's Turn:\n";
                Game_Control* dummygameControl = new Game_Control;
                makeCopy(dummygameControl, gamecontrol);

                pair<int, int> score_and_bin = minimax(gamecontrol,10,true, -999999, 999999);

                makeCopy(gamecontrol, dummygameControl);
                delete dummygameControl;

                bin = score_and_bin.second;
                cout << "Bin: " << bin << endl;
            }

            // show board and take bin number
            distribute_stones(bin, gamecontrol);
            print_board(gamecontrol);

            // Game Ending Condition
            bool condition = Game_Ending_Condition(gamecontrol);
            if(condition) {
                print_board(gamecontrol);
                if(gamecontrol->getStorage2() > gamecontrol->getStorage1()){
                    cout << "WINNER: Computer!!!\n";
                }
                else if(gamecontrol->getStorage2() == gamecontrol->getStorage1()){
                    cout << "DRAW!!!\n";
                }
                else{
                    cout << "WINNER: Player!!!\n";
                }
                break;
            }
        }
    }
    // computer vs computer
    else if(playing_mode == 2){
        int bin;
        if(first_player == 1){    // Computer 1
            gamecontrol->setTurn(0);   // turn even hoile Computer 1 turn
        }
        else if(first_player == 2){   // computer 2
            gamecontrol->setTurn(1);   // turn odd hoile Computer 2 turn
        }

        while(true){
            cout << "TURN: " << gamecontrol->getTurn() << endl;
            if(gamecontrol->getTurn()%2 == 0){
                cout << "Computer 1's Turn:\n";
            }
            else{
                cout << "Computer 2's Turn:\n";
            }
            Game_Control* dummygameControl = new Game_Control;
            makeCopy(dummygameControl, gamecontrol);

            pair<int, int> score_and_bin = minimax(gamecontrol,10,true, -999999, 999999);

            makeCopy(gamecontrol, dummygameControl);
            delete dummygameControl;

            bin = score_and_bin.second;
            cout << "Bin: " << bin << endl;

            distribute_stones(bin, gamecontrol);
            print_board(gamecontrol);

            // Game Ending Condition
            bool condition = Game_Ending_Condition(gamecontrol);
            if(condition) {
                print_board(gamecontrol);
                if(gamecontrol->getStorage2() > gamecontrol->getStorage1()){
                    cout << "WINNER: Computer 2!!!\n";
                }
                else if(gamecontrol->getStorage2() == gamecontrol->getStorage1()){
                    cout << "DRAW!!!\n";
                }
                else{
                    cout << "WINNER: Computer 1!!!\n";
                }
                break;
            }
        }
    }
    // player vs player
    else if(playing_mode == 3){
        int bin;
        if(first_player == 1){
            gamecontrol->setTurn(0);   // turn even hoile player 1 turn
        }
        else if(first_player == 2){
            gamecontrol->setTurn(1);   // turn odd hoile player 2 turn
        }
        while(true){
            cout << "TURN: " << gamecontrol->getTurn() << endl;
            if(gamecontrol->getTurn()%2 == 0){
                cout << "Player 1's Turn:\n";
            }
            else{
                cout << "Player 2's Turn:\n";
            }

            // show board and take bin number
            cout << "Enter bin (1-6) \n";
            cin >> bin;
            if(bin < 1 || bin > 6){
                cout << "Invalid Bin, Try Again!\n";
                continue;
            }
            distribute_stones(bin, gamecontrol);
            print_board(gamecontrol);

            // Game Ending Condition
            bool condition = Game_Ending_Condition(gamecontrol);
            if(condition) {
                print_board(gamecontrol);
                if(gamecontrol->getStorage2() > gamecontrol->getStorage1()){
                    cout << "WINNER: Player 2!!!\n";
                }
                else if(gamecontrol->getStorage2() == gamecontrol->getStorage1()){
                    cout << "DRAW!!!\n";
                }
                else{
                    cout << "WINNER: Player 1!!!\n";
                }
                break;
            }
        }
    }

}


int main() {
    int playing_mode,first_player;
    cout << "Choose Option:\n1.Player vs Computer\t 2. Computer vs Computer\t 3.Player vs Player\n";
    cin >> playing_mode;
    if(playing_mode != 2){
        cout << "Do you want to play first?\n1.yes\t 2.no\n";
        cin >> first_player;
    }
    else if(playing_mode == 2){
        cout << "Choose 1st Player: \n1. Computer 1\t 2. Computer 2\n";
        cin >> first_player;
    }
    // board initialization
    Game_Control *gamecontrol = new Game_Control;;
    for(int i = 0; i < N; i++){
        gamecontrol->getGameBoard()[0][i] = 4;
        gamecontrol->getGameBoard()[1][i] = 4;
    }
//    for testing
//    for(int i = 0; i < 1; i++){
//        gamecontrol->getGameBoard()[0][i] = 1;
//        gamecontrol->getGameBoard()[1][i] = 1;
//    }
//    gamecontrol->getGameBoard()[0][5] = 6;
//    gamecontrol->getGameBoard()[1][3] = 3;
//    gamecontrol->getGameBoard()[0][3] = 4;
//    gamecontrol->getGameBoard()[1][2] = 4;
//
//    print_board(gamecontrol);
//
//    gamecontrol->setTurn(1);
//    int move = checkAdditionalMove(gamecontrol);
//    cout << move;

    print_board(gamecontrol);
    start_playing(playing_mode, first_player, gamecontrol);

    return 0;
}
