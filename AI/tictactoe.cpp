#include <iostream>
#include <vector>

using namespace std;

vector<int> gameBoard(10, 2);
int turnCount = 1;
int playerSymbol;
int computerSymbol;

int findOptimalMove()
{
  if (gameBoard[5] == 2)
    return 5;
  return (gameBoard[2] == 2) ? 2 : ((gameBoard[4] == 2) ? 4 : ((gameBoard[6] == 2) ? 6 : 8));
}

void makeMove(int position)
{
  gameBoard[position] = (turnCount % 2 != 0) ? playerSymbol : computerSymbol;
  turnCount++;
}

int findWinningMove(int symbol)
{
  vector<vector<int>> winningLines = {
      {1, 2, 3}, {4, 5, 6}, {7, 8, 9}, {1, 4, 7}, {2, 5, 8}, {3, 6, 9}, {1, 5, 9}, {3, 5, 7}};

  for (auto line : winningLines)
  {
    int product = gameBoard[line[0]] * gameBoard[line[1]] * gameBoard[line[2]];
    if (product == symbol * symbol * 2)
    {
      for (int square : line)
      {
        if (gameBoard[square] == 2)
          return square;
      }
    }
  }
  return 0;
}

void displayBoard()
{
  for (int i = 1; i <= 9; i++)
  {
    if (gameBoard[i] == 2)
      cout << ". ";
    else if (gameBoard[i] == 3)
      cout << "X ";
    else
      cout << "O ";

    if (i % 3 == 0)
      cout << endl;
  }
}

void computerMove()
{
  if (turnCount == 1)
  {
    makeMove(1);
  }
  else if (turnCount == 2)
  {
    if (gameBoard[5] == 2)
      makeMove(5);
    else
      makeMove(1);
  }
  else if (turnCount == 3)
  {
    if (gameBoard[9] == 2)
      makeMove(9);
    else
      makeMove(3);
  }
  else
  {
    int winningMove = findWinningMove(computerSymbol);
    if (winningMove != 0)
      makeMove(winningMove);
    else
    {
      int blockingMove = findWinningMove(playerSymbol);
      if (blockingMove != 0)
        makeMove(blockingMove);
      else
        makeMove(findOptimalMove());
    }
  }
}

bool checkWinner(int symbol)
{
  vector<vector<int>> winningLines = {
      {1, 2, 3}, {4, 5, 6}, {7, 8, 9}, {1, 4, 7}, {2, 5, 8}, {3, 6, 9}, {1, 5, 9}, {3, 5, 7}};

  for (auto line : winningLines)
  {
    if (gameBoard[line[0]] == symbol && gameBoard[line[1]] == symbol && gameBoard[line[2]] == symbol)
    {
      return true;
    }
  }

  return false;
}

bool isBoardFull()
{
  for (int i = 1; i <= 9; i++)
  {
    if (gameBoard[i] == 2)
      return false;
  }
  return true;
}

void startGame()
{
  char playerChoice;
  do
  {
    cout << "Do you want to be X or O? Enter X or O: ";
    cin >> playerChoice;
  } while (playerChoice != 'X' && playerChoice != 'x' && playerChoice != 'O' && playerChoice != 'o');

  playerSymbol = (playerChoice == 'O' || playerChoice == 'o') ? 5 : 3;
  computerSymbol = (playerSymbol == 3) ? 5 : 3;

  while (true)
  {
    displayBoard();

    if (turnCount % 2 != 0)
    {
      int playerMove;
      cout << "Your turn (enter a number 1-9): ";
      cin >> playerMove;
      if (playerMove < 1 || playerMove > 9 || gameBoard[playerMove] != 2)
      {
        cout << "Invalid move, please try again." << endl;
        continue;
      }
      makeMove(playerMove);
    }
    else
    {
      cout << "Computer's turn..." << endl;
      computerMove();
    }

    if (checkWinner(playerSymbol))
    {
      displayBoard();
      cout << "Congratulations! You won!" << endl;
      break;
    }
    else if (checkWinner(computerSymbol))
    {
      displayBoard();
      cout << "Computer won! Better luck next time!" << endl;
      break;
    }
    if (isBoardFull())
    {
      displayBoard();
      cout << "It's a draw!" << endl;
      break;
    }
  }
}

int main()
{
  startGame();
  return 0;
}