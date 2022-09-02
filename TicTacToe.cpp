///////////////////////////////////////////////////////////////////////////////////////////////////////
//                                                                                                   //
//      Author:         PRAVEER SHARAN                                                               //
//      Program:        TIC-TAC-TOE                                                                  //
//                                                                                                   //
//      Description:    The user plays a tic-tac-toe game with the computer. The user goes first,    //
//                      as the 'X' and the computer goes second, as the 'O'. The catch with this     //
//                      this program is that the computer can never lose. This is done by matching   //
//                      the tic-tac-toe board to a type of board where the user cannot use any       //
//                      tricks on the computer. Once this is done, the computer just prevents the    //
//                      loss by putting an 'O' to get three 'O's in a row or to stop the user from   //
//                      getting three 'X's in a row. The user can challenge the computer as many     //
//                      times as he or she wishes.                                                   //
//                                                                                                   //
///////////////////////////////////////////////////////////////////////////////////////////////////////





#include <iostream>
#include <cmath>                            // needed to use the abs() function, which calculates the absolute value
using namespace std;

void displayBoard(char board[3][3]) {       // this function displays the most updated 3x3 tic-tac-toe board
    cout << "\t0   1   2" << endl;
    for (int i = 0; i < 3; i++) {
        cout << "      " << i << "\t" << board[i][0] << " | ";
        cout << board[i][1] << " | ";
        cout << board[i][2] << " |" << endl;
        cout << "\t" << "_   _   _" << endl;
    }
}

void place(char board[3][3], int a, int b, char c) {       // places either an 'X' or an 'O' in one of the cells of the tic-tac-toe board
    board[a][b] = c;
    if (c == 'O')                                          // if the computer plays, then the computer will tell that to the user
        cout << "I have PLAYED on (" << a << ", " << b << "):" << endl;
    displayBoard(board);                                   // displays the updated board finally
    cout << "---------------------------------------------------\n" << endl;
}

int win(char board[3][3], int a, int b, int c) {                // if there are two 'O's and one empty cell in a line, this function tells the computer to play in the empty cell so it will win
    if (board[a/10][a%10] == 'O' && board[b/10][b%10] == 'O' && board[c/10][c%10] == ' ')            // scenario 1
        place(board, c/10, c%10, 'O');
    else if (board[a/10][a%10] == 'O' && board[b/10][b%10] == ' ' && board[c/10][c%10] == 'O')      // scenario 2
        place(board, b/10, b%10, 'O');
    else if (board[a/10][a%10] == ' ' && board[b/10][b%10] == 'O' && board[c/10][c%10] == 'O')      // scenario 3
        place(board, a/10, a%10, 'O');
    else
        return 0;                                                            // if the computer plays in this function, it returns 1, meaning that the user has lost, if it doesn't, it returns 0
    cout << "You LOSE!" << endl;
    return 1;
}

int cut(char board[3][3], int a, int b, int c) {                 // if there are two 'X's and one empty cell in a line, this function tells the computer to play in the empty cell to prevent the user from winning
    if (board[a/10][a%10] == 'X' && board[b/10][b%10] == 'X' && board[c/10][c%10] == ' ')           // scenario 1
        place(board, c/10, c%10, 'O');
    else if (board[a/10][a%10] == 'X' && board[b/10][b%10] == ' ' && board[c/10][c%10] == 'X')      // scenario 2
        place(board, b/10, b%10, 'O');
    else if (board[a/10][a%10] == ' ' && board[b/10][b%10] == 'X' && board[c/10][c%10] == 'X')      // scenario 3
        place(board, a/10, a%10, 'O');
    else
        return 0;                                               // if the computer plays in this function, it returns 1, if it doesn't, it returns 0
    return -1;
}

int check(char board[3][3]) {                                   // asks the user for input - which cell they want to place their 'X' in
    int x, y;
    bool vacant = false;
    do {                                                        // this do-while loop checks if the spot that they entered exists and is vacant
        cout << "Your turn: ";
        cin >> x >> y;
        if (board[x][y] == 'X' || board[x][y] == 'O')
            cout << "This spot is ALREADY OCCUPIED. Try another spot." << endl;
        else if ((x > 2 || x < 0) || (y > 2 || y < 0))
            cout << "This spot DOES NOT EXIST. Try another spot." << endl;
        else
            vacant = true;
    } while (vacant == false);
    return (10 * x + y);                                        // returns the user input in a two digit form (i.e.  2, 3 --> 23)
}

