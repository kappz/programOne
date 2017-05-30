/*
Author: Peter O'Donohue
Creation Date: 05/22/17
Modification Date: 05/29/17
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
	bool inBound(int row, int col);  // verifies array bounds aren't exceeded
	bool checkFlank(int deltaRow, int deltaCol, int currentRow, int currentCol, int& count);  // checks and computes flanks
	void setNumPieces();  // sets the number of white and black pieces each
	void set();  // sets up the board with player input data
	int count(char color);  // returns the number of squares containing color
	int bestMove(int&  row, int& col, char color);  // returns the max resultOfMove(row,col)
	int resultOfMove(int row, int col, char color);  // computes result of placing a white disk at a legal square
private:     
	int rowNum = 0;  // stores row number from user given input
	int colNum = 0;  // stores column number from user given input
	int numBlack = 0;  // stores number of black spaces
	int numWhite = 0;  // stores number of white spaces
	int deltaRow = 0;  // stores change in row
	int deltaCol = 0;  // stores change in column
	int currentRow = 0;  // stores current row
	int currentCol = 0;  // stores current column
	char colorChoice = ' ';  // stores color of square 
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
	// PRE: row and col have been initialized with a value 
	// POST: row and col have been verified to be within bounds of array 'board'

	if (row >= 0 && row <= 7 && col >= 0 && col <= 7) // verifies both row and col are withing array dimensions
		return true;
	else
		return false;
}

bool Board::checkFlank(int deltaRow, int deltaCol, int currentRow, int currentCol, int& tempCount)
{
	// PRE: resultOfMove function has been called and all arguements have been initialized
	// POST: a column, row, or diagonal has been determined to be either true or false
	++tempCount;
	if (deltaRow == -1 && deltaCol == -1) // checks bottom left diagonal of placement
	{
		while (inBound(currentRow + (1 * deltaRow), currentCol + (1 * deltaCol)))  // verify function stays within array bounds
		{
			if (board[currentRow + (1 * deltaRow)][currentCol + (1 * deltaCol)] == 'w')  // returns true if a 'w' is encountered
				return true;
			else if (board[currentRow + (1 * deltaRow)][currentCol + (1 * deltaCol)] == 'b')  // increments counter if square is 'b'
			{
				++tempCount;
				--deltaRow;
				--deltaCol;
			}
			else 
				return false;
		}
	}

	else if (deltaRow == -1 && deltaCol == 0)  // checks row below placement
	{
		while (inBound(currentRow + (1 * deltaRow), currentCol + (1 * deltaCol)))  // verify function stays within array bounds
		{
			if (board[currentRow + (1 * deltaRow)][currentCol + (1 * deltaCol)] == 'w') // returns true if a 'w' is encountered
				return true;
			else if (board[currentRow + (1 * deltaRow)][currentCol + (1 * deltaCol)] == 'b')  // increments counter if square is 'b'
			{
				++tempCount;
				--deltaRow;
			}
			else 
				return false;
		}
	}

	else if (deltaRow == -1 && deltaCol == 1)  // check bottom right diagonal of placement
	{
		while (inBound(currentRow + (1 * deltaRow), currentCol + (1 * deltaCol)))  // verify function stays within array bounds
		{
			if (board[currentRow + (1 * deltaRow)][currentCol + (1 * deltaCol)] == 'w') // returns true if a 'w' is encountered
				return true;
			else if (board[currentRow + (1 * deltaRow)][currentCol + (1 * deltaCol)] == 'b')  // increments counter if square is 'b'
			{
				++tempCount;
				--deltaRow;
				++deltaCol;
			}
			else 
				return false;
		}
	}

	else if (deltaRow == 0 && deltaCol == -1)  // checks left side row of placement
	{
		while (inBound(currentRow + (1 * deltaRow), currentCol + (1 * deltaCol)))  // verify function stays within array bounds
		{
			if (board[currentRow + (1 * deltaRow)][currentCol + (1 * deltaCol)] == 'w') // returns true if a 'w' is encountered
				return true;
			else if (board[currentRow + (1 * deltaRow)][currentCol + (1 * deltaCol)] == 'b')  // increments counter if square is 'b'   
			{
				++tempCount;
				--deltaCol;
			}
			else 
				return false;
		}
	}

	else if (deltaRow == 0 && deltaCol == 1)  // checks right side row of placement
	{
		while (inBound(currentRow + (1 * deltaRow), currentCol + (1 * deltaCol)))  // verify function stays within array bounds
		{
			if (board[currentRow + (1 * deltaRow)][currentCol + (1 * deltaCol)] == 'w') // returns true if a 'w' is encountered
				return true;
			else if (board[currentRow + (1 * deltaRow)][currentCol + (1 * deltaCol)] == 'b')  // increments counter if square is 'b'
			{
				++tempCount;
				++deltaCol;
			}
			else 
				return false;
			++deltaCol;
		}
	}

	else if (deltaRow == 1 && deltaCol == -1)  // checks top left diagonal of placement
	{
		while (inBound(currentRow + (1 * deltaRow), currentCol + (1 * deltaCol)))  // verify function stays within array bounds
		{
			if (board[currentRow + (1 * deltaRow)][currentCol + (1 * deltaCol)] == 'w') // returns true if a 'w' is encountered
				return true;
			else if (board[currentRow + (1 * deltaRow)][currentCol + (1 * deltaCol)] == 'b')  // increments counter if square is 'b'
			{
				++tempCount;
				++deltaRow;
				--deltaCol;
			}
			else 
				return false;
		}
	}
	
	else if (deltaRow == 1 && deltaCol == 0)  // checks column above placement
	{
		while (inBound(currentRow + (1 * deltaRow), currentCol + (1 * deltaCol)))  // verify function stays within array bounds
		{
			if (board[currentRow + (1 * deltaRow)][currentCol + (1 * deltaCol)] == 'w') // returns true if a 'w' is encountered
				return true;
			else if (board[currentRow + (1 * deltaRow)][currentCol + (1 * deltaCol)] == 'b')  // increments counter if square is 'b'
			{
				++tempCount;
				++deltaRow;
			}
			else 
				return false;
		}
	}

	else if (deltaRow == 1 && deltaCol == 1)  // checks top right diagonal of placement
	{
		while (inBound(currentRow + (1 * deltaRow), currentCol + (1 * deltaCol)))  // verify function stays within array bounds
		{
			if (board[currentRow + (1 * deltaRow)][currentCol + (1 * deltaCol)] == 'w') // returns true if a 'w' is encountered
				return true;
			else if (board[currentRow + (1 * deltaRow)][currentCol + (1 * deltaCol)] == 'b')  // increments counter if square is 'b'
			{
				++tempCount;
				++deltaRow;
				++deltaCol;
			}
			else 
				return false;
		}
	}
	else
		return false;
}
int Board::count(char color)
{
	// PRE: a color choice of type char must be initialized and 
	// passed to the function as an argument
	// POST: total amount of squares containing color choice has 
	// been computed and returned to the main function

	if (color == 'w' || color == 'b' || color == ' ')  // verify user's choice is within scope
	{
		int numColor = 0;
		int totalNumColors = 0;  // stores number of squares containing color
		totalNumColors = numColor;
		for (int i = 0; i < SIZE; ++i)  // read array
			for (int j = 0; j < SIZE; ++j)
			{
				if (board[i][j] == color)
					++totalNumColors;
				// increments color amount if square contains user's color choice.
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
void Board::set()
{
	// PRE: row and col values must be passed by the user
	// POST: row and col values have been verified to be withing scope
	// array element at row and col has been assigned a value of white black or blank

	int tempRow = 0;  // stores row value before verifying if value is legal
	int tempCol = 0;  // stores column value before verifying if value is legal

	// prompt user for first input data


		for (int i = 0; i < numWhite; ++i)
		{
			cout << "Enter the row and column number for a white disk: ";
			cin >> tempRow >> tempCol;
			// verifiy placement is withing bound
			while ((!inBound(tempRow, tempCol)) || (Board::board[(SIZE - 1) - tempRow][tempCol] != ' '))
			{
				cout << "Invalid row or column number." << endl << "Enter the correct row and column number: ";
				cin >> tempRow >> tempCol;
			}
			rowNum = tempRow;
			colNum = tempCol;
			Board::board[(SIZE - 1) - rowNum][colNum] = 'w'; // adjust placement row location for board
		}
		for (int j = 0; j < numBlack; ++j)
		{
			cout << "Enter the row and column number for a black disk: ";
			cin >> tempRow >> tempCol;
			rowNum = tempRow;
			colNum = tempCol;
			// verifiy placement is withing bound
			while ((!inBound(tempRow, tempCol)) || (Board::board[(SIZE - 1) - tempRow][tempCol] != ' '))
			{
				cout << "Invalid row or column number." << endl << "Enter the correct row and column number: ";
				cin >> tempRow >> tempCol;
			}
			rowNum = tempRow;
			colNum = tempCol;
			Board::board[(SIZE - 1) - rowNum][colNum] = 'b';  // adjust placement row location for board
		}
	
	return;
}
int Board::resultOfMove(int row, int col, char color)
{
	// PRE: bestMove function has been called
	// nested for loop has been executed and values are passed through arguments above
	// color has default argument of 'b'
	// POST: maximum value of placement has been determined and passed back to bestMove function for comparison
	int moveCount = 0;
	int tempCount = 0;
	for (int i = -1; i <= 1; ++i)
	{
		for (int j = -1; j <= 1; ++j)
		{
			if (board[row + (1 * i)][col + (1 * j)] == color)  // if adjacent adjacent square contains a black disk
			{
				
				currentRow = row + (1 * i);  // set current row to adjacent square 
				currentCol = col + (1 * j);  // ste current col to adjacent square
				deltaRow = 1 * i;  // set change of row
				deltaCol = 1 * j;  // set change of col
				
			if (checkFlank(deltaRow, deltaCol, currentRow, currentCol, tempCount))  // check each adacent location for flank
			{
				moveCount += tempCount;
				tempCount = 0;
			}
			else
				tempCount = 0;
			}
		}
	}
	//cout << moveCount;
	return moveCount;
}
int Board::bestMove(int& row, int& col, char color)
{
	// PRE: function has been called from main function
	// functions checkFlank and resultOfMove have been called, executed, and returned their final values
	// POST: best placement has been determined and returned to main function for further execution
	int numBlack = 0;  // stores number of black disks flipped after a placement
	int maxNumBlack = 0; // stores maximum number of black disks flipped out of all possible placements
	for (int i = 0; i < SIZE; ++i)
	{
		for (int j = 0; j < SIZE; ++j)
		{
			if (board[i][j] == ' ')
			{
				numBlack = resultOfMove(i, j, color);
				
				if (numBlack == maxNumBlack && (row < i))  // sets minimum row if multiple same results have been determined
				{
					maxNumBlack = numBlack;
					row = i;
				}
				if (numBlack == maxNumBlack && (col < j)) // sets minimum col if multiple same results have been determined
				{
					maxNumBlack = numBlack;
					col = col;
				}
			
				if (numBlack > maxNumBlack)
				{
					maxNumBlack = numBlack;
					row = i;
					col = j;
				}
			}
		}
	}
	return maxNumBlack;
} 

int main()
{
	int total = 0;  // stores total black disks flipped
	int finalTotal = 0;  // stores result of white disks - black disks
	int bestRow = 0;  // stores row location for best placement
	int bestCol = 0;  // stores column location for best placement
	int numBlack = 0;  // stores number of black disks placed by user
	int numWhite = 0;  // stores number of white disks placed by user
	Board userInput;  // declare object of type board to store user's input
	userInput.setNumPieces(); // set the number of white and black pieces
	userInput.set();  // setup the board with user provided data 
	numWhite = userInput.count('w');  // computes number of white disks placed by user
	numBlack = userInput.count('b');  // computes number of black disks placed by user
	total = userInput.bestMove(bestRow, bestCol, 'b');  // computes maximum number of black disks flipped 
	numBlack = numBlack - total;  // computes final number of black disks after best placement has been determined
	numWhite = (numWhite + 1) + total; // computes final number of white disks after best placement has been determined
	finalTotal = numWhite - numBlack;  // computes final score
	cout << (SIZE -1) - bestRow << " " << bestCol << " " << finalTotal << endl;  // print results
	system("pause");
	return 0;
}
