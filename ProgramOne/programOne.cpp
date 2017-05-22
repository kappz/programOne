/*
Author: Peter O'Donohue
Creation Date: 05/22/17
Modification Date: 05/22/17
Description: This program will display to you a situation from the board game "Othello".
In the situation, the white pieces represent you, and the black pieces represent
your opponent. The program will then determine what the optimal placement is for the
given situation, and will finish by outputing that position to you.
*/

#include <iostream>
using namespace std;

// define class board

const int SIZE = 64; // used to set the maximum row and column limits

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
	int numColor = 0;  // stores number of squares containing color
	int row = 0;  // stores row number from user given input
	int col = 0;  // stores column number from user given input
	char color = ' ';  // stores color of square 
};

// class Board member function definitions
Board::Board()
{
	// PRE: char array 'board' has been declared
	// POST: each element in array 'baord' is initialized with ' '.
	
	for (int i = 0; i < SIZE; ++i)   // search entire array
		for (int j = 0; j < SIZE; ++j)
		{
			board[i][j] = ' ';  // intitializs array element to ' '
		}
	return;
}

int Board::count(char color)
{
	// PRE: a color choice of type char must be initialized and 
	// passed to the function as an argument
	// POST: total amount of squares containing color choice has 
	// been computed and returned to the main function

	int totalColors = 0;  // stores total amount of squares containing color

	for (int i = 0; i < SIZE; ++i)  // search entire array
		for (int j = 0; j < SIZE; ++j)
		{
			if ((board[i][j] == 'W') || (board[i][j] == 'B')) 
				++totalColors;  // increments color amount if square contains user's color choice.
		}
	return totalColors;
}

void Board::set(int row, int col, char color)
{
	// PRE: the row, column, and color variables must be initialized
	// by the user and passed through the function as arguments
	// POST: the element in array 'board' at the designated location
	// at 'row' and 'col' has been intitialized with char 'color'

	if ((row <= 64 && col <= 64) && (color == 'W' || 'B'))
		Board::board[row][col] = color;
	else
		cout << "ERROR: row, column, and or your color choice are invalid." << endl;
}

int main()
{
	system("pause");
	return 1;
}