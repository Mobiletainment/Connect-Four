#include "precomp.h"
#include "Game.h"
using namespace std;

CL_GraphicContext *Game::gc;
string Game::winner;

Game::Game(CL_DisplayWindow &window)
{
	gc = &window.get_gc();
	board = &Board::GetInstance();
	startMessage = new string("Press [1] to start first, or\n\n\nPress [2] to start with computer");
	whichPlayer[0] = "Player White (You)";
	whichPlayer[1] = "Player Black (Computer)";
}

Game::~Game(){
	delete player;
	delete computer;
}

void Game::Run(CL_DisplayWindow &window){
	game_display_window = window;

	*gc = window.get_gc();

	quit = false;
	CL_Slot slot_key_down = window.get_ic().get_keyboard().sig_key_down().connect(this, &Game::OnKeyDown);
	
	function<void(string)> callbackFunction;
	
	callbackFunction = &(Game::PlayerHasWonNotification);

	player = new Player(*gc, callbackFunction);
	player->AttachKeyboard(game_display_window);

	computer = new PlayerNPC(*gc,callbackFunction);
	sprintf_s(horizonMessage, "Horizon: %d", PlayerNPC::Horizon);
	//Set up font
	CL_FontDescription system_font_desc;
	system_font_desc.set_typeface_name("courier new");
	CL_Font_System system_font(*gc, system_font_desc);
	system_font.set_font_metrics(CL_FontMetrics(7.0f));
	string spacing = "  ";
	string columnIdentifiers = "Use keys:  [1]  [2]   [3]  [4]  [5]   [6]  [7]";

	system_font.draw_text(*gc, 10, 20, *startMessage);
	window.flip(0);
	while (startMessage != nullptr)
	{
		CL_KeepAlive::process();
	}
	
	
	char numberOfMinMaxCalls[32];
	numberOfMinMaxCalls[0] = '\0';
	while (!quit)
	{	
		gc->clear(CL_Colorf(20, 56, 108));
		int currentPlayer = board->Turn % 2;

		if (currentPlayer == 0)
			system_font.draw_text(*gc, 10, 20, "Current Turn: " + whichPlayer[0]);
		else
			system_font.draw_text(*gc, 10, 20, "Current Turn: " + whichPlayer[1]);
		
		
		//Draw column numbers
		system_font.draw_text(*gc, 10, 120, columnIdentifiers);
		board->Draw(*gc); 

		system_font.draw_text(*gc, 350, 50, numberOfMinMaxCalls);
		system_font.draw_text(*gc, 410, 80, horizonMessage);

		if(!winner.empty())
		{
			system_font.draw_text(*gc, 10, 60, winner);
		}
		window.flip(0);
		CL_KeepAlive::process();

		if (currentPlayer == 0)
			player->WaitForTurn();
		else
		{
			int minMaxCalls = computer->WaitForTurn();
			sprintf_s(numberOfMinMaxCalls, "#MinMaxCalls: %d", minMaxCalls);
		}
	}	
}

string Game::GetActivePlayerName(Player *playerKI)
{
	if(playerKI->PlayerIdentifier() == 'o')
	{
		return "Black Player";
	}
	else
		return "White Player";
}

void Game::PlayerHasWonNotification(string whosTheWinner)
{
	if (winner.empty()) //only assign winner the first time a winner is determined
		winner = whosTheWinner;
}

void Game::OnKeyDown(const CL_InputEvent &key, const CL_InputState &state)
{
	if (key.id == CL_KEY_ESCAPE) quit = true;
	else if (startMessage != nullptr && key.id == CL_KEY_1)
	{
		board->Turn = 0; //player 1 makes all even turns, computer all odd

		delete startMessage;
		startMessage = nullptr;
	}
	else if (startMessage != nullptr && key.id == CL_KEY_2)
	{
		board->Turn = 1; //cheap trick to start with computer instead of player
		delete startMessage;
		startMessage = nullptr;
	}
	else if (key.id == CL_KEY_UP)
	{
		if (PlayerNPC::Horizon < 42)
		{
			PlayerNPC::Horizon += 1;
			sprintf_s(horizonMessage, "Horizon: %d", PlayerNPC::Horizon);
		}
	}
	else if (key.id == CL_KEY_DOWN)
	{
		if (PlayerNPC::Horizon > 0)
		{
			PlayerNPC::Horizon -= 1;
			sprintf_s(horizonMessage, "Horizon: %d", PlayerNPC::Horizon);
		}
	}
}