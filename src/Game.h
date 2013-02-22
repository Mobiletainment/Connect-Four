#include "precomp.h"
#include "Board.h"
#include <functional>
#include "PlayerNPC.h"

class Game
{ 
private:
	void OnKeyDown(const CL_InputEvent &key, const CL_InputState &state);
	Board *board;
	int view_x, view_y;
	bool quit;
	CL_DisplayWindow game_display_window;
	void static PlayerHasWonNotification(string winner);
	static string winner;
	char horizonMessage[12];
	string *startMessage;
public:
	static CL_GraphicContext *gc;
	Game( CL_DisplayWindow &window);
	~Game();
	Player *player;
	PlayerNPC *computer;
	string whichPlayer[2];
	void Run(CL_DisplayWindow &window);

	string GetActivePlayerName(Player *player);

	void OnQuit() { quit = true; }
};
