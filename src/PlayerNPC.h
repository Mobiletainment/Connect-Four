#include "Player.h"

using namespace std;

class PlayerNPC : public Player
{
public:
	PlayerNPC( CL_GraphicContext &gc, function<void(string)>playerHasWonNotification);
	virtual char PlayerIdentifier();
	int WaitForTurn();
	static unsigned int Horizon;
private:
	int EvaluateWorth(int row, int column, char player, vector<vector<char>> &field, int multiply);
	int Maximize(vector<vector<char>> &board, int turn, int &alpha, int &beta);
	int Minimize(vector<vector<char>> &board, int turn, int &alpha, int &beta);
	virtual char OtherPlayerIdentifier();
	static unsigned int totalCalls;
	int necessaryPointsForWinning;
	int totalDepth;

};

