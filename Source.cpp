/*---------------------------------------------------------------------------------------------------------------------------------------------
  Game 1024
  Class: CS 141, Spring 2019. Lecture 9 AM
  System: Visual Studio 2019
  Author: Omar Flores

  ---------------------------------------------------------------------------------------------------------------------------------------------
*/
//  prog5_1024.cpp
//     Text version of the game 1024, a variant of 2048 available online at:
//        http://gabrielecirulli.github.io/2048/
//     Object of game is to combine number tiles with the same value, accumulating
//     points as the game progresses, to try and create the tile with the value 1024.
//     Each move consists of sliding pieces to the left, up, right or down.
/*  Running program looks like:

	 Dale Reed
	 UIC CS 141, Spring 2019
	 Welcome to 1024.
	 This program is based off of Gabriele Cirulli's game online at
	 bit.ly/great2048

	 For each move enter a direction as a letter key, as follows:
		 W
	   A S D
	 where A=left,W=up, D=right and S=down.

	 After a move, when two identical valued tiles come together they
	 join to become a new single tile with the value of the sum of the
	 two originals. This value gets added to the score.  On each move
	 one new randomly chosen value of 2 or 4 is placed in a random open
	 square.  User input of x exits the game.

	 Game ends when you reach 1024.

	 Score: 0
	 .     4     .     .

	 .     .     .     .

	 .     .     4     .

	 .     .     .     .

	 1. Your move: a

	 Score: 0
	 4     .     .     .

	 .     .     .     .

	 4     .     .     .

	 .     .     2     .

	 2. Your move: a
	 .
	 .
	 .
*/

#include <iostream>     // For std::cin, std::cout, std::endl;
#include <iomanip>      // used for setting output field size using setw
#include <cstdlib>      // For rand()
#include <cmath>
  // So we don't need std:: in front of every std::cin, std::cout, and std::endl;


const int MaxBoardSize = 12;          // Max number of squares per side
const int MaxTileStartValue = 1024;   // Max tile value to start out on a 4x4 board


//--------------------------------------------------------------------
// Display Instructions
void displayInstructions()
{
		std::cout << "Welcome to 1024. \n"
		<< "  \n"
		<< "For each move enter a direction as a letter key, as follows: \n"
		<< "    W    \n"
		<< "  A S D  \n"
		<< "where A=left,W=up, D=right and S=down. \n"
		<< "  \n"
		<< "After a move, when two identical valued tiles come together they    \n"
		<< "join to become a new single tile with the value of the sum of the   \n"
		<< "two originals. This value gets added to the score.  On each move    \n"
		<< "one new randomly chosen value of 2 or 4 is placed in a random open  \n"
		<< "square.  User input of x exits the game.                            \n"
		<< "  \n";
}//end displayInstructions()


//--------------------------------------------------------------------
// Place a randomly selected 2 or 4 into a random open square on
// the board.
void placeRandomPiece(int board[], int squaresPerSide)
{
	// Randomly choose a piece to be placed (2 or 4)
	int pieceToPlace = 2;
	if (rand() % 2 == 1) {
		pieceToPlace = 4;
	}

	// Find an unoccupied square that currently has a 0
	int index;
	do {
		index = rand() % (squaresPerSide * squaresPerSide);
	} while (board[index] != 0);

	// board at position index is blank, so place piece there
	board[index] = pieceToPlace;
}//end placeRandomPiece()

void fillBoard(int board[], int size) {

	for (int i = 0; i < size; i++) {

		board[i] = 0;
	}

}// end FillBoard()

void displayAsciiBoard(int board[], int squaresPerSide, int score) {

	std::cout << "\n\tScore: " << score << std::endl;;

	for (int i = 0; i < squaresPerSide * squaresPerSide; i++) {

		// Send output to the next line at the beginning of each new table row

		if (i % squaresPerSide == 0 && i > 0) {

			std::cout << std::endl << std::endl;;

		}

		// Display either '.' or the number

		std::cout << std::setw(i % squaresPerSide == 0 ? 9 : 6);

		if (board[i] == 0) {

			std::cout << ".";
		}

		else {
			std::cout << board[i];

		}
	}
	std::cout << std::endl;;
	std::cout << std::endl;;
}

