#ifndef _PLAYSCREEN_H
#define _PLAYSCREEN_H
#include "Level.h"

#include <chrono>
#include <thread>

class PlayScreen : public GameEntity {
private:
	Timer* mTimer;
	InputManager* mInput;

	BackgroundStars* mStars;
	
	PlaySideBar* mSideBar;

	Texture* mStartLabel;

	float mLevelStartTimer;
	float mLevelStartDelay;
	
	bool mGameStarted;
	
	Level* mLevel;
	bool mLevelStarted;
	int mCurrentStage;

	Player* mPlayer;

	XMLDocument Scores;
	int HScore;

private:
	
	void StartNextLevel();
	void HandleHighScore();

public:
	PlayScreen();
	~PlayScreen();

	void StartNewGame();
	
	bool GameOver();

	void Update();
	void Render();
};


#endif // !_PLAYSCREEN_H
