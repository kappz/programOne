/*
Author: Peter O'Donohue
Creation Date: 05/22/17
Modification Date: 05/23/17
Description: This program will prompt you for input data to setup a board scenario for the game "Othello".
You'll first input how many of each color disk is in play, with the white disks representing you and the black disks
representing your opponent. The program will then prompt you to enter the row and column location of the white disks first,
followed by the location of each black disk. The program will finish by computing the move or moves that flip the most opposing
disks, and will then print the location of this disk and the resulting score.
*/

#include <iostream>
using namespace std;

const int SIZE = 8; // used to set the maximum row and column limits

// define class 'Board'
class Board {
	char board[SIZE][SIZE]; // each square holds 'b', 'w', or ' '
public:
	Board();  //initializes the board to all blanks
	bool inBound(int row, int col);
	bool legalMove(int row, int col);
	bool checkFlank(int deltaRow, int deltaCol, int currentRow, int currentCol, int& count);
	void setNumPieces();  // sets the number of white and black pieces each
	void setBoard();  // sets up the board with player input data
	void set(int row, int col, char color); // sets the square at (row, col) to color
	void displayBoard();  //  prints out the board
	int count(char color);  // returns the number of squares containing color
	int bestMove(int&  row, int& col, char color);  // returns the max resultOfMove(row,col)
	int resultOfMove(int row, int col, char color);  // returns the number of color - number of other color
													   // when a disk of color is placed at (row, col)
private:     
	int diskCount = 0;
	int blank = (int)' ';  // int to represent a blank space
	int rowNum = 0;  // stores row number from user given input
	int colNum = 0;  // stores column number from user given input
	int numBlack = 0;  // stores number of black spaces
	int numWhite = 0;  // stores number of white spaces
	int deltaRow = 0;
	int deltaCol = 0;
	int currentRow = 0;
	int currentCol = 0;
	int totalNumColors = 0;  // stores number of squares containing color
	char colorChoice = 'c';  // stores color of square 
};