bool shiftLeft(int board[], int squaresPerSide, int& score) { // Returns the validity of a left move, true/false
	bool valid = false;
	// Last merge is used so that we don't double merge the same number twice on the same play by keeping track of the index
	// that was last merged
	int lastMerge = 0;
	// Go through all rows
	for (int i = 0; i < squaresPerSide; i++) {
		// Go through all columns from beginning to end
		for (int j = 1; j < squaresPerSide; j++) {
			int ind = i * squaresPerSide + j;
			// Check if the board is not empty at that position
			if (board[ind] != 0)
			{
				// Move element to the leftmost position available
				int indk = -1;
				int k = 0;
				for (; k < j; k++)
				{
					indk = i * squaresPerSide + k;
					if (board[indk] == 0)
					{
						// Move number to the new empty position
						board[indk] = board[ind];
						board[ind] = 0;
						valid = true;
						break;
					}
				}
				// Check if we didn't make a move to set the index as the original one
				if (k == j)
				{
					indk = ind;
				}


				// Merge
				if (indk >= 0 && board[indk] == board[indk - 1] && indk > lastMerge)
				{
					lastMerge = indk;
					board[indk - 1] += board[indk];
					board[indk] = 0;
					score += board[indk - 1];
					valid = true;
				}
			}
		}
	}

	return valid;
}// end shiftLeft

bool shiftRight(int board[], int squaresPerSide, int& score) { // Returns the validity of a right move, true/false
	bool valid = false;
	// Last merge is used so that we don't double merge the same number twice on the same play by keeping track of the index
	// that was last merged
	int lastMerge = 0;
	// Go through all rows
	for (int i = 0; i < squaresPerSide; i++) {
		lastMerge = i * squaresPerSide + squaresPerSide - 1;

		// Go through all columns from end to beginning
		for (int j = squaresPerSide - 2; j >= 0; j--) {
			int ind = i * squaresPerSide + j;
			// Check if the board is not empty at that position
			if (board[ind] != 0)
			{
				// Move element to the rightmost position available
				int indk = -1;
				int k = squaresPerSide - 1;
				for (; k > j; k--)
				{
					indk = i * squaresPerSide + k;
					if (board[indk] == 0)
					{
						// Move number to the new empty position
						board[indk] = board[ind];
						board[ind] = 0;
						valid = true;
						break;
					}
				}
				// Check if we didn't make a move to set the index as the original one
				if (k == j)
				{
					indk = ind;
				}

				// Merge by comparing the position of the number with the previous position (which in case of right is the next column)

				if (indk >= 0 && board[indk] == board[indk + 1] && indk < lastMerge)
				{
					lastMerge = indk;
					board[indk + 1] += board[indk];
					board[indk] = 0;
					score += board[indk + 1];
					valid = true;
				}
			}
		}
	}

	return valid;
} // end of shiftRight()

bool shiftUp(int board[], int squaresPerSide, int& score) { // Returns the validity of an up move, true/false
	bool valid = false;
	// Last merge is used so that we don't double merge the same number twice on the same play by keeping track of the index
	// that was last merged
	int lastMerge = 0;
	// Go through all columns
	for (int i = 0; i < squaresPerSide; i++) {

		// Go through all rows
		for (int j = 1; j < squaresPerSide; j++) {

			int ind = i + j * squaresPerSide;

			// Check if the board is not empty at that position
			if (board[ind] != 0)
			{
				// Move element to the upmost position available
				int indk = -1;
				int k = 0;
				for (; k < j; k++)
				{
					indk = i + k * squaresPerSide;
					if (board[indk] == 0)
					{
						// Move number to the new empty position
						board[indk] = board[ind];
						board[ind] = 0;
						valid = true;
						break;
					}
				}

				// Check if we didn't make a move to set the index as the original one
				if (k == j)
				{
					indk = ind;
				}

				// Merge by comparing the position of the number with the previous position (which in case of up is the previous row)
				if (indk >= squaresPerSide && board[indk] == board[indk - squaresPerSide] && lastMerge < indk)
				{
					lastMerge = indk;
					// Merge the numbers
					board[indk - squaresPerSide] += board[indk];
					board[indk] = 0;
					score += board[indk - squaresPerSide];
					valid = true;
				}
			}
		}
	}
	return valid;
}// end of shiftUp()

