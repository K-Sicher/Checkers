// Checkers.c Made By:
// 	Kevin Sicher
// 	C290 - Tools for Computing
//
//	How to play:
//	- Run in Terminal
//	- Enter a Y-coordinate first, then X-coordinate. Then repeat for the targeted location of the move.
//
// Currently the AI code is not functioning correctly but it is here in this file commented out.



#include <stdio.h>
#include <stdlib.h>

// Board 
void print_board(int board[9] [8])
{
	int x,y;
	char z = 1;
	for (x = 1; x < 9; x++)
	{
		printf("%d", z);
		z++;
		for (y = 1; y < 9; y++)
		{
			printf("|");
			switch(board[x][y])
			{
				case 0:
					printf(" ");
					break;
				case 1:
					printf("x");
					break;
				case 2:
					printf("o");
					break;
				case 3:
					printf("X");
					break;
				case 4:
					printf("O");
					break;
			}
		}
		printf("\n");
	}
	printf("  1 2 3 4 5 6 7 8 9\n");
}

// Even numbers are O's | Odd Numbers are X's
void set_defaults(int board[9][8])
{
	board[1][2] = 1; board[1][4] = 1; board[1][6] = 1; board[1][8] = 1;
	board[2][1] = 1; board[2][3] = 1; board[2][5] = 1; board[2][7] = 1;
	board[3][2] = 1; board[3][4] = 1; board[3][6] = 1; board[3][8] = 1;
	board[6][1] = 2; board[6][3] = 2; board[6][5] = 2; board[6][7] = 2;
	board[7][2] = 2; board[7][4] = 2; board[7][6] = 2; board[7][8] = 2;
	board[8][1] = 2; board[8][3] = 2; board[8][5] = 2; board[8][7] = 2;
}

// Odd's are assigned to 0, Even's are assigned to 1.
int Opponent(int you)
{
	if (you == 1 || you == 3)
		return 2;
	if (you == 2 || you == 4)
		return 1;
}

// A King is assigned to numbers 3 and 4
void Is_King(int x, int y, int board[9][8], int turn)
{
	if (turn == 1)
		if (x == 8)
			board[x][y] == 3;
	if (turn == 2)
		if (x == 1)
			board[x][y] == 4;
}

// Can this move happen
int NextChainValid(int board[9][8], int x[4])
{
	if (board[x[3] + 1][x[4] + 1] == Opponent (board[x[3]][x[4]]) || board [x[3] + 1][x[4] + 1] == Opponent (board[x[3]][x[4]] + 2))
		return 1;
	else if (board[x[3] + 1][x[4] - 1] == Opponent (board[x[3]][x[4]]) || board[x[3] + 1][x[4] - 1] == Opponent (board[x[3]][x[4]] + 2))
		return 1;
	else if (board[x[3] - 1][x[4] + 1] == Opponent (board[x[3]][x[4]]) || board[x[3] - 1][x[4] + 1] == Opponent (board[x[3]][x[4]] + 2))
		return 1;
	else if (board[x[3] - 1][x[4] - 1] == Opponent (board[x[3]][x[4]]) || board[x[3] - 1][x[4] - 1] == Opponent (board[x[3]][x[4]] + 2))
		return 1;
	else
		return 0;
}

