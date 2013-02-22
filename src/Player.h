#include "Board.h"
#include <functional>

class Player
{ 

public:
	Player( CL_GraphicContext &gc, function<void(string)>playerHasWonNotification);
	void AttachKeyboard(CL_DisplayWindow &window); 
	virtual char PlayerIdentifier();
	virtual int WaitForTurn();
	

protected:
	bool block;
	void NotifyPlayerHasWon();
	void OnKeyDown(const CL_InputEvent &key, const CL_InputState &state);
	CL_SlotContainer slots;
	int choosenColumn;
	void MakeTurn(int choosenColumn);
	void MadeTurn(int row, int column);
	bool EvaluateWin(int row, int column, char player, vector<vector<char>> &field);
	string winnerMessage;
	function<void(string)>playerHasWonNotificationCallback;
	int boardWidth;
	int boardHeight;
};
