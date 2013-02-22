#include "precomp.h"
#include "PlayerNPC.h"
#include <limits>

using namespace std;

unsigned int PlayerNPC::Horizon;
unsigned int PlayerNPC::totalCalls;

PlayerNPC::PlayerNPC(CL_GraphicContext &gc, function<void(string)>playerHasWonNotification) : Player(gc, playerHasWonNotification)
{
	Horizon = 42; //horizont = 42 = maximum number of turns
	totalDepth = 0;
	winnerMessage = "You lost!\n\n\nYou got tearfully defeated\n\n\nby the mighty artificial intelligence";
	necessaryPointsForWinning = 20;
}

char PlayerNPC::PlayerIdentifier()
{
	return 'o';
}

char PlayerNPC::OtherPlayerIdentifier()
{
	return 'x';
}

int PlayerNPC::WaitForTurn()
{
	vector<vector<char>> tempBoard = Board::GetInstance().Data;
	
	totalCalls = 0;
	int alpha = INT_MIN; //highest achievable
	int beta = INT_MAX;
	int column = Maximize(tempBoard, 0, alpha, beta); //0 is the number of turns (first turn)
	MakeTurn(column);
	//++Board::GetInstance().Turn; //increase the turn and give it to the next player
	return totalCalls;
}

//alpha is the highest realistically achievable win.
//anything equal or below alpha is useless, as we wouldn't get a higher achievable win from it.
//alpha is therefore the lower border

//beta is the highest loss
//
int PlayerNPC::Maximize(vector<vector<char>> &board, int turn, int &alpha, int &beta)
{
	if (turn > Horizon) //we go not further than the horizon. No winner here
	{
		return 0;
	}

	if (turn > totalDepth)
		totalDepth = turn;
	
	vector<int> values(boardWidth);

	for (int column = 0; column < boardWidth; column++)
	{
		if (board[0][column] != 0) //top column is full!
		{
			values[column] = INT_MIN; //assign a value that is lower than everything else, so it won't be chosen
			continue;
		}
		
		for(int row = boardHeight - 1; row >= 0; --row)
		{
			if(board[row][column] == 0)
			{
				++totalCalls;
				//evaluate worth doesn't change the field at the according row/coumn, instead just checks its surroundings
				int worth = EvaluateWorth(row, column, PlayerIdentifier(), board, Horizon-turn); //calculate how much the node is worth
				if (worth >= necessaryPointsForWinning && turn > 0) //we have a winning, so this is a node (end state for the current tree)
				{
					//values[column] = EvaluateWorth(row, column, PlayerIdentifier()); //calculate how much the node is worth
					return worth;
				}
				else
				{
					//we're not going to copy the board for further move, instead we do and afterwards undo it
					board[row][column] = PlayerIdentifier();
					int value = Minimize(board, turn+1, alpha, beta); //go to next level and minimize the value
					board[row][column] = 0; //undo move

					if (value > worth)
						values[column] = value;
					else
						values[column] = worth; //heuristical value

					if (values[column] > alpha) //new highest value
						alpha = values[column]; //alpha = highest value
				}

				break;
			}

			//the upper level is maximizing, we are minimizing -> as soon as our calculated value is beneath the
			//parents lowest highest value, it won't choose this possibility anyway and therefore we can cut off
			//further calculation and just return this value as minimum (it could be even lesser than this minumum,
			//but it doesn't matter as its below the parents value in any case
			if (values[column] >= beta)
			{
				if (turn > 0) //don't cut below base node, because we want all the information to detect the best move
					return values[column]; //cut off here
			}
		}
		
	}

	if (turn > 0)
		return alpha; //return highest value
	else
	{
		int highestValue = values[0];
		int column = 0;
		for (unsigned int i = 1; i < values.size(); i++)
		{
			if (values[i] > highestValue)
			{
				highestValue = values[i];
				column = i;
			}
		}

		return column;
	}

	
}

int PlayerNPC::Minimize(vector<vector<char>> &board, int turn, int &alpha, int &beta)
{
	if (turn > Horizon) //we go not further than the horizon. No winner here
	{
		return 0;
	}

	if (turn > totalDepth)
		totalDepth = turn;

	for (int column = 0; column < boardWidth; column++)
	{
		if (board[0][column] != 0) //top column is full!
		{
			continue;
		}

		for(int row = boardHeight - 1; row >= 0; --row)
		{
			if(board[row][column] == 0)
			{
				++totalCalls;
				int worth = EvaluateWorth(row, column, OtherPlayerIdentifier(), board, Horizon-turn);
				if (worth >= necessaryPointsForWinning) //we have a winning condition
				{
					//values[column] =  -EvaluateWorth(row, column, OtherPlayerIdentifier()); //it's a leave node and it has the value -1, because the other Player wins with this constellation!
					return -worth; //it's a leave node and it has the value -1, because the other Player wins with this constellation!
				}
				else
				{
					//we're not going to copy the board for further move, instead we do and afterwards undo it
					board[row][column] = OtherPlayerIdentifier();
					int value = Maximize(board, turn+1, alpha, beta); //go to next level and minimize the value
					board[row][column] = 0; //undo move

					if (value < beta)
						beta = value;
					else if (worth < beta)
						beta = worth;
				}
				break;
			}
		}

		//the upper level is maximizing, we are minimizing -> as soon as our calculated beta (minimum) is beneath the
		//parents lowest highest value, it won't choose this possibility anyway and therefore we can cut off
		//further calculation and just return this value as minimum (it could be even lesser than this minumum,
		//but it doesn't matter as its below the parents value in any case
		if (beta <= alpha)
			return beta; //cut off here
	}

	return beta; //return lowest value
}

