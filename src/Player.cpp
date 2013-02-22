#include "precomp.h"
#include "Player.h"
 
using namespace std;
 
Player::Player(CL_GraphicContext &gc, function<void(string)>playerHasWonNotification): choosenColumn(0), playerHasWonNotificationCallback(playerHasWonNotification), block(true)
{
	winnerMessage = "You won! Congratulation!\n\n\nYou defeated the mighty AI";
	boardWidth = Board::GetInstance().GetWidth();
	boardHeight = Board::GetInstance().GetHeight();
}

void Player::AttachKeyboard(CL_DisplayWindow &window)
{
	slots.connect(window.get_ic().get_keyboard().sig_key_down(), this, &Player::OnKeyDown);
}

void Player::OnKeyDown(const CL_InputEvent &key, const CL_InputState &state)
{
	if (block)
		return;

	if		(key.id == CL_KEY_1)	MakeTurn(0);
	else if (key.id == CL_KEY_2)	MakeTurn(1);
	else if (key.id == CL_KEY_3)	MakeTurn(2);
	else if (key.id == CL_KEY_4)	MakeTurn(3);
	else if (key.id == CL_KEY_5)	MakeTurn(4);
	else if (key.id == CL_KEY_6)	MakeTurn(5);
	else if (key.id == CL_KEY_7)	MakeTurn(6);

}

int Player::WaitForTurn()
{
	block = false;
	return true;
}

void Player::MakeTurn(int choosenColumn)
{
	bool madeTurn = false;
	vector<vector<char>> &board = Board::GetInstance().Data;
	for(int row = Board::GetInstance().GetHeight()-1; row > -1; --row)
	{
		if(board[row][choosenColumn] == 0)
		{
			//whichPlayer
			board[row][choosenColumn] = PlayerIdentifier();
			madeTurn = true;
			MadeTurn(row, choosenColumn);
			break;
		}
	}

	if (madeTurn == false)
	{
		cout << "No turn made";
	}
}

void Player::MadeTurn(int row, int column)
{
	if(EvaluateWin(row, column, PlayerIdentifier(), Board::GetInstance().Data)) //check if new turn lead player to the lead
	{
		playerHasWonNotificationCallback(winnerMessage);
	}

	Board::GetInstance().Turn++; //increase the turn and give it to the next player
	block = true;
}

char Player::PlayerIdentifier()
{
	return 'x';
}

bool Player::EvaluateWin(int row, int column, char player, vector<vector<char>> &field)
{	
	//in every possible direction (horizontal, vertical, diagonal1, diagonal2, we only need to check 3 neighbours to determine if player has won
	
#pragma region CheckHorizontally
{

	//If we find 3 neighbours, we have a sum of 4, which is the winning condition
	//check max. 3 values to the left of the current stone
	int connected = 0;
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

	//do we already have 3 conencted neighbours? Then we don't need to check any further
	if (connected == 3)
		return true;

	//now check only necessary remaining values to the right of the current stone
	int checksRemaining = 3 - connected;
	for (int i = 1; i <= checksRemaining; i++)
	{
		//check if we don't run out of bounds first
		if (column+i > boardWidth-1)
			break; //no more stones to the right exist

		if (field[row][column+i] == player)
			++connected;
		else
			break; //no more stones to the right are connected
	}

	//now we can determine if the player got 3 connected stones horizontally (4 in total)
	if (connected == 3)
		return true;
}
#pragma endregion

#pragma region Vertically
{
	//If we find 3 neighbours, we have a sum of 4, which is the winning condition
	//check max. 3 values to the bottom of the current stone
	//Note: we don't need to check the upper direction, as the current stone is already on top
	int connected = 0;

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
		return true;
}
#pragma endregion


#pragma region CheckDiagonalBottomLeftToTopRight
{
	//If we find 3 neighbours, we have a sum of 4, which is the winning condition
	//check max. 3 values to the bottom-Left direction of the current stone
	int connected = 0;
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

	//do we already have 3 connected neighbours? Then we don't need to check any further
	if (connected == 3)
		return true;

	//now check only necessary remaining values to the top right direction of the current stone
	int checksRemaining = 3 - connected;
	for (int i = 1; i <= checksRemaining; i++)
	{
		//check if we don't run out of bounds first
		if (column+i > boardWidth-1 || row-i < 0)
			break; //no more stones in the direction exist

		if (field[row-i][column+i] == player)
			++connected;
		else
			break; //no more stones in this direction are connected
	}

	//now we can determine if the player got 3 connected stones diagonally from bottom left to top right (4 in total)
	if (connected == 3)
		return true;
}
#pragma endregion

#pragma region CheckDiagonalBottomRightToTopLeft
{
	//If we find 3 neighbours, we have a sum of 4, which is the winning condition
	//check max. 3 values to the bottom-right direction of the current stone
	int connected = 0;
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

	//do we already have 3 connected neighbours? Then we don't need to check any further
	if (connected == 3)
		return true;

	//now check only necessary remaining values to the top Left direction of the current stone
	int checksRemaining = 3 - connected;
	for (int i = 1; i <= checksRemaining; i++)
	{
		//check if we don't run out of bounds first
		if (column-i < 0 || row-i < 0)
			break; //no more stones in the direction exist

		if (field[row-i][column-i] == player)
			++connected;
		else
			break; //no more stones in this direction are connected
	}

	//now we can determine if the player got 3 connected stones diagonally from bottom left to top right (4 in total)
	if (connected == 3)
		return true;
}
#pragma endregion


	return false;
}
