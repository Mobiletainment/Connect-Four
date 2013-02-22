#include "precomp.h"
#include "Board.h"
#include "Game.h"

using namespace std;

Board *Board::instance = 0;

//Map Initialization
Board::Board(CL_GraphicContext &gc) : width(7), height(6), Turn(0)
{	 
	Data = vector<vector<char>>(height,vector<char>(width));
	tileImages.resize(height, vector<CL_Sprite>(width));

	tileSpritedesc.add_frame(CL_ImageProviderFactory::load("resources/Empty2.png"));
	tileSpritedesc.add_frame(CL_ImageProviderFactory::load("resources/White.png")); //Player1
	tileSpritedesc.add_frame(CL_ImageProviderFactory::load("resources/Black.png")); //Player2

	directionArrow = CL_Sprite(gc, "resources/ThrowDirection.png");
	directionArrowTop = CL_Sprite(gc, "resources/ThrowDirectionWithoutShadow.png");

	for(int row = 0; row < height; ++row)
	{
		for(int column = 0; column < width; ++column)
		{
			Data[row][column] = 0;
			//Initialize Tile Images
			tileImages[row][column] = CL_Sprite(gc, tileSpritedesc);
		}
	}

}

Board &Board::GetInstance() //Singleton
{
	if (!instance)
		instance =  new Board(*Game::gc);
	return *instance;
}

Board::~Board()
{
}

void Board::Draw(CL_GraphicContext &gc)
{
	static int tileOffsetX = 128;
	static int tileOffsetY = 128;
	int tilePosX = tileOffsetX;
	int tilePosY = tileOffsetY;	
;

	int column = 0;
	for(int x = 0; x < height; ++x)
	{	 
		for(int y = 0; y < width; ++y)
		{
			//0 -> Leer, 1 -> Gelb, 2 -> rot
			if(Data[x][y] == 0)
				tileImages[x][y].set_frame(0);				
			else if(Data[x][y] == 'x')
				tileImages[x][y].set_frame(1);				
			else if(Data[x][y] == 'o')
				tileImages[x][y].set_frame(2);				


			tileImages[x][y].draw(gc, tilePosX, tilePosY);
			column++;

			if(column == width)
			{
				tilePosY += Board::GetTileHeight();
				tilePosX = tileOffsetX;
				column = 0;
			}
			else
			{
				tilePosX += Board::GetTileWidth();
			}
		}
	}
	directionArrowTop.draw(gc, 0, tileOffsetY);
	directionArrow.draw(gc, 0, tilePosY - 2* Board::GetTileHeight());
}