int PlayerNPC::EvaluateWorth(int row, int column, char player, vector<vector<char>> &field, int multiply)
{	
	int connected = 0;
	int totalPoints = 0;

	//in every possible direction (horizontal, vertical, diagonal1, diagonal2, we only need to check 3 neighbours to determine if player has won

#pragma region CheckHorizontally
	{

		//If we find 3 neighbours, we have a sum of 4, which is the winning condition
		//check max. 3 values to the left of the current stone

		for (int i = -1; i >= -3; i--)
		{
			//check if we don't run out of bounds first
			if (column+i < 0)
				break; //continue with checking to the right side of the stone instead

			if (field[row][column+i] == player)
				++connected;
			else
				break; //continue checking to the right
		}


		//now check only necessary remaining values to the right of the current stone
		for (int i = 1; i <= 3; i++)
		{
			//check if we don't run out of bounds first
			if (column+i > boardWidth-1)
				break; //no more stones to the right exist

			if (field[row][column+i] == player)
				++connected;
			else
				break; //no more stones to the right are connected
		}
		if (connected == 3)
			totalPoints += necessaryPointsForWinning;
		else
			totalPoints += connected;
	}
#pragma endregion

#pragma region Vertically
	{
		//If we find 3 neighbours, we have a sum of 4, which is the winning condition
		//check max. 3 values to the bottom of the current stone
		//Note: we don't need to check the upper direction, as the current stone is already on top
		connected = 0;
		for (int i = 1; i <= 3; i++)
		{
			//check if we don't run out of bounds first
			if (row+i > boardHeight-1)
				break; //no more stones to the right exist

			if (field[row+i][column] == player)
				++connected;
			else
				break; //no more stones in bottom direction are connected
		}

		//now we can determine if the player got 3 connected stones horizontally (4 in total)
		if (connected == 3)
			totalPoints += necessaryPointsForWinning;
		else
			totalPoints += connected;
	}
#pragma endregion


#pragma region CheckDiagonalBottomLeftToTopRight
	{
		//If we find 3 neighbours, we have a sum of 4, which is the winning condition
		//check max. 3 values to the bottom-Left direction of the current stone

		connected = 0;

		for (int i = -1; i >= -3; i--)
		{
			//check if we don't run out of bounds first
			if (column+i < 0 || row-i > boardHeight-1)
				break; //continue with checking to the top right direction of the stone instead

			if (field[row-i][column+i] == player)
				++connected;
			else
				break; //continue checking to the bottom left side of the stone instead
		}


		//now check only necessary remaining values to the top right direction of the current stone
		for (int i = 1; i <= 3; i++)
		{
			//check if we don't run out of bounds first
			if (column+i > boardWidth-1 || row-i < 0)
				break; //no more stones in the direction exist

			if (field[row-i][column+i] == player)
				++connected;
			else
				break; //no more stones in this direction are connected
		}

		if (connected == 3)
			totalPoints += necessaryPointsForWinning;
		else
			totalPoints += connected;
	}
#pragma endregion

#pragma region CheckDiagonalBottomRightToTopLeft
	{
		//If we find 3 neighbours, we have a sum of 4, which is the winning condition
		//check max. 3 values to the bottom-right direction of the current stone
		connected = 0;
		for (int i = -1; i >= -3; i--)
		{
			//check if we don't run out of bounds first
			if (column-i > boardWidth-1 || row-i > boardHeight-1)
				break; //continue with checking to the top left direction of the stone instead

			if (field[row-i][column-i] == player)
				++connected;
			else
				break; //continue checking to the top left side of the stone instead
		}

		//now check only necessary remaining values to the top Left direction of the current stone
		for (int i = 1; i <= 3; i++)
		{
			//check if we don't run out of bounds first
			if (column-i < 0 || row-i < 0)
				break; //no more stones in the direction exist

			if (field[row-i][column-i] == player)
				++connected;
			else
				break; //no more stones in this direction are connected
		}

		if (connected == 3)
			totalPoints += necessaryPointsForWinning;
		else
			totalPoints += connected;
	}

	if (totalPoints >= necessaryPointsForWinning)
		totalPoints *= multiply; //kick boost for early winning

#pragma endregion

	//give stones in the middle a bonus of 2 points if their in the first row
	if (row == boardHeight-1)
	{
		if (column == 3)
			totalPoints +=2;
		if (column == 2 || column == 4)
			totalPoints +=1;
	}
	return totalPoints;
}