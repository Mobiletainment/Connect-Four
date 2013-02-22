
#ifndef header_map
#define header_map

using namespace std;

class Board
{
public:
	static Board &GetInstance(); //Singleton
	int GetWidth() { return width; }
	int GetHeight() { return height; }	 
	int GetTileWidth() { return 64; } 
	int GetTileHeight() { return 64; }
	int Turn;

	vector<vector<char>> Data; //the actual field
	void Draw(CL_GraphicContext &gc);
	~Board();

private:
	Board( CL_GraphicContext &gc); //private constructor for singleton
	static Board *instance;
	vector<vector<CL_Sprite>> tileImages;
	CL_Sprite directionArrow;
	CL_Sprite directionArrowTop;
	CL_SpriteDescription tileSpritedesc;
	int width, height;
};

#endif