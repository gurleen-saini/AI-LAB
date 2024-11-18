#include <iostream>
#include <vector>
using namespace std;

vector<int> board(10, 2); // 2 for blank, 3 for X, 5 for O
int turn = 0;
int player_symbol;
int comp_symbol;

bool checking_for_winner(int symbol)
{
  vector<vector<int>> lines = {
      {1, 2, 3}, {4, 5, 6}, {7, 8, 9}, {1, 4, 7}, {2, 5, 8}, {3, 6, 9}, {1, 5, 9}, {3, 5, 7}};
  for (auto line : lines)
  {
    if (board[line[0]] == symbol && board[line[1]] == symbol &&
        board[line[2]] == symbol)
    {
      return true;
    }
  }
  return false;
}

int evaluate_board()
{
  if (checking_for_winner(comp_symbol))
    return 10;
  else if (checking_for_winner(player_symbol))
    return -10;
  else
    return 0; // Draw
}

bool moves_left()
{
  for (int i = 1; i <= 9; i++)
  {
    if (board[i] == 2)
      return true;
  }
  return false;
}

int minimax(int depth, int maxDepth, bool isAI)
{
  int score = evaluate_board();

  // If the game is over, return the score adjusted by depth
  if (score == 10)
    return score - depth; // AI prefers faster wins
  if (score == -10)
    return score + depth; // AI prefers slower losses

  if (!moves_left())
    return 0;

  if (isAI)
  {
    int best = -1000;

    for (int i = 1; i <= 9; i++)
    {
      if (board[i] == 2)
      {
        board[i] = comp_symbol;

        best = max(best, minimax(depth + 1, maxDepth, false));
        board[i] = 2; // While returing to previous depth undo the score
      }
    }
    return best;
  }
  else
  {
    int best = 1000;

    for (int i = 1; i <= 9; i++)
    {
      if (board[i] == 2)
      {
        board[i] = player_symbol;
        best = min(best, minimax(depth + 1, maxDepth, true));
        board[i] = 2;
      }
    }
    return best;
  }
}

int find_best_move()
{
  int bestVal = -1000;
  int bestMove = -1;

  for (int i = 1; i <= 9; i++)
  {
    if (board[i] == 2)
    {
      board[i] = comp_symbol;

      int moveVal = minimax(0, 4, false);

      board[i] = 2;

      if (moveVal > bestVal)
      {
        bestMove = i;
        bestVal = moveVal;
      }
    }
  }
  return bestMove;
}

int Make2()
{
  if (board[5] == 2)
    return 5;
  return (board[2] == 2) ? 2 : ((board[4] == 2) ? 4 : ((board[6] == 2) ? 6 : 8));
}

void Go(int n)
{
  board[n] = (turn % 2 != 0) ? player_symbol : comp_symbol;
  turn++;
}

int Posswin(int p)
{
  vector<vector<int>> lines = {
      {1, 2, 3}, {4, 5, 6}, {7, 8, 9}, {1, 4, 7}, {2, 5, 8}, {3, 6, 9},

      {1, 5, 9},
      {3, 5, 7}};

  for (auto line : lines)
  {
    int product = board[line[0]] * board[line[1]] * board[line[2]];
    if (product == p * p * 2)
    {
      for (int square : line)
      {
        if (board[square] == 2)
          return square;
      }
    }
  }
  return 0;
}

void printBoard()
{
  for (int i = 1; i <= 9; i++)
  {
    if (board[i] == 2)
      cout << ". ";
    else if (board[i] == 3)
      cout << "X ";
    else
      cout << "O ";

    if (i % 3 == 0)
      cout << endl;
  }
}

bool filled_board()
{
  for (int i = 1; i <= 9; i++)
  {
    if (board[i] == 2)
      return false;
  }
  return true;
}

void compmoves()
{
  int move = find_best_move();
  Go(move);
}

void PlayGame()
{
  char choice;
  do
  {
    cout << "Do you want to be X or O? Enter X or O: ";
    cin >> choice;
  } while (choice != 'X' && choice != 'x' && choice != 'O' && choice != 'o');

  player_symbol = (choice == 'O' || choice == 'o') ? 5 : 3;
  comp_symbol = (player_symbol == 3) ? 5 : 3;

  while (true)
  {
    printBoard();

    if (turn % 2 == 0)
    {
      cout << "Comp's turn..." << endl;
      compmoves();
    }
    else
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

    if (checking_for_winner(player_symbol))
    {
      printBoard();
      cout << "Congratulations! You won!" << endl;
      break;
    }
    else if (checking_for_winner(comp_symbol))
    {

      printBoard();
      cout << "Computer won! Better luck next time!" << endl;
      break;
    }

    if (filled_board())
    {
      printBoard();
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