void preventLoss(char board[3][3]) {                            // function that prevents the computer from losing by using the win() and cut() functions
    int x, y, a, played, input;
    played = a = 0;
    bool seek = true;
    int lines[8][3] = {{0, 1, 2}, {10, 11, 12}, {20, 21, 22}, {0, 10, 20}, {1, 11, 21}, {2, 12, 22}, {0, 11, 22}, {2, 11, 20}};     // list of all possible lines in tic-tac-toe
    for (int i = 0; i < 8 && played == 0; i++)                  // iterates through all lines, checking if it is possible for the computer to secure a win
        played = win(board, lines[i][0], lines[i][1], lines[i][2]);
    for (int i = 0; i < 8 && played == 0; i++)                  // if it is possible for the computer to win, it will do that instead of cutting, so this is second priority
        played = cut(board, lines[i][0], lines[i][1], lines[i][2]);
    if (played == 0) {                                          // if the computer cannot win or cut anything, it will place 'O' in the first cell that is empty
        seek = false;
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                if (board[i][j] == ' ' && seek == false) {
                    place(board, i, j, 'O');                    // if the cell is found, it is placed, so seek turns true, and played turns -1 to show that the game may continue
                    played = -1;
                    seek = true;
                }
            }
        }
    }
    if (seek == false)                                          // if no empty cell was found, all cells are occupied, meaning that there is a draw
        cout << "It is a DRAW!" << endl;
    if (played == -1) {                                         // this asks for the next user input
        input = check(board);
        place(board, input / 10, input % 10, 'X');
        preventLoss(board);
    }
}

int main() {
    cout << "WELCOME to this game of TIC-TAC-TOE!\n\n" << endl;         // explains the instructions
    cout << "In this game, you will be the X's and I will be the O's. Being the X's, you will of course go first. The goal of tic-tac-toe is to get ";
    cout << "three of your character (in this case the X's) in a row, column, or diagonal." << endl;
    cout << "HOW TO PLACE AN 'X':    In order to place your character, you will be prompted. Enter in your x-column, followed by a space, followed by ";
    cout << "your y-column. This is what the board looks like --- " << endl;
    cout << "\t0   1   2" << endl;
    cout << "      0\t  |   |   |\n\t_   _   _\n      1\t  |   |   |\n\t_   _   _\n      2\t  |   |   |\n\t_   _   _" << endl;
    cout << "In order to place your X, enter which row it is, followed by a space, followed by which column it is. For example, a prompt '2 1' would ";
    cout << "be in the bottom in the center column.\n\nThat's everything! Let's PLAY!\n\n";
    int x, y, x2, y2, input;                        // these variables will be used for recording user input
    char ans;
    bool again = true;
    char board[3][3];                               // the tic-tac-toe board
    while (again == true) {
        for (int i = 0; i < 3; i++) {               // sets the entire board to empty
            for (int j = 0; j < 3; j++)
                board[i][j] = ' ';
        }
        input = check(board);
        x = input / 10;                             // x and y are the coordinates of the user's first input
        y = input % 10;
        place(board, x, y, 'X');
        if (x == 1 && y == 1) {                     // if the user chooses the center
            place(board, 2, 2, 'O');
            input = check(board);
            x2 = input / 10;                        // x2 and y2 are the coordinates of the user's second input
            y2 = input % 10;
            place(board, x2, y2, 'X');
            if (x2 == 0 && y2 == 0) {               // if the user chooses the top left corner next
                place(board, 2, 0, 'O');
                input = check(board);
                place(board, input / 10, input % 10, 'X');
            }
        }
        else if (x == 1 || y == 1) {                // if the user chooses the side
            place(board, 1, 1, 'O');
            input = check(board);
            x2 = input / 10;                        // x2 and y2 are the coordinates of the user's second input
            y2 = input % 10;
            place(board, x2, y2, 'X');
            if (abs(x2 - x) == 1 && abs(y2 - y) == 1) {     // if the user chooses another side that is not directly across from the previous side as the next input
                place(board, x*x2, y*y2, 'O');
                input = check(board);
                place(board, input / 10, input % 10, 'X');
            }
            else if ((x2 - x == 0 && abs(y2 - y) == 2) || (abs(x2 - x) == 2 && y2 - y == 0)) {          // if the user chooses the opposite side as the next input
                place(board, 2, 2, 'O');
                input = check(board);
                place(board, input / 10, input % 10, 'X');
            }
        }
        else {                                      // if the user chooses the corner
            place(board, 1, 1, 'O');
            input = check(board);
            x2 = input / 10;                        // x2 and y2 are the coordinates of the user's second input
            y2 = input % 10;
            place(board, x2, y2, 'X');
            if (abs(x2 - x) * abs(y2 - y) == 2) {       // if the user chooses a side that is not adjacent to the 'X'
                if (x % 2 == 0 && y2 % 2 == 0)          // ensures that the computer plays in a corner which is on the same row as one 'X' and on the same column as another 'X'
                    place(board, x, y2, 'O');
                else
                    place(board, x2, y, 'O');
                input = check(board);
                place(board, input / 10, input % 10, 'X');
            }
            else if (abs(x2 - x) * abs(y2 - y) == 4) {  // if the user chooses the corner that is completely opposite as the next input
                place(board, 1, 2, 'O');
                input = check(board);
                place(board, input / 10, input % 10, 'X');
            }
        }
        preventLoss(board);                             // in the current state of the board, the algorithm is all that is necessary to prevent a loss
        cout << "Would you like to play again? [Y/N]";
        cin >> ans;
        if (ans == 'Y' || ans == 'y')                   // if the user answers 'Y/y' or yes, then the while loop occurs again
            cout << "RESETTING the board..." << endl;
        else                                            // if the user answers something else or no, then the program stops
            again = false;
    }
    return 0;
}