bool shiftDown(int board[], int squaresPerSide, int& score) { // Returns the validity of a down move, true/false
	bool valid = false;
	// Last merge is used so that we don't double merge the same number twice on the same play by keeping track of the index
	// that was last merged
	int lastMerge = 0;
	// Go through all columns
	for (int i = 0; i < squaresPerSide; i++) {
		lastMerge = squaresPerSide * squaresPerSide - i - 1;
		// Go through all rows
		for (int j = squaresPerSide - 2; j >= 0; j--) {
			int ind = i + j * squaresPerSide;
			// Check if the board is not empty at that position
			if (board[ind] != 0)
			{
				// move element to the leftmost position available
				int indk = -1;
				int k = squaresPerSide - 1;
				for (; k > j; k--)
				{
					indk = i + k * squaresPerSide;
					if (board[indk] == 0)
					{
						// Move number to the new empty position
						board[indk] = board[ind];
						board[ind] = 0;
						valid = true;
						break;
					}
				}
				// Check if we didn't make a move to set the index as the original one
				if (k == j)
				{
					indk = ind;
				}


				// Merge
				if (indk >= 0 && board[indk] == board[indk + squaresPerSide] && indk < lastMerge)
				{
					lastMerge = indk;
					board[indk + squaresPerSide] += board[indk];
					board[indk] = 0;
					score += board[indk + squaresPerSide];
					valid = true;
				}
			}
		}
	}
	return valid;
} // end of shiftDown()

bool checkBoardFull(int board[], int squaresPerSide) {
	bool full = true;
	for (int i = 0; i < squaresPerSide; i++) {
		for (int j = 0; j < squaresPerSide; j++) {
			int ind = i * squaresPerSide + j;
			// Checks to see if board position is equal to 0
			if (board[ind] == 0) {
				// Returns false meaning board is not full
				full = false;
			}
		}
	}
	// Board is full 
	if (full)
		std::cout << "\nNo more available moves.  Game is over." << std::endl;;

	return full;
}// end checkBoardFull()

bool checkWin(int board[], int squaresPerSide, int winScore) { // Going through the board
	for (int i = 0; i < squaresPerSide; i++) {
		for (int j = 0; j < squaresPerSide; j++) {
			int ind = i * squaresPerSide + j;
			//Checks to see if maxTileValue is on board
			if (board[ind] == winScore) {
				std::cout << "Congratulations!You made it to 1024 !!!" << std::endl;;
				return true;
			}
		}
	}

	return false;
} // end of checkWin()

struct Node {
	int board[MaxBoardSize * MaxBoardSize];
	int score, move;
	Node* pNext; 

};

void copyBoard(int originalBoard[], int board[], int squaresPerSide)
{
	for (int i = 0; i < squaresPerSide; i++) {
		for (int j = 0; j < squaresPerSide; j++) {
			int ind = i * squaresPerSide + j;

			board[ind] = originalBoard[ind];
		}
	}
}

void undo(Node* &pHead, int board[], int squaresPerSide, int &moveNumber, int &score) {
	Node* pTemp = pHead;

	pHead = pHead->pNext;
	delete pTemp;

	copyBoard(pHead->board, board, squaresPerSide);
	moveNumber = pHead->move;
	score = pHead->score;
}