// class Board member function definitions
Board::Board()
{
	// PRE: char array 'board' has been declared
	// POST: each element in array 'baord' is initialized with ' '.
	// Instructions are printed to user
	
	// display instructions
	cout << "This program will prompt you for the input data to setup a board scenario" << endl
		 << "for the game Othello. The board is 8x8, with a resulting 64 total spaces," << endl
		 << "and with the rows and columns numbered 0 - 7. You'll first input how many of" << endl
		 << "each color disk are in play, with the white disks representing you and" << endl
		 << "the black disks representing your opponent. The program will then prompt" << endl
		 << "you to enter the row and column location of the white disks first," << endl
		 << "followed by the location of each black disk. The program will finish" << endl
		 << "by computing the move or moves that flip the most opposing disks, and" << endl
		 << "will then print the location of this disk and the resulting score." << endl << endl;
		
	// read through array
	for (int i = 0; i < SIZE; ++i)
	{
		for (int j = 0; j < SIZE; ++j)
		{
			board[i][j] = ' ';  // intitializs array element to ' '
		}
	}
	return;
}
bool Board::inBound(int row, int col)
{
	if (row >= 0 && row <= 7 && col >= 0 && col <= 7)
		return true;
}
bool Board::legalMove(int row, int col)
{
	if (board[row][col] == ' ')
		return true;
}
bool Board::checkFlank(int deltaRow, int deltaCol, int currentRow, int currentCol, int& tempCount)
{
		while (inBound(currentRow + (1 * deltaRow), currentCol + (1 * deltaCol)))
			{
				if (board[currentRow + (1 * deltaRow)][currentCol + (1 * deltaCol)] == 'w')
					return true;
				else if (board[currentRow + (1 * deltaRow)][currentCol + (1 * deltaCol)] == 'b')
				{
					++tempCount;
					if (deltaRow < 0)
							--deltaRow;
					if (deltaRow > 0)
							++deltaRow;
					if (deltaCol < 0)
							--deltaCol;
					if (deltaCol > 0)
							++deltaCol;
				}
				if (board[currentRow + (1 * deltaRow)][currentCol + (1 * deltaCol)] == ' ')
						return false;
			}
			
		
}
int Board::count(char color)
{
	// PRE: a color choice of type char must be initialized and 
	// passed to the function as an argument
	// POST: total amount of squares containing color choice has 
	// been computed and returned to the main function

	if (color == 'w' || color == 'b' || color == ' ')  // verify user's choice is within scope
	{
		for (int i = 0; i < SIZE; ++i)  // read array
			for (int j = 0; j < SIZE; ++j)
			{
				if (board[i][j] == color)
					++totalNumColors;  // increments color amount if square contains user's color choice.
			}
		return totalNumColors;
	}
	else
	{
		cout << "Enter a valid color choice: ";
		cin >> color;
		return count(color);
	}
}
void Board::setNumPieces()
{
	// PRE: the object userInput has been created
	// POST: data provided by user has been verified to be withing scope
	// private data members are assigned these values

	int numWhiteSpaces = 0;  // stores user entered data for the total number of white disks
	int numBlackSpaces = 0;  // stores user entered data for the total number of black disks
	// prompt user for total number of white and black disks each
	cout << "Enter the total number of white and" << endl
		<< "black spaces, seperating each by a space: ";
	cin >> numWhiteSpaces >> numBlackSpaces;
	// verify data is within scope of legal data
	while ((numWhiteSpaces <= 0 || numWhiteSpaces > 64) || (numBlackSpaces <= 0 || numBlackSpaces > 64)
		|| (numWhiteSpaces + numBlackSpaces > 64))
	{
		cout << "ERROR: Invalid data input." << endl
			<< "Enter a valid amount of white and black spaces: ";  // prompts user to enter new data if current is not valid
		cin >> numWhiteSpaces >> numBlackSpaces;
	}
	// assigns user value to private data member after verifying it's within scope
	numWhite = numWhiteSpaces;
	numBlack = numBlackSpaces;
	return;
}
void Board::setBoard()
{
	// PRE: row and col values must be passed by the user
	// POST: row and col values have been verified to be withing scope
	// array element at row and col has been assigned a value of white black or blank

	int tempRow = 0;  // stores row value before verifying if value is legal
	int tempCol = 0;  // stores column value before verifying if value is legal

	// prompt user for first input data

	for (int i = 0; i < numWhite + numBlack; ++i)
	{
		// prompt for location of disk
		cout << "Enter the row and column number for the" << endl
			 << "location of a disk, seperating each by a space: ";
		cin >> tempRow >> tempCol;
		while ((7 < tempRow || tempRow < 0) || (7 < tempCol || tempCol < 0)
			|| (Board::board[(SIZE - 1) - tempRow][tempCol] != ' '))
		{
			cout << "Invalid row or column number." << endl << "Enter the correct row and column number: ";
			cin >> tempRow >> tempCol;
		}

		if (i < numWhite)
		{
			rowNum = tempRow;
			colNum = tempCol;
			Board::board[(SIZE - 1) - rowNum][colNum] = 'w';
		}
		else if (i >= numWhite)
		{
			rowNum = tempRow;
			colNum = tempCol;
			Board::board[(SIZE - 1) - rowNum][colNum] = 'b';
		}
	}
	return;
}
void Board::displayBoard()
{
	// PRE: user has initialized board array
	// POST: board array has been read and printed to user

	// print each element of array post user intitialization
	for (int i = 0; i < SIZE; ++i)
	{
		cout << endl;
		for (int j = 0; j < SIZE; ++j)
		{
			if (board[i][j] == 32)
				cout << 0 << "   ";
			else
				cout << board[i][j] << "   ";
		}
		cout << endl;
	}
}
void Board::set(int row, int col, char color = ' ')
{
	// PRE: the values of row, col, and color have been passed
	// passed through the function as arguments after being defined
	// POST: the element in array 'board' at the designated location
	// at 'row' and 'col' has been intitialized with color

	// verify user choice for column, row, and color are within scope
	if ((row <= 7 && row >= 0) && (col <= 7 && col >= 0) && ( (color == 'w') || (color == 'b') || (color == ' ') ) )
	{
		rowNum = row;
		colNum = col;
		colorChoice = color;
	}
	
	if (colorChoice == 'w')  // if caller chose white set that square to white
	{
		Board::board[(SIZE - 1) - rowNum][colNum] = 'w';
	}
	else if (colorChoice == 'b')  // if caller chose black then set the square to black
	{
		Board::board[(SIZE - 1) - rowNum][colNum] = 'b';
	}
	else if (colorChoice == ' ')  // if caller chose blank then set the square to be blank
	{
		Board::board[(SIZE - 1) - rowNum][colNum] = ' ';
	}
	else// if value is outside of scope
	{
		cout << "ERROR: row, column, and or your color choice are invalid." << endl
			<< "Enter the row, column, and choice of color: ";
		cin >> row >> col >> color;
		color = tolower(color);
		Board::set(row, col, color);
	}
}
int Board::resultOfMove(int row, int col, char color)
{
	int moveCount = 0;
	int tempCount = 0;
	for (int i = -1; i <= 1; ++i)
		for (int j = -1; j <= 1; ++j)
		{
			if (board[row + (1 * i)][col + (1 * j)] == color)
			{
				++tempCount;
				currentRow = row + (1 * i);
				currentCol = col + (1 * j);
				deltaRow = 1 * i;
				deltaCol = 1 * j;
				if (checkFlank(deltaRow, deltaCol, currentRow, currentCol, tempCount))
				{
					moveCount += tempCount;
					tempCount = 0;
				}
				else
					tempCount = 0;
				 
			}
		}
	cout << moveCount << " ";
	return moveCount;
}
int Board::bestMove(int& row, int& col, char color)
{
	int numBlack = 0;
	int maxNumBlack = 0;
	for (int i = 0; i < SIZE; ++i)
		for (int j = 0; j < SIZE; ++j)
		{
			numBlack = resultOfMove(i, j, color);
			if (numBlack >= maxNumBlack)
			{
				maxNumBlack = numBlack;
				row = i;
				col = j;
			}
		}
	
	cout << maxNumBlack << " ";
	return maxNumBlack;
}

int main()
{
	int total = 0;
	int finalTotal = 0;
	int bestRow = 0;
	int bestCol = 0;
	int numBlack = 0;
	int numWhite = 0;
	Board userInput;  // declare object of type board to store user's input
	userInput.setNumPieces(); // set the number of white and black pieces
	userInput.setBoard();  // setup the board with user provided data
	numWhite = userInput.count('w');
	numBlack = userInput.count('b');
	//userInput.displayBoard();  // display board to user
	cout << "Finished numBlack and numWhite" << endl;
	total = userInput.bestMove(bestRow, bestCol, 'b');
	cout << "Finished best move function" << endl;
	numBlack = numBlack - total;
	numWhite = numWhite + total;
	finalTotal = numWhite - numBlack;
	cout << bestRow << " " << bestCol << " " << finalTotal << endl;
	cout << "Thanks!";
	system("pause");
	return 0;
}
