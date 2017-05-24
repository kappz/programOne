/*
Author: Peter O'Donohue
Creation Date: 05/22/17
Modification Date: 05/23/17
Description: This program will prompt you for input data to setup a board scenario for the game "Othello".
The program will then compute the optimal move or moves, and output their location to you.
*/

#include <iostream>
#include <iomanip>
using namespace std;

const int SIZE = 8; // used to set the maximum row and column limits

// define class 'Board'
class Board {
	char board[SIZE][SIZE]; // each square holds 'b', 'w', or ' '
public:

	Board();  //initializes the board to all blanks
	int count(char color);  // returns the number of squares containing color
	void setNumPieces();  // sets the number of white and black pieces each
	void setBoard();
	void set(int row, int col, char color); // sets the square at (row, col) to color
	void displayBoard();
	int resultOfMove(int row, int col, char color);  // returns the number of color - number of other color
													   // when a disk of color is placed at (row, col)
	int bestMove(int & row, int &col, char color);  // returns the max resultOfMove(row,col)
private:     
	int w = (int)'w';  // value to represent white space
	int b = (int)'b'; // value to represent a black space
	int blank = (int)' ';  // int to represent a blank space
	int rowNum = 0;  // stores row number from user given input
	int colNum = 0;  // stores column number from user given input
	int numBlack = 0;  // stores number of black spaces
	int numWhite = 0;  // stores number of white spaces
	char colorChoice = 'c';  // stores color of square 
	int totalNumColors = 0;  // stores number of squares containing color
};

// class Board member function definitions

Board::Board()
{
	// PRE: char array 'board' has been declared
	// POST: each element in array 'baord' is initialized with ' '.
	// Instructions are printed to user
	
	// display instructions
	cout << "Hello, This program will prompt you for input data to setup" << endl
		<< "a board scenario for the game 'Othello'. It will then compute" << endl
		<< "the optimal move or moves, and output their locations to you." << endl << endl;

	for (int i = 0; i < SIZE; ++i)
	{
		for (int j = 0; j < SIZE; ++j)
		{
			board[i][j] = ' ';  // intitializs array element to ' '
		}
	}
	return;
}

int Board::count(char color)
{
	// PRE: a color choice of type char must be initialized and 
	// passed to the function as an argument
	// POST: total amount of squares containing color choice has 
	// been computed and returned to the main function

	if (color == 'w' || color == 'b' || color == ' ')
	{
		for (int i = 0; i < SIZE; ++i)  // search entire array
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
	// PRE: values for function arguments have been defined by user
	// POST: data provided by user has been verified to be legal
	// private data members are assigned these values

	int numWhiteSpaces = 0;  // stores user entered data for the total number of white spaces
	int numBlackSpaces = 0;  // stores user entered data for the total number of black spaces
	// prompt user for total number of white and black spaces each
	cout << "Please enter the total number of white and" << endl
		<< "black spaces, seperating each by a space: " << endl;
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
	// PRE: row and col values must be declared by the user
	// POST: row and col values have been verified to be legal data values
	// array element at row and col has been given a value

	int tempRow = 0;  // stores row value before verifying if value is legal
	int tempCol = 0;  // stores column value before verifying if value is legal

	// prompt user for first input data

	for (int i = 0; i < numWhite + numBlack; ++i)
	{
		cout << "Enter the row and column number for the location of a piece: " << endl
			<< "your first input (i.e. 2, 3): ";
		cin >> tempRow >> tempCol;
		while ( (7 < tempRow || tempRow < 0 ) || ( 7 < tempCol || tempCol < 0 ) 
			   || (Board::board[(SIZE - 1) - tempRow][tempCol] != ' ') )
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
	// PRE: the row, column, and color variables must be initialized
	// by the user and passed through the function as arguments
	// POST: the element in array 'board' at the designated location
	// at 'row' and 'col' has been intitialized with char 'color'

	// verify user choice for column, row, and color are within scope
	if ((row <= 7 && row >= 0) && (col <= 7 && col >= 0) && (color == 'w' || color == 'b' || color == ' '))
	{
		rowNum = row;
		colNum = col;
		colorChoice = color;
	}
	switch (colorChoice)
	{
	case ('w'):  // if caller chose white set that square to white
	{
		Board::board[(SIZE - 1) - rowNum][colNum] = 'w';
		break;
	}
	case ('b'):  // if caller chose black then set the square to black
	{
		Board::board[(SIZE - 1) - rowNum][colNum] = 'b';
		break;
	}
	case (' '):  // if caller chose blank then set the square to be blank
	{
		Board::board[(SIZE - 1) - rowNum][colNum] = ' ';
		break;
	}
	default: // if value is outside of scope
	{
		cout << "ERROR: row, column, and or your color choice are invalid." << endl
			<< "Enter the row, column, and choice of color: ";
		cin >> row >> col >> color;
		color = tolower(color);
		Board::set(row, col, color);
	}
	}
}

int main()
{
	int total = 0;
	Board userInput;  // declare object of type board to store user's input
	userInput.setNumPieces(); // set the number of white and black pieces
	userInput.setBoard();  // setup the board with user provided data
	userInput.displayBoard();  // display board to user
	system("pause");
	return 1;
}