//---------------------------------------------------------------------------------------
int main()
{
	int score = 0;
	int squaresPerSide = 4;        // User will enter this value.  Set default to 4
	int board[MaxBoardSize * MaxBoardSize];          // space for largest possible board
	int previousBoard[MaxBoardSize * MaxBoardSize];  // space for copy of board, used to see
													  //    if a move changed the board.
	int maxTileValue = MaxTileStartValue;  // 1024 for 4x4 board, 2048 for 5x5, 4096 for 6x6, etc.
	char userInput = ' ';                  // handles user input
	int move = 1;                          // user move counter

	Node* pHead = NULL;

	displayInstructions();

	std::cout << std::endl;;

	std::cout << "Game ends when you reach " << maxTileValue << "." << std::endl;;

	// Get the board size, create and initialize the board, and set the max tile value depending on board size
	// ..
	const int boardSize = 16;

	fillBoard(board, boardSize);
	placeRandomPiece(board, squaresPerSide);
	placeRandomPiece(board, squaresPerSide);

	Node* node = new Node();
	copyBoard(board, node->board, squaresPerSide);
	node->score = 0;
	node->move = 1;
	node->pNext = NULL;

	pHead = node;

	bool valid = true; // Valid move 
	// Infinite loop to run program until user selects exit, board is full, or max tile value is reached
	while (true)
	{
		// Display the text-based board
		displayAsciiBoard(board, squaresPerSide, score);

		std::cout << "\tList: ";
		Node* pTemp = pHead;
		while (pTemp) {
			std::cout << pTemp->move;
			if (pTemp->pNext) {
				std::cout << "->";
			}

			pTemp = pTemp->pNext;
		}
		std::cout << "\n\n";

		// Prompt for and handle user input
		std::cout << move << ". Your move: ";
		std::cin >> userInput;
		switch (userInput) {
		case 'x':
			std::cout << "\nThanks for playing. Exiting program... \n";
			exit(0);
			break;
			//...
		case 'r':
			std::cout << "\nResetting board" << std::endl;;
			std::cout << "\nEnter the size board you want, between 4 and 12: " << std::endl;;
			std::cin >> squaresPerSide;
			score = 0; // Reset score to 0
			move = 1;  // Reset move to 1
			valid = false; // Invalid move, piece doesn't get placed, move doesn't get incremented
			maxTileValue = pow(2, squaresPerSide + 6); // Equation to determine maxTileValue 
			fillBoard(board, squaresPerSide * squaresPerSide); // Creating the board
			placeRandomPiece(board, squaresPerSide); // Plastd::cing 2 random pieces for the new game that's resized 
			placeRandomPiece(board, squaresPerSide);

			std::cout << "Game ends when you reach " << maxTileValue << "." << std::endl;;

			break;

		case 'a':
			valid = shiftLeft(board, squaresPerSide, score); // Move left boolean
			break;
		case 'w':
			valid = shiftUp(board, squaresPerSide, score); // Move up boolean
			break;
		case 'd':
			valid = shiftRight(board, squaresPerSide, score); // Move right boolean
			break;
		case 's':
			valid = shiftDown(board, squaresPerSide, score); // Move down boolean
			break;
		case 'p':
			// Plastd::cing value at preferred index
			int index, value;
			std::cin >> index >> value;
			board[index] = value;
			valid = false; // Invalid move, piece doesn't get placed, move doesn't get incremented
			continue; // Continue with game 
		case 'u':
			if (pHead->pNext == NULL) {
				std::cout << "*** You cannot undo past the beginning of the game.  Please retry. ***";
			}
			else {
				std::cout << "\t* Undoing move *" << std::endl;
				undo(pHead, board, squaresPerSide, move, score);
			}
			continue;
		default:
			std::cout << "Invalid input, please retry.";
			continue;
		}//end switch( userInput)

		// If the move resulted in pieces changing position, then it was a valid move
		// so place a new random piece (2 or 4) in a random open square and update the move number.
		// ...
		if (valid) {
			placeRandomPiece(board, squaresPerSide);
			move++;

			// prepend node with board information
			Node* node = new Node();
			copyBoard(board, node->board, squaresPerSide);
			node->score = score;
			node->move = move;
			node->pNext = pHead;

			pHead = node;
		}

		// See if we're done.  If so, display the final board and break.
		// Checks to see if maxTileValue is on board
		if (checkWin(board, squaresPerSide, maxTileValue) ||
			// Checks to see if board is full
			checkBoardFull(board, squaresPerSide)) {

			displayAsciiBoard(board, squaresPerSide, score);
			break;
		}

		//system("clear");   // Clear the screen in UNIX / Codio.  Should be "cls" on windows.
							 //     May not work in default Mac Xcode configuration, or some other environments.
	}//end while( true)


	// destroy list
	Node* pTemp = pHead;
	while (pHead) {
		pHead = pHead->pNext;
		delete pTemp;
		pTemp = pHead;
	}

	return 0;
}//end main()