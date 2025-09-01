#include <iostream>
#include <string>

#define WIDTH 16
#define LENGTH 30

void history(){
    std::cout<< "\n\nMINESWEEPER game dates back The 90s:) GOOD LUCK finding 97 mines\n";
}

void header(){
    std::cout << "\x1B[48;2;0;0;50m";
    std::cout << R"(
   ##     ## ## ##    ## ########  ######  ##      ## ######## ######## ########  ######## ########
   ###   ### ## ###   ## ##       ##    ## ##  ##  ## ##       ##       ##     ## ##       ##     ##
   #### #### ## ####  ## ##       ##       ##  ##  ## ##       ##       ##     ## ##       ##     ##
   ## ### ## ## ## ## ## ######    ######  ##  ##  ## ######   ######   ########  ######   ########
   ##     ## ## ##  #### ##             ## ##  ##  ## ##       ##       ##        ##       ##   ##
   ##     ## ## ##   ### ##       ##    ## ##  ##  ## ##       ##       ##        ##       ##    ##
   ##     ## ## ##    ## ########  ######   ###  ###  ######## ######## ##        ######## ##     ##)";
    history();
}


struct CELL{
    int integer = 0;
    std::string str  = " ";
};

CELL whatIsInThecell(int i, int j, CELL cell, std::string (&Rboard)[WIDTH][LENGTH]){

    if(i == 0) cell.integer = j;
    else if(j == 0) cell.integer = i;
    /*else cell.str  = "m";//*/ else cell.str = Rboard[j - 1][i - 1];
    return cell;
}


void DrawCell(std::string (&Rboard)[WIDTH][LENGTH]){
    for(int j = 0; j < WIDTH + 1; j++){
        for(int i = 0; i< LENGTH + 1; i++)
            std::cout << "+---";
        std::cout << "+\n";
        for(int i = 0; i < LENGTH + 1; i++){
            CELL cell;
            cell = whatIsInThecell(i, j, cell, Rboard);
            if(i == 0 or j == 0){
                std::cout << "| "<< cell.integer;
                if(cell.integer/10 == 0)
                    std::cout << " ";
                }
            else std::cout << "| "<< cell.str << " ";
            }
        std::cout << "|\n";
        }
    for(int i = 0; i < LENGTH + 1; i++)
        std::cout  << "+---";
    std::cout << "+";
}



class Board{
public:
    int numMINE = 97;
    bool gameover = false;
    std::string board[WIDTH][LENGTH];
    std::string copyboard[WIDTH][LENGTH];
    std::string Rboard[WIDTH][LENGTH];
    int  Board[WIDTH][LENGTH];

    void init(){
        for(int i = 0; i < WIDTH ; i++){
            for(int j = 0; j < LENGTH ; j++){
                board[i][j] = " ";
                copyboard[i][j] = Rboard[i][j] = " ";
                Board[i][j] = 0;
                }
            }
    }

    void BombInBoard(){

        std::cout << "\x1B[48;2;12;13;12m";
        // if over std::cout << "\x1B[38;2;255;0;0m";
        std::cout << "\x1B[38;2;0;255;0m";

        //BOMB in first row
        board[0][10] = board[0][14] = board[0][15] = board[0][16] = board[0][18] = board[0][21] = board[0][27] = "*";
        //BOMB in second row
        board[1][14] = board[1][16] = board[1][23] = board[1][26] = "*";
        //BOMB in third row
        board[2][2] = board[2][5] = board[2][15] = board[2][16] = board[2][18] = "*";
        //BOMB in fourth row
        board[3][3] = board[3][5] = board[3][16] = board[3][22] = board[3][24] = board[3][27] = "*";
        //BOMB in fifth row
        board[4][17] = board[4][19] = board[4][28] = "*";
        //sixth row
        board[5][14] = board[5][16] = board[5][18] = board[5][20] = board[5][24] = "*";
        //seven
        board[6][1] = board[6][3] = board[6][5] = board[6][18] = board[6][25] = "*";
        //eight
        board[7][2] = board[7][12] = board[7][13] = board[7][15] = board[7][23] = "*";
        //nine
        board[8][6] = board[8][13] = board[8][19] = board[8][25] = "*";
        //ten
        board[9][0] = board[9][9] = board[9][12] = board[9][15] = board[9][16] = board[9][17] = board[9][19] = board[9][21] = "*";
        //eleven
        board[10][0] = board[10][2] = board[10][4] = board[10][14] = board[10][15] = board[10][16] = board[10][22] = "*";
        //12
        board[11][14] = board[11][16] = board[11][18] = board[11][22] = "*";
        //13
        board[12][4] = board[12][5] = board[12][10] = board[12][13] = board[12][14] = board[10][15] = board[10][16] = board[12][21] = board[12][22] = board[12][26] = "*";
        //14
        board[13][1] = board[13][4] = board[13][21] = board[13][24] = "*";
        //15
        board[14][2] = board[14][3] = board[14][7] = board[14][13] = board[14][16] = board[14][19] = board[14][24] = board[14][26] = board[14][27] = board[14][29] = "*";
        //16
        board[15][5] = board[15][6] = board[15][7] = board[15][8] = board[15][13] = board[15][21] = board[15][24] = board[15][25] = board[15][26] = board[15][27] = "*";
        }
/*
    void showTheBoard(){

        for(int i = 0; i < WIDTH ; i++){
            for(int j = 0; j < LENGTH; j++)
                cout << "\x1b]50;" <<"10x2000"<< "\a" << flush <<copyboard[i][j] << " ";
        cout << endl;
    }
        }*/
    void N_mines(){

        for(int i = 0; i < WIDTH; i++){
            for(int j = 0; j < LENGTH; j++){
                if(board[i - 1][j - 1] == "*" && i - 1 > -1 && j - 1 > -1)
                    Board[i][j] += 1;
                if(board[i - 1][j] == "*" && i - 1 > -1)
                    Board[i][j] += 1;
                if(board[i - 1][j + 1] == "*" && i - 1 > -1 && j + 1 < 17)
                    Board[i][j] += 1;
                if(board[i][j - 1] == "*" && j - 1 > -1)
                    Board[i][j] += 1;
                if(board[i][j + 1] == "*" && j + 1 < 17)
                    Board[i][j] += 1;
                if(board[i + 1][j - 1] == "*" && i + 1 < 17 && j - 1 > -1)
                    Board[i][j] += 1;
                if(board[i + 1][j] == "*" && i + 1 < 17 )
                    Board[i][j] += 1;
                if(board[i + 1][j + 1] == "*" && i + 1 < 17 && j + 1 < 17)
                    Board[i][j] += 1;
            }
        }
    }


