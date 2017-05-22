/*
Author: Peter O'Donohue
Creation Date: 05/22/17
Modification Date: 05/22/17
Description: This program will prompt you for input data to setup a board scenario for the game "Othello".
The program will then compute the optimal move, and output it's location to you.
given situation, and will finish by outputing that position to you.
*/

#include <iostream>
using namespace std;

const int SIZE = 8; // used to set the maximum row and column limits

// define class 'Board'
class Board {
	char board[SIZE][SIZE]; // each square holds 'b', 'w', or ' '
public:
	Board();  //initializes the board to all blanks
	int count(char color);  // returns the number of squares containing color
	void set(int row, int col, char color); // sets the square at (row, col) to color
	int resultOfMove(int row, int col, char color);  // returns the number of color - number of other color
													   // when a disk of color is placed at (row, col)
	int bestMove(int & row, int &col, char color);  // returns the max resultOfMove(row,col)
private:                                           // when a disk of color is placed at (row, col)
	int rowNum;  // stores row number from user given input
	int colNum;  // stores column number from user given input
	char colorChoice;  // stores color of square 
	int totalNumColors;  // stores number of squares containing color
};

// class Board member function definitions
Board::Board()
{
	// PRE: char array 'board' has been declared
	// POST: each element in array 'baord' is initialized with ' '.
	
	for (int i = 0; i < SIZE; ++i)
	{
		cout << endl; // DELETE
		for (int j = 0; j < SIZE; ++j)
		{
			board[i][j] = 'i';  // intitializs array element to ' '
			cout << board[i][j] << " ";
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

	for (int i = 0; i < SIZE; ++i)  // search entire array
		for (int j = 0; j < SIZE; ++j)
		{
			if ((board[SIZE - i][j] == 'W') || (board[SIZE - i][j] == 'B')) 
				++totalNumColors;  // increments color amount if square contains user's color choice.
		}
	return totalNumColors;
}

void Board::set(int row, int col, char color)
{
	// PRE: the row, column, and color variables must be initialized
	// by the user and passed through the function as arguments
	// POST: the element in array 'board' at the designated location
	// at 'row' and 'col' has been intitialized with char 'color'

	if ((row <= 64 && row >= 0) && (col <= 64 && col >= 0) && (color == 'W' || color == 'B'))
	{
		rowNum = row;
		colNum = col;
		colorChoice = color;
		Board::board[(SIZE - 1) - rowNum][colNum] = colorChoice;
		for (int i = 0; i < SIZE; ++i)  // search entire array
		{
			cout << endl;
			for (int j = 0; j < SIZE; ++j)
			{
				cout << board[i][j] << "  ";
			}
			cout << endl;
		}
	}
	else
	{
		cout << "ERROR: row, column, and or your color choice are invalid." << endl
			<< "Enter the row, column, and choice of color: ";
		cin >> row >> col >> color;
		color = toupper(color);
		Board::set(row, col, color);
	}
}

// function declarations
void exit();  // displays exit message to user
void instructions(); // displays instructions to user

int main()
{
	int row = 0;
	int col = 0;
	int numWhiteSpaces = 0;
	int numBlackSpaces = 0;
	char color = ' ';
	Board userInput;  // declare object of type board to store user's input
	
	instructions();  // display instructions to user

	cout << "Please enter the total number of white and" << endl
		 << "black spaces, seperating each by a space: " << endl;
	cin >> numWhiteSpaces >> numBlackSpaces;
	
	while ((numWhiteSpaces < 0 || numWhiteSpaces > 64) || (numBlackSpaces < 0 || numBlackSpaces > 64)
		 || (numWhiteSpaces + numBlackSpaces > 64))
	{
		cout << "ERROR: Invalid data input." << endl
			<< "Enter a valid amount of white and black spaces: ";
		cin >> numWhiteSpaces >> numBlackSpaces;
	}

	// prompt user for first input data
	cout << "Enter the row, column, and color choice for" << endl
		 << "your first input (i.e. 55, 23, B): ";
	cin >> row >> col >> color;
	color = toupper(color);
	userInput.set(row, col, color);

	for (int i = 1; i < numWhiteSpaces + numBlackSpaces; ++i)
	{
		cout << "Enter the row, column, and color choice for" << endl
			 << "your next input (i.e. 55, 23, B): ";
		cin >> row >> col >> color;
		color = toupper(color);
		userInput.set(row, col, color);
	}
	system("pause");
	return 1;
}

// function definitions
void instructions()
{
	// PRE: the main function has executed and the function 'instructions' has 
	// been defined
	// POST: A message with instructions on how to use the program has 
	// been displayed to user.

	// display instructions
	cout << "Hello, This program will prompt you for input data to setup" << endl
		<< "a board scenario for the game 'Othello'. It will then compute" << endl
		<< "the optimal move or moves, and output their locations to you." << endl;
	return;
}