// Checkers Output function for creating a new state
void get_co(int board[9][8], int turn, int pawn[2])
{
	int x[4];
	getxyaz:
	if(turn == 1)
		printf("x's turn.\n");
	else
		printf("o's turn.\n");
	printf("Write XYAZ: \n");
	scanf("%d %d %d %d", &x[1], &x[2], &x[3], &x[4]);
	if (board[x[1]][x[2]] == turn || board[x[1]][x[2]] == turn + 2)
	{
		if (turn == 1)
		{
			if (x[3] == x[1] + 1 && x[4] == x[2] + 1 || x[4] == x[2] - 1)
			{
				board[x[1]][x[2]] = 0;
				board[x[3]][x[4]] = turn;
				int x2, y2;
				if (x[1] > x[3])
					x2 = x[1] - 1;
				else
					x2 = x[3] - 1;
				if (x[2] > x[4])
					y2 = x[2] - 1;
				else
					y2 = x[4] - 1;
				board[x2][y2] = 0;
				pawn[turn + 1]--;
				Is_King (x[3],x[4], board, turn);
				if (NextChainValid (board, x))
					get_co (board, turn, pawn);
			}
		else
		{
			printf("Invalid move.\n");
			goto getxyaz;
		}
		}
		else if (turn == 2)
		{
		if (x[3] == x[1] - 1 && x[4] == x[2] + 1 || x[4] == x[2] - 1)
		{
			board[x[1]][x[2]] = 0;
			board[x[3]][x[4]] = turn;
			Is_King (x[3], x[4], board, turn);
		}
		else if (x[3] == x[1] - 2 && x[4] == x[2] + 2 || x[4] == x[2] - 2)
		{
			board[x[1]][x[2]] = 0;
			board[x[3]][x[4]] = turn;
			int x2, y2;
			if (x[1] > x[3])
				x2 = x[1] - 1;
			else
				x2 = x[3] - 1;
			if (x[2] > x[4])
				y2 = x[2] - 1;
			else
				y2 = x[4] - 1;
			board[x2][y2] = 0;
			pawn[turn - 1]--;
			Is_King (x[3], x[4], board, turn);
			if (NextChainValid (board, x))
				get_co (board, turn, pawn);
		}
		else
		{
			printf("Invalid move.\n");
			goto getxyaz;
		}
		}
		else if (turn == 3)
		{
		if (x[3] == x[1] - 1 || x[3] == x[1] + 1 && x[4] == x[2] + 1 || x[4] == x[2] - 1)
		{
			board[x[1]][x[4]] = turn;
			Is_King (x[3], x[4], board, turn);
		}
		else if (x[3] == x[1] + 2 || x[3] == x[1] - 2 && x[4] == x[2] + 2|| x[4] == x[2] - 2)
		{
			board[x[1]][x[2]] = 0;
			board[x[3]][x[4]] = turn;
			int x2, y2;
			if (x[1] > x[3])
				x2 = x[1] - 1;
			else
				x2 = x[3] - 1;
			if (x[2] > x[4])
				y2 = x[2] - 1;
			else
				y2 = x[4] - 1;
			board[x2][y2] = 0;
			pawn [turn - 1]--;
			Is_King (x[3], x[4], board, turn);
			if (NextChainValid (board, x))
				get_co (board, turn, pawn);
		}
		else
		{
			printf("Invalid move.\n");
			goto getxyaz;
		}
		}
		else if (turn == 4)
		{
			if (x[3] == x[1] - 1 && x[4] == x[2] + 1 || x[4] == x[2] - 1)
			{
				board[x[1]][x[2]] = 0;
				board[x[3]][x[4]] = turn;
				Is_King (x[3], x[4], board, turn);
			}
			else if (x[3] == x[1] + 2 && x[4] == x[2] + 2 || x[4] == x[2] - 2)
			{
				board[x[1]][x[2]] = 0;
				board[x[3]][x[4]] = turn;
				int x2, y2;
				if (x[1] > x[3])
					x2 = x[1] - 1;
				else
					x2 = x[3] - 1;
				if (x[2] > x[4])
					y2 = x[2] - 1;
				else
					y2 = x[4] - 1;
				board[x2][y2] = 0;
				pawn[turn - 3]--;
				Is_King (x[3], x[4], board, turn);
				if (NextChainValid(board, x))
					get_co (board, turn, pawn);
			}
			else
			{
				printf("Invalid move.\n");
				goto getxyaz;
			}
			}
	}
}

// When there are no pawns, a winner is available.
int Winner(int x, int o)
{
	if (x == 0)
	{
		printf("O Wins.\n\n");
		return 1;
	}
	else if (o == 0)
	{
		printf("X wins.\n\n");
		return 1;
	}
	else
		return 0;
}

// Set the Board, Pawns, and determine if a winner is available.
int main()
{
	int board[9][8] = {0}, turn = 2, pawn[2] = {12};
	set_defaults(board);
	while (Winner(pawn[1], pawn[2]))
	{
		print_board(board);
		get_co(board, turn, pawn);
		if (turn == 2)
			turn = 1;
		else
			turn = 2;
	}
	scanf("asd");
}

// AI Algorithm
//
// int alphaBeta (int alpha, int beta, int depthleft) {
//   if (depthleft == 0) return quiesce (alpha, beta);
//   for (NextChainValid) {
//   score = -alphaBeta (-beta, -alpha, depthleft - 1);
//   if (score >= beta)
//     return beta; // this is the cutoff for a fail
//   if (score > alpha)
//     alpha = score; // Alpha can be max like in MiniMax
//   }
//   return alpha;
// }
//  Quiescence search makes the alpha beta more reliable
//  This still does not choose the best move for the game, but rather 
//  the score potential
//