    void UpdateBoarddata(int i, int j, char choise){

        if(choise == 'r'){
            if(board[i][j] == "*"){
                gameover = true;
            }

            else if(Board[i][j] == 0)
            {
                for(int k = i;k < WIDTH; k++){
                    if(board[k][j] == "*")
                        break;
                    else
                        Rboard[k][j] = std::to_string(Board[k][j]);
                }
                for(int k = i;k > -1; k--){
                    if(board[k][j] == "*")
                        break;
                    else
                        Rboard[k][j] = std::to_string(Board[k][j]);
                }
                for(int k = j;k > -1; k--){
                    if(board[i][k] == "*")
                        break;
                    else
                        Rboard[i][k] = std::to_string(Board[i][k]);
                }
                for(int k = j;k < LENGTH; k++){
                    if(board[i][k] == "*")
                        break;
                    else
                        Rboard[i][k] = std::to_string(Board[i][k]);
                }
                for(int k = i, t = j;k < WIDTH && t > -1; k++ && t--){
                    if(board[k][t] == "*")
                        break;
                    else
                        Rboard[k][t] = std::to_string(Board[k][t]);
                }
                for(int k = i, t = j;k < WIDTH && t < LENGTH; k++ && t++){
                    if(board[k][t] == "*")
                        break;
                    else
                        Rboard[k][t] = std::to_string(Board[k][t]);
                }
                for(int k = i, t = j;k > -1 && t < LENGTH; k-- && t++){
                    if(board[k][t] == "*")
                        break;
                    else
                        Rboard[k][t] = std::to_string(Board[k][t]);
                }
                for(int k = i, t = j;k > -1 && t > -1; k-- && t--){
                    if(board[k][t] == "*")
                        break;
                    else
                        Rboard[k][t] = std::to_string(Board[k][t]);
                }

            }
            else
                Rboard[i][j] = std::to_string(Board[i][j]);
        }

        if(choise == 'f'){
            Rboard[i][j] = "f";
            // numMINE -= 1;
        }

    }

    void SaveTheBoard(){
        for(int i = 0; i < WIDTH ; i++){
            for(int j = 0; j < LENGTH ; j++)
                copyboard[i][j] = Rboard[i][j];
        }
    }

    void getInput(){
        // SaveTheBoard();
        int in[2];
        char choise;
        std::cout << "\nENTER the coordinate of the cell (_vertical first number, _horixontal second number) : ";
        std::cin >> in[0] >> in[1];
        if(in[0] > 16 || in[1] > 30){//develope !!
        for(int i = 0; i < 5; i++){
            std::cout << "Please enter the right coordinate : ";
            std::cin >> in[0] >> in[1];
            }
        }
        std::cout << "ENTER f for flag OR r for revealing : ";
        std::cin >> choise;
        while(choise != 'f' && choise != 'r'){
            std::cout<< "please enter the right command : ";
            std::cin >> choise;
        }
        UpdateBoarddata(in[0] - 1, in[1] - 1, choise);
    }

    void Undo(){

        std::string b;
        std::cout <<"\n\nif u wanna undo type B else Type I for ignore \n";
        std::cin >> b;
        if(b == "B" || b == "b"){
            for(int i = 0; i < WIDTH ; i++){
                for(int j = 0; j < LENGTH ; j++)
                    Rboard[i][j] = copyboard[i][j];
            }
        }
    }

    void game(){
        init();
        BombInBoard();
        N_mines();
        while(!gameover){
            DrawCell(Rboard);
            Undo();
            getInput();
        }
    }
};



int main(){

    header();
    Board Brd;
    Brd.game();
    //exit
    if(Brd.gameover == true){
        std::cout << "\x1B[38;2;255;0;0m";
        std::cout << "GAME OVER!\n";
        DrawCell(Brd.board);
    }
    else {
        std::cout << "\x1B[38;2;0;0;255m";
        std::cout << "!!!!!!!!!!!!!!!!!!!!!!DUDE CONGRATULATION U WON AN IMPOSSIBEL GAME !!!!!!!!!!!!!!!!!";
        DrawCell(Brd.board);
    }
}
