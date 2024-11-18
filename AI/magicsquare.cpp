#include <iostream>
#include <vector>

using namespace std;

vector<int> board(10, 2); 
int magic_square[10] = {0, 8, 3, 4, 1, 5, 9, 6, 7, 2};
int turn = 1;
int userSymbol;
int aiSymbol;

int Make2()
{
    if (board[5] == 2)
        return 5;
    if (board[2] == 2)
        return 2;
    if (board[4] == 2)
        return 4;
    if (board[6] == 2)
        return 6;
    if (board[8] == 2)
        return 8;
    return 0;
}

void Go(int n)
{
    board[n] = (turn % 2 != 0) ? userSymbol : aiSymbol;
    turn++;
}

int PossWin(int p)
{
    for (int i = 1; i <= 9; i++)
    {
        if (board[i] == p)
        {
            for (int j = i + 1; j <= 9; j++)
            {
                if (board[j] == p)
                {
                    int third_pos = 15 - (magic_square[i] + magic_square[j]);
                    for (int k = 1; k <= 9; k++)
                    {
                        if (magic_square[k] == third_pos && board[k] == 2)
                        {
                            return k;
                        }
                    }
                }
            }
        }
    }
    return 0;
}

void print_board()
{
    for (int i = 1; i <= 9; i++)
    {
        if (board[i] == 2)
            cout << "- ";
        else if (board[i] == 3)
            cout << "X ";
        else
            cout << "O ";

        if (i % 3 == 0)
            cout << endl;
    }
}

void AIMove()
{
    if (turn == 1)
    {
        Go(1);
    }
    else if (turn == 2)
    {
        if (board[5] == 2)
            Go(5);
        else
            Go(1);
    }
    else if (turn == 3)
    {
        if (board[9] == 2)
            Go(9);
        else
            Go(3);
    }
    else if (turn == 4) 
    {
        int blockMove = PossWin(userSymbol);
        if (blockMove != 0)
        {
            Go(blockMove);
        }
        else
        {
            if(board[2]==userSymbol && board[6]==userSymbol){   
                if(board[1]==2){
                    Go(1);
                }
                else Go(9);
            }
            else if(board[6]==userSymbol && board[8]==userSymbol){
                if(board[3]==2){
                    Go(3);
                }
                else Go(7);
            }
            else if(board[4]==userSymbol && board[8]==userSymbol){
                if(board[1]==2){
                    Go(1);
                }
                else Go(9);
            }
            else if(board[2]==userSymbol && board[4]==userSymbol){
                if(board[3]==2){
                    Go(3);
                }
                else Go(7);
            }
            else if(board[1]==userSymbol && board[8]==userSymbol){  
                Go(7);
            }
            else if(board[3]==userSymbol && board[8]==userSymbol){
                Go(9);
            }
            else if(board[2]==userSymbol && board[9]==userSymbol){
                Go(3);
            }
            else if(board[2]==userSymbol && board[7]==userSymbol){
                Go(1);
            }
            else if(board[1]==userSymbol && board[9]==userSymbol){ 
                if(board[2]==2){
                    Go(2);
                }
                else Go(8);
            }
            else if(board[3]==userSymbol && board[9]==userSymbol){
                if(board[2]==2){
                    Go(2);
                }
                else Go(8);
            }
            else {
                for (int i = 1; i <= 9; i++)
                {
                    if (i != Make2() && board[i] == 2)
                    {
                        Go(i);
                        break;
                    }
                }
            }
        }
    }
    else if (turn == 5)
    {
        int winMove = PossWin(aiSymbol);
        if (winMove != 0)
        {
            Go(winMove);
        }
        else
        {
            int blockMove = PossWin(userSymbol);
            if (blockMove != 0)
            {
                Go(blockMove);
            }
            else if (board[7] == 2)
            {
                Go(7);
            }
            else
            {
                Go(3);
            }
        }
    }
    else if (turn == 6)
    {
        int winMove = PossWin(aiSymbol);
        if (winMove != 0)
        {
            Go(winMove);
        }
        else
        {
            int blockMove = PossWin(userSymbol);
            if (blockMove != 0)
            {
                Go(blockMove);
            }
            else
            {
                Go(Make2());
            }
        }
    }
    else
    {
        int winMove = PossWin(aiSymbol);
        if (winMove != 0)
        {
            Go(winMove);
        }
        else
        {
            int blockMove = PossWin(userSymbol);
            if (blockMove != 0)
            {
                Go(blockMove);
            }
            else
            {
                for (int i = 1; i <= 9; i++)
                {
                    if (board[i] == 2)
                    {
                        Go(i);
                    }
                }
            }
        }
    }
}

bool check_winner(int p)
{
    vector<vector<int>> winningCombos = {
        {1, 2, 3}, {4, 5, 6}, {7, 8, 9}, {1, 4, 7}, {2, 5, 8}, {3, 6, 9}, {1, 5, 9}, {3, 5, 7}};

    for (const auto &combo : winningCombos)
    {
        if (board[combo[0]] == p && board[combo[1]] == p && board[combo[2]] == p)
        {
            return true;
        }
    }

    return false;
}

bool is_board_full()
{
    for (int i = 1; i <= 9; i++)
    {
        if (board[i] == 2)
            return false;
    }
    return true;
}

void PlayGame()
{
    char choice;
    do
    {
        cout << "Do you want to be X or O? Enter X or O: ";
        cin >> choice;
    } while (choice != 'X' && choice != 'x' && choice != 'O' && choice != 'o');

    userSymbol = (choice == 'O' || choice == 'o') ? 5 : 3;
    aiSymbol = (userSymbol == 3) ? 5 : 3;

    while (true)
    {
        print_board();

        if (turn % 2 != 0)
        {
            int move;
            cout << "Your turn (enter a number 1-9): ";
            cin >> move;
            if (move < 1 || move > 9 || board[move] != 2)
            {
                cout << "Invalid move, please try again." << endl;
                continue;
            }
            Go(move);
        }
        else
        {
            cout << "AI's turn..." << endl;
            AIMove();
        }

        if (check_winner(userSymbol))
        {
            print_board();
            cout << "Congratulations! You won!" << endl;
            break;
        }
        else if (check_winner(aiSymbol))
        {
            print_board();
            cout << "AI won! Better luck next time!" << endl;
            break;
        }

        if (is_board_full())
        {
            print_board();
            cout << "It's a draw!" << endl;
            break;
        }
    }
}

int main()
{
    PlayGame();
    return 0;
}