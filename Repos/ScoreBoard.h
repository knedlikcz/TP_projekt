#ifndef _SCOREBOARD_H
#define _SCOREBOARD_H
#include "Texture.h"
#include <vector>

using namespace QuickSDL;

class ScoreBoard : public GameEntity {

private:
	
	std::vector<Texture*> mScore;

	SDL_Color mColor;

public:
	ScoreBoard();
	ScoreBoard(SDL_Color color);
	~ScoreBoard();

	void Score(int score);
	int GetScore();
	
	void Render();

private:
	void ClearBoard();
};

#endif // !_SCOREBOARD_H
